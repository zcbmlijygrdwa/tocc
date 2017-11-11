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
#ifndef MAFilter_H
#define MAFilter_H

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

		void init();
		float put(float dataIn);
		void getSum();
		void reset();
};


#endif
