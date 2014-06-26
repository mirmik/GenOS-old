//============================================================================
// Name			: Transformation.h
// Author		: pankratov.vs
// Version		: 1.0
// Description		: AHRS-library.
//					Algorythm of orientation calculation
//					is based on Sebastian O.H. Madgwick's works
//					http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
// Email		: vasiliy@mishinmachines.com
// Site			: http://www.mishinmachines.com
//============================================================================

#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_

#include "MirmOS.h"
#include "CRIUS.h"
#include "Quaternion.h"
#include "Euler.h"
#include <math.h>
//#include <Arduino.h>
//#include <L3G4200D_T.h>
//#include <LSM303_T.h>
#include <Wire_T.h>

// PARAMS
// L3G4200D gyro: 2000 dps full scale
// 70 mdps/digit; 1 dps = 0.07
#define GYRO_SCALE (0.07/3*11)
//#define GYRO_SCALE 0.2
// LSM303 accelerometer: 8 g sensitivity
// 3.8 mg/digit; 1 g = 256
#define GRAVITY 256  //this equivalent to 1G in the raw data coming from the accelerometer

class CRIUS_Transformation {
friend class CRIUS;
public:
	CRIUS_Transformation();
	void calculate();
	void calculateOrientation();
	// get absolute angle	
	Euler getAbs();
	// get relative angle
	Euler getDiff();	
	void init();	

	// magnetometer calibration
	void setCalib(int minx, int maxx, int miny, int maxy, int minz, int maxz);
	void calibrate();
	// fix current pose
	void fix();

public:
	void calculateTranslation();

	void getData();

	// quaternion calculated with gyro data
	Quaternion gyroQuat();
	// quaternion calculated with accelerometer
	//			and magnetometer data
	Quaternion accelMagQuat();

	// current orientation in quaternion representation
	Quaternion curOr,curOr2;
	Quaternion fixed;

	// SENSORS
	
	
	// SENSOR DATA
	Quaternion gyro;
	Quaternion acc;

	Quaternion mag;
	
	// get calibrated magnetometer data
	float getMagnet(int value, int axis);
	// cast quaternion to euler	
	//Euler quat2eu(Quaternion q);
	Euler quat2euAircraft(Quaternion q);
	Euler quat2euZYZ(Quaternion q);
	Euler quat2euXYZ(Quaternion q);

	// delta t (period of measurements) in seconds
	float dt;
	int32_t ctime;

	// magnetometer params
	int min_x, max_x, min_y, max_y, min_z, max_z;

	// magnet field vector (x and z axis, it is accepted that y = 0)
	Quaternion b;

	// ALGORYTHM PARAMS
	// factor for reducing noise in accelerometer and magnetometer
	// 		supposed to be more then 1
	float beta;
};

#endif /* TRANSFORMATION_H_ */
