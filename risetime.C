#include <fstream>
#include <string>
#include <iostream>


int risetime() {
	/*
		Create vectors
		Read the file
		Feed vectors
		Make the graph
	*/
	TVectorD x (2003),y (2003);
	TGraph tr;
	double x_in, y_in; 
	double max_y = 0.0, risetime = 0.0, endtime = 0.0, starttime = 0.0;
	std::string xtitle, ytitle, temp;
	
	std::ifstream file("C2wfm_test_silicio_HV800_LV5_BW200_00001.txt");
	
	//Consume first few lines
	for(int i = 0; i < 4; i++)
		std::getline(file, temp);
	
	//for the next line, get the x and y axis titles
	file >> xtitle; file >> ytitle;
	std::cout << xtitle + " " + ytitle << std::endl;
	
	//Now get the numbers
	int i = 0, riseindex = 0, max_index = 0;
	while(file) {
		file >> x_in; 
		file >> y_in;
		x[i] = x_in; y[i++] = y_in;
	}
	
	//Find the maximum value in the y vector and then print it, then get the time for it
	for(i = 0; i < 1200; i++) {
		if(y[i] > max_y) {
			max_y = y[i];
			max_index = i;
		}	
	}
	endtime = x[max_index];	
	printf("Max Y variable is %f at event %d\n", max_y, max_index);
	printf("Tenth of max_y: %f\n", max_y/10);
	
	//Now find the approx time at 10% starting from the max index
	
	i = max_index;
	while(i > 0) {
		if(y[i] < max_y/10) {
			//access element ahead of it
			starttime = x[i];
			riseindex = i;
			break;
		}
		i--;
	}
	
	printf("Rise time should start at event %d\n", riseindex);
	risetime = endtime - starttime;
	
	
	TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
	c1->SetFillColor(42);
	c1->SetGrid();
	
	gr = new TGraph(x,y);
	gr->SetTitle("a simple graph");
	gr->GetXaxis()->SetTitle(xtitle.data());
	gr->GetYaxis()->SetTitle(ytitle.data());
	gr->Draw("ACP");
	
	// TCanvas::Update() draws the frame, after which one can change it
	c1->Update();
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();
	
	cout << "The rise time is " << risetime << endl;
	return 0;
}