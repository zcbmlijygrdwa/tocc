class MAFilter
{

	public:
		float buffer[10];
		int bufferedSize;
		int totalSize;
		bool ifBufferFull;
		float sum;

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
				return sum/bufferedSize;

			}
			else
			{

				return sum/totalSize;
			}

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
