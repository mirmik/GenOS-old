#include "CRIUS.h"
//#include "mirmos_types.h"

CRIUS_cls CRIUS;

/*
void CRIUS_cls::init() {
CRIUS.leds_init();
CRIUS.sensors_init();
} 
//int16_vector3 gyroADC,accADC,magADC,magZero,magZeroTempMin,magZeroTempMax,accZero,angleTrim,gyroZero;
//int32_vector3 g;
  
//float_vector3   magGain = {1.0,1.0,1.0};  // gain for each axis, populated at sensor init

uint8_t rawADC[6];
//uint8_t magInit = 0;
//int16_t acc_1G_UP,acc_1G_DOWN;

#define ACC_ORIENTATION(X, Y, Z)  {acc_raw.x  = -X; acc_raw.y  = -Y; acc_raw.z  =  Z;}
#define GYRO_ORIENTATION(X, Y, Z) {gyro_raw.x = X; gyro_raw.y = Y; gyro_raw.z =  -Z;}
#define MAG_ORIENTATION(X, Y, Z)  {mag_raw.x  =  X; mag_raw.y  =  Y; mag_raw.z  = -Z;} 

/*
#define ACC_ORIENTATION(X, Y, Z)  {imu.accADC[ROLL]  = -X; imu.accADC[PITCH]  = -Y; imu.accADC[YAW]  =  Z;} 
  #define GYRO_ORIENTATION(X, Y, Z) {imu.gyroADC[ROLL] =  Y; imu.gyroADC[PITCH] = -X; imu.gyroADC[YAW] = -Z;} 
  #define MAG_ORIENTATION(X, Y, Z)  {imu.magADC[ROLL]  =  X; imu.magADC[PITCH]  =  Y; imu.magADC[YAW]  = -Z;} 
  #
*/



/*
////////////////////////I2C/////////////////////////////////
void CRIUS_cls::i2c_getSixRawADC(uint8_t add, uint8_t reg) {
  i2c_read_reg_to_buf(add, reg, &rawADC, 6);} 
 //**********************************************************
  
  //Функции, отвечающие за получение первичной информации с датчиков.
// После получения информации тут же запускается обработка _Common().
//Запросить данные у гироскопа
void CRIUS_cls::gyro_read () {
  i2c_getSixRawADC(MPU6050_ADDRESS, 0x43);
  GYRO_ORIENTATION( ((rawADC[0]<<8) | rawADC[1])>>2 , // range: +/- 8192; +/- 2000 deg/sec
                    ((rawADC[2]<<8) | rawADC[3])>>2 ,
                    ((rawADC[4]<<8) | rawADC[5])>>2 );
}

//Запросить данные у акселерометра
void CRIUS_cls::acc_read () {
  i2c_getSixRawADC(MPU6050_ADDRESS, 0x3B);
  ACC_ORIENTATION( ((rawADC[0]<<8) | rawADC[1])>>3 ,
                   ((rawADC[2]<<8) | rawADC[3])>>3 ,
                   ((rawADC[4]<<8) | rawADC[5])>>3 );
}

// Запросить данные у магнетометра непосредственно.
void CRIUS_cls::direct_mag_read() {
i2c_getSixRawADC(MAG_ADDRESS,MAG_DATA_REGISTER);
MAG_ORIENTATION( ((rawADC[0]<<8) | rawADC[1]) ,
                     ((rawADC[4]<<8) | rawADC[5]) ,
                     ((rawADC[2]<<8) | rawADC[3]) );
}


// Запросить данные у магнетометра через MPU6050.
void CRIUS_cls::mag_read() {
      i2c_getSixRawADC(MPU6050_ADDRESS, 0x49);               //0x49 is the first memory room for EXT_SENS_DATA
  
       MAG_ORIENTATION( ((rawADC[0]<<8) | rawADC[1]) ,
                         ((rawADC[4]<<8) | rawADC[5]) ,
                         ((rawADC[2]<<8) | rawADC[3]) );
    };

////////////////////////////////////////////////////////////////

void CRIUS_cls::read_and_common()
{
acc_read();
gyro_read();
mag_read();
acc_common();
gyro_common();
mag_common();
}


//Обработчики первичной информации:
// ****************
// ACC common part
// ****************
inline void CRIUS_cls::acc_fast_calibration(){
 static int32_vector3 a; 
	
		for (uint8_t axis = 0; axis < 3; axis++) {
		if (fast_calibratingA == 512) a.elem[axis]=0;
		a.elem[axis] +=acc_raw.elem[axis];
		}
		// Calculate average, shift Z down by acc_1G and store values in EEPROM at end of calibration
	if (fast_calibratingA == 1) {
		c.acc_zero.x  = a.x>>9;
		c.acc_zero.y = a.y>>9;
		c.acc_zero.z   = (a.z>>9)-c.acc_1G; // for nunchuk 200=1G
		}
		fast_calibratingA--;
	}

void CRIUS_cls::acc_common() {  
  if (fast_calibratingA>0) acc_fast_calibration();
  acc_com = acc_raw - c.acc_zero;  
}

inline void CRIUS_cls::gyro_fast_calibration(){
 static int32_vector3 g; 
	
		for (uint8_t axis = 0; axis < 3; axis++) {
		if (fast_calibratingG == 512) g.elem[axis]=0;
		g.elem[axis] +=gyro_raw.elem[axis];
		}
		// Calculate average, shift Z down by acc_1G and store values in EEPROM at end of calibration
	if (fast_calibratingG == 1) {
		c.gyro_zero.x  = g.x>>9;
		c.gyro_zero.y = g.y>>9;
		c.gyro_zero.z   = (g.z>>9); // for nunchuk 200=1G
		}
		fast_calibratingG--; 
	}
// ****************
// GYRO common part
// ****************
void CRIUS_cls::gyro_common() {
  //Эта часть отвечает за калибровку.
  if (fast_calibratingG>0)  gyro_fast_calibration();
  gyro_com = gyro_raw - c.gyro_zero;

}



//******************************************************
//MAG
//****************************************************
uint8_t CRIUS_cls::mag_common() {  // return 1 when news values are available, 0 otherwise
 
 //no fastclaibration algoritm.
   mag_com = mag_raw - c.mag_zero;   
  return 1;
}


void CRIUS_cls::mag_calibration(){
/*
static unsigned long tstart,t;
  uint8_t axis;
 if (MCalibrating==1)
  {
  if (MCalibrating!=LastMCalibrating) {tstart=millis();
  for(axis=0;axis<3;axis++) {
        magZeroTempMin[axis] = 0;
       magZeroTempMax[axis]=0;
	   magGain[axis]=1;
    }
	}
  LastMCalibrating=MCalibrating;
  // 30s: you have 30s to turn the multicontroller in all directions
    for(axis=0;axis<3;axis++) {
        if (magADC[axis] < magZeroTempMin[axis]) magZeroTempMin[axis] = magADC[axis];
        if (magADC[axis] > magZeroTempMax[axis]) magZeroTempMax[axis] = magADC[axis];
      }
	for(axis=0;axis<3;axis++)
        magZero[axis] = (magZeroTempMin[axis] + magZeroTempMax[axis])>>1;
  if ((millis() - tstart) > 30000) {MCalibrating=0;LastMCalibrating=0;
    for(axis=0;axis<3;axis++) {
	magGain[axis]=1000.0/(magZeroTempMax[axis]-magZeroTempMin[axis]);
	}}*/
	//}


//*******************************************
/*
#include <avr/eeprom.h>
int correct=1;

/*
void calibrateUp()
{static int32_t acc_1G_UP;
 int32_t a=0; 
for (int i=0;i<512;i++){
  CRIUS.acc_read();
 		a +=CRIUS.acc_raw.z;
		}	
acc_1G_UP= a >> 9;
prln(acc_1G_UP);
}

void calibrateDown()
{static int32_t acc_1G_DOWN; 
int32_t a=0; 
for (int i=0;i<512;i++){
  CRIUS.acc_read();
 		a +=CRIUS.acc_raw.z;
		}	
acc_1G_DOWN= a /512;
prln(acc_1G_DOWN);

//acc_1G=(abs(acc_1G_UP)+abs(acc_1G_DOWN)) >> 1;
prln(acc_1G);
}*/
/*
uint8_t accprint,gyroprint,magprint,bins2,vect32,baro;

uint8_t usprint;


void CRIUS_calibratesave(void* p)
{eeprom_write_block ((const void *)&CRIUS.c, p, sizeof(CRIUS_calibration_info_t));}
void CRIUS_calibrateload(void* p)
{eeprom_read_block ((void *)&CRIUS.c, (const void *)p, sizeof(CRIUS_calibration_info_t));}


void CRIUS_calibratesave_h()
{CRIUS_calibratesave((void*)30);}
void CRIUS_calibrateload_h()
{CRIUS_calibrateload((void*)30);}



extern int32_t BaroAlt;
extern void userPrint();
timer_t* t;
void printADC_h(){
   
if(accprint!=0){
pr("a ")  vector_print(CRIUS.acc_com);
//pr("az ")    VectorPrint(accZero);
}
if(gyroprint!=0){
pr("g ")  vector_print(CRIUS.gyro_com); 
//pr("gz ")   VectorPrint(gyroZero);
}
if(magprint!=0){
pr("m ")  vector_print(CRIUS.mag_com); 
 // VectorPrint(magZeroTempMax);
 // VectorPrint(magZeroTempMin);
//  VectorPrint(magZero);
//pr("mG ")   VectorPrint(magGain);
}
//if(bins2!=0){
//pr("P:") tab pr(angle[PITCH]) tab pr("R:") tab pr(angle[ROLL]) tab // pr("H:") tab pr(heading) tab pr("D:") tab pr(axisDekl) tab pr(deklination); }
/*
if (vect32!=0)
{pr("HX:") tab pr(headvect.V.X) tab pr("HY:") tab pr(headvect.V.Y) tab pr("HZ:") tab pr(headvect.V.Z) tab pr("MX:") tab pr(EstM32.V.X) tab pr("MY:") tab pr(EstM32.V.Y) tab pr("MZ:") tab pr(EstM32.V.Z) tab pr("GX:") tab pr(EstG32.V.X) tab pr("GY:") tab pr(EstG32.V.Y) tab pr("GZ:") tab pr(EstG32.V.Z)}

if (baro!=0)
{pr("BARO:"); tab pr(BaroAlt); tab}
*//*
if(usprint!=0) userPrint();

pr("\r\n")



}

void printADC()
{
t=SH.newTimer(printADC_h,50,REPEAT);
}


void stopADC()
{SH.deleteTimer(t);}


void calibrate()
{CRIUS.fast_calibratingA=512;
CRIUS.fast_calibratingG=512;
CRIUS.fast_calibratingB=20;
}

void calibrateM(){
  CRIUS.calibratingM=1;}


  void CRIUS_cls::MIRMOSfunc_include(void)
  {
param("acc",accprint,UINT8);
param("gyro",gyroprint,UINT8);
param("mag",magprint,UINT8);
param("bins",bins2,UINT8);
param("vect32",vect32,UINT8);
param("usprint",usprint,UINT8);
param("correct",correct,INT16);
param("baro",baro,UINT8);
command("csave",CRIUS_calibratesave_h);
command("cload",CRIUS_calibrateload_h);
command("printADC",printADC);
command("stopADC",stopADC);
command("calibrate",calibrate);
command("calibrateM",calibrateM);
//command("cup",calibrateUp);
//command("cdown",calibrateDown);
}





*/
