#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(){
	float r, c;
	float fr, fc;
	cout<<"set output dimensions(r and c):"<<endl;
	cin>>r>>c;
	string filename;
	cout<<"string file:"<<endl;
	cin>>filename;
	string line;
	vector<string> lines;

	ifstream in(filename.c_str());
	ofstream out("pista.txt");
	int trows=0;
	while(getline(in, line)){
		lines.push_back(line);	
		trows++;
	}

	fr = trows;
	fc = lines[0].size();
	cout<<"fr-fc:"<<fr<<" "<<fc<<endl;	
	for(float i = 0.0; i < fr; i+=(fr/r)){
		for(float j = 0.0; j < fc; j+= (fc/c)){
			out<<(int)(lines[(int)i][(int)j]==' ');
		}
		out<<endl;
	}
}
