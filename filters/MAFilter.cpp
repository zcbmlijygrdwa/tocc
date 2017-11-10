/*============================
  This class is an implementation of a moving average filter. This is a single-input and single-output filter.

  The class take the raw data as the input, and returns the filtered data as the output.

Input:
dataIn: raw data input

Ouput:
filteredData: filtered data

Parameters:
None

Usage:

Filter maf;
maf.init();

......
realTimeLoop
{
....
filteredData = maf.spin(rawData);
...
}

maf.reset(); //reset the filter


Created by Zhenyu Yang on 2017/10/25

==============================================*/


class MAFilter
{

	public:
		float buffer[10];
		int bufferedSize;
		int totalSize;
		bool ifBufferFull;
		float sum;
		float filteredData;

	public:

		void init()
		{
			bufferedSize = 0;
			totalSize = 10;
			ifBufferFull = false;
			sum = 0;
		}

		float put(float dataIn)
		{

			if(bufferedSize<totalSize)
			{
				buffer[bufferedSize] = dataIn;
				bufferedSize++;
			}
			else
			{
				ifBufferFull = true;
				bufferedSize = 0;
				buffer[bufferedSize] = dataIn;
				bufferedSize++;
			}

			getSum();

			if(!ifBufferFull)
			{
				filteredData =  sum/bufferedSize;

			}
			else
			{

				filteredData =  sum/totalSize;
			}

			return filteredData;

		}



		void getSum()
		{
			sum = 0;

			if(!ifBufferFull)
			{
				for(int i = 0 ;i<bufferedSize;i++)
				{
					sum+=buffer[i];
				}

			}

			else
			{

				for(int i = 0 ;i<totalSize;i++)
				{
					sum+=buffer[i];
				}
			}
		}

		void reset()
		{
			ifBufferFull = false;
			bufferedSize = 0;

			for(int i = 0 ;i<totalSize;i++)
			{
				buffer[i] = 0;
			}

		}

};
