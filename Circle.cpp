#include <cmath>
#include "Point2D.h"
#include <iostream>


class Circle
{

	public: 
		float r;
		float dist2D(Point2D n, Point2D m)
		{

			return sqrt( (n.x-m.x)*(n.x-m.x)  + (n.y - m.y)*(n.y  -m.y)  );

		}

		void getCenter(Point2D p1, Point2D p2, float *center)
		{
			float x_center1 = 0;
			float y_center1 = 0;
			float x_center2 = 0;
			float y_center2 = 0;

			if((p2.x-p1.x)!=0&&(p2.y-p1.y!=0)){

				float k = (p2.y-p1.y)/(p2.x-p1.x);
				float x_middle = (p1.x+p2.x)/2.0f;
				float y_middle = (p1.y+p2.y)/2.0f;
				std::cout<<"k = "<<k<<"\n";	
				float K_middle_to_center = -1/k;

				std::cout<<"K_middle_to_center = "<<K_middle_to_center<<"\n";	
				float d = dist2D(p1,p2); 
				std::cout<<"d = "<<d<<"\n";	
				float theta = acos((d/2)/r);
				std::cout<<"theta = "<<theta<<"\n";	
				float d_middle_to_center = r*sin(theta);
				std::cout<<"d_middle_to_center = "<<d_middle_to_center<<"\n";	

				float beta = atan(K_middle_to_center);
				float delta_x = d_middle_to_center*cos(beta);
				float delta_y = d_middle_to_center*sin(beta);
				x_center1 = x_middle+delta_x;
				y_center1 = y_middle+delta_y;

				x_center2 = x_middle-delta_x;
				y_center2 = y_middle-delta_y;
			}





			center[0] = x_center1;
			center[1] = y_center1;
			center[2] = x_center2;
			center[3] = y_center2;
		}






};
