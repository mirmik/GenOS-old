


#include "CRIUS.h"

int16_t  i2c_errors_count = 0;
uint32_t neutralizeTime = 0;


#define I2C_PULLUPS_ENABLE         PORTD |= 1<<0; PORTD |= 1<<1;       // PIN 20&21 (SDA&SCL)
#define I2C_PULLUPS_DISABLE        PORTD &= ~(1<<0); PORTD &= ~(1<<1);
// ************************************************************************************************************
// I2C general functions
// ************************************************************************************************************
//////////////////////// 
//MPU_READ
uint8_t CRIUS_cls::MPU6050_read_reg(uint8_t addres)
{
static uint8_t buf;
i2c_read_reg_to_buf(MPU6050_ADDRESS, addres, &buf, 1);
return(buf);
}
//////////////////////////////////////////////////////

void CRIUS_cls::i2c_init(void) {
  #if defined(INTERNAL_I2C_PULLUPS)
    I2C_PULLUPS_ENABLE
  #else
    I2C_PULLUPS_DISABLE
  #endif
  TWSR = 0;                                    // no prescaler => prescaler = 1
  TWBR = ((F_CPU / I2C_SPEED) - 16) / 2;       // change the I2C clock rate
  TWCR = 1<<TWEN;                              // enable twi module, no interrupt
}

void CRIUS_cls::i2c_rep_start(uint8_t address) {
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) ; // send REPEAT START condition
  waitTransmissionI2C();                       // wait until transmission completed
  TWDR = address;                              // send device address
  TWCR = (1<<TWINT) | (1<<TWEN);
  waitTransmissionI2C();                       // wail until transmission completed
}

void CRIUS_cls::i2c_stop(void) {
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
  //  while(TWCR & (1<<TWSTO));                // <- can produce a blocking state with some WMP clones
}

void CRIUS_cls::i2c_write(uint8_t data ) {
  TWDR = data;                                 // send data to the previously addressed device
  TWCR = (1<<TWINT) | (1<<TWEN);
  waitTransmissionI2C();
}

uint8_t CRIUS_cls::i2c_read(uint8_t ack) {
  TWCR = (1<<TWINT) | (1<<TWEN) | (ack? (1<<TWEA) : 0);
  waitTransmissionI2C();
  uint8_t r = TWDR;
  if (!ack) i2c_stop();
  return r;
}

uint8_t CRIUS_cls::i2c_readAck() {
  return i2c_read(1);
}

uint8_t CRIUS_cls::i2c_readNak(void) {
  return i2c_read(0);
}

void CRIUS_cls::waitTransmissionI2C() {
  uint16_t count = 255;
  while (!(TWCR & (1<<TWINT))) {
    count--;
    if (count==0) {              //we are in a blocking state => we don't insist
      TWCR = 0;                  //and we force a reset on TWINT register
      neutralizeTime = micros(); //we take a timestamp here to neutralize the value during a short delay
      i2c_errors_count++;
      break;
    }
  }
}

size_t CRIUS_cls::i2c_read_to_buf(uint8_t add, void *buf, size_t size) {
  i2c_rep_start((add<<1) | 1);  // I2C read direction
  size_t bytes_read = 0;
  uint8_t *b = (uint8_t*)buf;
  while (size--) {
    /* acknowledge all but the final byte */
    *b++ = i2c_read(size > 0);
    /* TODO catch I2C errors here and abort */
    bytes_read++;
  }
  return bytes_read;
}

size_t CRIUS_cls::i2c_read_reg_to_buf(uint8_t add, uint8_t reg, void *buf, size_t size) {
  i2c_rep_start(add<<1); // I2C write direction
  i2c_write(reg);        // register selection
  return i2c_read_to_buf(add, buf, size);
}


void CRIUS_cls::i2c_writeReg(uint8_t add, uint8_t reg, uint8_t val) {
  i2c_rep_start(add<<1); // I2C write direction
  i2c_write(reg);        // register selection
  i2c_write(val);        // value to write in register
  i2c_stop();
}

uint8_t CRIUS_cls::i2c_readReg(uint8_t add, uint8_t reg) {
  uint8_t val;
  i2c_read_reg_to_buf(add, reg, &val, 1);
  return val;
}














//***************************************************
  #define MS561101BA_ADDRESS 0x77 //CBR=0 0xEE I2C address when pin CSB is connected to LOW (GND)
  //#define MS561101BA_ADDRESS 0x76 //CBR=1 0xEC I2C address when pin CSB is connected to HIGH (VCC)

// ************************************************************************************************************
// I2C Barometer MS561101BA
// ************************************************************************************************************
//
// specs are here: http://www.meas-spec.com/downloads/MS5611-01BA03.pdf
// useful info on pages 7 -> 12

// registers of the device
#define MS561101BA_PRESSURE    0x40
#define MS561101BA_TEMPERATURE 0x50
#define MS561101BA_RESET       0x1E

// OSR (Over Sampling Ratio) constants
#define MS561101BA_OSR_256  0x00
#define MS561101BA_OSR_512  0x02
#define MS561101BA_OSR_1024 0x04
#define MS561101BA_OSR_2048 0x06
#define MS561101BA_OSR_4096 0x08

#define OSR MS561101BA_OSR_4096

static struct {
  // sensor registers from the MS561101BA datasheet
  uint16_t c[7];
  union {uint32_t val; uint8_t raw[4]; } ut; //uncompensated T
  union {uint32_t val; uint8_t raw[4]; } up; //uncompensated P
  uint8_t  state;
  uint32_t deadline;
} ms561101ba_ctx;

#define CONVERSIONTIME 8600

void  CRIUS_cls::Baro_init() {
  CRIUS.i2c_MS561101BA_reset();
  //delay(100);
  CRIUS.i2c_MS561101BA_readCalibration();
 // delay(10);
  CRIUS.i2c_MS561101BA_UT_Start(); 
  ms561101ba_ctx.deadline = micros()+CONVERSIONTIME; 
}


extern  int32_t baroTemperature,baroPressure,baroPressureSum;


//return 0: no data available, no computation ;  1: new value available  ; 2: no new value, but computation time
uint8_t CRIUS_cls::Baro_update() {                            // first UT conversion is started in init procedure
  if (micros() < ms561101ba_ctx.deadline) return 0; 
  ms561101ba_ctx.deadline = micros()+CONVERSIONTIME;  // UT and UP conversion take 8.5ms so we do next reading after *10ms* 
  //TWBR = ((F_CPU / 400000L) - 16) / 2;          // change the I2C clock rate to 400kHz, MS5611 is ok with this speed
  if (ms561101ba_ctx.state == 0) {
    CRIUS.i2c_MS561101BA_UT_Read(); 
    CRIUS.i2c_MS561101BA_UP_Start();              // moved here for less timecycle spike
    ms561101ba_ctx.state = 1;
    return 1;
  } else {
    CRIUS.i2c_MS561101BA_UP_Read();
    CRIUS.i2c_MS561101BA_UT_Start(); 
    ms561101ba_ctx.state = 0; 
    return 2;
  }
}





void CRIUS_cls::i2c_MS561101BA_reset(){
   i2c_writeReg(MS561101BA_ADDRESS, MS561101BA_RESET, 0);
}

void CRIUS_cls::i2c_MS561101BA_readCalibration(){
  union {uint16_t val; uint8_t raw[2]; } data;
  for(uint8_t i=0;i<6;i++) {
    i2c_rep_start(MS561101BA_ADDRESS<<1);
    i2c_write(0xA2+2*i);
    delay(10);
    i2c_rep_start((MS561101BA_ADDRESS<<1) | 1);//I2C read direction => 1
    delay(10);
    data.raw[1] = i2c_readAck();  // read a 16 bit register
    data.raw[0] = i2c_readNak();
    ms561101ba_ctx.c[i+1] = data.val;
  }
}

// read uncompensated temperature value: send command first
void CRIUS_cls::i2c_MS561101BA_UT_Start() {
  i2c_rep_start(MS561101BA_ADDRESS<<1);      // I2C write direction
  i2c_write(MS561101BA_TEMPERATURE + OSR);  // register selection
  i2c_stop();
}

void CRIUS_cls::i2c_MS561101BA_UP_Start () {
  i2c_rep_start(MS561101BA_ADDRESS<<1);      // I2C write direction
  i2c_write(MS561101BA_PRESSURE + OSR);     // register selection
  i2c_stop();
}


// read uncompensated temperature value: read result bytes
void CRIUS_cls::i2c_MS561101BA_UT_Read() {
  i2c_rep_start(MS561101BA_ADDRESS<<1);
  i2c_write(0);
  i2c_rep_start((MS561101BA_ADDRESS<<1) | 1);
  ms561101ba_ctx.ut.raw[2] = i2c_readAck();
  ms561101ba_ctx.ut.raw[1] = i2c_readAck();
  ms561101ba_ctx.ut.raw[0] = i2c_readNak();
}

// read uncompensated pressure value: read result bytes
void CRIUS_cls::i2c_MS561101BA_UP_Read () {
  i2c_rep_start(MS561101BA_ADDRESS<<1);
  i2c_write(0);
  i2c_rep_start((MS561101BA_ADDRESS<<1) | 1);
  ms561101ba_ctx.up.raw[2] = i2c_readAck();
  ms561101ba_ctx.up.raw[1] = i2c_readAck();
  ms561101ba_ctx.up.raw[0] = i2c_readNak();
}




void CRIUS_cls::i2c_MS561101BA_Calculate() {
  int32_t off2,sens2,delt;
// Typical mathematic :( . To undestand that, you need to read datasheet (page 7/20).
  int64_t dT       = (int32_t)ms561101ba_ctx.ut.val - ((int32_t)ms561101ba_ctx.c[5] << 8);
  baroTemperature  = 2000 + ((dT * ms561101ba_ctx.c[6])>>23);
  int64_t off      = ((uint32_t)ms561101ba_ctx.c[2] <<16) + ((dT * ms561101ba_ctx.c[4]) >> 7);
  int64_t sens     = ((uint32_t)ms561101ba_ctx.c[1] <<15) + ((dT * ms561101ba_ctx.c[3]) >> 8);

  if (baroTemperature < 2000) { // temperature lower than 20st.C 
    delt = baroTemperature-2000;
    delt  = 5*delt*delt;
    off2  = delt>>1;
    sens2 = delt>>2;
    if (baroTemperature < -1500) { // temperature lower than -15st.C
      delt  = baroTemperature+1500;
      delt  = delt*delt;
      off2  += 7 * delt;
      sens2 += (11 * delt)>>1;
    }
    off  -= off2; 
    sens -= sens2;
  }

  baroPressure     = (( (ms561101ba_ctx.up.val * sens ) >> 21) - off) >> 15;
}