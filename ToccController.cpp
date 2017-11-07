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
		float fov;
		float resWidth;
		float resHeight;

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

		float xm_target;
		float distX_target;
		float distS_target;


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
		PID pid_yaw;
		PID pid_phi;

		float circle[3];


	public:
		void init()
		{
			PI =  3.141592653f;
			fov = (140.0f/180)*PI;

			pid_yaw.init();
			pid_yaw.setPID(0.01,0,0);
			pid_phi.init();
			pid_phi.setPID(0.01,0,0);
		}


		void spin(float *controlOutput)
		{
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

			//float circle[3];

			//get the circle
			float d = std::abs(distS_target);
			float w = resWidth;
			float alpha = 2*atan((d/w)*tan(fov/2));

			float distance = sqrt((red_x_3d-blue_x_3d)*(red_x_3d-blue_x_3d)+(red_y_3d-blue_y_3d)*(red_y_3d-blue_y_3d));
			float r = (distance/2)/sin(alpha);//radius

			float h = (distance/2)/tan(alpha);
			float beta = ((PI / 2 - atan ((blue_y_3d - red_y_3d) / (blue_x_3d - red_x_3d))));

			//print ("r = " + r+", h = "+h);
			//print ("beta = " + beta);

			float delta_x = h*cos(beta);
			float delta_y = h*sin(beta);
			//print ("delta_x = " + delta_x);
			//print ("delta_y = " + delta_y);
			//print ("blue_x_3d = " + blue_x_3d+", red_x_3d = "+red_x_3d);
			float center_x = (blue_x_3d+red_x_3d)/2+delta_x;
			float center_y = (red_y_3d+blue_y_3d)/2-delta_y;
			//print ("center_x = " + center_x);
			//print ("center_y = " + center_y);

			circle [0] = center_x;
			circle [1] = center_y;
			circle [2] = r;

			//return circle;

		}











};
