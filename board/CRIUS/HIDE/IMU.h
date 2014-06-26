

#if !defined IMU_H
#define  IMU_H

#include "CRIUS.h"

//******  advanced users settings *******************
/* Set the Low Pass Filter factor for ACC
   Increasing this value would reduce ACC noise (visible in GUI), but would increase ACC lag time
   Comment this if  you do not want filter at all.
   unit = n power of 2 */
// this one is also used for ALT HOLD calculation, should not be changed
  #define ACC_LPF_FACTOR 4 // that means a LPF of 16

/* Set the Gyro Weight for Gyro/Acc complementary filter
   Increasing this value would reduce and delay Acc influence on the output of the filter*/
//  #define GYR_CMPF_FACTOR 600
#define GYR_CMPF_FACTOR 1000

/* Set the Gyro Weight for Gyro/Magnetometer complementary filter
   Increasing this value would reduce and delay Magnetometer influence on the output of the filter*/
//#define GYR_CMPFM_FACTOR 250
#define GYR_CMPFM_FACTOR 30

//****** end of advanced users settings *************
#define INV_GYR_CMPF_FACTOR   (1.0f / (GYR_CMPF_FACTOR  + 1.0f))
#define INV_GYR_CMPFM_FACTOR  (1.0f / (GYR_CMPFM_FACTOR + 1.0f))

#define GYRO_SCALE ((2279 * PI)/((32767.0f / 4.0f ) * 180.0f * 1000000.0f)) /350*300 //(ITG3200 and MPU6050)
// +-2000/sec deg scale
// for WMP, empirical value should be #define GYRO_SCALE (1.0f/200e6f)
// !!!!should be adjusted to the rad/sec and be part defined in each gyro sensor

typedef struct fp_vector {		
  float X,Y,Z;		
} t_fp_vector_def;

typedef union {		
  float A[3];		
  t_fp_vector_def V;		
} t_fp_vector;

typedef struct int32_t_vector {
  int32_t X,Y,Z;
} t_int32_t_vector_def;

typedef union {
  int32_t A[3];
  t_int32_t_vector_def V;
} t_int32_t_vector;


void getEstimatedAttitude();
void getEstimatedAltitude();
void angleCalculate();


extern t_fp_vector EstG;
extern t_int32_t_vector EstG32;
extern t_int32_t_vector EstM32;
extern t_fp_vector EstM;
#endif