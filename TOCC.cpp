/*===================================
  This is class for Two Object Camera Controller (TOCC).
  This controller requires 3 inputs and produces 3 outputs.

  Controller Inputs:
  [1] xm: The x coordinate of the middle point of two objects in a camera frame.
  [2] distX: The x coordinate difference between two objects in a camera frame.
  [3] distS: This difference in size between two objects in a camaera frame. 


  Controller Output:
  [1] yaw: The camera rotation about x axis of the gloable coordinate.
  [2] xt: The camera translation in x derection of the gloable coordinate.
  [3] zt: The camera translation in z derection of the gloable coordinate.



Usage:

float cameraModel[7];
cameraModel[0] = x0;
cameraModel[1] = y0;
cameraModel[2] = fx;
cameraModel[3] = fy;
cameraModel[4] = fov;
cameraModel[5] = resWidth;
cameraModel[6] = resHeight;



float cameraTransformation[6];
cameraTransformation[0] = xt;
cameraTransformation[1] = yt;
cameraTransformation[2] = zt;
cameraTransformation[3] = roll;
cameraTransformation[4] = yaw;
cameraTransformation[5] = pitch;

float controlIn[3] = {29,2,3};

float target[4] = {300,20,10,5};

float output[3];

TOCC tocc;
tocc.init();
tocc.setCameraModel(cameraModel);
tocc.setCameraTransformation(cameraTransformation);
tocc.set3DPoint1(point3D1);
tocc.set3DPoint2(point3D2);
tocc.setControlTargets(target);
tocc.setControlInput(controlIn);


realTimeLoop{

..........
tocc.setControlInput(controlIn);
tocc.set3DPoint1(point3D1);
tocc.set3DPoint2(point3D2);
tocc.setCameraTransformation(cameraTransformation);

tocc.spin(output);
cameraTransformation[0] = output[1];
cameraTransformation[2] = output[2];
cameraTransformation[4] = output[0];
......................


}

tocc.reset(); //reset the tocc

Created on 2017/11/01 By Zhenyu Yang
================================== */



#include<iostream>
#include <cmath>
#include "TOCC.h"

TrajectoryPlanning tp;
void TOCC::init()
{
	PI =  3.141592653f;  //define pi
	fov = (140.0f/180)*PI; //default field of view

	//PID controllers initialization
	pid_yaw.init();
	pid_yaw.setPID(0.01,0,0);
	pid_phi.init();
	pid_phi.setPID(0.01,0,0);

	//MA filters initialization
	maf_xm.init();
	maf_distX.init();
	maf_distS.init();

	maf_xt.init();
	maf_zt.init();
	maf_x3d.init();
	maf_z3d.init();
	maf_x3d2.init();
	maf_z3d2.init();

	
	maf_xm.setBufferSize(10);
	maf_distX.setBufferSize(10);
	maf_distS.setBufferSize(10);

	maf_xt.setBufferSize(10);
	maf_zt.setBufferSize(10);
	maf_x3d.setBufferSize(10);
	maf_z3d.setBufferSize(10);
	maf_x3d2.setBufferSize(10);
	maf_z3d2.setBufferSize(10);
	//trajectory planning initialization
	tp.init();
}


void TOCC::spin(float *controlOutput)
{
	//this function runs every frame to calculate the next transformation of the camera.
	//assuming the roll, pitch and yt remains zeros. 
	float yaw_control_output = pid_yaw.spin(xm);	
	controlOutput[0] = yaw_control_output;

	getCircle(r);
	float phi = pid_phi.spin (distS);
	//phi -=0.3f;  //offset
	//float r = circle[2];
	//xt = r*cos(phi)+circle[0];
	//zt = r*sin(phi)+circle[1];
	float wapPoint[2];
	tp.getWayPoint(phi,circle,wapPoint);	
	controlOutput[1] = wapPoint[0];
	controlOutput[2] = wapPoint[1];
}


void TOCC::setCameraModel(float model[])
{
	fov = model[4];
	resWidth = model[5];        	
	tp.setScreenWidth(resWidth);
	tp.setFov(fov);
}



void TOCC::setCameraTransformation(float data[])
{
	xt = maf_xt.put(data[0]);
	yt =  (data[1]);
	zt =  maf_zt.put(data[2]);
	roll =  (data[3]);
	yaw =  (data[4]);
	pitch =  (data[5]);

	tp.setCameraTransformation(data);
}

void TOCC::set3DPoints(float data[])
{
	x3d = maf_xt.put(data[0]);
	y3d = (data[1]);
	z3d = maf_z3d.put(data[2]);

	x3d1 = maf_x3d.put(data[3]);
	y3d1 = (data[4]);
	z3d1 = maf_z3d.put(data[5]);

	tp.set3DPoints(data);
}

void TOCC::set3DPoint1(float data[])
{
	x3d = data[0];
	y3d = data[1];
	z3d = data[2];

	tp.set3DPoint1(data);
}

void TOCC::set3DPoint2(float data[])
{
	x3d1 = data[0];
	y3d1 = data[1];
	z3d1 = data[2];

	tp.set3DPoint2(data);
}

void TOCC::setControlInput(float data[])
{
	xm = maf_xm.put(data[0]);
	distX = maf_distX.put(data[1]);
	distS = maf_distS.put(data[2]);
}

void TOCC::setControlTargets(float data[])
{
	xm_target = data[0];
	distX_target = data[1];
	distS_target = data[2];
	r = data[3];  

	pid_yaw.setTarget(xm_target);
	pid_phi.setTarget(distS_target);

	tp.setDistXTarget(distX_target);
}



void TOCC::getCircle(float r){
	Point2D pp1;
	Point2D pp2;
	Point2D cam;
	Circle c;

	pp1.x = x3d;
	pp1.y = z3d;

	pp2.x = x3d1;
	pp2.y = z3d1;

	cam.x = xt;
	cam.y = zt;

	c.r = r;

	float out[2];
	c.getCenter(pp1,pp2,cam,out);
	circle [0] = out[0];
	circle [1] = out[1];
	circle [2] = r;



}



void TOCC::reset()
{

	//PID controllers initialization
	pid_yaw.reset();
	pid_phi.reset();


}

