//#include "InvertJacobian.cpp"

class TOCC
{

	public:

		//==========================
		//	camera parameters
		//=========================

		//location of the camera
		float xt;
		float yt;
		float zt;

		//rotation of the camera
		float roll;
		float yaw;
		float pitch;

		//derivative of location of the camera
		float xt_v;
		float yt_v;
		float zt_v;

		//derivative of rotation of the camera
		float roll_v;
		float yaw_v;
		float pitch_v;



		//===================================
		//	on-screen objects parameters
		//===================================

		float x2d;
		float y2d;

		float x2d1;
		float y2d1;

		float xm;
		float distX;
		float distS;

		float x2d_v;
		float y2d_v;

		float x2d1_v;
		float y2d1_v;

		float xm_v;
		float distX_v;
		float distS_v;
		
		float xm_target;
		float distX_target;
		float distS_target;


		//===================================
		//	invert jacobian
		//===================================

		InvertJacobian ij;
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

		TOCC()
		{

			xt = 0;
			yt =  0;
			zt = 0;
			roll =  0;
			yaw =  0;
			pitch =  0;

			xt_v = 0;
			yt_v =  0;
			zt_v = 0;
			roll_v =  0;
			yaw_v =  0;
			pitch_v =  0;
			
			xm = 0;
                	distX = 0;
                	distS = 0;


		}


		void setCameraModel(float model[])
		{
			ij.setCameraModel(model);
		}  


		void setK_size(float data)
                {
                        ij.setK_size(data);
                }

		void set3DPoint1(float data[])
                {
			ij.set3DPoint1(data);
                }

                void set3DPoint2(float data[])
                {
			ij.set3DPoint2(data);
                }

		void setControlInput(float data[])
		{
			xm = data[0];
			distX = data[1];
			distS = data[2];
		}
                void setOnScreenTarget(float data[])
                {
		xm_target = data[0];
		distX_target = data[1];
		distS_target = data[2];
                }


                void setCameraTransformation(float data[])
                {
                        xt = data[0];
                        yt =  data[1];
                        zt =  data[2];
                        roll =  data[3];
                        yaw =  data[4];
                        pitch =  data[5];

			ij.setCameraTransformation(data);
                }



		void setCameraVelocity(float data[])
		{
			xt_v = data[0];
			yt_v =  data[1];
			zt_v =  data[2];
			roll_v =  data[3];
			yaw_v =  data[4];
			pitch_v =  data[5];
		}




		void updateInvertJacobian()
{
		ij.compute();
		float Jdata[9];
		 ij.getResults(Jdata);
		jacobian_1_1 = Jdata[0];
		jacobian_1_2 = Jdata[1];
		jacobian_1_3 = Jdata[2];
		jacobian_2_1 = Jdata[3];
		jacobian_2_2 = Jdata[4];
		jacobian_2_3 = Jdata[5];
		jacobian_3_1 = Jdata[6];
		jacobian_3_2 = Jdata[7];
		jacobian_3_3 = Jdata[8];


}



		//dynamic update
		void spin( float controlOutput[])
			{

				updateInvertJacobian();

				xm_v = -0.01f*(xm-xm_target);				
				distX_v = -0.01f*(distX-distX_target);				
				distS_v = -0.01f*(distS-distS_target);				
				//std::cout<<"------------------------"<<std::endl;
				
				/*
				std::cout<<"jacobian_1_1 = "<<jacobian_1_1<<std::endl;
				std::cout<<"jacobian_1_2 = "<<jacobian_1_1<<std::endl;
				std::cout<<"jacobian_1_3 = "<<jacobian_1_1<<std::endl;
				std::cout<<"jacobian_2_1 = "<<jacobian_2_1<<std::endl;
				std::cout<<"jacobian_2_2 = "<<jacobian_2_2<<std::endl;
				std::cout<<"jacobian_2_3 = "<<jacobian_2_3<<std::endl;
				std::cout<<"jacobian_3_1 = "<<jacobian_3_1<<std::endl;
				std::cout<<"jacobian_3_2 = "<<jacobian_3_2<<std::endl;
				std::cout<<"jacobian_3_3 = "<<jacobian_3_3<<std::endl;
				*/
				//update xt_v
				xt_v =  jacobian_1_1*xm_v+jacobian_1_2*distX_v+jacobian_1_3*distS_v;
				zt_v =  jacobian_2_1*xm_v+jacobian_2_2*distX_v+jacobian_2_3*distS_v;
				yaw_v = jacobian_3_1*xm_v+jacobian_3_2*distX_v+jacobian_3_3*distS_v;

				//output
				controlOutput[0] = xt_v;	
				controlOutput[1] = zt_v;	
				controlOutput[2] = yaw_v;	
				
				//std::cout<<"xm_v = "<<xm_v<<", distX_v = "<<distX_v<<", distS_v = "<<distS_v<<std::endl;
				//std::cout<<"controlOutput = "<<controlOutput[0]<<", "<<controlOutput[1]<<", "<<controlOutput[2]<<std::endl;


			}




};

