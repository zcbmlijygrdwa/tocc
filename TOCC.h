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
#include "basicController/PID.h"
#include "toric/Circle.h"
#include "filters/MAFilter.h"
#include "trajectory/TrajectoryPlanning.h"
#include <cmath>

class TOCC
{

	public:
		//==========================
		//      constants
		//=========================

		float PI;

		//==========================
		//      camera parameters
		//=========================

		//location of the camera
		float xt;
		float yt;
		float zt;

		//rotation of the camera
		float roll;
		float yaw;
		float pitch;

		//optic  parameters
		float fov;   //horizontal field of view
		float resWidth; //screen size, width
		float resHeight;//screen size, height

		//===================================
		//      on-screen objects parameters
		//===================================

		float x2d;
		float y2d;

		float x2d1;
		float y2d1;

		float xm;
		float distX;
		float distS;

		float xm_target;	//desired screen location of the center of two objects, in x direction
		float distX_target;	//desired screen distance between two objects, in x direction
		float distS_target;	//desired screen size difference(in pixels) between two objects.


		//===================================
		//      3D objects parameters
		//===================================

		float x3d;
		float y3d;
		float z3d;

		float x3d1;
		float y3d1;
		float z3d1;

		//===================================
		//      PID controllers
		//===================================
		PID pid_yaw;	//control camera yaw
		PID pid_phi;	//control the phi angle in the toric circle

		float circle[3];//the cirle on the toric parallel wiith the ground
		float r;  //the radius of the toric circle


		//===================================
		//      MA filters
		//===================================

		MAFilter maf_xm;
		MAFilter maf_distX;
		MAFilter maf_distS;
		
		MAFilter maf_xt;
		MAFilter maf_zt;
		MAFilter maf_x3d;
		MAFilter maf_z3d;
		MAFilter maf_x3d2;
		MAFilter maf_z3d2;

	public:
		void init();
		void spin(float *controlOutput);
		void setCameraModel(float data[]);
		void setCameraTransformation(float data[]);
		void set3DPoints(float data[]);
		void set3DPoint1(float data[]);
		void set3DPoint2(float data[]);
		void setControlInput(float data[]);
		void setControlTargets(float data[]);
		void getCircle(float r);
		void reset();
};

