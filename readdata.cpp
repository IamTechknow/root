#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
	/*
		Create vectors
		Read the file
		Feed vectors
		Make the graph
	*/
	vector<double> x,y;
//	TGraph tr;
	double x_in, y_in;
	string xtitle, ytitle, temp;
	
	std::ifstream file("C2wfm_test_silicio_HV800_LV5_BW200_00001.txt");
	
	//Consume first few lines
	for(int i = 0; i < 4; i++)
		std::getline(file, temp);
	
	//for the next line, get the x and y axis titles
	file >> xtitle; file >> ytitle;
	cout << xtitle + " " + ytitle << endl;
	
	//Now get the numbers
	while(file) {
		file >> x_in; 
		file >> y_in;
		x.push_back(x_in); y.push_back(y_in);
	//	printf("%d %d", x_in, y_in);
		//anything needed to put file to the next line?
	}
	
	/*gr = new TGraph(x,y);
	gr->SetTitle("a simple graph");
	gr->GetXaxis()->SetTitle("X title");
	gr->GetYaxis()->SetTitle("Y title");
	gr->Draw("ACP");
	
	// TCanvas::Update() draws the frame, after which one can change it
	c1->Update();
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();*/
	cout << x.size() << " " << y.size() << endl;
	for(int i = 0; i < 10; i++)
		cout << x[i] << " " << y[i] << endl;
	return 0;
}