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
tocc.setCameraTransformation(cameraTransformation);
tocc.set3DPoint1(point3D1);
tocc.set3DPoint2(point3D2);
tocc.setControlTargets(target);
tocc.setControlInput(controlIn);

for(int i = 0; i < 100;i++)
{

controlIn[0] = 29+i*0.05f;
tocc.setControlInput(controlIn);
tocc.set3DPoint1(point3D1);
tocc.set3DPoint2(point3D2);
tocc.setCameraTransformation(cameraTransformation);

tocc.spin(output);
std::cout<<"output[0] = "<<output[0]<<std::endl;
std::cout<<"output[1] = "<<output[1]<<std::endl;
std::cout<<"output[2] = "<<output[2]<<std::endl;
std::cout<<"========================"<<std::endl;
cameraTransformation[0] = output[1];
cameraTransformation[2] = output[2];
cameraTransformation[4] = output[0];


tocc.reset(); //reset the tocc

}


Created on 2017/11/01 By Zhenyu Yang
================================== */



#include<iostream>
#include "toric/Circle.cpp"
#include "filters/MAFilter.cpp"
#include <cmath>
#include "TOCC.h"
void TOCC::init()
{
	PI =  3.141592653f;  //define pi
	fov = (140.0f/180)*PI; //default field of view

	//PID controllers initialization
	pid_yaw.init();
	pid_yaw.setPID(0.01,0,0);
	pid_phi.init();
	pid_phi.setPID(0.01,0,0);
}


void TOCC::spin(float *controlOutput)
{
	//this function runs every frame to calculate the next transformation of the camera.
	//assuming the roll, pitch and yt remains zeros. 
	float yaw_control_output = pid_yaw.spin(xm);	
	std::cout<<"yaw out = "<<yaw_control_output<<std::endl;
	controlOutput[0] = yaw_control_output;

	getCircle(r);
	float phi = pid_phi.spin (distS);
	phi -=0.3f;
	float r = circle[2];
	xt = r*cos(phi)+circle[0];
	zt = r*sin(phi)+circle[1];	
	controlOutput[1] = zt;
	controlOutput[2] = xt;
}

void TOCC::setCameraTransformation(float data[])
{
	xt = data[0];
	yt =  data[1];
	zt =  data[2];
	roll =  data[3];
	yaw =  data[4];
	pitch =  data[5];
}

void TOCC::set3DPoints(float data[])
{
	x3d = data[0];
	y3d = data[1];
	z3d = data[2];

	x3d1 = data[3];
	y3d1 = data[4];
	z3d1 = data[5];

}

void TOCC::set3DPoint1(float data[])
{
	x3d = data[0];
	y3d = data[1];
	z3d = data[2];
}

void TOCC::set3DPoint2(float data[])
{
	x3d1 = data[0];
	y3d1 = data[1];
	z3d1 = data[2];
}

void TOCC::setControlInput(float data[])
{
	xm = data[0];
	distX = data[1];
	distS = data[2];
}

void TOCC::setControlTargets(float data[])
{
	xm_target = data[0];
	distX_target = data[1];
	distS_target = data[2];
	r = data[3];  

	pid_yaw.setTarget(xm_target);
	pid_phi.setTarget(distS_target);
}



void TOCC::getCircle(float r){
	/*
	   float red_x_3d = x3d;
	   float red_y_3d = z3d;
	   float blue_x_3d = x3d1;
	   float blue_y_3d = z3d1;

	//get the circle
	float d = std::abs(distS_target);
	float w = resWidth;
	float alpha = 2*atan((d/w)*tan(fov/2));

	float distance = sqrt((red_x_3d-blue_x_3d)*(red_x_3d-blue_x_3d)+(red_y_3d-blue_y_3d)*(red_y_3d-blue_y_3d));
	float r = (distance/2)/sin(alpha);//radius

	float h = (distance/2)/tan(alpha);
	float beta = ((PI / 2 - atan ((blue_y_3d - red_y_3d) / (blue_x_3d - red_x_3d))));

	float delta_x = h*cos(beta);
	float delta_y = h*sin(beta);
	float center_x = (blue_x_3d+red_x_3d)/2+delta_x;
	float center_y = (red_y_3d+blue_y_3d)/2-delta_y;

	circle [0] = center_x;
	circle [1] = center_y;
	circle [2] = r;
	 */
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

