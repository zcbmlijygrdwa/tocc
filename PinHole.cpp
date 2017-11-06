#include <iostream>
#include <math.h>
#include "helpFunctions.h"

class PinHole
{

	public:
		//inputs for camera model
		float x0;
		float y0;
		float fx;
		float fy;
		float K_size;

		//inputs for camera translationi
		float xt;
		float yt;
		float zt;
		float roll;
		float yaw;
		float pitch;

		//inputs for 2 3D points
		float x3d;
		float y3d;
		float z3d;
		float x3d2;
		float y3d2;
		float z3d2;

		//2D points
		float x2d1;
		float y2d1;
		float x2d2;
		float y2d2;

	public:

		PinHole()
		{


			/*
			//default inputs for camera model
			x0 = 0;
			y0 = 0;
			fx = 5.0/10000;
			fy = fx;
			K_size = 1.0f;
			//default inputs for camera translationi
			xt = 0;
			yt = 0;
			zt = 0;
			roll = 0;
			yaw = 0;
			pitch = 0;


			//default inputs for 2 3D points
			x3d = -55;
			y3d = 0;
			z3d = 10;
			x3d2 = 5;
			y3d2 = 0;
			z3d2 = 10;

			 */		}

		//sets
		void setCameraModel(float model[])
		{
			x0 = model[0];
			y0 = model[1];
			fx = model[2];
			fy = model[3];
		}

		void setCameraModel_x0(float data)
		{
			x0 = data;
		}

		void setCameraModel_y0(float data)
		{
			y0 = data;
		}

		void setCameraModel_fx(float data)
		{
			fx = data;
		}

		void setCameraModel_fy(float data)
		{
			fy = data;
		}



		void set3DPoint1(float x, float y, float z)
		{
			x3d = x;
			y3d = y;
			z3d =z;
		}

		void set3DPoint2(float x, float y, float z)
		{
			x3d2 = x;
			y3d2 = y;
			z3d2 = z;
		}


		void set3DPoint1(float data[])
		{
			x3d = data[0];
			y3d = data[1];
			z3d = data[2];
		}

		void set3DPoint2(float data[])
		{
			x3d2 = data[0];
			y3d2 = data[1];
			z3d2 = data[2];
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

		void getResults(float *data)
		{
			data[0] = x2d1;
			data[1] = y2d1;
			data[2] = x2d2;
			data[3] = y2d2;

		}



		void compute()
		{
			x2d1 = (fx*xt + x0*zt + x3d*(fx*cos(yaw) - x0*sin(yaw)) + z3d*(fx*sin(yaw) + x0*cos(yaw)))/(zt + z3d*cos(yaw) - x3d*sin(yaw));

			y2d1 = (fy*y3d + fy*yt + y0*zt + y0*z3d*cos(yaw) - x3d*y0*sin(yaw))/(zt + z3d*cos(yaw) - x3d*sin(yaw));

			x2d2 = (fx*xt + x0*zt + x3d2*(fx*cos(yaw) - x0*sin(yaw)) + z3d2*(fx*sin(yaw) + x0*cos(yaw)))/(zt + z3d2*cos(yaw) - x3d2*sin(yaw));

			y2d2 = (fy*y3d2 + fy*yt + y0*zt + y0*z3d2*cos(yaw) - x3d2*y0*sin(yaw))/(zt + z3d2*cos(yaw) - x3d2*sin(yaw));


//			std::cout<<"Computing pinhole done!"<<std::endl;




		}


};
