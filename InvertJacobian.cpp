#include <iostream>
#include <math.h>
#include "helpFunctions.h"

class InvertJacobian
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
		float jacobian_1_1;
		float jacobian_1_2;
		float jacobian_1_3;
		float jacobian_2_1;
		float jacobian_2_2;
		float jacobian_2_3;
		float jacobian_3_1;
		float jacobian_3_2;
		float jacobian_3_3;
	public:

		InvertJacobian()
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

		void setK_size(float data)
		{
			K_size = data;
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
			data[0] = jacobian_1_1;
			data[1] = jacobian_1_2;
			data[2] = jacobian_1_3;

			data[3] = jacobian_2_1;
			data[4] = jacobian_2_2;
			data[5] = jacobian_2_3;

			data[6] = jacobian_3_1;
			data[7] = jacobian_3_2;
			data[8] = jacobian_3_3;

		}

		void displayJacobian()
		{
			std::cout<<"jacobian_1_1 = "<<jacobian_1_1<<std::endl;
			std::cout<<"jacobian_1_2 = "<<jacobian_1_1<<std::endl;
			std::cout<<"jacobian_1_3 = "<<jacobian_1_1<<std::endl;
			std::cout<<"jacobian_2_1 = "<<jacobian_2_1<<std::endl;
			std::cout<<"jacobian_2_2 = "<<jacobian_2_2<<std::endl;
			std::cout<<"jacobian_2_3 = "<<jacobian_2_3<<std::endl;
			std::cout<<"jacobian_3_1 = "<<jacobian_3_1<<std::endl;
			std::cout<<"jacobian_3_2 = "<<jacobian_3_2<<std::endl;
			std::cout<<"jacobian_3_3 = "<<jacobian_3_3<<std::endl;


		}


		float power2(float x)
		{
			return x*x;
		}

		float power3(float x)
		{
			return x*x*x;
		}

		int compute()
		{
			//std::cout<<"Computing invert jacobian...."<<std::endl;
			//std::cout<<"xt = "<<xt<<", yt = "<<yt<<", zt = "<<zt<<std::endl;
			//std::cout<<"roll = "<<roll<<", yaw = "<<yaw<<", pitch = "<<pitch<<std::endl;

			float x3d_s = power2(x3d);
			float y3d_s = power2(y3d);
			float z3d_s = power2(z3d);

			float x3d2_s = power2(x3d2);
			float y3d2_s = power2(y3d2);
			float z3d2_s = power2(z3d2);

			float xt_s = power2(xt);
			float yt_s = power2(yt);
			float zt_s = power2(zt);

			float x3d_c = power3(x3d);
			float y3d_c = power3(y3d);
			float z3d_c = power3(z3d);

			float x3d2_c = power3(x3d2);
			float y3d2_c = power3(y3d2);
			float z3d2_c = power3(z3d2);

			float xt_c = power3(xt);
			float yt_c = power3(yt);
			float zt_c = power3(zt);

			float sin_yaw_s = power2(sin(yaw));
			float cos_yaw_s= power2(cos(yaw));
			float sin_yaw_c= power3(sin(yaw));
			float cos_yaw_c= power3(cos(yaw));
			
/*
			   std::cout<<"x3d_s = "<<x3d_s<<std::endl;
			   std::cout<<"y3d_s = "<<y3d_s<<std::endl;
			   std::cout<<"z3d_s = "<<z3d_s<<std::endl;
			   std::cout<<"x3d2_s = "<<x3d2_s<<std::endl;
			   std::cout<<"y3d2_s = "<<y3d2_s<<std::endl;
			   std::cout<<"z3d2_s = "<<z3d2_s<<std::endl;
			   std::cout<<"xt_s = "<<xt_s<<std::endl;
			   std::cout<<"yt_s = "<<yt_s<<std::endl;
			   std::cout<<"zt_s = "<<zt_s<<std::endl;


			   std::cout<<"x3d_c = "<<x3d_c<<std::endl;
			   std::cout<<"y3d_c = "<<y3d_c<<std::endl;
			   std::cout<<"z3d_c = "<<z3d_c<<std::endl;
			   std::cout<<"x3d2_c = "<<x3d2_c<<std::endl;
			   std::cout<<"y3d2_c = "<<y3d2_c<<std::endl;
			   std::cout<<"z3d2_c = "<<z3d2_c<<std::endl;
			   std::cout<<"xt_c = "<<xt_c<<std::endl;
			   std::cout<<"yt_c = "<<yt_c<<std::endl;
			   std::cout<<"zt_c = "<<zt_c<<std::endl;

			   std::cout<<"sin_yaw_s = "<<sin_yaw_s<<std::endl;
			   std::cout<<"cos_yaw_s = "<<cos_yaw_s<<std::endl;
			   std::cout<<"sin_yaw_c = "<<sin_yaw_c<<std::endl;
			   std::cout<<"cos_yaw_c = "<<cos_yaw_c<<std::endl;
			 */



			jacobian_1_1 = -((z3d - z3d2)*(x3d_s*z3d2_s - x3d2_s*z3d_s - x3d_s*zt_s + x3d2_s*zt_s - z3d_s*zt_s + z3d2_s*zt_s - z3d*zt_c*cos(yaw) + z3d2*zt_c*cos(yaw) + x3d*zt_c*sin(yaw) - x3d2*zt_c*sin(yaw) - 2*cos_yaw_s*x3d_s*z3d2_s + 2*cos_yaw_s*x3d2_s*z3d_s - x3d*x3d2_s*z3d*sin(2*yaw) + x3d2*x3d_s*z3d2*sin(2*yaw) - x3d*z3d*z3d2_s*sin(2*yaw) + x3d2*z3d2*z3d_s*sin(2*yaw) + cos_yaw_c*x3d*x3d2_s*xt - cos_yaw_c*x3d2*x3d_s*xt - cos_yaw_c*x3d*xt*z3d2_s + cos_yaw_c*x3d2*xt*z3d_s - cos_yaw_c*x3d_s*z3d2*zt + cos_yaw_c*x3d2_s*z3d*zt - cos_yaw_c*z3d*z3d2_s*zt + cos_yaw_c*z3d2*z3d_s*zt + sin_yaw_c*x3d*x3d2_s*zt - sin_yaw_c*x3d2*x3d_s*zt + sin_yaw_c*x3d_s*xt*z3d2 - sin_yaw_c*x3d2_s*xt*z3d - sin_yaw_c*x3d*z3d2_s*zt + sin_yaw_c*x3d2*z3d_s*zt + sin_yaw_c*xt*z3d*z3d2_s - sin_yaw_c*xt*z3d2*z3d_s - 2*x3d*xt*z3d2*zt + 2*x3d2*xt*z3d*zt - x3d*x3d2_s*xt*cos(yaw) + x3d2*x3d_s*xt*cos(yaw) - x3d*xt*zt_s*cos(yaw) + x3d2*xt*zt_s*cos(yaw) - x3d_s*z3d2*zt*cos(yaw) + x3d2_s*z3d*zt*cos(yaw) + 2*z3d*z3d2_s*zt*cos(yaw) - 2*z3d2*z3d_s*zt*cos(yaw) - 2*x3d*x3d2_s*zt*sin(yaw) + 2*x3d2*x3d_s*zt*sin(yaw) - x3d*z3d2_s*zt*sin(yaw) + x3d2*z3d_s*zt*sin(yaw) - xt*z3d*z3d2_s*sin(yaw) + xt*z3d2*z3d_s*sin(yaw) - xt*z3d*zt_s*sin(yaw) + xt*z3d2*zt_s*sin(yaw) + 2*x3d*x3d2*z3d*zt*cos(yaw) - 2*x3d*xt*z3d*z3d2*cos(yaw) - 2*x3d*x3d2*z3d2*zt*cos(yaw) + 2*x3d2*xt*z3d*z3d2*cos(yaw) - 2*x3d*x3d2*xt*z3d*sin(yaw) + 2*x3d*x3d2*xt*z3d2*sin(yaw) - 2*x3d*z3d*z3d2*zt*sin(yaw) + 2*x3d2*z3d*z3d2*zt*sin(yaw) - 2*cos_yaw_c*x3d*x3d2*z3d*zt + 2*cos_yaw_c*x3d*xt*z3d*z3d2 + 2*cos_yaw_c*x3d*x3d2*z3d2*zt - 2*cos_yaw_c*x3d2*xt*z3d*z3d2 + 2*sin_yaw_c*x3d*x3d2*xt*z3d - 2*sin_yaw_c*x3d*x3d2*xt*z3d2 + 2*sin_yaw_c*x3d*z3d*z3d2*zt - 2*sin_yaw_c*x3d2*z3d*z3d2*zt))/(fx*(x3d_c*xt + x3d2_c*xt + z3d_c*zt + z3d2_c*zt + x3d*x3d2_c*cos(yaw) + x3d2*x3d_c*cos(yaw) - 2*x3d_s*x3d2_s*cos(yaw) + x3d_s*xt_s*cos(yaw) + x3d2_s*xt_s*cos(yaw) - 2*x3d_s*z3d2_s*cos(yaw) - 2*x3d2_s*z3d_s*cos(yaw) + z3d*z3d2_c*cos(yaw) + z3d2*z3d_c*cos(yaw) - 2*z3d_s*z3d2_s*cos(yaw) + z3d_s*zt_s*cos(yaw) + z3d2_s*zt_s*cos(yaw) - x3d*z3d2_c*sin(yaw) - x3d2*z3d_c*sin(yaw) + x3d_c*z3d2*sin(yaw) + x3d2_c*z3d*sin(yaw) - x3d*x3d2_s*xt - x3d2*x3d_s*xt + x3d*xt*z3d_s - 2*x3d*xt*z3d2_s - 2*x3d2*xt*z3d_s + x3d2*xt*z3d2_s + x3d_s*z3d*zt - 2*x3d_s*z3d2*zt - 2*x3d2_s*z3d*zt + x3d2_s*z3d2*zt - z3d*z3d2_s*zt - z3d2*z3d_s*zt + x3d*x3d2*z3d*zt + x3d*xt*z3d*z3d2 + x3d*x3d2*z3d2*zt + x3d2*xt*z3d*z3d2 - 2*x3d*x3d2*xt_s*cos(yaw) + x3d*x3d2*z3d_s*cos(yaw) + x3d*x3d2*z3d2_s*cos(yaw) + x3d_s*z3d*z3d2*cos(yaw) + x3d2_s*z3d*z3d2*cos(yaw) - 2*z3d*z3d2*zt_s*cos(yaw) - x3d2*x3d_s*z3d*sin(yaw) - x3d*x3d2_s*z3d2*sin(yaw) + x3d*xt_s*z3d*sin(yaw) - x3d*xt_s*z3d2*sin(yaw) - x3d2*xt_s*z3d*sin(yaw) + x3d2*xt_s*z3d2*sin(yaw) - x3d_s*xt*zt*sin(yaw) - x3d2_s*xt*zt*sin(yaw) + x3d*z3d2*z3d_s*sin(yaw) + x3d2*z3d*z3d2_s*sin(yaw) - x3d*z3d*zt_s*sin(yaw) + x3d*z3d2*zt_s*sin(yaw) + x3d2*z3d*zt_s*sin(yaw) - x3d2*z3d2*zt_s*sin(yaw) + xt*z3d_s*zt*sin(yaw) + xt*z3d2_s*zt*sin(yaw) + 2*x3d*xt*z3d*zt*cos(yaw) - 2*x3d*xt*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*zt*cos(yaw) + 2*x3d2*xt*z3d2*zt*cos(yaw) + 2*x3d*x3d2*xt*zt*sin(yaw) - 2*xt*z3d*z3d2*zt*sin(yaw)));

float test1 = -((z3d - z3d2)*(x3d_s*z3d2_s - x3d2_s*z3d_s - x3d_s*zt_s + x3d2_s*zt_s - z3d_s*zt_s + z3d2_s*zt_s - z3d*zt_c*cos(yaw) + z3d2*zt_c*cos(yaw) + x3d*zt_c*sin(yaw) - x3d2*zt_c*sin(yaw) - 2*cos_yaw_s*x3d_s*z3d2_s + 2*cos_yaw_s*x3d2_s*z3d_s - x3d*x3d2_s*z3d*sin(2*yaw) + x3d2*x3d_s*z3d2*sin(2*yaw) - x3d*z3d*z3d2_s*sin(2*yaw) + x3d2*z3d2*z3d_s*sin(2*yaw) + cos_yaw_c*x3d*x3d2_s*xt - cos_yaw_c*x3d2*x3d_s*xt - cos_yaw_c*x3d*xt*z3d2_s + cos_yaw_c*x3d2*xt*z3d_s - cos_yaw_c*x3d_s*z3d2*zt + cos_yaw_c*x3d2_s*z3d*zt - cos_yaw_c*z3d*z3d2_s*zt + cos_yaw_c*z3d2*z3d_s*zt + sin_yaw_c*x3d*x3d2_s*zt - sin_yaw_c*x3d2*x3d_s*zt + sin_yaw_c*x3d_s*xt*z3d2 - sin_yaw_c*x3d2_s*xt*z3d - sin_yaw_c*x3d*z3d2_s*zt + sin_yaw_c*x3d2*z3d_s*zt + sin_yaw_c*xt*z3d*z3d2_s - sin_yaw_c*xt*z3d2*z3d_s - 2*x3d*xt*z3d2*zt + 2*x3d2*xt*z3d*zt - x3d*x3d2_s*xt*cos(yaw) + x3d2*x3d_s*xt*cos(yaw) - x3d*xt*zt_s*cos(yaw) + x3d2*xt*zt_s*cos(yaw) - x3d_s*z3d2*zt*cos(yaw) + x3d2_s*z3d*zt*cos(yaw) + 2*z3d*z3d2_s*zt*cos(yaw) - 2*z3d2*z3d_s*zt*cos(yaw) - 2*x3d*x3d2_s*zt*sin(yaw) + 2*x3d2*x3d_s*zt*sin(yaw) - x3d*z3d2_s*zt*sin(yaw) + x3d2*z3d_s*zt*sin(yaw) - xt*z3d*z3d2_s*sin(yaw) + xt*z3d2*z3d_s*sin(yaw) - xt*z3d*zt_s*sin(yaw) + xt*z3d2*zt_s*sin(yaw) + 2*x3d*x3d2*z3d*zt*cos(yaw) - 2*x3d*xt*z3d*z3d2*cos(yaw) - 2*x3d*x3d2*z3d2*zt*cos(yaw) + 2*x3d2*xt*z3d*z3d2*cos(yaw) - 2*x3d*x3d2*xt*z3d*sin(yaw) + 2*x3d*x3d2*xt*z3d2*sin(yaw) - 2*x3d*z3d*z3d2*zt*sin(yaw) + 2*x3d2*z3d*z3d2*zt*sin(yaw) - 2*cos_yaw_c*x3d*x3d2*z3d*zt + 2*cos_yaw_c*x3d*xt*z3d*z3d2 + 2*cos_yaw_c*x3d*x3d2*z3d2*zt - 2*cos_yaw_c*x3d2*xt*z3d*z3d2 + 2*sin_yaw_c*x3d*x3d2*xt*z3d - 2*sin_yaw_c*x3d*x3d2*xt*z3d2 + 2*sin_yaw_c*x3d*z3d*z3d2*zt - 2*sin_yaw_c*x3d2*z3d*z3d2*zt));

float test2 = (fx*(x3d_c*xt + x3d2_c*xt + z3d_c*zt + z3d2_c*zt + x3d*x3d2_c*cos(yaw) + x3d2*x3d_c*cos(yaw) - 2*x3d_s*x3d2_s*cos(yaw) + x3d_s*xt_s*cos(yaw) + x3d2_s*xt_s*cos(yaw) - 2*x3d_s*z3d2_s*cos(yaw) - 2*x3d2_s*z3d_s*cos(yaw) + z3d*z3d2_c*cos(yaw) + z3d2*z3d_c*cos(yaw) - 2*z3d_s*z3d2_s*cos(yaw) + z3d_s*zt_s*cos(yaw) + z3d2_s*zt_s*cos(yaw) - x3d*z3d2_c*sin(yaw) - x3d2*z3d_c*sin(yaw) + x3d_c*z3d2*sin(yaw) + x3d2_c*z3d*sin(yaw) - x3d*x3d2_s*xt - x3d2*x3d_s*xt + x3d*xt*z3d_s - 2*x3d*xt*z3d2_s - 2*x3d2*xt*z3d_s + x3d2*xt*z3d2_s + x3d_s*z3d*zt - 2*x3d_s*z3d2*zt - 2*x3d2_s*z3d*zt + x3d2_s*z3d2*zt - z3d*z3d2_s*zt - z3d2*z3d_s*zt + x3d*x3d2*z3d*zt + x3d*xt*z3d*z3d2 + x3d*x3d2*z3d2*zt + x3d2*xt*z3d*z3d2 - 2*x3d*x3d2*xt_s*cos(yaw) + x3d*x3d2*z3d_s*cos(yaw) + x3d*x3d2*z3d2_s*cos(yaw) + x3d_s*z3d*z3d2*cos(yaw) + x3d2_s*z3d*z3d2*cos(yaw) - 2*z3d*z3d2*zt_s*cos(yaw) - x3d2*x3d_s*z3d*sin(yaw) - x3d*x3d2_s*z3d2*sin(yaw) + x3d*xt_s*z3d*sin(yaw) - x3d*xt_s*z3d2*sin(yaw) - x3d2*xt_s*z3d*sin(yaw) + x3d2*xt_s*z3d2*sin(yaw) - x3d_s*xt*zt*sin(yaw) - x3d2_s*xt*zt*sin(yaw) + x3d*z3d2*z3d_s*sin(yaw) + x3d2*z3d*z3d2_s*sin(yaw) - x3d*z3d*zt_s*sin(yaw) + x3d*z3d2*zt_s*sin(yaw) + x3d2*z3d*zt_s*sin(yaw) - x3d2*z3d2*zt_s*sin(yaw) + xt*z3d_s*zt*sin(yaw) + xt*z3d2_s*zt*sin(yaw) + 2*x3d*xt*z3d*zt*cos(yaw) - 2*x3d*xt*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*zt*cos(yaw) + 2*x3d2*xt*z3d2*zt*cos(yaw) + 2*x3d*x3d2*xt*zt*sin(yaw) - 2*xt*z3d*z3d2*zt*sin(yaw)));


			jacobian_1_2 = -((z3d/2 - z3d2/2)*(2*x3d_s*x3d2_s + x3d_s*z3d2_s + x3d2_s*z3d_s + x3d_s*zt_s + x3d2_s*zt_s + z3d_s*zt_s + z3d2_s*zt_s + z3d*zt_c*cos(yaw) + z3d2*zt_c*cos(yaw) - x3d*zt_c*sin(yaw) - x3d2*zt_c*sin(yaw) - 2*cos_yaw_s*x3d_s*x3d2_s + 2*cos_yaw_s*z3d_s*z3d2_s + 4*x3d*x3d2*zt_s - x3d*x3d2_s*z3d*sin(2*yaw) - x3d2*x3d_s*z3d2*sin(2*yaw) - x3d*z3d*z3d2_s*sin(2*yaw) - x3d2*z3d2*z3d_s*sin(2*yaw) - 2*x3d*z3d2*zt_s*sin(2*yaw) - 2*x3d2*z3d*zt_s*sin(2*yaw) - cos_yaw_c*x3d*x3d2_s*xt - cos_yaw_c*x3d2*x3d_s*xt + cos_yaw_c*x3d*xt*z3d2_s + cos_yaw_c*x3d2*xt*z3d_s - 4*cos_yaw_s*x3d*x3d2*zt_s - cos_yaw_c*x3d_s*z3d2*zt - cos_yaw_c*x3d2_s*z3d*zt + cos_yaw_c*z3d*z3d2_s*zt + cos_yaw_c*z3d2*z3d_s*zt + 4*cos_yaw_s*z3d*z3d2*zt_s - sin_yaw_c*x3d*x3d2_s*zt - sin_yaw_c*x3d2*x3d_s*zt + sin_yaw_c*x3d_s*xt*z3d2 + sin_yaw_c*x3d2_s*xt*z3d + sin_yaw_c*x3d*z3d2_s*zt + sin_yaw_c*x3d2*z3d_s*zt - sin_yaw_c*xt*z3d*z3d2_s - sin_yaw_c*xt*z3d2*z3d_s - 2*x3d*xt*z3d2*zt - 2*x3d2*xt*z3d*zt + x3d*x3d2_s*xt*cos(yaw) + x3d2*x3d_s*xt*cos(yaw) + x3d*xt*zt_s*cos(yaw) + x3d2*xt*zt_s*cos(yaw) + 3*x3d_s*z3d2*zt*cos(yaw) + 3*x3d2_s*z3d*zt*cos(yaw) + 2*z3d*z3d2_s*zt*cos(yaw) + 2*z3d2*z3d_s*zt*cos(yaw) - 2*x3d*x3d2_s*zt*sin(yaw) - 2*x3d2*x3d_s*zt*sin(yaw) - 3*x3d*z3d2_s*zt*sin(yaw) - 3*x3d2*z3d_s*zt*sin(yaw) + xt*z3d*z3d2_s*sin(yaw) + xt*z3d2*z3d_s*sin(yaw) + xt*z3d*zt_s*sin(yaw) + xt*z3d2*zt_s*sin(yaw) + 2*x3d*x3d2*z3d*zt*cos(yaw) - 2*x3d*xt*z3d*z3d2*cos(yaw) + 2*x3d*x3d2*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*z3d2*cos(yaw) - 2*x3d*x3d2*xt*z3d*sin(yaw) - 2*x3d*x3d2*xt*z3d2*sin(yaw) - 2*x3d*z3d*z3d2*zt*sin(yaw) - 2*x3d2*z3d*z3d2*zt*sin(yaw) - 2*x3d*x3d2*xt*zt*sin(2*yaw) + 2*xt*z3d*z3d2*zt*sin(2*yaw) - 2*cos_yaw_c*x3d*x3d2*z3d*zt + 2*cos_yaw_c*x3d*xt*z3d*z3d2 - 2*cos_yaw_c*x3d*x3d2*z3d2*zt + 2*cos_yaw_c*x3d2*xt*z3d*z3d2 + 4*cos_yaw_s*x3d*xt*z3d2*zt + 4*cos_yaw_s*x3d2*xt*z3d*zt + 2*sin_yaw_c*x3d*x3d2*xt*z3d + 2*sin_yaw_c*x3d*x3d2*xt*z3d2 + 2*sin_yaw_c*x3d*z3d*z3d2*zt + 2*sin_yaw_c*x3d2*z3d*z3d2*zt))/(fx*(x3d_c*xt + x3d2_c*xt + z3d_c*zt + z3d2_c*zt + x3d*x3d2_c*cos(yaw) + x3d2*x3d_c*cos(yaw) - 2*x3d_s*x3d2_s*cos(yaw) + x3d_s*xt_s*cos(yaw) + x3d2_s*xt_s*cos(yaw) - 2*x3d_s*z3d2_s*cos(yaw) - 2*x3d2_s*z3d_s*cos(yaw) + z3d*z3d2_c*cos(yaw) + z3d2*z3d_c*cos(yaw) - 2*z3d_s*z3d2_s*cos(yaw) + z3d_s*zt_s*cos(yaw) + z3d2_s*zt_s*cos(yaw) - x3d*z3d2_c*sin(yaw) - x3d2*z3d_c*sin(yaw) + x3d_c*z3d2*sin(yaw) + x3d2_c*z3d*sin(yaw) - x3d*x3d2_s*xt - x3d2*x3d_s*xt + x3d*xt*z3d_s - 2*x3d*xt*z3d2_s - 2*x3d2*xt*z3d_s + x3d2*xt*z3d2_s + x3d_s*z3d*zt - 2*x3d_s*z3d2*zt - 2*x3d2_s*z3d*zt + x3d2_s*z3d2*zt - z3d*z3d2_s*zt - z3d2*z3d_s*zt + x3d*x3d2*z3d*zt + x3d*xt*z3d*z3d2 + x3d*x3d2*z3d2*zt + x3d2*xt*z3d*z3d2 - 2*x3d*x3d2*xt_s*cos(yaw) + x3d*x3d2*z3d_s*cos(yaw) + x3d*x3d2*z3d2_s*cos(yaw) + x3d_s*z3d*z3d2*cos(yaw) + x3d2_s*z3d*z3d2*cos(yaw) - 2*z3d*z3d2*zt_s*cos(yaw) - x3d2*x3d_s*z3d*sin(yaw) - x3d*x3d2_s*z3d2*sin(yaw) + x3d*xt_s*z3d*sin(yaw) - x3d*xt_s*z3d2*sin(yaw) - x3d2*xt_s*z3d*sin(yaw) + x3d2*xt_s*z3d2*sin(yaw) - x3d_s*xt*zt*sin(yaw) - x3d2_s*xt*zt*sin(yaw) + x3d*z3d2*z3d_s*sin(yaw) + x3d2*z3d*z3d2_s*sin(yaw) - x3d*z3d*zt_s*sin(yaw) + x3d*z3d2*zt_s*sin(yaw) + x3d2*z3d*zt_s*sin(yaw) - x3d2*z3d2*zt_s*sin(yaw) + xt*z3d_s*zt*sin(yaw) + xt*z3d2_s*zt*sin(yaw) + 2*x3d*xt*z3d*zt*cos(yaw) - 2*x3d*xt*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*zt*cos(yaw) + 2*x3d2*xt*z3d2*zt*cos(yaw) + 2*x3d*x3d2*xt*zt*sin(yaw) - 2*xt*z3d*z3d2*zt*sin(yaw)));

float test3 = -((z3d/2 - z3d2/2)*(2*x3d_s*x3d2_s + x3d_s*z3d2_s + x3d2_s*z3d_s + x3d_s*zt_s + x3d2_s*zt_s + z3d_s*zt_s + z3d2_s*zt_s + z3d*zt_c*cos(yaw) + z3d2*zt_c*cos(yaw) - x3d*zt_c*sin(yaw) - x3d2*zt_c*sin(yaw) - 2*cos_yaw_s*x3d_s*x3d2_s + 2*cos_yaw_s*z3d_s*z3d2_s + 4*x3d*x3d2*zt_s - x3d*x3d2_s*z3d*sin(2*yaw) - x3d2*x3d_s*z3d2*sin(2*yaw) - x3d*z3d*z3d2_s*sin(2*yaw) - x3d2*z3d2*z3d_s*sin(2*yaw) - 2*x3d*z3d2*zt_s*sin(2*yaw) - 2*x3d2*z3d*zt_s*sin(2*yaw) - cos_yaw_c*x3d*x3d2_s*xt - cos_yaw_c*x3d2*x3d_s*xt + cos_yaw_c*x3d*xt*z3d2_s + cos_yaw_c*x3d2*xt*z3d_s - 4*cos_yaw_s*x3d*x3d2*zt_s - cos_yaw_c*x3d_s*z3d2*zt - cos_yaw_c*x3d2_s*z3d*zt + cos_yaw_c*z3d*z3d2_s*zt + cos_yaw_c*z3d2*z3d_s*zt + 4*cos_yaw_s*z3d*z3d2*zt_s - sin_yaw_c*x3d*x3d2_s*zt - sin_yaw_c*x3d2*x3d_s*zt + sin_yaw_c*x3d_s*xt*z3d2 + sin_yaw_c*x3d2_s*xt*z3d + sin_yaw_c*x3d*z3d2_s*zt + sin_yaw_c*x3d2*z3d_s*zt - sin_yaw_c*xt*z3d*z3d2_s - sin_yaw_c*xt*z3d2*z3d_s - 2*x3d*xt*z3d2*zt - 2*x3d2*xt*z3d*zt + x3d*x3d2_s*xt*cos(yaw) + x3d2*x3d_s*xt*cos(yaw) + x3d*xt*zt_s*cos(yaw) + x3d2*xt*zt_s*cos(yaw) + 3*x3d_s*z3d2*zt*cos(yaw) + 3*x3d2_s*z3d*zt*cos(yaw) + 2*z3d*z3d2_s*zt*cos(yaw) + 2*z3d2*z3d_s*zt*cos(yaw) - 2*x3d*x3d2_s*zt*sin(yaw) - 2*x3d2*x3d_s*zt*sin(yaw) - 3*x3d*z3d2_s*zt*sin(yaw) - 3*x3d2*z3d_s*zt*sin(yaw) + xt*z3d*z3d2_s*sin(yaw) + xt*z3d2*z3d_s*sin(yaw) + xt*z3d*zt_s*sin(yaw) + xt*z3d2*zt_s*sin(yaw) + 2*x3d*x3d2*z3d*zt*cos(yaw) - 2*x3d*xt*z3d*z3d2*cos(yaw) + 2*x3d*x3d2*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*z3d2*cos(yaw) - 2*x3d*x3d2*xt*z3d*sin(yaw) - 2*x3d*x3d2*xt*z3d2*sin(yaw) - 2*x3d*z3d*z3d2*zt*sin(yaw) - 2*x3d2*z3d*z3d2*zt*sin(yaw) - 2*x3d*x3d2*xt*zt*sin(2*yaw) + 2*xt*z3d*z3d2*zt*sin(2*yaw) - 2*cos_yaw_c*x3d*x3d2*z3d*zt + 2*cos_yaw_c*x3d*xt*z3d*z3d2 - 2*cos_yaw_c*x3d*x3d2*z3d2*zt + 2*cos_yaw_c*x3d2*xt*z3d*z3d2 + 4*cos_yaw_s*x3d*xt*z3d2*zt + 4*cos_yaw_s*x3d2*xt*z3d*zt + 2*sin_yaw_c*x3d*x3d2*xt*z3d + 2*sin_yaw_c*x3d*x3d2*xt*z3d2 + 2*sin_yaw_c*x3d*z3d*z3d2*zt + 2*sin_yaw_c*x3d2*z3d*z3d2*zt));

float test4  =(fx*(x3d_c*xt + x3d2_c*xt + z3d_c*zt + z3d2_c*zt + x3d*x3d2_c*cos(yaw) + x3d2*x3d_c*cos(yaw) - 2*x3d_s*x3d2_s*cos(yaw) + x3d_s*xt_s*cos(yaw) + x3d2_s*xt_s*cos(yaw) - 2*x3d_s*z3d2_s*cos(yaw) - 2*x3d2_s*z3d_s*cos(yaw) + z3d*z3d2_c*cos(yaw) + z3d2*z3d_c*cos(yaw) - 2*z3d_s*z3d2_s*cos(yaw) + z3d_s*zt_s*cos(yaw) + z3d2_s*zt_s*cos(yaw) - x3d*z3d2_c*sin(yaw) - x3d2*z3d_c*sin(yaw) + x3d_c*z3d2*sin(yaw) + x3d2_c*z3d*sin(yaw) - x3d*x3d2_s*xt - x3d2*x3d_s*xt + x3d*xt*z3d_s - 2*x3d*xt*z3d2_s - 2*x3d2*xt*z3d_s + x3d2*xt*z3d2_s + x3d_s*z3d*zt - 2*x3d_s*z3d2*zt - 2*x3d2_s*z3d*zt + x3d2_s*z3d2*zt - z3d*z3d2_s*zt - z3d2*z3d_s*zt + x3d*x3d2*z3d*zt + x3d*xt*z3d*z3d2 + x3d*x3d2*z3d2*zt + x3d2*xt*z3d*z3d2 - 2*x3d*x3d2*xt_s*cos(yaw) + x3d*x3d2*z3d_s*cos(yaw) + x3d*x3d2*z3d2_s*cos(yaw) + x3d_s*z3d*z3d2*cos(yaw) + x3d2_s*z3d*z3d2*cos(yaw) - 2*z3d*z3d2*zt_s*cos(yaw) - x3d2*x3d_s*z3d*sin(yaw) - x3d*x3d2_s*z3d2*sin(yaw) + x3d*xt_s*z3d*sin(yaw) - x3d*xt_s*z3d2*sin(yaw) - x3d2*xt_s*z3d*sin(yaw) + x3d2*xt_s*z3d2*sin(yaw) - x3d_s*xt*zt*sin(yaw) - x3d2_s*xt*zt*sin(yaw) + x3d*z3d2*z3d_s*sin(yaw) + x3d2*z3d*z3d2_s*sin(yaw) - x3d*z3d*zt_s*sin(yaw) + x3d*z3d2*zt_s*sin(yaw) + x3d2*z3d*zt_s*sin(yaw) - x3d2*z3d2*zt_s*sin(yaw) + xt*z3d_s*zt*sin(yaw) + xt*z3d2_s*zt*sin(yaw) + 2*x3d*xt*z3d*zt*cos(yaw) - 2*x3d*xt*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*zt*cos(yaw) + 2*x3d2*xt*z3d2*zt*cos(yaw) + 2*x3d*x3d2*xt*zt*sin(yaw) - 2*xt*z3d*z3d2*zt*sin(yaw)));


			jacobian_1_3 = -(x3d_s*xt - x3d2_s*xt + xt*z3d_s - xt*z3d2_s - x3d*x3d2_s*cos(yaw) + x3d2*x3d_s*cos(yaw) + x3d*xt_s*cos(yaw) - x3d2*xt_s*cos(yaw) - x3d*z3d2_s*cos(yaw) + x3d2*z3d_s*cos(yaw) + x3d_s*z3d2*sin(yaw) - x3d2_s*z3d*sin(yaw) + xt_s*z3d*sin(yaw) - xt_s*z3d2*sin(yaw) - z3d*z3d2_s*sin(yaw) + z3d2*z3d_s*sin(yaw) - x3d*z3d2*zt + x3d2*z3d*zt + xt*z3d*zt*cos(yaw) - xt*z3d2*zt*cos(yaw) - x3d*xt*zt*sin(yaw) + x3d2*xt*zt*sin(yaw))/(2*K_size*(x3d_c*xt + x3d2_c*xt + z3d_c*zt + z3d2_c*zt + x3d*x3d2_c*cos(yaw) + x3d2*x3d_c*cos(yaw) - 2*x3d_s*x3d2_s*cos(yaw) + x3d_s*xt_s*cos(yaw) + x3d2_s*xt_s*cos(yaw) - 2*x3d_s*z3d2_s*cos(yaw) - 2*x3d2_s*z3d_s*cos(yaw) + z3d*z3d2_c*cos(yaw) + z3d2*z3d_c*cos(yaw) - 2*z3d_s*z3d2_s*cos(yaw) + z3d_s*zt_s*cos(yaw) + z3d2_s*zt_s*cos(yaw) - x3d*z3d2_c*sin(yaw) - x3d2*z3d_c*sin(yaw) + x3d_c*z3d2*sin(yaw) + x3d2_c*z3d*sin(yaw) - x3d*x3d2_s*xt - x3d2*x3d_s*xt + x3d*xt*z3d_s - 2*x3d*xt*z3d2_s - 2*x3d2*xt*z3d_s + x3d2*xt*z3d2_s + x3d_s*z3d*zt - 2*x3d_s*z3d2*zt - 2*x3d2_s*z3d*zt + x3d2_s*z3d2*zt - z3d*z3d2_s*zt - z3d2*z3d_s*zt + x3d*x3d2*z3d*zt + x3d*xt*z3d*z3d2 + x3d*x3d2*z3d2*zt + x3d2*xt*z3d*z3d2 - 2*x3d*x3d2*xt_s*cos(yaw) + x3d*x3d2*z3d_s*cos(yaw) + x3d*x3d2*z3d2_s*cos(yaw) + x3d_s*z3d*z3d2*cos(yaw) + x3d2_s*z3d*z3d2*cos(yaw) - 2*z3d*z3d2*zt_s*cos(yaw) - x3d2*x3d_s*z3d*sin(yaw) - x3d*x3d2_s*z3d2*sin(yaw) + x3d*xt_s*z3d*sin(yaw) - x3d*xt_s*z3d2*sin(yaw) - x3d2*xt_s*z3d*sin(yaw) + x3d2*xt_s*z3d2*sin(yaw) - x3d_s*xt*zt*sin(yaw) - x3d2_s*xt*zt*sin(yaw) + x3d*z3d2*z3d_s*sin(yaw) + x3d2*z3d*z3d2_s*sin(yaw) - x3d*z3d*zt_s*sin(yaw) + x3d*z3d2*zt_s*sin(yaw) + x3d2*z3d*zt_s*sin(yaw) - x3d2*z3d2*zt_s*sin(yaw) + xt*z3d_s*zt*sin(yaw) + xt*z3d2_s*zt*sin(yaw) + 2*x3d*xt*z3d*zt*cos(yaw) - 2*x3d*xt*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*zt*cos(yaw) + 2*x3d2*xt*z3d2*zt*cos(yaw) + 2*x3d*x3d2*xt*zt*sin(yaw) - 2*xt*z3d*z3d2*zt*sin(yaw)));

float test5 = -(x3d_s*xt - x3d2_s*xt + xt*z3d_s - xt*z3d2_s - x3d*x3d2_s*cos(yaw) + x3d2*x3d_s*cos(yaw) + x3d*xt_s*cos(yaw) - x3d2*xt_s*cos(yaw) - x3d*z3d2_s*cos(yaw) + x3d2*z3d_s*cos(yaw) + x3d_s*z3d2*sin(yaw) - x3d2_s*z3d*sin(yaw) + xt_s*z3d*sin(yaw) - xt_s*z3d2*sin(yaw) - z3d*z3d2_s*sin(yaw) + z3d2*z3d_s*sin(yaw) - x3d*z3d2*zt + x3d2*z3d*zt + xt*z3d*zt*cos(yaw) - xt*z3d2*zt*cos(yaw) - x3d*xt*zt*sin(yaw) + x3d2*xt*zt*sin(yaw))
;

float test6  = (2*K_size*(x3d_c*xt + x3d2_c*xt + z3d_c*zt + z3d2_c*zt + x3d*x3d2_c*cos(yaw) + x3d2*x3d_c*cos(yaw) - 2*x3d_s*x3d2_s*cos(yaw) + x3d_s*xt_s*cos(yaw) + x3d2_s*xt_s*cos(yaw) - 2*x3d_s*z3d2_s*cos(yaw) - 2*x3d2_s*z3d_s*cos(yaw) + z3d*z3d2_c*cos(yaw) + z3d2*z3d_c*cos(yaw) - 2*z3d_s*z3d2_s*cos(yaw) + z3d_s*zt_s*cos(yaw) + z3d2_s*zt_s*cos(yaw) - x3d*z3d2_c*sin(yaw) - x3d2*z3d_c*sin(yaw) + x3d_c*z3d2*sin(yaw) + x3d2_c*z3d*sin(yaw) - x3d*x3d2_s*xt - x3d2*x3d_s*xt + x3d*xt*z3d_s - 2*x3d*xt*z3d2_s - 2*x3d2*xt*z3d_s + x3d2*xt*z3d2_s + x3d_s*z3d*zt - 2*x3d_s*z3d2*zt - 2*x3d2_s*z3d*zt + x3d2_s*z3d2*zt - z3d*z3d2_s*zt - z3d2*z3d_s*zt + x3d*x3d2*z3d*zt + x3d*xt*z3d*z3d2 + x3d*x3d2*z3d2*zt + x3d2*xt*z3d*z3d2 - 2*x3d*x3d2*xt_s*cos(yaw) + x3d*x3d2*z3d_s*cos(yaw) + x3d*x3d2*z3d2_s*cos(yaw) + x3d_s*z3d*z3d2*cos(yaw) + x3d2_s*z3d*z3d2*cos(yaw) - 2*z3d*z3d2*zt_s*cos(yaw) - x3d2*x3d_s*z3d*sin(yaw) - x3d*x3d2_s*z3d2*sin(yaw) + x3d*xt_s*z3d*sin(yaw) - x3d*xt_s*z3d2*sin(yaw) - x3d2*xt_s*z3d*sin(yaw) + x3d2*xt_s*z3d2*sin(yaw) - x3d_s*xt*zt*sin(yaw) - x3d2_s*xt*zt*sin(yaw) + x3d*z3d2*z3d_s*sin(yaw) + x3d2*z3d*z3d2_s*sin(yaw) - x3d*z3d*zt_s*sin(yaw) + x3d*z3d2*zt_s*sin(yaw) + x3d2*z3d*zt_s*sin(yaw) - x3d2*z3d2*zt_s*sin(yaw) + xt*z3d_s*zt*sin(yaw) + xt*z3d2_s*zt*sin(yaw) + 2*x3d*xt*z3d*zt*cos(yaw) - 2*x3d*xt*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*zt*cos(yaw) + 2*x3d2*xt*z3d2*zt*cos(yaw) + 2*x3d*x3d2*xt*zt*sin(yaw) - 2*xt*z3d*z3d2*zt*sin(yaw)));


			jacobian_2_1 = 1.0f*((x3d - x3d2)*(x3d_s*z3d2_s - x3d2_s*z3d_s - x3d_s*zt_s + x3d2_s*zt_s - z3d_s*zt_s + z3d2_s*zt_s - z3d*zt_c*cos(yaw) + z3d2*zt_c*cos(yaw) + x3d*zt_c*sin(yaw) - x3d2*zt_c*sin(yaw) - 2*cos_yaw_s*x3d_s*z3d2_s + 2*cos_yaw_s*x3d2_s*z3d_s - x3d*x3d2_s*z3d*sin(2*yaw) + x3d2*x3d_s*z3d2*sin(2*yaw) - x3d*z3d*z3d2_s*sin(2*yaw) + x3d2*z3d2*z3d_s*sin(2*yaw) + cos_yaw_c*x3d*x3d2_s*xt - cos_yaw_c*x3d2*x3d_s*xt - cos_yaw_c*x3d*xt*z3d2_s + cos_yaw_c*x3d2*xt*z3d_s - cos_yaw_c*x3d_s*z3d2*zt + cos_yaw_c*x3d2_s*z3d*zt - cos_yaw_c*z3d*z3d2_s*zt + cos_yaw_c*z3d2*z3d_s*zt + sin_yaw_c*x3d*x3d2_s*zt - sin_yaw_c*x3d2*x3d_s*zt + sin_yaw_c*x3d_s*xt*z3d2 - sin_yaw_c*x3d2_s*xt*z3d - sin_yaw_c*x3d*z3d2_s*zt + sin_yaw_c*x3d2*z3d_s*zt + sin_yaw_c*xt*z3d*z3d2_s - sin_yaw_c*xt*z3d2*z3d_s - 2*x3d*xt*z3d2*zt + 2*x3d2*xt*z3d*zt - x3d*x3d2_s*xt*cos(yaw) + x3d2*x3d_s*xt*cos(yaw) - x3d*xt*zt_s*cos(yaw) + x3d2*xt*zt_s*cos(yaw) - x3d_s*z3d2*zt*cos(yaw) + x3d2_s*z3d*zt*cos(yaw) + 2*z3d*z3d2_s*zt*cos(yaw) - 2*z3d2*z3d_s*zt*cos(yaw) - 2*x3d*x3d2_s*zt*sin(yaw) + 2*x3d2*x3d_s*zt*sin(yaw) - x3d*z3d2_s*zt*sin(yaw) + x3d2*z3d_s*zt*sin(yaw) - xt*z3d*z3d2_s*sin(yaw) + xt*z3d2*z3d_s*sin(yaw) - xt*z3d*zt_s*sin(yaw) + xt*z3d2*zt_s*sin(yaw) + 2*x3d*x3d2*z3d*zt*cos(yaw) - 2*x3d*xt*z3d*z3d2*cos(yaw) - 2*x3d*x3d2*z3d2*zt*cos(yaw) + 2*x3d2*xt*z3d*z3d2*cos(yaw) - 2*x3d*x3d2*xt*z3d*sin(yaw) + 2*x3d*x3d2*xt*z3d2*sin(yaw) - 2*x3d*z3d*z3d2*zt*sin(yaw) + 2*x3d2*z3d*z3d2*zt*sin(yaw) - 2*cos_yaw_c*x3d*x3d2*z3d*zt + 2*cos_yaw_c*x3d*xt*z3d*z3d2 + 2*cos_yaw_c*x3d*x3d2*z3d2*zt - 2*cos_yaw_c*x3d2*xt*z3d*z3d2 + 2*sin_yaw_c*x3d*x3d2*xt*z3d - 2*sin_yaw_c*x3d*x3d2*xt*z3d2 + 2*sin_yaw_c*x3d*z3d*z3d2*zt - 2*sin_yaw_c*x3d2*z3d*z3d2*zt))/(fx*(x3d_c*xt + x3d2_c*xt + z3d_c*zt + z3d2_c*zt + x3d*x3d2_c*cos(yaw) + x3d2*x3d_c*cos(yaw) - 2*x3d_s*x3d2_s*cos(yaw) + x3d_s*xt_s*cos(yaw) + x3d2_s*xt_s*cos(yaw) - 2*x3d_s*z3d2_s*cos(yaw) - 2*x3d2_s*z3d_s*cos(yaw) + z3d*z3d2_c*cos(yaw) + z3d2*z3d_c*cos(yaw) - 2*z3d_s*z3d2_s*cos(yaw) + z3d_s*zt_s*cos(yaw) + z3d2_s*zt_s*cos(yaw) - x3d*z3d2_c*sin(yaw) - x3d2*z3d_c*sin(yaw) + x3d_c*z3d2*sin(yaw) + x3d2_c*z3d*sin(yaw) - x3d*x3d2_s*xt - x3d2*x3d_s*xt + x3d*xt*z3d_s - 2*x3d*xt*z3d2_s - 2*x3d2*xt*z3d_s + x3d2*xt*z3d2_s + x3d_s*z3d*zt - 2*x3d_s*z3d2*zt - 2*x3d2_s*z3d*zt + x3d2_s*z3d2*zt - z3d*z3d2_s*zt - z3d2*z3d_s*zt + x3d*x3d2*z3d*zt + x3d*xt*z3d*z3d2 + x3d*x3d2*z3d2*zt + x3d2*xt*z3d*z3d2 - 2*x3d*x3d2*xt_s*cos(yaw) + x3d*x3d2*z3d_s*cos(yaw) + x3d*x3d2*z3d2_s*cos(yaw) + x3d_s*z3d*z3d2*cos(yaw) + x3d2_s*z3d*z3d2*cos(yaw) - 2*z3d*z3d2*zt_s*cos(yaw) - x3d2*x3d_s*z3d*sin(yaw) - x3d*x3d2_s*z3d2*sin(yaw) + x3d*xt_s*z3d*sin(yaw) - x3d*xt_s*z3d2*sin(yaw) - x3d2*xt_s*z3d*sin(yaw) + x3d2*xt_s*z3d2*sin(yaw) - x3d_s*xt*zt*sin(yaw) - x3d2_s*xt*zt*sin(yaw) + x3d*z3d2*z3d_s*sin(yaw) + x3d2*z3d*z3d2_s*sin(yaw) - x3d*z3d*zt_s*sin(yaw) + x3d*z3d2*zt_s*sin(yaw) + x3d2*z3d*zt_s*sin(yaw) - x3d2*z3d2*zt_s*sin(yaw) + xt*z3d_s*zt*sin(yaw) + xt*z3d2_s*zt*sin(yaw) + 2*x3d*xt*z3d*zt*cos(yaw) - 2*x3d*xt*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*zt*cos(yaw) + 2*x3d2*xt*z3d2*zt*cos(yaw) + 2*x3d*x3d2*xt*zt*sin(yaw) - 2*xt*z3d*z3d2*zt*sin(yaw)));

float test7 = 1.0f*((x3d - x3d2)*(x3d_s*z3d2_s - x3d2_s*z3d_s - x3d_s*zt_s + x3d2_s*zt_s - z3d_s*zt_s + z3d2_s*zt_s - z3d*zt_c*cos(yaw) + z3d2*zt_c*cos(yaw) + x3d*zt_c*sin(yaw) - x3d2*zt_c*sin(yaw) - 2*cos_yaw_s*x3d_s*z3d2_s + 2*cos_yaw_s*x3d2_s*z3d_s - x3d*x3d2_s*z3d*sin(2*yaw) + x3d2*x3d_s*z3d2*sin(2*yaw) - x3d*z3d*z3d2_s*sin(2*yaw) + x3d2*z3d2*z3d_s*sin(2*yaw) + cos_yaw_c*x3d*x3d2_s*xt - cos_yaw_c*x3d2*x3d_s*xt - cos_yaw_c*x3d*xt*z3d2_s + cos_yaw_c*x3d2*xt*z3d_s - cos_yaw_c*x3d_s*z3d2*zt + cos_yaw_c*x3d2_s*z3d*zt - cos_yaw_c*z3d*z3d2_s*zt + cos_yaw_c*z3d2*z3d_s*zt + sin_yaw_c*x3d*x3d2_s*zt - sin_yaw_c*x3d2*x3d_s*zt + sin_yaw_c*x3d_s*xt*z3d2 - sin_yaw_c*x3d2_s*xt*z3d - sin_yaw_c*x3d*z3d2_s*zt + sin_yaw_c*x3d2*z3d_s*zt + sin_yaw_c*xt*z3d*z3d2_s - sin_yaw_c*xt*z3d2*z3d_s - 2*x3d*xt*z3d2*zt + 2*x3d2*xt*z3d*zt - x3d*x3d2_s*xt*cos(yaw) + x3d2*x3d_s*xt*cos(yaw) - x3d*xt*zt_s*cos(yaw) + x3d2*xt*zt_s*cos(yaw) - x3d_s*z3d2*zt*cos(yaw) + x3d2_s*z3d*zt*cos(yaw) + 2*z3d*z3d2_s*zt*cos(yaw) - 2*z3d2*z3d_s*zt*cos(yaw) - 2*x3d*x3d2_s*zt*sin(yaw) + 2*x3d2*x3d_s*zt*sin(yaw) - x3d*z3d2_s*zt*sin(yaw) + x3d2*z3d_s*zt*sin(yaw) - xt*z3d*z3d2_s*sin(yaw) + xt*z3d2*z3d_s*sin(yaw) - xt*z3d*zt_s*sin(yaw) + xt*z3d2*zt_s*sin(yaw) + 2*x3d*x3d2*z3d*zt*cos(yaw) - 2*x3d*xt*z3d*z3d2*cos(yaw) - 2*x3d*x3d2*z3d2*zt*cos(yaw) + 2*x3d2*xt*z3d*z3d2*cos(yaw) - 2*x3d*x3d2*xt*z3d*sin(yaw) + 2*x3d*x3d2*xt*z3d2*sin(yaw) - 2*x3d*z3d*z3d2*zt*sin(yaw) + 2*x3d2*z3d*z3d2*zt*sin(yaw) - 2*cos_yaw_c*x3d*x3d2*z3d*zt + 2*cos_yaw_c*x3d*xt*z3d*z3d2 + 2*cos_yaw_c*x3d*x3d2*z3d2*zt - 2*cos_yaw_c*x3d2*xt*z3d*z3d2 + 2*sin_yaw_c*x3d*x3d2*xt*z3d - 2*sin_yaw_c*x3d*x3d2*xt*z3d2 + 2*sin_yaw_c*x3d*z3d*z3d2*zt - 2*sin_yaw_c*x3d2*z3d*z3d2*zt));


float test8 = (fx*(x3d_c*xt + x3d2_c*xt + z3d_c*zt + z3d2_c*zt + x3d*x3d2_c*cos(yaw) + x3d2*x3d_c*cos(yaw) - 2*x3d_s*x3d2_s*cos(yaw) + x3d_s*xt_s*cos(yaw) + x3d2_s*xt_s*cos(yaw) - 2*x3d_s*z3d2_s*cos(yaw) - 2*x3d2_s*z3d_s*cos(yaw) + z3d*z3d2_c*cos(yaw) + z3d2*z3d_c*cos(yaw) - 2*z3d_s*z3d2_s*cos(yaw) + z3d_s*zt_s*cos(yaw) + z3d2_s*zt_s*cos(yaw) - x3d*z3d2_c*sin(yaw) - x3d2*z3d_c*sin(yaw) + x3d_c*z3d2*sin(yaw) + x3d2_c*z3d*sin(yaw) - x3d*x3d2_s*xt - x3d2*x3d_s*xt + x3d*xt*z3d_s - 2*x3d*xt*z3d2_s - 2*x3d2*xt*z3d_s + x3d2*xt*z3d2_s + x3d_s*z3d*zt - 2*x3d_s*z3d2*zt - 2*x3d2_s*z3d*zt + x3d2_s*z3d2*zt - z3d*z3d2_s*zt - z3d2*z3d_s*zt + x3d*x3d2*z3d*zt + x3d*xt*z3d*z3d2 + x3d*x3d2*z3d2*zt + x3d2*xt*z3d*z3d2 - 2*x3d*x3d2*xt_s*cos(yaw) + x3d*x3d2*z3d_s*cos(yaw) + x3d*x3d2*z3d2_s*cos(yaw) + x3d_s*z3d*z3d2*cos(yaw) + x3d2_s*z3d*z3d2*cos(yaw) - 2*z3d*z3d2*zt_s*cos(yaw) - x3d2*x3d_s*z3d*sin(yaw) - x3d*x3d2_s*z3d2*sin(yaw) + x3d*xt_s*z3d*sin(yaw) - x3d*xt_s*z3d2*sin(yaw) - x3d2*xt_s*z3d*sin(yaw) + x3d2*xt_s*z3d2*sin(yaw) - x3d_s*xt*zt*sin(yaw) - x3d2_s*xt*zt*sin(yaw) + x3d*z3d2*z3d_s*sin(yaw) + x3d2*z3d*z3d2_s*sin(yaw) - x3d*z3d*zt_s*sin(yaw) + x3d*z3d2*zt_s*sin(yaw) + x3d2*z3d*zt_s*sin(yaw) - x3d2*z3d2*zt_s*sin(yaw) + xt*z3d_s*zt*sin(yaw) + xt*z3d2_s*zt*sin(yaw) + 2*x3d*xt*z3d*zt*cos(yaw) - 2*x3d*xt*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*zt*cos(yaw) + 2*x3d2*xt*z3d2*zt*cos(yaw) + 2*x3d*x3d2*xt*zt*sin(yaw) - 2*xt*z3d*z3d2*zt*sin(yaw)));

			jacobian_2_2 = ((x3d/2 - x3d2/2)*(2*x3d_s*x3d2_s + x3d_s*z3d2_s + x3d2_s*z3d_s + x3d_s*zt_s + x3d2_s*zt_s + z3d_s*zt_s + z3d2_s*zt_s + z3d*zt_c*cos(yaw) + z3d2*zt_c*cos(yaw) - x3d*zt_c*sin(yaw) - x3d2*zt_c*sin(yaw) - 2*cos_yaw_s*x3d_s*x3d2_s + 2*cos_yaw_s*z3d_s*z3d2_s + 4*x3d*x3d2*zt_s - x3d*x3d2_s*z3d*sin(2*yaw) - x3d2*x3d_s*z3d2*sin(2*yaw) - x3d*z3d*z3d2_s*sin(2*yaw) - x3d2*z3d2*z3d_s*sin(2*yaw) - 2*x3d*z3d2*zt_s*sin(2*yaw) - 2*x3d2*z3d*zt_s*sin(2*yaw) - cos_yaw_c*x3d*x3d2_s*xt - cos_yaw_c*x3d2*x3d_s*xt + cos_yaw_c*x3d*xt*z3d2_s + cos_yaw_c*x3d2*xt*z3d_s - 4*cos_yaw_s*x3d*x3d2*zt_s - cos_yaw_c*x3d_s*z3d2*zt - cos_yaw_c*x3d2_s*z3d*zt + cos_yaw_c*z3d*z3d2_s*zt + cos_yaw_c*z3d2*z3d_s*zt + 4*cos_yaw_s*z3d*z3d2*zt_s - sin_yaw_c*x3d*x3d2_s*zt - sin_yaw_c*x3d2*x3d_s*zt + sin_yaw_c*x3d_s*xt*z3d2 + sin_yaw_c*x3d2_s*xt*z3d + sin_yaw_c*x3d*z3d2_s*zt + sin_yaw_c*x3d2*z3d_s*zt - sin_yaw_c*xt*z3d*z3d2_s - sin_yaw_c*xt*z3d2*z3d_s - 2*x3d*xt*z3d2*zt - 2*x3d2*xt*z3d*zt + x3d*x3d2_s*xt*cos(yaw) + x3d2*x3d_s*xt*cos(yaw) + x3d*xt*zt_s*cos(yaw) + x3d2*xt*zt_s*cos(yaw) + 3*x3d_s*z3d2*zt*cos(yaw) + 3*x3d2_s*z3d*zt*cos(yaw) + 2*z3d*z3d2_s*zt*cos(yaw) + 2*z3d2*z3d_s*zt*cos(yaw) - 2*x3d*x3d2_s*zt*sin(yaw) - 2*x3d2*x3d_s*zt*sin(yaw) - 3*x3d*z3d2_s*zt*sin(yaw) - 3*x3d2*z3d_s*zt*sin(yaw) + xt*z3d*z3d2_s*sin(yaw) + xt*z3d2*z3d_s*sin(yaw) + xt*z3d*zt_s*sin(yaw) + xt*z3d2*zt_s*sin(yaw) + 2*x3d*x3d2*z3d*zt*cos(yaw) - 2*x3d*xt*z3d*z3d2*cos(yaw) + 2*x3d*x3d2*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*z3d2*cos(yaw) - 2*x3d*x3d2*xt*z3d*sin(yaw) - 2*x3d*x3d2*xt*z3d2*sin(yaw) - 2*x3d*z3d*z3d2*zt*sin(yaw) - 2*x3d2*z3d*z3d2*zt*sin(yaw) - 2*x3d*x3d2*xt*zt*sin(2*yaw) + 2*xt*z3d*z3d2*zt*sin(2*yaw) - 2*cos_yaw_c*x3d*x3d2*z3d*zt + 2*cos_yaw_c*x3d*xt*z3d*z3d2 - 2*cos_yaw_c*x3d*x3d2*z3d2*zt + 2*cos_yaw_c*x3d2*xt*z3d*z3d2 + 4*cos_yaw_s*x3d*xt*z3d2*zt + 4*cos_yaw_s*x3d2*xt*z3d*zt + 2*sin_yaw_c*x3d*x3d2*xt*z3d + 2*sin_yaw_c*x3d*x3d2*xt*z3d2 + 2*sin_yaw_c*x3d*z3d*z3d2*zt + 2*sin_yaw_c*x3d2*z3d*z3d2*zt))/(fx*(x3d_c*xt + x3d2_c*xt + z3d_c*zt + z3d2_c*zt + x3d*x3d2_c*cos(yaw) + x3d2*x3d_c*cos(yaw) - 2*x3d_s*x3d2_s*cos(yaw) + x3d_s*xt_s*cos(yaw) + x3d2_s*xt_s*cos(yaw) - 2*x3d_s*z3d2_s*cos(yaw) - 2*x3d2_s*z3d_s*cos(yaw) + z3d*z3d2_c*cos(yaw) + z3d2*z3d_c*cos(yaw) - 2*z3d_s*z3d2_s*cos(yaw) + z3d_s*zt_s*cos(yaw) + z3d2_s*zt_s*cos(yaw) - x3d*z3d2_c*sin(yaw) - x3d2*z3d_c*sin(yaw) + x3d_c*z3d2*sin(yaw) + x3d2_c*z3d*sin(yaw) - x3d*x3d2_s*xt - x3d2*x3d_s*xt + x3d*xt*z3d_s - 2*x3d*xt*z3d2_s - 2*x3d2*xt*z3d_s + x3d2*xt*z3d2_s + x3d_s*z3d*zt - 2*x3d_s*z3d2*zt - 2*x3d2_s*z3d*zt + x3d2_s*z3d2*zt - z3d*z3d2_s*zt - z3d2*z3d_s*zt + x3d*x3d2*z3d*zt + x3d*xt*z3d*z3d2 + x3d*x3d2*z3d2*zt + x3d2*xt*z3d*z3d2 - 2*x3d*x3d2*xt_s*cos(yaw) + x3d*x3d2*z3d_s*cos(yaw) + x3d*x3d2*z3d2_s*cos(yaw) + x3d_s*z3d*z3d2*cos(yaw) + x3d2_s*z3d*z3d2*cos(yaw) - 2*z3d*z3d2*zt_s*cos(yaw) - x3d2*x3d_s*z3d*sin(yaw) - x3d*x3d2_s*z3d2*sin(yaw) + x3d*xt_s*z3d*sin(yaw) - x3d*xt_s*z3d2*sin(yaw) - x3d2*xt_s*z3d*sin(yaw) + x3d2*xt_s*z3d2*sin(yaw) - x3d_s*xt*zt*sin(yaw) - x3d2_s*xt*zt*sin(yaw) + x3d*z3d2*z3d_s*sin(yaw) + x3d2*z3d*z3d2_s*sin(yaw) - x3d*z3d*zt_s*sin(yaw) + x3d*z3d2*zt_s*sin(yaw) + x3d2*z3d*zt_s*sin(yaw) - x3d2*z3d2*zt_s*sin(yaw) + xt*z3d_s*zt*sin(yaw) + xt*z3d2_s*zt*sin(yaw) + 2*x3d*xt*z3d*zt*cos(yaw) - 2*x3d*xt*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*zt*cos(yaw) + 2*x3d2*xt*z3d2*zt*cos(yaw) + 2*x3d*x3d2*xt*zt*sin(yaw) - 2*xt*z3d*z3d2*zt*sin(yaw))); 

float test9 = ((x3d/2 - x3d2/2)*(2*x3d_s*x3d2_s + x3d_s*z3d2_s + x3d2_s*z3d_s + x3d_s*zt_s + x3d2_s*zt_s + z3d_s*zt_s + z3d2_s*zt_s + z3d*zt_c*cos(yaw) + z3d2*zt_c*cos(yaw) - x3d*zt_c*sin(yaw) - x3d2*zt_c*sin(yaw) - 2*cos_yaw_s*x3d_s*x3d2_s + 2*cos_yaw_s*z3d_s*z3d2_s + 4*x3d*x3d2*zt_s - x3d*x3d2_s*z3d*sin(2*yaw) - x3d2*x3d_s*z3d2*sin(2*yaw) - x3d*z3d*z3d2_s*sin(2*yaw) - x3d2*z3d2*z3d_s*sin(2*yaw) - 2*x3d*z3d2*zt_s*sin(2*yaw) - 2*x3d2*z3d*zt_s*sin(2*yaw) - cos_yaw_c*x3d*x3d2_s*xt - cos_yaw_c*x3d2*x3d_s*xt + cos_yaw_c*x3d*xt*z3d2_s + cos_yaw_c*x3d2*xt*z3d_s - 4*cos_yaw_s*x3d*x3d2*zt_s - cos_yaw_c*x3d_s*z3d2*zt - cos_yaw_c*x3d2_s*z3d*zt + cos_yaw_c*z3d*z3d2_s*zt + cos_yaw_c*z3d2*z3d_s*zt + 4*cos_yaw_s*z3d*z3d2*zt_s - sin_yaw_c*x3d*x3d2_s*zt - sin_yaw_c*x3d2*x3d_s*zt + sin_yaw_c*x3d_s*xt*z3d2 + sin_yaw_c*x3d2_s*xt*z3d + sin_yaw_c*x3d*z3d2_s*zt + sin_yaw_c*x3d2*z3d_s*zt - sin_yaw_c*xt*z3d*z3d2_s - sin_yaw_c*xt*z3d2*z3d_s - 2*x3d*xt*z3d2*zt - 2*x3d2*xt*z3d*zt + x3d*x3d2_s*xt*cos(yaw) + x3d2*x3d_s*xt*cos(yaw) + x3d*xt*zt_s*cos(yaw) + x3d2*xt*zt_s*cos(yaw) + 3*x3d_s*z3d2*zt*cos(yaw) + 3*x3d2_s*z3d*zt*cos(yaw) + 2*z3d*z3d2_s*zt*cos(yaw) + 2*z3d2*z3d_s*zt*cos(yaw) - 2*x3d*x3d2_s*zt*sin(yaw) - 2*x3d2*x3d_s*zt*sin(yaw) - 3*x3d*z3d2_s*zt*sin(yaw) - 3*x3d2*z3d_s*zt*sin(yaw) + xt*z3d*z3d2_s*sin(yaw) + xt*z3d2*z3d_s*sin(yaw) + xt*z3d*zt_s*sin(yaw) + xt*z3d2*zt_s*sin(yaw) + 2*x3d*x3d2*z3d*zt*cos(yaw) - 2*x3d*xt*z3d*z3d2*cos(yaw) + 2*x3d*x3d2*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*z3d2*cos(yaw) - 2*x3d*x3d2*xt*z3d*sin(yaw) - 2*x3d*x3d2*xt*z3d2*sin(yaw) - 2*x3d*z3d*z3d2*zt*sin(yaw) - 2*x3d2*z3d*z3d2*zt*sin(yaw) - 2*x3d*x3d2*xt*zt*sin(2*yaw) + 2*xt*z3d*z3d2*zt*sin(2*yaw) - 2*cos_yaw_c*x3d*x3d2*z3d*zt + 2*cos_yaw_c*x3d*xt*z3d*z3d2 - 2*cos_yaw_c*x3d*x3d2*z3d2*zt + 2*cos_yaw_c*x3d2*xt*z3d*z3d2 + 4*cos_yaw_s*x3d*xt*z3d2*zt + 4*cos_yaw_s*x3d2*xt*z3d*zt + 2*sin_yaw_c*x3d*x3d2*xt*z3d + 2*sin_yaw_c*x3d*x3d2*xt*z3d2 + 2*sin_yaw_c*x3d*z3d*z3d2*zt + 2*sin_yaw_c*x3d2*z3d*z3d2*zt));

float test10 = (fx*(x3d_c*xt + x3d2_c*xt + z3d_c*zt + z3d2_c*zt + x3d*x3d2_c*cos(yaw) + x3d2*x3d_c*cos(yaw) - 2*x3d_s*x3d2_s*cos(yaw) + x3d_s*xt_s*cos(yaw) + x3d2_s*xt_s*cos(yaw) - 2*x3d_s*z3d2_s*cos(yaw) - 2*x3d2_s*z3d_s*cos(yaw) + z3d*z3d2_c*cos(yaw) + z3d2*z3d_c*cos(yaw) - 2*z3d_s*z3d2_s*cos(yaw) + z3d_s*zt_s*cos(yaw) + z3d2_s*zt_s*cos(yaw) - x3d*z3d2_c*sin(yaw) - x3d2*z3d_c*sin(yaw) + x3d_c*z3d2*sin(yaw) + x3d2_c*z3d*sin(yaw) - x3d*x3d2_s*xt - x3d2*x3d_s*xt + x3d*xt*z3d_s - 2*x3d*xt*z3d2_s - 2*x3d2*xt*z3d_s + x3d2*xt*z3d2_s + x3d_s*z3d*zt - 2*x3d_s*z3d2*zt - 2*x3d2_s*z3d*zt + x3d2_s*z3d2*zt - z3d*z3d2_s*zt - z3d2*z3d_s*zt + x3d*x3d2*z3d*zt + x3d*xt*z3d*z3d2 + x3d*x3d2*z3d2*zt + x3d2*xt*z3d*z3d2 - 2*x3d*x3d2*xt_s*cos(yaw) + x3d*x3d2*z3d_s*cos(yaw) + x3d*x3d2*z3d2_s*cos(yaw) + x3d_s*z3d*z3d2*cos(yaw) + x3d2_s*z3d*z3d2*cos(yaw) - 2*z3d*z3d2*zt_s*cos(yaw) - x3d2*x3d_s*z3d*sin(yaw) - x3d*x3d2_s*z3d2*sin(yaw) + x3d*xt_s*z3d*sin(yaw) - x3d*xt_s*z3d2*sin(yaw) - x3d2*xt_s*z3d*sin(yaw) + x3d2*xt_s*z3d2*sin(yaw) - x3d_s*xt*zt*sin(yaw) - x3d2_s*xt*zt*sin(yaw) + x3d*z3d2*z3d_s*sin(yaw) + x3d2*z3d*z3d2_s*sin(yaw) - x3d*z3d*zt_s*sin(yaw) + x3d*z3d2*zt_s*sin(yaw) + x3d2*z3d*zt_s*sin(yaw) - x3d2*z3d2*zt_s*sin(yaw) + xt*z3d_s*zt*sin(yaw) + xt*z3d2_s*zt*sin(yaw) + 2*x3d*xt*z3d*zt*cos(yaw) - 2*x3d*xt*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*zt*cos(yaw) + 2*x3d2*xt*z3d2*zt*cos(yaw) + 2*x3d*x3d2*xt*zt*sin(yaw) - 2*xt*z3d*z3d2*zt*sin(yaw)));


			jacobian_2_3 = -(x3d_s*zt - x3d2_s*zt + z3d_s*zt - z3d2_s*zt + x3d_s*z3d2*cos(yaw) - x3d2_s*z3d*cos(yaw) - z3d*z3d2_s*cos(yaw) + z3d2*z3d_s*cos(yaw) + z3d*zt_s*cos(yaw) - z3d2*zt_s*cos(yaw) + x3d*x3d2_s*sin(yaw) - x3d2*x3d_s*sin(yaw) + x3d*z3d2_s*sin(yaw) - x3d2*z3d_s*sin(yaw) - x3d*zt_s*sin(yaw) + x3d2*zt_s*sin(yaw) + x3d*xt*z3d2 - x3d2*xt*z3d + x3d*xt*zt*cos(yaw) - x3d2*xt*zt*cos(yaw) + xt*z3d*zt*sin(yaw) - xt*z3d2*zt*sin(yaw))/(2*K_size*(x3d_c*xt + x3d2_c*xt + z3d_c*zt + z3d2_c*zt + x3d*x3d2_c*cos(yaw) + x3d2*x3d_c*cos(yaw) - 2*x3d_s*x3d2_s*cos(yaw) + x3d_s*xt_s*cos(yaw) + x3d2_s*xt_s*cos(yaw) - 2*x3d_s*z3d2_s*cos(yaw) - 2*x3d2_s*z3d_s*cos(yaw) + z3d*z3d2_c*cos(yaw) + z3d2*z3d_c*cos(yaw) - 2*z3d_s*z3d2_s*cos(yaw) + z3d_s*zt_s*cos(yaw) + z3d2_s*zt_s*cos(yaw) - x3d*z3d2_c*sin(yaw) - x3d2*z3d_c*sin(yaw) + x3d_c*z3d2*sin(yaw) + x3d2_c*z3d*sin(yaw) - x3d*x3d2_s*xt - x3d2*x3d_s*xt + x3d*xt*z3d_s - 2*x3d*xt*z3d2_s - 2*x3d2*xt*z3d_s + x3d2*xt*z3d2_s + x3d_s*z3d*zt - 2*x3d_s*z3d2*zt - 2*x3d2_s*z3d*zt + x3d2_s*z3d2*zt - z3d*z3d2_s*zt - z3d2*z3d_s*zt + x3d*x3d2*z3d*zt + x3d*xt*z3d*z3d2 + x3d*x3d2*z3d2*zt + x3d2*xt*z3d*z3d2 - 2*x3d*x3d2*xt_s*cos(yaw) + x3d*x3d2*z3d_s*cos(yaw) + x3d*x3d2*z3d2_s*cos(yaw) + x3d_s*z3d*z3d2*cos(yaw) + x3d2_s*z3d*z3d2*cos(yaw) - 2*z3d*z3d2*zt_s*cos(yaw) - x3d2*x3d_s*z3d*sin(yaw) - x3d*x3d2_s*z3d2*sin(yaw) + x3d*xt_s*z3d*sin(yaw) - x3d*xt_s*z3d2*sin(yaw) - x3d2*xt_s*z3d*sin(yaw) + x3d2*xt_s*z3d2*sin(yaw) - x3d_s*xt*zt*sin(yaw) - x3d2_s*xt*zt*sin(yaw) + x3d*z3d2*z3d_s*sin(yaw) + x3d2*z3d*z3d2_s*sin(yaw) - x3d*z3d*zt_s*sin(yaw) + x3d*z3d2*zt_s*sin(yaw) + x3d2*z3d*zt_s*sin(yaw) - x3d2*z3d2*zt_s*sin(yaw) + xt*z3d_s*zt*sin(yaw) + xt*z3d2_s*zt*sin(yaw) + 2*x3d*xt*z3d*zt*cos(yaw) - 2*x3d*xt*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*zt*cos(yaw) + 2*x3d2*xt*z3d2*zt*cos(yaw) + 2*x3d*x3d2*xt*zt*sin(yaw) - 2*xt*z3d*z3d2*zt*sin(yaw)));


			jacobian_3_1 = (x3d_c*xt + x3d2_c*xt + x3d*x3d2_c*cos(yaw) + x3d2*x3d_c*cos(yaw) - 2*x3d_s*x3d2_s*cos(yaw) - x3d_s*z3d2_s*cos(yaw) - x3d2_s*z3d_s*cos(yaw) - x3d_s*zt_s*cos(yaw) - x3d2_s*zt_s*cos(yaw) + z3d_s*zt_s*cos(yaw) + z3d2_s*zt_s*cos(yaw) - x3d*z3d2_c*sin(yaw) - x3d2*z3d_c*sin(yaw) - cos_yaw_c*x3d*x3d2_c - cos_yaw_c*x3d2*x3d_c + 2*cos_yaw_c*x3d_s*x3d2_s - cos_yaw_s*x3d_c*xt - cos_yaw_s*x3d2_c*xt + cos_yaw_c*z3d*z3d2_c + cos_yaw_c*z3d2*z3d_c - 2*cos_yaw_c*z3d_s*z3d2_s + cos_yaw_s*z3d_c*zt + cos_yaw_s*z3d2_c*zt + sin_yaw_c*x3d*z3d2_c + sin_yaw_c*x3d2*z3d_c + sin_yaw_c*x3d_c*z3d2 + sin_yaw_c*x3d2_c*z3d - x3d*x3d2_s*xt - x3d2*x3d_s*xt + x3d_s*z3d*zt - 3*x3d_s*z3d2*zt - 3*x3d2_s*z3d*zt + x3d2_s*z3d2*zt - x3d_s*xt*z3d*sin(2*yaw) - x3d2_s*xt*z3d2*sin(2*yaw) - x3d*z3d_s*zt*sin(2*yaw) - x3d2*z3d2_s*zt*sin(2*yaw) + cos_yaw_s*x3d*x3d2_s*xt + cos_yaw_s*x3d2*x3d_s*xt - cos_yaw_c*x3d*x3d2*z3d_s - cos_yaw_c*x3d*x3d2*z3d2_s + cos_yaw_s*x3d*xt*z3d_s - cos_yaw_s*x3d*xt*z3d2_s - cos_yaw_s*x3d2*xt*z3d_s + cos_yaw_s*x3d2*xt*z3d2_s + cos_yaw_c*x3d_s*z3d*z3d2 + cos_yaw_c*x3d2_s*z3d*z3d2 - cos_yaw_s*x3d_s*z3d*zt + cos_yaw_s*x3d_s*z3d2*zt + cos_yaw_s*x3d2_s*z3d*zt - cos_yaw_s*x3d2_s*z3d2*zt - cos_yaw_s*z3d*z3d2_s*zt - cos_yaw_s*z3d2*z3d_s*zt - 2*sin_yaw_c*x3d*x3d2_s*z3d + sin_yaw_c*x3d2*x3d_s*z3d + sin_yaw_c*x3d*x3d2_s*z3d2 - 2*sin_yaw_c*x3d2*x3d_s*z3d2 - 2*sin_yaw_c*x3d*z3d*z3d2_s + sin_yaw_c*x3d*z3d2*z3d_s + sin_yaw_c*x3d2*z3d*z3d2_s - 2*sin_yaw_c*x3d2*z3d2*z3d_s + 2*x3d*x3d2*z3d*zt + 2*x3d*x3d2*z3d2*zt + 2*x3d*x3d2*z3d_s*cos(yaw) + 2*x3d*x3d2*z3d2_s*cos(yaw) + 2*x3d*x3d2*zt_s*cos(yaw) - x3d_s*z3d*z3d2*cos(yaw) - x3d2_s*z3d*z3d2*cos(yaw) - 2*z3d*z3d2*zt_s*cos(yaw) + 2*x3d*x3d2_s*z3d*sin(yaw) - 2*x3d2*x3d_s*z3d*sin(yaw) - 2*x3d*x3d2_s*z3d2*sin(yaw) + 2*x3d2*x3d_s*z3d2*sin(yaw) - 2*x3d_s*xt*zt*sin(yaw) - 2*x3d2_s*xt*zt*sin(yaw) + 2*x3d*z3d*z3d2_s*sin(yaw) - x3d*z3d2*z3d_s*sin(yaw) - x3d2*z3d*z3d2_s*sin(yaw) + 2*x3d2*z3d2*z3d_s*sin(yaw) - 2*x3d*z3d*zt_s*sin(yaw) + 2*x3d*z3d2*zt_s*sin(yaw) + 2*x3d2*z3d*zt_s*sin(yaw) - 2*x3d2*z3d2*zt_s*sin(yaw) + 2*x3d*xt*z3d*zt*cos(yaw) - 2*x3d*xt*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*zt*cos(yaw) + 2*x3d2*xt*z3d2*zt*cos(yaw) + 4*x3d*x3d2*xt*zt*sin(yaw) + x3d*x3d2*xt*z3d*sin(2*yaw) + x3d*x3d2*xt*z3d2*sin(2*yaw) + x3d*z3d*z3d2*zt*sin(2*yaw) + x3d2*z3d*z3d2*zt*sin(2*yaw))/(fx*(x3d_c*xt + x3d2_c*xt + z3d_c*zt + z3d2_c*zt + x3d*x3d2_c*cos(yaw) + x3d2*x3d_c*cos(yaw) - 2*x3d_s*x3d2_s*cos(yaw) + x3d_s*xt_s*cos(yaw) + x3d2_s*xt_s*cos(yaw) - 2*x3d_s*z3d2_s*cos(yaw) - 2*x3d2_s*z3d_s*cos(yaw) + z3d*z3d2_c*cos(yaw) + z3d2*z3d_c*cos(yaw) - 2*z3d_s*z3d2_s*cos(yaw) + z3d_s*zt_s*cos(yaw) + z3d2_s*zt_s*cos(yaw) - x3d*z3d2_c*sin(yaw) - x3d2*z3d_c*sin(yaw) + x3d_c*z3d2*sin(yaw) + x3d2_c*z3d*sin(yaw) - x3d*x3d2_s*xt - x3d2*x3d_s*xt + x3d*xt*z3d_s - 2*x3d*xt*z3d2_s - 2*x3d2*xt*z3d_s + x3d2*xt*z3d2_s + x3d_s*z3d*zt - 2*x3d_s*z3d2*zt - 2*x3d2_s*z3d*zt + x3d2_s*z3d2*zt - z3d*z3d2_s*zt - z3d2*z3d_s*zt + x3d*x3d2*z3d*zt + x3d*xt*z3d*z3d2 + x3d*x3d2*z3d2*zt + x3d2*xt*z3d*z3d2 - 2*x3d*x3d2*xt_s*cos(yaw) + x3d*x3d2*z3d_s*cos(yaw) + x3d*x3d2*z3d2_s*cos(yaw) + x3d_s*z3d*z3d2*cos(yaw) + x3d2_s*z3d*z3d2*cos(yaw) - 2*z3d*z3d2*zt_s*cos(yaw) - x3d2*x3d_s*z3d*sin(yaw) - x3d*x3d2_s*z3d2*sin(yaw) + x3d*xt_s*z3d*sin(yaw) - x3d*xt_s*z3d2*sin(yaw) - x3d2*xt_s*z3d*sin(yaw) + x3d2*xt_s*z3d2*sin(yaw) - x3d_s*xt*zt*sin(yaw) - x3d2_s*xt*zt*sin(yaw) + x3d*z3d2*z3d_s*sin(yaw) + x3d2*z3d*z3d2_s*sin(yaw) - x3d*z3d*zt_s*sin(yaw) + x3d*z3d2*zt_s*sin(yaw) + x3d2*z3d*zt_s*sin(yaw) - x3d2*z3d2*zt_s*sin(yaw) + xt*z3d_s*zt*sin(yaw) + xt*z3d2_s*zt*sin(yaw) + 2*x3d*xt*z3d*zt*cos(yaw) - 2*x3d*xt*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*zt*cos(yaw) + 2*x3d2*xt*z3d2*zt*cos(yaw) + 2*x3d*x3d2*xt*zt*sin(yaw) - 2*xt*z3d*z3d2*zt*sin(yaw))); 



			jacobian_3_2 = (x3d_c*xt - x3d2_c*xt + 2*z3d*zt_c - 2*z3d2*zt_c - x3d*x3d2_c*cos(yaw) + x3d2*x3d_c*cos(yaw) - x3d_s*z3d2_s*cos(yaw) + x3d2_s*z3d_s*cos(yaw) + x3d_s*zt_s*cos(yaw) - x3d2_s*zt_s*cos(yaw) + 3*z3d_s*zt_s*cos(yaw) - 3*z3d2_s*zt_s*cos(yaw) + x3d*z3d2_c*sin(yaw) - x3d2*z3d_c*sin(yaw) + cos_yaw_c*x3d*x3d2_c - cos_yaw_c*x3d2*x3d_c - cos_yaw_s*x3d_c*xt + cos_yaw_s*x3d2_c*xt + 2*cos_yaw_c*x3d_s*z3d2_s - 2*cos_yaw_c*x3d2_s*z3d_s - cos_yaw_c*z3d*z3d2_c + cos_yaw_c*z3d2*z3d_c + cos_yaw_s*z3d_c*zt - cos_yaw_s*z3d2_c*zt - sin_yaw_c*x3d*z3d2_c + sin_yaw_c*x3d2*z3d_c + sin_yaw_c*x3d_c*z3d2 - sin_yaw_c*x3d2_c*z3d + x3d*x3d2_s*xt - x3d2*x3d_s*xt + 2*x3d*xt*zt_s - 2*x3d2*xt*zt_s + x3d_s*z3d*zt - 3*x3d_s*z3d2*zt + 3*x3d2_s*z3d*zt - x3d2_s*z3d2*zt - x3d_s*xt*z3d*sin(2*yaw) + 2*x3d*x3d2_s*zt*sin(2*yaw) - 2*x3d2*x3d_s*zt*sin(2*yaw) + x3d2_s*xt*z3d2*sin(2*yaw) - x3d*z3d_s*zt*sin(2*yaw) + 2*x3d*z3d2_s*zt*sin(2*yaw) - 2*x3d2*z3d_s*zt*sin(2*yaw) + x3d2*z3d2_s*zt*sin(2*yaw) - cos_yaw_s*x3d*x3d2_s*xt + cos_yaw_s*x3d2*x3d_s*xt - cos_yaw_c*x3d*x3d2*z3d_s + cos_yaw_c*x3d*x3d2*z3d2_s + cos_yaw_s*x3d*xt*z3d_s + cos_yaw_s*x3d*xt*z3d2_s - cos_yaw_s*x3d2*xt*z3d_s - cos_yaw_s*x3d2*xt*z3d2_s + cos_yaw_c*x3d_s*z3d*z3d2 - cos_yaw_c*x3d2_s*z3d*z3d2 - cos_yaw_s*x3d_s*z3d*zt + 5*cos_yaw_s*x3d_s*z3d2*zt - 5*cos_yaw_s*x3d2_s*z3d*zt + cos_yaw_s*x3d2_s*z3d2*zt - 3*cos_yaw_s*z3d*z3d2_s*zt + 3*cos_yaw_s*z3d2*z3d_s*zt - 2*sin_yaw_c*x3d*x3d2_s*z3d + sin_yaw_c*x3d2*x3d_s*z3d - sin_yaw_c*x3d*x3d2_s*z3d2 + 2*sin_yaw_c*x3d2*x3d_s*z3d2 - 2*sin_yaw_c*x3d*z3d*z3d2_s + sin_yaw_c*x3d*z3d2*z3d_s - sin_yaw_c*x3d2*z3d*z3d2_s + 2*sin_yaw_c*x3d2*z3d2*z3d_s + 2*x3d*x3d2*z3d*zt - 2*x3d*x3d2*z3d2*zt + 2*x3d*x3d2*z3d_s*cos(yaw) - 2*x3d*x3d2*z3d2_s*cos(yaw) - x3d_s*z3d*z3d2*cos(yaw) + x3d2_s*z3d*z3d2*cos(yaw) + 2*x3d*x3d2_s*z3d*sin(yaw) - 2*x3d2*x3d_s*z3d*sin(yaw) + 2*x3d*x3d2_s*z3d2*sin(yaw) - 2*x3d2*x3d_s*z3d2*sin(yaw) - 2*x3d_s*xt*zt*sin(yaw) + 2*x3d2_s*xt*zt*sin(yaw) + 2*x3d*z3d*z3d2_s*sin(yaw) - x3d*z3d2*z3d_s*sin(yaw) + x3d2*z3d*z3d2_s*sin(yaw) - 2*x3d2*z3d2*z3d_s*sin(yaw) - 2*x3d*z3d*zt_s*sin(yaw) + 4*x3d*z3d2*zt_s*sin(yaw) - 4*x3d2*z3d*zt_s*sin(yaw) + 2*x3d2*z3d2*zt_s*sin(yaw) + 2*x3d*xt*z3d*zt*cos(yaw) + 2*x3d*xt*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*zt*cos(yaw) - 2*x3d2*xt*z3d2*zt*cos(yaw) + x3d*x3d2*xt*z3d*sin(2*yaw) - x3d*x3d2*xt*z3d2*sin(2*yaw) + x3d*z3d*z3d2*zt*sin(2*yaw) - x3d2*z3d*z3d2*zt*sin(2*yaw))/(2*fx*(x3d_c*xt + x3d2_c*xt + z3d_c*zt + z3d2_c*zt + x3d*x3d2_c*cos(yaw) + x3d2*x3d_c*cos(yaw) - 2*x3d_s*x3d2_s*cos(yaw) + x3d_s*xt_s*cos(yaw) + x3d2_s*xt_s*cos(yaw) - 2*x3d_s*z3d2_s*cos(yaw) - 2*x3d2_s*z3d_s*cos(yaw) + z3d*z3d2_c*cos(yaw) + z3d2*z3d_c*cos(yaw) - 2*z3d_s*z3d2_s*cos(yaw) + z3d_s*zt_s*cos(yaw) + z3d2_s*zt_s*cos(yaw) - x3d*z3d2_c*sin(yaw) - x3d2*z3d_c*sin(yaw) + x3d_c*z3d2*sin(yaw) + x3d2_c*z3d*sin(yaw) - x3d*x3d2_s*xt - x3d2*x3d_s*xt + x3d*xt*z3d_s - 2*x3d*xt*z3d2_s - 2*x3d2*xt*z3d_s + x3d2*xt*z3d2_s + x3d_s*z3d*zt - 2*x3d_s*z3d2*zt - 2*x3d2_s*z3d*zt + x3d2_s*z3d2*zt - z3d*z3d2_s*zt - z3d2*z3d_s*zt + x3d*x3d2*z3d*zt + x3d*xt*z3d*z3d2 + x3d*x3d2*z3d2*zt + x3d2*xt*z3d*z3d2 - 2*x3d*x3d2*xt_s*cos(yaw) + x3d*x3d2*z3d_s*cos(yaw) + x3d*x3d2*z3d2_s*cos(yaw) + x3d_s*z3d*z3d2*cos(yaw) + x3d2_s*z3d*z3d2*cos(yaw) - 2*z3d*z3d2*zt_s*cos(yaw) - x3d2*x3d_s*z3d*sin(yaw) - x3d*x3d2_s*z3d2*sin(yaw) + x3d*xt_s*z3d*sin(yaw) - x3d*xt_s*z3d2*sin(yaw) - x3d2*xt_s*z3d*sin(yaw) + x3d2*xt_s*z3d2*sin(yaw) - x3d_s*xt*zt*sin(yaw) - x3d2_s*xt*zt*sin(yaw) + x3d*z3d2*z3d_s*sin(yaw) + x3d2*z3d*z3d2_s*sin(yaw) - x3d*z3d*zt_s*sin(yaw) + x3d*z3d2*zt_s*sin(yaw) + x3d2*z3d*zt_s*sin(yaw) - x3d2*z3d2*zt_s*sin(yaw) + xt*z3d_s*zt*sin(yaw) + xt*z3d2_s*zt*sin(yaw) + 2*x3d*xt*z3d*zt*cos(yaw) - 2*x3d*xt*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*zt*cos(yaw) + 2*x3d2*xt*z3d2*zt*cos(yaw) + 2*x3d*x3d2*xt*zt*sin(yaw) - 2*xt*z3d*z3d2*zt*sin(yaw)));



			jacobian_3_3 = -(x3d*z3d2 - x3d2*z3d + x3d*zt*cos(yaw) - xt*z3d*cos(yaw) - x3d2*zt*cos(yaw) + xt*z3d2*cos(yaw) + x3d*xt*sin(yaw) - x3d2*xt*sin(yaw) + z3d*zt*sin(yaw) - z3d2*zt*sin(yaw))/(2*K_size*(x3d_c*xt + x3d2_c*xt + z3d_c*zt + z3d2_c*zt + x3d*x3d2_c*cos(yaw) + x3d2*x3d_c*cos(yaw) - 2*x3d_s*x3d2_s*cos(yaw) + x3d_s*xt_s*cos(yaw) + x3d2_s*xt_s*cos(yaw) - 2*x3d_s*z3d2_s*cos(yaw) - 2*x3d2_s*z3d_s*cos(yaw) + z3d*z3d2_c*cos(yaw) + z3d2*z3d_c*cos(yaw) - 2*z3d_s*z3d2_s*cos(yaw) + z3d_s*zt_s*cos(yaw) + z3d2_s*zt_s*cos(yaw) - x3d*z3d2_c*sin(yaw) - x3d2*z3d_c*sin(yaw) + x3d_c*z3d2*sin(yaw) + x3d2_c*z3d*sin(yaw) - x3d*x3d2_s*xt - x3d2*x3d_s*xt + x3d*xt*z3d_s - 2*x3d*xt*z3d2_s - 2*x3d2*xt*z3d_s + x3d2*xt*z3d2_s + x3d_s*z3d*zt - 2*x3d_s*z3d2*zt - 2*x3d2_s*z3d*zt + x3d2_s*z3d2*zt - z3d*z3d2_s*zt - z3d2*z3d_s*zt + x3d*x3d2*z3d*zt + x3d*xt*z3d*z3d2 + x3d*x3d2*z3d2*zt + x3d2*xt*z3d*z3d2 - 2*x3d*x3d2*xt_s*cos(yaw) + x3d*x3d2*z3d_s*cos(yaw) + x3d*x3d2*z3d2_s*cos(yaw) + x3d_s*z3d*z3d2*cos(yaw) + x3d2_s*z3d*z3d2*cos(yaw) - 2*z3d*z3d2*zt_s*cos(yaw) - x3d2*x3d_s*z3d*sin(yaw) - x3d*x3d2_s*z3d2*sin(yaw) + x3d*xt_s*z3d*sin(yaw) - x3d*xt_s*z3d2*sin(yaw) - x3d2*xt_s*z3d*sin(yaw) + x3d2*xt_s*z3d2*sin(yaw) - x3d_s*xt*zt*sin(yaw) - x3d2_s*xt*zt*sin(yaw) + x3d*z3d2*z3d_s*sin(yaw) + x3d2*z3d*z3d2_s*sin(yaw) - x3d*z3d*zt_s*sin(yaw) + x3d*z3d2*zt_s*sin(yaw) + x3d2*z3d*zt_s*sin(yaw) - x3d2*z3d2*zt_s*sin(yaw) + xt*z3d_s*zt*sin(yaw) + xt*z3d2_s*zt*sin(yaw) + 2*x3d*xt*z3d*zt*cos(yaw) - 2*x3d*xt*z3d2*zt*cos(yaw) - 2*x3d2*xt*z3d*zt*cos(yaw) + 2*x3d2*xt*z3d2*zt*cos(yaw) + 2*x3d*x3d2*xt*zt*sin(yaw) - 2*xt*z3d*z3d2*zt*sin(yaw))); 

/*			
			   std::cout<<"test1 = "<<test1<<std::endl;
			   std::cout<<"test2 = "<<test2<<std::endl;
			   std::cout<<"test3 = "<<test3<<std::endl;
			   std::cout<<"test4 = "<<test4<<std::endl;
			   std::cout<<"test5 = "<<test5<<std::endl;
			   std::cout<<"test6 = "<<test6<<std::endl;
			   std::cout<<"test7 = "<<test7<<std::endl;
			   std::cout<<"test8 = "<<test8<<std::endl;
			   std::cout<<"test9 = "<<test9<<std::endl;
			   std::cout<<"test10 = "<<test10<<std::endl;
*/			 


			//			std::cout<<"Computing invert jacobian, done!"<<std::endl;




		}


};
