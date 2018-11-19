#include <iostream>
#include <fstream>
#include <complex>
#include <iomanip>
using namespace std;

int main()
{
	float percent_distortion;
	int choice;
	float dB;
	fstream myfile;
	float *out_clipped;
	float max = 0;
	int num = 0, k;
	/* input buffers */
	float *samples = new float[150000];
	float *time = new float[150000];

	std::cout << std::setprecision(6) << std::fixed;

	/* input .dat file path */
	myfile.open("C:\\Anu\\academics\\Computer_Audio\\A2\\sin_20000Hz_-3dBFS_3s.dat", std::ios_base::in);
	fstream outfile;
	/* output .dat file path*/
	outfile.open("C:\\Anu\\academics\\Computer_Audio\\A3\\sin_20000Hz_-3dBFS_3s_out_clipped.dat", std::ios_base::out);

	float thresh;

	/* finding the maximum amplitude value in the given sample */
	while (myfile >> time[num] >> samples[num])
	{
		if (max < fabs(samples[num]))
			max = fabs(samples[num]);
		/* updating the number of samples */
		num++;
	}

	/* the distortion is applied based on the user input */
	printf("Enter the distortion required in percentage or dB\n");
	printf("\tPercentage - 1\n\tdB - 2\n");
	scanf("%d", &choice);
	switch (choice)
	{
		case 1:	printf("Enter the percentage for distortion\n");
				scanf("%f", &percent_distortion);
				/* calculation of the threshold value based on percentage*/
				thresh = ((100 - percent_distortion) * max) / 100;
				break;
		case 2: printf("Enter the distortion in dB\n");
				scanf("%f", &dB);
				/* calculation of the threshold value based on decibels*/
				thresh = pow(10, dB / 20);
				break;
	}

	/* allocation of output buffer */
	out_clipped = (float *)malloc(sizeof(float)*num*2);

	/* hard clipped filter implementation*/
	for (k = 0; k < num; k++)
	{
		/* checking if the input value is beyong the threshold value 
		   and assigning the output value accordingly */
		if (samples[k] < -thresh)
			out_clipped[k] = -thresh;
		else if (samples[k] > thresh)
			out_clipped[k] = thresh;
		else
			out_clipped[k] = samples[k];
	}

	/* writing the time and amplitude output values to the file */
	for (k = 0; k < num; k++)
	{
		outfile << time[k] << "\t"<< out_clipped[k] << endl;
	}
	return 0;
}