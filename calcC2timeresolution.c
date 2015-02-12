#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

int calcC2timeresolution() {
	TVectorD x (2003),y (2003);
	double x_in, y_in;
	std::string xtitle, ytitle, temp, name_template = "C1_Ch3G10_CSA_Ch2G10_BB_Ch1G3_BB_Ch4Trigger"; //0-9
	TH1D *hpx = new TH1D("hpx","Rise Times", 200, -1e-9,1e-8);
	
	//Start benchmark to measure run time
	gBenchmark->Start("calc100risetime");
	int valid_events = 0;
	
	for(int i = 0; i < 18918; i++) {
		double max_y = 0.0, risetime = 0.0, endtime = 0.0, starttime = 0.0;
		int riseindex = 0, max_index = 0;
		//Parse Text filename to obtain file stream for the file.
		std::ostringstream oss;
		if(i < 10)
			oss << name_template << "0000" << i << ".txt";
		else if(i < 100)
			oss << name_template << "000" << i << ".txt";
		else if(i < 1000)
			oss << name_template << "00" << i << ".txt";
		else if(i < 10000)
			oss << name_template << "0" << i << ".txt";
		else
			oss << name_template << i << ".txt"; 
		
		std::string str = oss.str();
		//cout << str << endl;
		std::ifstream file(str.data());
		
		//Consume first few lines
		for(int k = 0; k < 5; k++) {
			std::getline(file, temp);
		}	
		
		//Now get the numbers, put into TVectorD objects
		int j = 0;
		while(file) {
			getline(file, temp);
			istringstream ss(temp);
			string tokenx, tokeny;
		
			getline(ss, tokenx, ',');
			getline(ss, tokeny, ',');
			
			x[j] = atof(tokenx.data());
			y[j++] = atof(tokeny.data());
		}
		
		for(j = 0; j < 2000; j++) {
			if(y[j] > max_y) {
				max_y = y[j];
				max_index = j;
			}	
		}
		
		if(max_y > 0.015) { //Apply a "cut" to get rid of events with noise
				//Find the maximum value in the y vector and then print it, then get the time for it
			valid_events++;
			endtime = x[max_index];	
			printf("Max Y variable is %f at event %d\n", max_y, max_index);
			printf("Tenth of max_y: %f\n", max_y/10);
			
			//Now find the approx time at 10% starting from the max index
			j = max_index;
			while(j > 0) {
				if(y[j] < max_y/10) {
					starttime = x[j];
					riseindex = j;
					break;
				}
				j--;
			}
			
			//Now find the approx time at 90% from max
			j = max_index;
			while(j > 0) {
				if(y[j] < max_y * 0.9) {
					endtime = x[j];
					max_index = j;
					break;
				}
				j--;
			}
			
			//TODO: Bring code from updated risetime.C from laptop
			//Then put all these values into a histogram and then fit them
			
			printf("Rise time should start at event %d and end at %d\n", riseindex, max_index);
			risetime = endtime - starttime;
			cout << "The rise time is " << risetime << endl;
			hpx->Fill(risetime); //place risetimes onto histogram
		}	
		else
			cout << "Max value is " << max_y << ", could be noise" << endl;
	} 
	cout << "Found " << valid_events << " Valid events" << endl;
	gBenchmark->Show("calc100risetime");
	hpx->GetXaxis()->SetTitle("sec");
	hpx->GetYaxis()->SetTitle("occurrences");
	hpx->Draw();
	return 0;
}