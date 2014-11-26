#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <map>
using namespace std;

#define R first
#define C second

typedef pair<int, int> ii;
int size;
int rs[]={-1, 0, 1, 0}, cs[]={0, 1, 0, -1};
int **r;
double ***q;
const int number_actions=3;
double maxQ=0;
int rmax, cmax;
int total_max=0;
void init_reward_matrix(){
	ifstream in("roadlarge.txt");
	r= new int*[size];
	for(int i=0; i<size; ++i)
		r[i]=new int[size];
	for(int i=0; i< size; ++i)
		for(int j=0; j< size; ++j){
			in>>r[i][j];
			if (total_max< r[i][j]){
				total_max=r[i][j];
				rmax=i; cmax=j;
			}
		}
	//r[size-1][size-1]=1000;
}

void init_q_matrix(){
	q=new double**[size];
	for(int i=0; i<size; ++i){
		q[i]=new double*[size];
		for(int j=0; j<size; ++j)
			q[i][j]=new double[number_actions];
	}
	for(int i=0; i<size;++i)
		for(int j=0; j<size; ++j)
			q[i][j][0]=q[i][j][1]=q[i][j][2]=q[i][j][3]=0;			
}

double gamma=0.5, alpha =0.5;

void p(){
	cout<<"qmatrix:"<<endl<<"[pos]: action > value"<<endl;
	for(int i=0; i< size; ++i)
		for(int j=0; j< size; ++j){
			for(int k=0; k< number_actions; ++k)
				printf("[ %d, %d]: %d > %0.5f \t",  i, j, k, (float)q[i][j][k]/(float)maxQ);
			cout<<endl;
		}
}
void q_p(){
	cout<<"q matrix, only best values are printed xD"<<endl;	
	
	for(int i=0; i<size; ++i){
		if (!i)cout<<"\t";
		cout<<i<<"\t\t";
	}cout<<endl;
	float maxq;
	for(int i=0; i< size; ++i){
		for(int j=0; j< size; ++j){
			if (!j)cout<<i<<":\t";			
			maxq=-10000000.0f;
			for(int k=0; k< number_actions; ++k)
					if (maxq < (float)q[i][j][k]/(float)maxQ)
						maxq = (float)q[i][j][k]/(float)maxQ;
			printf("%0.8f\t", maxq);
		}
		cout<<endl;
	}

}


inline int fix_pos(int pos){return (pos+size)%size;}

int main(){
	srand(time(0));
	cout<<"Ingrese tamaño de la matriz R"<<endl;
	cin>>size;
	float in;

	cout<<"Ingrese gamma (-1 default)";
	cin>>in; if (in<0.0f) gamma=in;
	cout<<"Ingrese alpha (-1 default)";
	cin>>in; if (in<0.0f) alpha=in;
	
	init_reward_matrix();
	init_q_matrix();

	int nepisodes=10000;
	int maxq, action;
	int nextstate, nextstate_, inxst;
	ii goalstate(rmax,cmax);
	for(int i=0; i< nepisodes; ++i){
	
		ii state(rand()%size, rand()%size);
		//cout<<"Start episode "<<i<<" with initial state:["<<state.R<<", "<<state.C<<"]"<<endl;
		if (r[state.R][state.C]<0) {
			i--;
			continue;
		}
		while(true){
			int next= rand()%number_actions, nr, nc;
			
			//Random next state
			nr=fix_pos(state.R + rs[next]);
			nc=fix_pos(state.C + cs[next]);
			ii nextstate(nr, nc);
			//we choose the max q action from the next state
			maxq=q[nextstate.R][nextstate.C][0];
			action=0;
			for(int i=0; i< number_actions; ++i)
				if (maxq <= q[nextstate.R][nextstate.C][i]){
					maxq = q[nextstate.R][nextstate.C][i];
					action = i;
				}
			
			//update q matrix
			q[state.R][state.C][next] += alpha * ((double) r[nextstate.R][nextstate.C] + gamma*q[nextstate.R][nextstate.C][action] - q[state.R][state.C][next]);
			maxQ=max(maxQ, q[state.R][state.C][next]);//we keep the maxq to normalize the q matrix at print process
			if (state == goalstate) break;
			state = nextstate;
		}
		//cout<<"End episode "<<i<<endl;
	}
	q_p();//print q matrix
}
