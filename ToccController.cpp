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

  Created on 2017/11/01 By Zhenyu Yang
  ================================== */



#include<iostream>

#include "PID.cpp"
#include <cmath>

class ToccController
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


	public:
		void init()
		{
			PI =  3.141592653f;  //define pi
			fov = (140.0f/180)*PI; //default field of view


			//PID controllers initialization
			pid_yaw.init();
			pid_yaw.setPID(0.01,0,0);
			pid_phi.init();
			pid_phi.setPID(0.01,0,0);
		}


		void spin(float *controlOutput)
		{
		//this function runs every frame to calculate the next transformation of the camera.
		//assuming the roll, pitch and yt remains zeros. 
			float yaw_control_output = pid_yaw.spin(xm);	
			std::cout<<"yaw out = "<<yaw_control_output<<std::endl;
			controlOutput[0] = yaw_control_output;

			getCircle();
			float phi = pid_phi.spin (distS);
			phi -=0.3f;
			float r = circle[2];
			xt = r*cos(phi)+circle[0];
			zt = r*sin(phi)+circle[1];	
			controlOutput[1] = zt;
			controlOutput[2] = xt;
		}

		void setCameraTransformation(float data[])
		{
			xt = data[0];
			yt =  data[1];
			zt =  data[2];
			roll =  data[3];
			yaw =  data[4];
			pitch =  data[5];
		}

		void set3DPoints(float data[])
		{
			x3d = data[0];
			y3d = data[1];
			z3d = data[2];

			x3d1 = data[3];
			y3d1 = data[4];
			z3d1 = data[5];

		}

		void set3DPoint1(float data[])
		{
			x3d = data[0];
			y3d = data[1];
			z3d = data[2];
		}

		void set3DPoint2(float data[])
		{
			x3d1 = data[0];
			y3d1 = data[1];
			z3d1 = data[2];
		}

		void setControlInput(float data[])
		{
			xm = data[0];
			distX = data[1];
			distS = data[2];
		}

		void setControlTargets(float data[])
		{
			xm_target = data[0];
			distX_target = data[1];
			distS_target = data[2];

			pid_yaw.setTarget(xm_target);
			pid_phi.setTarget(distS_target);
		}



		void getCircle(){

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

		}
};
