#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

int testmulti() {
	double x_in, y_in;
	std::string xtitle, ytitle, temp, name_template = "C2wfm_test_silicio_HV800_LV5_BW200_000"; //0-9
	TMultiGraph *mg = new TMultiGraph();
	TGraph *g[100]; //put each graph here
	
	//Start benchmark to measure run time
	gBenchmark->Start("testmulti");
	
	for(int i = 0; i < 100; i++) {
		//Parse Text filename to obtain file stream for the file.
		std::ostringstream oss;
		if(i < 10)
			oss << name_template << 0 << i << ".txt"; 
		else
			oss << name_template << i << ".txt"; 
		std::string str = oss.str();
	
		std::ifstream file(str.data());
		g[i] = new TGraph();
		
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
			g[i]->SetPoint(j++,x_in,y_in);
		}
		mg->Add(g[i]);
	} 
	
	TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,800,600);
	c1->SetFillColor(42);
	c1->SetGrid();
	mg->SetTitle("Mutliple Graphs");
	mg->Draw("a");
	
	//Show benchmark results
	gBenchmark->Show("testmulti");
	
	// TCanvas::Update() draws the frame, after which one can change it
	c1->Update();
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();

	return 0;
}