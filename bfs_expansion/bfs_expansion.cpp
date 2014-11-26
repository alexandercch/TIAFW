#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <cstdio>
using namespace std;

typedef pair<int, int> point;

#define R first
#define C second

#define IN 0
#define OUT -100

vector<string> smatrix;
int rows, cols;
int **matrix, **dist, **vis;
int nsteps = 8;//4;
//int rs[]={0, 0, 1, -1}, cs[]={1, -1, 0, 0};
int rs[]={-1, -1, -1, 0, 1, 1, 1, 0}, cs[]={-1, 0, 1, 1, 1, 0, -1, -1};

queue<point> q;
inline bool is_in(point p){return p.R >= 0 && p.C >= 0 && p.R < rows && p.C < cols;}
void prepare(){
	dist= new int*[rows];
	vis= new int*[rows];
	for(int i=0; i< rows; ++i){
		dist[i]= new int[cols];
		vis[i]= new int[cols];
		for(int j=0; j< cols; ++j){
			vis[i][j]=0;
			dist[i][j]=100;
			if (matrix[i][j]!=IN)continue;
			for(int k=0; k< nsteps; ++k){
				point p(i+rs[k], j+cs[k]);
				if(is_in(p) && matrix[p.R][p.C]!=matrix[i][j]){//border
					cout<<"border:"<<i<<" "<<j<<endl;
					q.push(point(i, j));					
					dist[i][j]=0;
					vis[i][j]=1;
					break;
				}
			}
		}
	}
}
void unqueue(){
	cout<<"unqueue..."<<endl;
	while(q.size()){
		point p= q.front();
		cout<<p.R<<" "<<p.C<<endl;
		q.pop();
	}
}
void bfs(){
	cout<<"preparing..."<<endl;
	prepare();//unqueue();
	int d=-1;
	cout<<"visiting..."<<endl;
	while(q.size()){
		point p(q.front());
		q.pop();
		d++;
		vis[p.R][p.C] = 1;
		for(int i=0; i< nsteps; ++i){
			point nextp(p.R+rs[i], p.C+cs[i]);
			if (is_in(nextp) && !vis[nextp.R][nextp.C]){				
				if (matrix[nextp.R][nextp.C]==OUT) continue;
				dist[nextp.R][nextp.C]= dist[p.R][p.C]+1;
				q.push(nextp);
				vis[nextp.R][nextp.C]=1;
			}
		}
	}
}

void load(string filename){
	ifstream in(filename.c_str());
	string el;
	for(int i=0; i< rows; ++i){
			in>>el;
			smatrix.push_back(el);
	}
	matrix= new int*[rows];
	
	for(int i = 0; i < rows; ++i){
		matrix[i]= new int[cols];
		for(int j = 0; j < cols; ++j)
			if (smatrix[i][j]=='1')
				matrix[i][j]=OUT;						
			else
				matrix[i][j]=IN;
	}
}
double f(int val, int maxd){
	double res= pow(3, val);
	res/=maxd;
	return res;
}
void p(){
	for(int i=0; i< rows; ++i){
		for(int j=0; j< cols; ++j)
			if (matrix[i][j]==IN)
				printf("%0.1f\t", f(dist[i][j], 10000));
			else
				cout<<"-1\t";
		cout<<endl;
	}

}
int main(){
	cout<<"medidas de la matriz:(rows, cols)";
	cin>>rows>>cols;
	//cout<<"start:(row and col)";
	//cin>>
	cout<<"loading..."<<endl;
	load("pista.txt");
	cout<<"bfs..."<<endl;
	bfs();
	cout<<"printing..."<<endl;
	p();
}
