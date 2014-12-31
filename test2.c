#include <fstream>
#include <string>
#include <iostream>
int test2() {
	gStyle->SetOptFit();
	TCanvas *c1 = new TCanvas("c1","multigraph",700,500);
	c1->SetGrid();

    // draw a frame to define the range
	TMultiGraph *mg = new TMultiGraph();

//First graph
	TVectorD x (2003),y (2003);
	double x_in, y_in;
	std::string xtitle, ytitle, temp, name = "C2wfm_test_silicio_HV800_LV5_BW200_00009.txt";
	std::ifstream file(name.data());	
	//Consume first few lines
	for(int i = 0; i < 4; i++)
		std::getline(file, temp);	
	//for the next line, get the x and y axis titles
	file >> xtitle; file >> ytitle;	
	//Now get the numbers
	int i = 0;
	while(file) {
		file >> x_in; 
		file >> y_in;
		x[i] = x_in; y[i++] = y_in;
	}

	gr = new TGraph(x,y);
	mg->Add(gr);
	
//Second Graph
	TVectorD x2 (2003),y2 (2003);
	double x_in2, y_in2;
	std::string name2 = "C2wfm_test_silicio_HV800_LV5_BW200_00004.txt";
	std::ifstream file2(name2.data());	
	//Consume first few lines
	for(int j = 0; j < 5; j++)
		std::getline(file, temp);	
	//Now get the numbers
	i = 0;
	while(file2) {
		file2 >> x_in2; 
		file2 >> y_in2;
		x[i] = x_in2; y[i++] = y_in2;
	}

	TGraph *gr2 = new TGraph(x2,y2);
	mg->Add(gr2);
	
	
	mg->Draw("AL");
	
	// TCanvas::Update() draws the frame, after which one can change it
	c1->Update();
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();
	return 0;
}