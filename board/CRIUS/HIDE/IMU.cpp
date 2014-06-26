
#include "IMU.h"
#define MAG 1

int16_Vector3 accSmooth,gyroData,angle;
int16_t  heading,heading2,axisDekl,deklination;

extern int correct;
extern int16_Vector3 gyroADC,accADC,magADC,magZero,magZeroTempMin,magZeroTempMax,accZero,angleTrim;
extern uint16_t acc_1G,acc_25deg;            // this is the 1G measured acceleration
extern uint8_t SMALL_ANGLES_25;


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

int16_t _atan(float z){
  int16_t a;
   if (z<=1.57)  a = 900 - 573 * z / (1.0f + 0.28f * z * z);
   else  a = 573 * z / (z * z + 0.28f);
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
 v->X +=  								+ delta[YAW]  * v_tmp.Y 			- delta[PITCH]  * v_tmp.Z ;
 v->Y +=  - delta[YAW]    * v_tmp.X 									+ delta[ROLL]   * v_tmp.Z ;
 v->Z +=  +	delta[PITCH]  * v_tmp.X  	- delta[ROLL] * v_tmp.Y;
 }



void vectorMultiply(t_int32_t_vector *v1,t_int32_t_vector *v2,t_int32_t_vector *rez) {
  rez->V.X =  v1->V.Z * v2->V.Y - v1->V.Y * v2->V.Z;
  rez->V.Y =  v1->V.X * v2->V.Z - v1->V.Z * v2->V.X;
  rez->V.Z =  v1->V.Y * v2->V.X - v1->V.X * v2->V.Y;
}






static int32_t accLPF32[3]    = {0, 0, 1};
static float invG; // 1/|G|

t_fp_vector EstG;
t_int32_t_vector EstG32,headvect;
t_int32_t_vector EstM32;
t_fp_vector EstM;

void getEstimatedAttitude(){
  uint8_t axis;
  int32_t accMag = 0;
  float scale, deltaGyroAngle[3];
  static uint16_t previousT;
  uint16_t currentT = micros();
///Вычисляем шаг. (считаем время от прошлого просчета)
  scale = (currentT - previousT) * GYRO_SCALE;
  previousT = currentT;

  // Initialization
  ///По каждой из трех осей.
  for (axis = 0; axis < 3; axis++) {
	///Получаем дельты по углам поворотов.
    deltaGyroAngle[axis] = gyroADC[axis]  * scale;

	/// Следующее выражение приводится к accSmooth[i]=1/16*accADC[i]+15/16*accSmooth[i-1]
	/// Это фильтр нижних частот, причем Т=16*h, где h - шаг дискретизации в секундах.
	/// Эксперимент показывает как минимум совпадение порядков (h=50мс. Выход на полку примерно 2с.).
    accLPF32[axis]    -= accLPF32[axis]>>ACC_LPF_FACTOR;
    accLPF32[axis]    += accADC[axis];
    accSmooth[axis]    = accLPF32[axis]>>ACC_LPF_FACTOR;
///Считаем модуль расчитанного вектора.
    accMag += (int32_t)accSmooth[axis]*accSmooth[axis] ;
  }
	

  /// Масштабируем модуль (g=100).
  accMag = accMag*100/((int32_t)acc_1G*acc_1G);

///Используя уравнение Пуассона, правим платформенные вектора G　и M.   
  rotateV(&EstG.V,deltaGyroAngle);
  rotateV(&EstM.V,deltaGyroAngle);

  // Apply complimentary filter (Gyro drift correction)
  // If accel magnitude >1.15G or <0.85G and ACC vector outside of the limit range => we neutralize the effect of accelerometers in the angle estimation.
  // To do that, we just skip filter, as EstV already rotated by Gyro
  if (correct==1){
  
  if ((72 < accMag) && (accMag < 133)){
  
 // digitalWrite(30,1);
  /// Коррекция платформенного вектора G　по показаниям акселлерометров. GYR_CMPF_FACTOR отвечает за чувствительность.
    for (axis = 0; axis < 3; axis++) {
      EstG.A[axis] = (EstG.A[axis] * GYR_CMPF_FACTOR + accSmooth[axis]) * INV_GYR_CMPF_FACTOR;
	}
	/// Коррекция платформенного вектора M　по показаниям магнетометра. GYR_CMPFM_FACTOR отвечает за чувствительность.
    for (axis = 0; axis < 3; axis++) {
      EstM.A[axis] = (EstM.A[axis] * GYR_CMPFM_FACTOR  + magADC[axis]) * INV_GYR_CMPFM_FACTOR;
    }
	}
	}

	for (axis=0;axis<3;axis++)
	{
    EstG32.A[axis] = EstG.A[axis];
	  EstM32.A[axis] = EstM.A[axis];
	}
}



void angleCalculate()
{
/// Дальше идет суровая математика, в силу которой мы получаем тангаж, крен, а также курс,
/// ... Причем в расчете курса учавствует магнетометр.
  // Attitude of the estimated vector
  int32_t sqGZ = sq(EstG32.V.Z);
  int32_t sqGX = sq(EstG32.V.X);
  int32_t sqGY = sq(EstG32.V.Y);
  int32_t sqGX_sqGZ = sqGX + sqGZ;
  float invmagXZ  = InvSqrt(sqGX_sqGZ);
  invG = InvSqrt(sqGX_sqGZ + sqGY);
  angle[ROLL]  = _atan2(EstG32.V.X ,EstG32.V.Z);
  angle[PITCH] = - _atan2(EstG32.V.Y , invmagXZ*sqGX_sqGZ);

    heading = _atan2(
      EstM32.V.Z * EstG32.V.X - EstM32.V.X * EstG32.V.Z,
      EstM32.V.Y * invG * sqGX_sqGZ  - (EstM32.V.X * EstG32.V.X + EstM32.V.Z * EstG32.V.Z) * invG * EstG32.V.Y ); 
   heading = heading /10;
 // vectorMultiply(&EstM32,&EstG32,&headvect);
  // heading2=
 // axisDekl=_atan2(EstG32.V.X , EstG32.V.Y);
 // deklination=_atan(EstG32.V.Z * InvSqrt(sqGX+sqGY));
}

  


 
  int32_t  BaroAlt,EstAlt; // in cm
  int32_t  VerticalVel,VerticalVel_h; // in cm/s
   int32_t baroPressure;
   int32_t baroTemperature;
   int32_t baroPressureSum;




#define UPDATE_INTERVAL 18000    // 40hz update rate (20hz LPF on acc)
#define BARO_TAB_SIZE   15


void getEstimatedAltitude(){
 // static uint32_t deadLine;
  static int32_t baroHistTab[BARO_TAB_SIZE];
    static uint8_t baroHistIdx;
 
  static int32_t baroGroundPressure;
  static uint16_t previousT;
  uint16_t currentT = micros();
  uint16_t dTime;

  
 dTime = currentT - previousT;
 if (dTime < UPDATE_INTERVAL) return;
 previousT = currentT;

 
    CRIUS.i2c_MS561101BA_Calculate();
 
  if(CRIUS.calibratingB > 1) {
    uint8_t indexplus1 = (baroHistIdx + 1);
    if (indexplus1 == BARO_TAB_SIZE) indexplus1 = 0;
    baroHistTab[baroHistIdx] = baroPressure;
    baroPressureSum += baroHistTab[baroHistIdx];
    baroPressureSum -= baroHistTab[indexplus1];
    baroHistIdx = indexplus1;  
	CRIUS.calibratingB--;
	return;
	}
	if(CRIUS.calibratingB == 1)
	{
    baroGroundPressure = baroPressureSum/(BARO_TAB_SIZE - 1);
	CRIUS.calibratingB--;
	return;
  }

  // pressure relative to ground pressure with temperature compensation (fast!)
  // baroGroundPressure is not supposed to be 0 here
  // see: https://code.google.com/p/ardupilot-mega/source/browse/libraries/AP_Baro/AP_Baro.cpp
//  BaroAlt = log( baroGroundPressure * (BARO_TAB_SIZE - 1)/ (float)baroPressureSum ) * (baroTemperature+27315) * 29.271267f; // in cemtimeter 
    BaroAlt = log( baroGroundPressure / (float)baroPressure ) * (baroTemperature+27315) * 29.271267f *10; // in cemtimeter 
    EstAlt = (EstAlt * 14 + BaroAlt * 2) >> 4; // additional LPF to reduce baro noise (faster by *30* µs)
	VerticalVel_h=BaroAlt-EstAlt;
	VerticalVel=((VerticalVel*28)+(VerticalVel_h)*4)>>5;
  return;
}
