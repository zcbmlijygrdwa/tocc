#include <iostream>
#include <math.h>
#include "InvertJacobian.cpp"
#include "TOCC.cpp"
#include "PinHole.cpp"
#include "ToccController.cpp"

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


	//================================
	//Invert Jacobian test
	//================================


	std::cout<<"-----------------------------"<<std::endl;


	InvertJacobian ij;

	ij.setCameraModel(cameraModel);
	ij.setCameraTransformation(cameraTransformation);
	ij.set3DPoint1(point3D1);
	ij.set3DPoint2(point3D2);
	ij.setK_size(1.0f);

	ij.compute();
	float d[3];
	ij.getResults(d);

	std::cout<<"invert jacobian obtained!"<<std::endl;
	std::cout<<"data1 = "<<d[0]<<std::endl;
	std::cout<<"data2 = "<<d[1]<<std::endl;
	std::cout<<"data3 = "<<d[2]<<std::endl;

	std::cout<<"data4 = "<<d[3]<<std::endl;
	std::cout<<"data5 = "<<d[4]<<std::endl;
	std::cout<<"data6 = "<<d[5]<<std::endl;

	std::cout<<"data7 = "<<d[6]<<std::endl;
	std::cout<<"data8 = "<<d[7]<<std::endl;
	std::cout<<"data9 = "<<d[8]<<std::endl;


	//================================
	//TOCC test
	//================================
/*
	TOCC tocc;

	tocc.setCameraModel(cameraModel);
	tocc.setCameraTransformation(cameraTransformation);
	tocc.set3DPoint1(point3D1);
	tocc.set3DPoint2(point3D2);
	tocc.setK_size(1.0f);
	tocc.setOnScreenTarget(onScreenTargets);




	xm_v = 0.001f;
	distX_v = 0;
	distS_v = 0;


	std::cout<<"initial : xm_v = "<<xm_v<<", distX_v = "<<distX_v<<", distS_v = "<<distS_v<<std::endl;

	float controlInput[3];
	controlInput[0] = xm_v;
	controlInput[1] = distX_v;
	controlInput[2] = distS_v;



	float controlOutput[3];

	for(int i = 0; i<0; i++)
	{


		tocc.spin(controlOutput);
		
		//update
		xt += controlOutput[0];
		zt += controlOutput[1];
		yaw += controlOutput[2];


		cameraTransformation[0] = xt;
		cameraTransformation[2] = zt;
		cameraTransformation[4] = yaw;
		ph.setCameraTransformation(cameraTransformation);
		tocc.setCameraTransformation(cameraTransformation);

		ph.compute();
		ph.getResults(phOutput);
		xm = (phOutput[0]+phOutput[2])/2.0f;
		distX = phOutput[0]-phOutput[2];
		float s1 = ((x3d-xt)*(x3d-xt) + (z3d - zt)*(z3d - zt))*K_size;
		float s2 = ((x3d2-xt)*(x3d2-xt) + (z3d2 - zt)*(z3d2 - zt))*K_size;

		distS = s1 - s2;

		std::cout<<"update: xm = "<<xm<<", distX = "<<distX<<", distS = "<<distS<<std::endl;
		std::cout<<"update: xt = "<<xt<<", zt = "<<zt<<", yaw = "<<yaw<<std::endl;

		float controlInput[3];
		controlInput[0] = xm;
		controlInput[1] = distX;
		controlInput[2] = distS;


		tocc.setControlInput(controlInput);
	}
*/







ToccController tc;
tc.init();
tc.setCameraTransformation(cameraTransformation);
tc.set3DPoint1(point3D1);
tc.set3DPoint2(point3D2);
float target[3] = {300,20,10};
tc.setControlTargets(target);
float controlIn[3] = {29,2,3};
tc.setControlInput(controlIn);
float output[3];


for(int i = 0; i < 100;i++){

controlIn[0] = 29+i*0.05f;
tc.setControlInput(controlIn);
tc.set3DPoint1(point3D1);
tc.set3DPoint2(point3D2);
tc.setCameraTransformation(cameraTransformation);

tc.spin(output);
std::cout<<"output[0] = "<<output[0]<<std::endl;
std::cout<<"output[1] = "<<output[1]<<std::endl;
std::cout<<"output[2] = "<<output[2]<<std::endl;
std::cout<<"========================"<<std::endl;
cameraTransformation[0] = output[1];
cameraTransformation[2] = output[2];
cameraTransformation[4] = output[0];

}
}
