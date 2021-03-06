
// g++ -o test test.cpp TOCC.cpp basicController/PID.cpp filters/MAFilter.cpp cameraProjection/PinHole.cpp toric/Circle.cpp trajectory/TrajectoryPlanning.cpp

#include <iostream>
#include <math.h>
#include "TOCC.h"
#include "cameraProjection/PinHole.h"
#include "toric/Circle.h"
#include "struct/Point2D.h"
#include "filters/MAFilter.h"
#include "trajectory/TrajectoryPlanning.h"

int main()
{


	//inputs for camera model
	float x0 = 0;
	float y0 = 0;
	float fx = 50.0f/1000;
	float fy = fx;
	float cameraModel[7];
	float fov = (60/180.0f)*3.14;
	float resWidth = 500;
	float resHeight  = 800;
	cameraModel[0] = x0;
	cameraModel[1] = y0;
	cameraModel[2] = fx;
	cameraModel[3] = fy;
	cameraModel[4] = fov;
	cameraModel[5] = resWidth;
	cameraModel[6] = resHeight;

	float K_size = 1.0f;
	//inputs for camera translationi
	float xt = 0;
	float yt = 0;
	float zt = 0;
	float roll = 0;
	float yaw = 0.2;
	float pitch = 0;
	float cameraTransformation[6];
	cameraTransformation[0] = xt;
	cameraTransformation[1] = yt;
	cameraTransformation[2] = zt;
	cameraTransformation[3] = roll;
	cameraTransformation[4] = yaw;
	cameraTransformation[5] = pitch;


	//inputs for 2 3D points
	float x3d = -15;
	float y3d = 0;
	float z3d = 10;
	float point3D1[3];
	point3D1[0] = x3d;
	point3D1[1] = y3d;
	point3D1[2] = z3d;


	float x3d2 = 5;
	float y3d2 = 0;
	float z3d2 = 10;
	float point3D2[3];
	point3D2[0] = x3d2;
	point3D2[1] = y3d2;
	point3D2[2] = z3d2;




	//on-screen 2D points

	float xm = 0;
	float distX = 0;
	float distS = 0;


	float xm_v = 0;
	float distX_v = 0;
	float distS_v = 0;

	float xm_target = 0.2f;
	float distX_target = 0.15f;
	float distS_target = 180.0f;
	float onScreenTargets[3];
	onScreenTargets[0] = xm_target;
	onScreenTargets[1] = distX_target;
	onScreenTargets[2] = distS_target;



	//================================
	//pinhole projection test

	std::cout<<"--------- Pin Hole projection test -------"<<std::endl;
	PinHole ph;
	ph.setCameraModel(cameraModel);
	ph.setCameraTransformation(cameraTransformation);
	ph.set3DPoint1(point3D1);
	ph.set3DPoint2(point3D2);

	ph.compute();
	float phOutput[4];
	ph.getResults(phOutput);


	std::cout<<"x2d1 = "<<phOutput[0]<<std::endl;
	std::cout<<"y2d1 = "<<phOutput[1]<<std::endl;
	std::cout<<"x2d2 = "<<phOutput[2]<<std::endl;
	std::cout<<"y2d2 = "<<phOutput[3]<<std::endl;





	std::cout<<"--------- tocc test -------"<<std::endl;



//TOCC test
TOCC tocc;
tocc.init();

tocc.setCameraModel(cameraModel);
tocc.setCameraTransformation(cameraTransformation);
tocc.set3DPoint1(point3D1);
tocc.set3DPoint2(point3D2);
float target[4] = {300,20,10,5};
tocc.setControlTargets(target);
float controlIn[3] = {29,2,3};
tocc.setControlInput(controlIn);
float output[3];


for(int i = 0; i < 10;i++){

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

}





//================ Circle test
	std::cout<<"--------- circle calculation test -------"<<std::endl;
Point2D pp1;
Point2D pp2;
Point2D cam;
Circle c;
float out[2];

//case 1
std::cout<<"case 1:"<<std::endl;
pp1.x = 1;
pp1.y = 1;

pp2.x = 1;
pp2.y = -1;

cam.x = -4;
cam.y = 4;

c.r = 1.414;
c.getCenter(pp1,pp2,cam,out);
std::cout<<"true center = ["<<0<<", "<<0<<"]"<<std::endl;
std::cout<<"calculated center = ["<<out[0]<<", "<<out[1]<<"]"<<std::endl;


//case 2
std::cout<<"case 2:"<<std::endl;
pp1.x = 1;
pp1.y = 1;

pp2.x = 1;
pp2.y = -1;

cam.x = 4;
cam.y = 4;

c.r = 1.414;
c.getCenter(pp1,pp2,cam,out);
std::cout<<"true center = ["<<2<<", "<<0<<"]"<<std::endl;
std::cout<<"calculated center = ["<<out[0]<<", "<<out[1]<<"]"<<std::endl;

//case 3
std::cout<<"case 3:"<<std::endl;
pp1.x = 1;
pp1.y = 1;

pp2.x = -1;
pp2.y = 1;

cam.x = -4;
cam.y = 4;

c.r = 1.414;
c.getCenter(pp1,pp2,cam,out);
std::cout<<"true center = ["<<0<<", "<<2<<"]"<<std::endl;
std::cout<<"calculated center = ["<<out[0]<<", "<<out[1]<<"]"<<std::endl;

//case 4
std::cout<<"case 4:"<<std::endl;
pp1.x = 1;
pp1.y = 1;

pp2.x = -1;
pp2.y = 1;

cam.x = -4;
cam.y = -4;

c.r = 1.414;
c.getCenter(pp1,pp2,cam,out);
std::cout<<"true center = ["<<0<<", "<<0<<"]"<<std::endl;
std::cout<<"calculated center = ["<<out[0]<<", "<<out[1]<<"]"<<std::endl;

//case 5
std::cout<<"case 5:"<<std::endl;
pp1.x = 1;
pp1.y = 1;

pp2.x = -1;
pp2.y = 1;

cam.x = -4;
cam.y = -4;

c.r = 1;
c.getCenter(pp1,pp2,cam,out);
std::cout<<"true center = ["<<0<<", "<<0<<"]"<<std::endl;
std::cout<<"calculated center = ["<<out[0]<<", "<<out[1]<<"]"<<std::endl;


//case 6
std::cout<<"case 6:"<<std::endl;
pp1.x = -0.137306;
pp1.y = 2.882683;

pp2.x = -1.914549;
pp2.y = 3.478368;

cam.x = -4;
cam.y = -4;

c.r = 10;
c.getCenter(pp1,pp2,cam,out);
std::cout<<"true center = ["<<0<<", "<<0<<"]"<<std::endl;
std::cout<<"calculated center = ["<<out[0]<<", "<<out[1]<<"]"<<std::endl;



//test for MA filter
	std::cout<<"--------- MA filter test -------"<<std::endl;
MAFilter maf;
maf.init();
maf.setBufferSize(20);

for(int i = 0;i<10;i++)
{

std::cout<<(i+1)<<"th round, putting 1 into MA filter, filter returns: "<<maf.put(1)<<std::endl;

}


std::cout<<"=========================================="<<std::endl;
maf.reset();
for(int i = 0;i<30;i++)
{

std::cout<<(i+1)<<"th round, putting 1 into MA filter, filter returns: "<<maf.put(1)<<std::endl;

}


std::cout<<"=========================================="<<std::endl;
maf.reset();


for(int i = 0;i<10;i++)
{

std::cout<<(i+1)<<"th round, putting "<<i<<" into MA filter, filter returns: "<<maf.put(i)<<std::endl;

}


std::cout<<"=========================================="<<std::endl;
maf.reset();
for(int i = 0;i<30;i++)
{

std::cout<<(i+1)<<"th round, putting "<<i<<" into MA filter, filter returns: "<<maf.put(i)<<std::endl;

}


}
