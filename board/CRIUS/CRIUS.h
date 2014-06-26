
#include "Arduino.h"
//#include "utility/CRIUS_Transformation.h"

#ifndef CRIUS_H
#define  CRIUS_H

//#include "IMU.h"

#define LED_RED 13
#define LED_GREEN 30
#define LED_YELLOW 31
void ledround(char*c);
void ledon(int argc, const char* const* argv);
void ledoff(char*c);
/*
enum rc {
  ROLL,
  PITCH,
  YAW,
};



#define MPU6050_ADDRESS     0x68
//MPU6050 Gyro LPF setting
//Default settings LPF 256Hz/8000Hz sample
      #define MPU6050_DLPF_CFG   0        //256Hz
//    #define MPU6050_DLPF_CFG   1        //188Hz
//    #define MPU6050_DLPF_CFG   2        //98Hz
//    #define MPU6050_DLPF_CFG   3        //42Hz
//    #define MPU6050_DLPF_CFG   4        //20Hz
//    #define MPU6050_DLPF_CFG   5        //10Hz
//    #define MPU6050_DLPF_CFG   6        //5Hz
 
#define INTERNAL_I2C_PULLUPS
#define I2C_SPEED 400000L
#define MAG_ADDRESS 0x1E
#define MAG_DATA_REGISTER 0x03
#define HMC58X3_R_CONFA 0
#define HMC58X3_R_CONFB 1
#define HMC58X3_R_MODE 2
#define HMC58X3_X_SELF_TEST_GAUSS (+1.16)                       //!< X axis level when bias current is applied.
#define HMC58X3_Y_SELF_TEST_GAUSS (+1.16)   //!< Y axis level when bias current is applied.
#define HMC58X3_Z_SELF_TEST_GAUSS (+1.08)                       //!< Y axis level when bias current is applied.
#define SELF_TEST_LOW_LIMIT  (243.0/390.0)   //!< Low limit when gain is 5.
#define SELF_TEST_HIGH_LIMIT (575.0/390.0)   //!< High limit when gain is 5.


struct CRIUS_calibration_info_t
{
int16_vector3 acc_zero,gyro_zero,mag_zero;
uint16_t acc_1G;// this is the 1G measured acceleration

};

*/
class CRIUS_cls {
public:
/*
uint16_t fast_calibratingA,fast_calibratingG,fast_calibratingB;
uint8_t calibratingM;

CRIUS_cls () 
{
memset(&c,0,sizeof(CRIUS_calibration_info_t));
fast_calibratingA=0;
fast_calibratingG=0;
fast_calibratingB=0;
calibratingM=0;
c.acc_1G=512;
};

//int16_vector3 gyro_raw ,acc_raw ,mag_raw;
//int16_vector3 gyro_com,acc_com,mag_com;
struct CRIUS_calibration_info_t c;
*/
//LEDS//
void leds_init();
void all_leds_on() {digitalWrite(LED_RED,1);  digitalWrite(LED_YELLOW,1);  digitalWrite(LED_GREEN,1);};
void all_leds_on_round();
void all_leds_off() {digitalWrite(LED_RED,0);  digitalWrite(LED_YELLOW,0);  digitalWrite(LED_GREEN,0);};
/*
//i2c///
void i2c_init(void);
void i2c_rep_start(uint8_t address);
void  i2c_stop(void);
void  i2c_write(uint8_t data );
uint8_t  i2c_read(uint8_t ack);
uint8_t  i2c_readAck();
uint8_t i2c_readNak(void);
void  waitTransmissionI2C();
size_t  i2c_read_to_buf(uint8_t add, void *buf, size_t size);
size_t  i2c_read_reg_to_buf(uint8_t add, uint8_t reg, void *buf, size_t size);
void  swap_endianness(void *buf, size_t size);
void  i2c_getSixRawADC(uint8_t add, uint8_t reg);
void  i2c_writeReg(uint8_t add, uint8_t reg, uint8_t val);
uint8_t  i2c_readReg(uint8_t add, uint8_t reg);
uint8_t MPU6050_read_reg(uint8_t addres);

//Common//
void gyro_common(void);
void acc_common(void);
void baro_common(void);
uint8_t mag_common(void);// return 1 when news values are available, 0 otherwise

void init();
void sensors_init();

//read//
void gyro_read();
void acc_read ();
void acc_read_raw ();
void mag_read();
void direct_mag_read();
void read_and_common();

//calibration///
inline void acc_fast_calibration();
inline void gyro_fast_calibration();
inline void mag_calibration(); //empty

//MirmOS//
void MIRMOSfunc_include();

void i2c_MS561101BA_reset();
void i2c_MS561101BA_readCalibration();
void i2c_MS561101BA_UT_Start();
void i2c_MS561101BA_UT_Read();
void i2c_MS561101BA_UP_Start ();
void i2c_MS561101BA_UP_Read();
void i2c_MS561101BA_Calculate();

void Baro_init();
uint8_t Baro_update();

*/
};

extern CRIUS_cls CRIUS;


#endif
