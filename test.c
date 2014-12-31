#include <fstream>
#include <string>
#include <iostream>


int test() {
	/*
		Create vectors
		Read the file
		Feed vectors
		Make the graph
	*/
	TVectorD x (2003),y (2003);
	TGraph tr;
	double x_in, y_in;
	std::string xtitle, ytitle, temp;
	
	std::ifstream file("C2wfm_test_silicio_HV800_LV5_BW200_00000.txt");
	
	//Consume first few lines
	for(int i = 0; i < 4; i++)
		std::getline(file, temp);
	
	//for the next line, get the x and y axis titles
	file >> xtitle; file >> ytitle;
	std::cout << xtitle + " " + ytitle << std::endl;
	
	//Now get the numbers
	int i = 0;
	while(file) {
		file >> x_in; 
		file >> y_in;
		x[i] = x_in; y[i++] = y_in;
	//	printf("%d %d", x_in, y_in);
	}
	
	//TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
	//c1->SetFillColor(42);
	//c1->SetGrid();
	
	gr = new TGraph(x,y);
	gr->SetTitle("a simple graph");
	gr->GetXaxis()->SetTitle(xtitle);
	gr->GetYaxis()->SetTitle(ytitle);
	gr->Draw("ACP");
	
	// TCanvas::Update() draws the frame, after which one can change it
	c1->Update();
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();
	//cout << x.size() << " " << y.size() << endl;
	//for(int i = 0; i < 10; i++)
	//	cout << x[i] << " " << y[i] << endl;
	return 0;
}