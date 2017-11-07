#include <iostream>

class PID{

	public:
		float target;

		float input;

		float error;
		float errorPrev;
		float error_d;
		float error_i;

		float p;
		float i;
		float d;

		float output_to_plant;
		float output_offset;

		bool isFlipped;

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

			std::cout<<"error = "<<error<<std::endl;
			std::cout<<"errorPrev = "<<errorPrev<<std::endl;
			std::cout<<"error_d = "<<error_d<<std::endl;
			output_to_plant = p * error + i * error_i + d * error_d;

			std::cout<<"output_to_plant = "<<output_to_plant<<std::endl;
			output_to_plant += output_offset;
			std::cout<<"output_to_plant = "<<output_to_plant<<std::endl;
			return output_to_plant;

		}


		



		void setOutputOffset(float input){

			output_offset = input;

		}



		void clearErrors(){

			error = 0;

			errorPrev = 0;

			error_d = 0;

			error_i = 0;

		}


/*
		string errorToString(string pidName){

			return ("PID "+pidName+": target = "+target+", input = "+input+", error = "+error+", error_i = "+error_i+", error_d = "+error_d+", output = "+output_to_plant);

		}

*/

};


