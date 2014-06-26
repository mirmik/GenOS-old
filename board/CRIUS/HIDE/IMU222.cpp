
#include "IMU.h"
#define MAG 1
extern int16_Vector3 gyroADC,gyroData,accADC,accSmooth,magADC,magZero,magZeroTempMin,magZeroTempMax,accZero,angleTrim;
extern int16_Vector3 gyroZero,angle;
extern int32_Vector3 g;
  
extern float_Vector3   magGain;  // gain for each axis, populated at sensor init

extern uint8_t rawADC[6];
extern uint16_t acc_1G,acc_25deg;            // this is the 1G measured acceleration
extern uint8_t SMALL_ANGLES_25;
 int16_t  heading;


void computeIMU () {
  uint8_t axis;
  static int16_t gyroADCprevious[3] = {0,0,0};
  int16_t gyroADCp[3];
  int16_t gyroADCinter[3];
  static uint32_t timeInterleave = 0;
  //we separate the 2 situations because reading gyro values with a gyro only setup can be acchieved at a higher rate
  //gyro+nunchuk: we must wait for a quite high delay betwwen 2 reads to get both WM+ and Nunchuk data. It works with 3ms
  //gyro only: the delay to read 2 consecutive values can be reduced to only 0.65ms
    #if ACC
      ACC_getADC();
      getEstimatedAttitude();
    #endif
    #if GYRO
      Gyro_getADC();
    #endif
    for (axis = 0; axis < 3; axis++)
      gyroADCp[axis] =  gyroADC[axis];
    timeInterleave=micros();

    if ((micros()-timeInterleave)>650) {
      
    } else {
       while((micros()-timeInterleave)<650) ; //empirical, interleaving delay between 2 consecutive reads
    }
    #if GYRO
      Gyro_getADC();
    #endif
    for (axis = 0; axis < 3; axis++) {
      gyroADCinter[axis] =  gyroADC[axis]+gyroADCp[axis];
      // empirical, we take a weighted value of the current and the previous values
      gyroData[axis] = (gyroADCinter[axis]+gyroADCprevious[axis])/3;
      gyroADCprevious[axis] = gyroADCinter[axis]>>1;
      
    }
  #if defined(GYRO_SMOOTHING)
    static int16_t gyroSmooth[3] = {0,0,0};
    for (axis = 0; axis < 3; axis++) {
      gyroData[axis] = (int16_t) ( ( (int32_t)((int32_t)gyroSmooth[axis] * (conf.Smoothing[axis]-1) )+gyroData[axis]+1 ) / conf.Smoothing[axis]);
      gyroSmooth[axis] = gyroData[axis];
    }
  #elif defined(TRI)
    static int16_t gyroYawSmooth = 0;
    gyroData[YAW] = (gyroYawSmooth*2+gyroData[YAW])/3;
    gyroYawSmooth = gyroData[YAW];
  #endif
}

// **************************************************
// Simplified IMU based on "Complementary Filter"
// Inspired by http://starlino.com/imu_guide.html
//
// adapted by ziss_dm : http://www.multiwii.com/forum/viewtopic.php?f=8&t=198
//
// The following ideas was used in this project:
// 1) Rotation matrix: http://en.wikipedia.org/wiki/Rotation_matrix
// 2) Small-angle approximation: http://en.wikipedia.org/wiki/Small-angle_approximation
// 3) C. Hastings approximation for atan2()
// 4) Optimization tricks: http://www.hackersdelight.org/
//
// Currently Magnetometer uses separate CF which is used only
// for heading approximation.
//
// **************************************************

//******  advanced users settings *******************
/* Set the Low Pass Filter factor for ACC
   Increasing this value would reduce ACC noise (visible in GUI), but would increase ACC lag time
   Comment this if  you do not want filter at all.
   unit = n power of 2 */
// this one is also used for ALT HOLD calculation, should not be changed
#ifndef ACC_LPF_FACTOR
  #define ACC_LPF_FACTOR 4 // that means a LPF of 16
#endif

/* Set the Gyro Weight for Gyro/Acc complementary filter
   Increasing this value would reduce and delay Acc influence on the output of the filter*/
#ifndef GYR_CMPF_FACTOR
  #define GYR_CMPF_FACTOR 600
#endif

/* Set the Gyro Weight for Gyro/Magnetometer complementary filter
   Increasing this value would reduce and delay Magnetometer influence on the output of the filter*/
#define GYR_CMPFM_FACTOR 250

//****** end of advanced users settings *************
#define INV_GYR_CMPF_FACTOR   (1.0f / (GYR_CMPF_FACTOR  + 1.0f))
#define INV_GYR_CMPFM_FACTOR  (1.0f / (GYR_CMPFM_FACTOR + 1.0f))

#define GYRO_SCALE ((2279 * PI)/((32767.0f / 4.0f ) * 180.0f * 1000000.0f)) //(ITG3200 and MPU6050)
// +-2000/sec deg scale
// for WMP, empirical value should be #define GYRO_SCALE (1.0f/200e6f)
// !!!!should be adjusted to the rad/sec and be part defined in each gyro sensor


int16_t _atan2(int32_t y, int32_t x){
  float z = (float)y / x;
  int16_t a;
  if ( abs(y) < abs(x) ){
     a = 573 * z / (1.0f + 0.28f * z * z);
   if (x<0) {
     if (y<0) a -= 1800;
     else a += 1800;
   }
  } else {
   a = 900 - 573 * z / (z * z + 0.28f);
   if (y<0) a -= 1800;
  }
  return a;
}


float InvSqrt (float x){ 
  union{  
    int32_t i;  
    float   f; 
  } conv; 
  conv.f = x; 
  conv.i = 0x5f3759df - (conv.i >> 1); 
  return 0.5f * conv.f * (3.0f - x * conv.f * conv.f);
}

// Rotate Estimated vector(s) with small angle approximation, according to the gyro data
void rotateV(struct fp_vector *v,float* delta) {
  fp_vector v_tmp = *v;
  v->Z -= delta[ROLL]  * v_tmp.X + delta[PITCH] * v_tmp.Y;
  v->X += delta[ROLL]  * v_tmp.Z - delta[YAW]   * v_tmp.Y;
  v->Y += delta[PITCH] * v_tmp.Z + delta[YAW]   * v_tmp.X;
}


static int32_t accLPF32[3]    = {0, 0, 1};
static float invG; // 1/|G|

t_fp_vector EstG;
static t_int32_t_vector EstG32;
#if MAG
  t_int32_t_vector EstM32;
  t_fp_vector EstM;
#endif

void getEstimatedAttitude(){
  uint8_t axis;
  int32_t accMag = 0;
  float scale, deltaGyroAngle[3];
  static uint16_t previousT;
  uint16_t currentT = micros();

  scale = (currentT - previousT) * GYRO_SCALE;
  previousT = currentT;

  // Initialization
  for (axis = 0; axis < 3; axis++) {
    deltaGyroAngle[axis] = gyroADC[axis]  * scale;

    accLPF32[axis]    -= accLPF32[axis]>>ACC_LPF_FACTOR;
    accLPF32[axis]    += accADC[axis];
    accSmooth[axis]    = accLPF32[axis]>>ACC_LPF_FACTOR;

    accMag += (int32_t)accSmooth[axis]*accSmooth[axis] ;
  }
  accMag = accMag*100/((int32_t)acc_1G*acc_1G);

  rotateV(&EstG.V,deltaGyroAngle);
  #if MAG
    rotateV(&EstM.V,deltaGyroAngle);
  #endif

  if ( abs(accSmooth[ROLL])<acc_25deg && abs(accSmooth[PITCH])<acc_25deg && accSmooth[YAW]>0) {
    SMALL_ANGLES_25 = 1;
  } else {
    SMALL_ANGLES_25 = 0;
  }

  // Apply complimentary filter (Gyro drift correction)
  // If accel magnitude >1.15G or <0.85G and ACC vector outside of the limit range => we neutralize the effect of accelerometers in the angle estimation.
  // To do that, we just skip filter, as EstV already rotated by Gyro
  if (  72 < accMag && accMag < 133 )
    for (axis = 0; axis < 3; axis++) {
      EstG.A[axis] = (EstG.A[axis] * GYR_CMPF_FACTOR + accSmooth[axis]) * INV_GYR_CMPF_FACTOR;
    }
  #if MAG
    for (axis = 0; axis < 3; axis++) {
      EstM.A[axis] = (EstM.A[axis] * GYR_CMPFM_FACTOR  + magADC[axis]) * INV_GYR_CMPFM_FACTOR;
      EstM32.A[axis] = EstM.A[axis];
    }
  #endif

  for (axis = 0; axis < 3; axis++)
    EstG32.A[axis] = EstG.A[axis]; //int32_t cross calculation is a little bit faster than float	

  // Attitude of the estimated vector
  int32_t sqGZ = sq(EstG32.V.Z);
  int32_t sqGX = sq(EstG32.V.X);
  int32_t sqGY = sq(EstG32.V.Y);
  int32_t sqGX_sqGZ = sqGX + sqGZ;
  float invmagXZ  = InvSqrt(sqGX_sqGZ);
  invG = InvSqrt(sqGX_sqGZ + sqGY);
  angle[ROLL]  = _atan2(EstG32.V.X , EstG32.V.Z);
  angle[PITCH] = _atan2(EstG32.V.Y , invmagXZ*sqGX_sqGZ);

  #if MAG 
  #define MAG_DECLINIATION  0.0f

    heading = _atan2(
      EstM32.V.Z * EstG32.V.X - EstM32.V.X * EstG32.V.Z,
      EstM32.V.Y * invG * sqGX_sqGZ  - (EstM32.V.X * EstG32.V.X + EstM32.V.Z * EstG32.V.Z) * invG * EstG32.V.Y ); 
    heading += MAG_DECLINIATION * 10; //add declination
    heading = heading /10;
  #endif
}


