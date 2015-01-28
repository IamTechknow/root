#include <fstream>
#include <string>
#include <iostream>

int maketree () {
	double x1[2003], y1[2003];
	
	TTree tree("Tree","Tree");
	double x_in, y_in;
	int value = 2003;
	tree.Branch("value", &value, "value/I");
	tree.Branch("x", &x_in, "x[value]/D");
	tree.Branch("y", &y_in, "y[value]/D");
	std::string xtitle, ytitle, temp;
	
	std::ifstream file("C3wfm_test_silicio_HV800_LV5_BW200_00000.txt");
	
	//Consume first few lines
	for(int i = 0; i < 4; i++)
		std::getline(file, temp);
	
	//for the next line, get the x and y axis titles
	file >> xtitle; file >> ytitle;
	
	while(file) {
		file >> x_in; 
		file >> y_in;
		cout<< y_in<<endl;
		tree.Fill();
	}
	
	TFile f("ntree_data1.root","RECREATE");
	tree.Write();
	f.Close();
	return 0;
}