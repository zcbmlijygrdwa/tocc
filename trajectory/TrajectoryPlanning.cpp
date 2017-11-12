
#include <cmath>
#include <iostream>

class TrajectoryPlanning
{

	public:

		float r;
		float xt;
		float zt;
		float d;
		float resWidth;
		float fov;
		float x3d;
		float z3d;
		float x3d1;
		float z3d1;

	public:

		void init()
		{
			r = 0;
			xt = 0;
			zt = 0;
			d = 0;
			resWidth = 0;
		}

		void setCameraTransformation(float data[])
		{
			xt = data[0];
			zt =  data[2];
		}

		void set3DPoints(float data[])
		{
			x3d = (data[0]);
			z3d = (data[2]);

			x3d1 =(data[3]);
			z3d1 =(data[5]);

		}


		void set3DPoint1(float data[])
		{
			x3d = data[0];
			z3d = data[2];
		}

		void set3DPoint2(float data[])
		{
			x3d1 = data[0];
			z3d1 = data[2];
		}

		void setScreenWidth(float data)
		{
			resWidth = data;
		}

		void setFov(float data)
		{
			fov = data;
		}

		void setDistXTarget(float distS_target)
		{

			d = std::abs(distS_target);
		}

		float getWayPoint()
		{
			float red_x_3d = x3d;
			float red_y_3d = z3d;
			float blue_x_3d = x3d1;
			float blue_y_3d = z3d1;
			float w = resWidth;
			float alpha = 2*atan((d/w)*tan(fov/2));

			float distance = sqrt((red_x_3d-blue_x_3d)*(red_x_3d-blue_x_3d)+(red_y_3d-blue_y_3d)*(red_y_3d-blue_y_3d));
			r = (distance/2)/sin(alpha);//radius
			return r;

		}

		void reset()
		{
			r = 0;
			xt = 0;
			zt = 0;
			d = 0;
			resWidth = 0;


		}




};
