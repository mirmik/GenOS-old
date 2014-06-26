/*
 * Transformation.cpp
 *
 *  Created on: 16.10.2012
 *      Author: pankratov.vs
 */

#include "CRIUS_Transformation.h"

CRIUS_Transformation::CRIUS_Transformation() {
	curOr.set(1, 0, 0, 0);
	//curOr2.set(1, 0, 0, 0);
	gyro = Quaternion(0, 0, 0, 0);
	acc = Quaternion(0, 0, 0, 0);	
	mag = Quaternion(0, 0, 0, 0);

	min_x = 0;
	max_x = 0;
	min_y = 0;
	max_y = 0;
	min_z = 0;
	max_z = 0;

	beta = 0.076;
	//beta=1;
	b.set(0, 1, 0, 0);
}
/*
void CRIUS_Transformation::calculate() {
	calculateOrientation();
	
}*/

// magnetometer calibration
void CRIUS_Transformation::setCalib(int minx, int maxx, int miny, int maxy, int minz, int maxz) {
	min_x = minx;
	max_x = maxx;
	min_y = miny;
	max_y = maxy;
	min_z = minz;
	max_z = maxz;	
}

void CRIUS_Transformation::calibrate() {
	// TODO: add writing magnet params to flash
}

float CRIUS_Transformation::getMagnet(int value, int axis) {
	switch(axis){
		case X:
			return (float)(value-min_x)/(max_x-min_x)-0.5;
		case Y:
			return (float)(value-min_y)/(max_y-min_y)-0.5;
		case Z:
			return (float)(value-min_z)/(max_z-min_z)-0.5;
	}
}

void CRIUS_Transformation::calculateOrientation() {
	getData();

	// The Algorythm
	Quaternion gyroQ = gyroQuat();
	Quaternion accmQ = accelMagQuat();
	//Quaternion accmQ2 = accelMagQuat();

	curOr = curOr + dt*(
	-gyroQ 
	- beta*accmQ
	);
	//curOr.normalize();

}

void CRIUS_Transformation::init() {
	//ctime = millis();
	//Wire.begin();
/*
	// gyro init
	gyro_dev.writeReg(L3G4200D_CTRL_REG1, 0x0F); // normal power mode, all axes enabled, 100 Hz
	gyro_dev.writeReg(L3G4200D_CTRL_REG4, 0x20); // 2000 dps full scale

	// accelerometer and magnetometer init
	accelMag_dev.writeAccReg(LSM303_CTRL_REG1_A, 0x27); // normal power mode, all axes enabled, 50 Hz
  	accelMag_dev.writeAccReg(LSM303_CTRL_REG4_A, 0x30); // 8 g full scale
	accelMag_dev.init();	
	accelMag_dev.writeMagReg(LSM303_MR_REG_M, 0x00); // continuous conversion mode

	// TODO: read magnet params from flash -> if(min_x = max_x) 

	// calculation of gyro and accelerometer offsets
	Quaternion g_sum(0, 0, 0, 0);
	Quaternion a_sum(0, 0, 0, 0);
	for(int i = 0; i < 50; i++){
		getData();
		g_sum = g_sum + gyro;
		a_sum = a_sum + accel;		
		delay(20);
	}
	gyro_offset = g_sum/50;
	accel_offset = a_sum/50;
	accel_offset.elem[Z] += GRAVITY;
	*/
	// execute gradient descent for n=500
	
	
	
	
	Quaternion jtf;
	for(int i=0; i<500; i++){
	getData();
		jtf = accelMagQuat();
		
	//jtf.print(); tab curOr.println();
		curOr = curOr - jtf*beta;
		
	}
	//curOr2=curOr;

	// fix current absolute orientation
	fix();

	ctime = micros();
}


void CRIUS_Transformation::getData() {

	CRIUS.read_and_common();
	
	gyro.set(0, CRIUS.gyro_com.x, CRIUS.gyro_com.y, CRIUS.gyro_com.z);
	gyro = GYRO_SCALE*DEG*gyro;
	acc.set(0, CRIUS.acc_com.x, CRIUS.acc_com.y, CRIUS.acc_com.z);
	mag.set(0, CRIUS.mag_com.x, CRIUS.mag_com.y, CRIUS.mag_com.z);
		
	dt = (micros() - ctime)*0.000001;
	ctime = micros();
}
/*
// translation of quaternion representation to euler-angeles regresentation
Euler CRIUS_Transformation::getAbs() {
	return quat2eu(curOr);
}*/
/*
Euler CRIUS_Transformation::getDiff() {
	Quaternion diff = fixed.conjugate()*curOr;	
	return quat2eu(diff);
}*/

void CRIUS_Transformation::fix() {
	fixed = curOr;
}

#define S11 (-1+2*q[1]*q[1]+2*q[0]*q[0])
#define S22 (-1+2*q[2]*q[2]+2*q[0]*q[0])
#define S33 (-1+2*q[3]*q[3]+2*q[0]*q[0])

#define S12 (2*(q[2]*q[1]-q[3]*q[0]))
#define S13 (2*(q[3]*q[1]+q[2]*q[0]))

#define S21 (2*(q[1]*q[2]+q[3]*q[0]))
#define S23 (2*(q[3]*q[2]-q[1]*q[0]))

#define S31 (2*(q[1]*q[3]-q[2]*q[0]))
#define S32 (2*(q[2]*q[3]+q[1]*q[0]))

Euler CRIUS_Transformation::quat2euZYZ(Quaternion q) {
	return Euler(atan2(S23,S13),
				acos(S33),
				-atan2(S32,S31));
}


Euler CRIUS_Transformation::quat2euXYZ(Quaternion q) {
	return Euler(-atan2(S23,S33),
				asin (S13),
				 atan2(S12,S11));
}

Euler CRIUS_Transformation::quat2euAircraft(Quaternion q) {
	return Euler(
				 -atan2(S21,S11),
				 asin (S31),
				 -atan2(S32,S33)
				 );
}


// orientation from angular rate
Quaternion CRIUS_Transformation::gyroQuat() {
	// quaternion derivative due to the time
	return 0.5*curOr*gyro;
}

// orientation from vector observation
// 		initially assume that there is no magnetic flux,
// 		distortion and linear accelerations (except gravity acceleration)
Quaternion CRIUS_Transformation::accelMagQuat() {
	
	Quaternion res;
	Quaternion a = acc.normalize();
	Quaternion m = mag.normalize();
	Quaternion q = curOr;

	// gradient of the function of difference between
	// 			sensor data and assumed quaternion
	//			(transposed jacobian [jt] multiplied on the function [f])
	Quaternion jtf;
	// the function
	float f[6];
	f[0] =  2*(q[1]*q[3]-q[0]*q[2])-a[X];
	f[1] = 2*(q[0]*q[1]+q[2]*q[3])-a[Y];
	f[2] = 2*(0.5-q[1]*q[1]-q[2]*q[2])-a[Z];
	f[3] = 2*b[X]*(0.5-q[2]*q[2]-q[3]*q[3])+2*b[Z]*(q[1]*q[3]-q[0]*q[2])-m[X];
	f[4] = 2*b[X]*(q[1]*q[2]-q[0]*q[3])+2*b[Z]*(q[0]*q[1]+q[2]*q[3])-m[Y];
	f[5] = 2*b[X]*(q[0]*q[2]+q[1]*q[3])+2*b[Z]*(0.5-q[1]*q[1]-q[2]*q[2])-m[Z];

	jtf.elem[0] = -2*q[2]*f[0] +
			2*q[1]*f[1] -
			2*b[Z]*q[2]*f[3] +
			(2*b[Z]*q[1]-2*b[X]*q[3])*f[4] +
			2*b[X]*q[2]*f[5];
	jtf.elem[1] = 2*q[3]*f[0] +
			2*q[0]*f[1] -
			4*q[1]*f[2] +
			2*b[Z]*q[3]*f[3] +
			(2*b[X]*q[2]+2*b[Z]*q[0])*f[4] +
			(2*b[X]*q[3]-4*b[Z]*q[1])*f[5];
	jtf.elem[2] = -2*q[0]*f[0]+
			2*q[3]*f[1] -
			4*q[2]*f[2] -
			(4*b[X]*q[2]+2*b[Z]*q[0])*f[3] +
			(2*b[X]*q[1]+2*b[Z]*q[3])*f[4] +
			(2*b[X]*q[0]-4*b[Z]*q[2])*f[5];
	jtf.elem[3] = 2*q[1]*f[0] +
			2*q[2]*f[1] +
			(2*b[Z]*q[1]-4*b[X]*q[3])*f[3] +
			(2*b[Z]*q[2]-2*b[X]*q[0])*f[4] +
			2*b[X]*q[1]*f[5];

	// calculating b
	Quaternion h = q*m*q.conjugate();
	b.set(0, sqrt(h[X]*h[X]+h[Y]*h[Y]), 0, h[Z]);

	//float mu = alpha*dt*gyro.absolute();
	return jtf.normalize();
}
