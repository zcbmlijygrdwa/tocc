
/*===================================
  This is a PID controller that can adjust its output based on the error (between the input and the reference value). 

  P, I, and D parameters can be used to tune the controller.

  This controller is a single-input single-output controller.

  Created on 2017/11/01 By Zhenyu Yang
  ================================== */


#include <iostream>

class PID{

	public:
		float target;	//target value

		float input;	//current value

		float error;	//current error
		float errorPrev;//previous error
		float error_d;	//error derivative
		float error_i;	//error integral

		float p;	
		float i;
		float d;

		float output_to_plant;	//output of the controller
		float output_offset;

		bool isFlipped;		//whether switch sign of the output

	public:

		void init()
		{
			target = 0;	

			input = 0;	

			error = 0;	
			errorPrev = 0;	
			error_d = 0;	
			error_i = 0;	

			p = 0;
			i = 0;
			d = 0;

			output_to_plant= 0;
			output_offset = 0;

			isFlipped= false;
		}

		void setTarget(float targetIn){
			target = targetIn;
		}



		void setPID(float pIn, float iIn, float dIn){
			p = pIn;
			i = iIn;
			d = dIn;
		}



		float spin(float inputIn){

			input = inputIn;

			if (!isFlipped) {

				error = target - input;

			} else {

				error = input - target;

			}

			error_d = error - errorPrev;
			error_i += error;
			errorPrev = error;

			output_to_plant = p * error + i * error_i + d * error_d;
			output_to_plant += output_offset;
			return output_to_plant;

		}

		void setOutputOffset(float input){
			//this function sets bias on the oncontroller output
			output_offset = input;
		}



		void clearErrors(){
			//this function restores all errors back to zeros.
			error = 0;
			errorPrev = 0;
			error_d = 0;
			error_i = 0;

		}
};


