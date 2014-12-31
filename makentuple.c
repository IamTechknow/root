#include <fstream>
#include <string>
#include <iostream>

int makentuple () {
	TNtuple data("ntuple","Example N-tuple","x:y");
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
	
	//Now get the numbers
	int i = 0;
	
	while(file) {
		file >> x_in; 
		file >> y_in;
		data.Fill(x_in, y_in);
	}
	
	TFile f("ntuple_data.root","RECREATE");
	data.Write();
	f.Close();
	return 0;
}