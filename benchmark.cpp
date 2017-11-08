#include <iostream>
#include <math.h>
#include "TOCC.h"
#include "PinHole.cpp"

int main()
{
	std::cout<<"hello"<<std::endl;


	//inputs for camera model
	float x0 = 0;
	float y0 = 0;
	float fx = 50.0f/1000;
	float fy = fx;
	float cameraModel[4];
	cameraModel[0] = x0;
	cameraModel[1] = y0;
	cameraModel[2] = fx;
	cameraModel[3] = fy;

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

	PinHole ph;
	ph.setCameraModel(cameraModel);
	ph.setCameraTransformation(cameraTransformation);
	ph.set3DPoint1(point3D1);
	ph.set3DPoint2(point3D2);

	ph.compute();
	float phOutput[4];
	ph.getResults(phOutput);
	//std::cout<<"x = 1, add1(x)  = "<<(add1(1))<<std::endl;

	std::cout<<"------------------------------------------"<<std::endl;
	std::cout<<"x2d1 = "<<phOutput[0]<<std::endl;
	std::cout<<"y2d1 = "<<phOutput[1]<<std::endl;
	std::cout<<"x2d2 = "<<phOutput[2]<<std::endl;
	std::cout<<"y2d2 = "<<phOutput[3]<<std::endl;
	std::cout<<"------------------------------------------"<<std::endl;










TOCC tocc;
tocc.init();
tocc.setCameraTransformation(cameraTransformation);
tocc.set3DPoint1(point3D1);
tocc.set3DPoint2(point3D2);
float target[3] = {300,20,10};
tocc.setControlTargets(target);
float controlIn[3] = {29,2,3};
tocc.setControlInput(controlIn);
float output[3];


for(int i = 0; i < 100;i++){

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
}
