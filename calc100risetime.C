#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

int calc100risetime() {
	TVectorD x (2003),y (2003);
	double x_in, y_in;
	std::string xtitle, ytitle, temp, name_template = "C2wfm_test_silicio_HV800_LV5_BW200_000"; //0-9
	
	//Start benchmark to measure run time
	gBenchmark->Start("calc100risetime");
	
	for(int i = 0; i < 100; i++) {
		double max_y = 0.0, risetime = 0.0, endtime = 0.0, starttime = 0.0;
		int riseindex = 0, max_index = 0;
		//Parse Text filename to obtain file stream for the file.
		std::ostringstream oss;
		if(i < 10)
			oss << name_template << 0 << i << ".txt"; 
		else
			oss << name_template << i << ".txt"; 
		std::string str = oss.str();
		std::ifstream file(str.data());
		
		//Consume first few lines
		for(int k = 0; k < 4; k++)
			std::getline(file, temp);
		//for the next line, get the x and y axis titles
		file >> xtitle; file >> ytitle;
		
		//Now get the numbers, put into graph
		int j = 0;
		while(file) {
			file >> x_in; 
			file >> y_in;
			x[j] = x_in; y[j++] = y_in;
		}
		
		//Find the maximum value in the y vector and then print it, then get the time for it
		for(j = 0; j < 1200; j++) {
			if(y[j] > max_y) {
				max_y = y[j];
				max_index = j;
			}	
		}
		if(max_y > 0.0015) {
			endtime = x[max_index];	
			printf("Max Y variable is %f at event %d\n", max_y, max_index);
			printf("Tenth of max_y: %f\n", max_y/10);
			
			//Now find the approx time at 10% starting from the max index
			
			j = max_index;
			while(j > 0) {
				if(y[j] < max_y/10) {
					//access element ahead of it
					starttime = x[j];
					riseindex = j;
					break;
				}
				j--;
			}
			
			//TODO: Bring code from updated risetime.C from laptop
			//Then put all these values into a histogram and then fit them
			
			printf("Rise time should start at event %d\n", riseindex);
			risetime = endtime - starttime;
			cout << "The rise time is " << risetime << endl;
		}	
		else
			cout << "Max value is " << max_y << ", could be noise" << endl;
	} 
	gBenchmark->Show("calc100risetime");
	return 0;
}
