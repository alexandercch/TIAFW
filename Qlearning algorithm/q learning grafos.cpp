//this code has been made from the tutorial found at
//http://mnemstudio.org/path-finding-q-learning-tutorial.htm
//there update q matrix equation seems to tbe wrong :( or incomplete :)
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include <algorithm>
using namespace std;
const int size=6;
int r[size][size]	=	{{-1, -1, -1, -1,  0, -1},
						{ -1, -1, -1,  0, -1, 100},
						{ -1, -1, -1,  0, -1, -1},
						{ -1,  0,  0, -1,  0, -1},
						{  0, -1, -1,  0, -1, 100},
						{ -1,  0, -1, -1,  0, 100}};

float q[size][size];
float gamma=0.8;
int state=1;
int goalstate=5;
void p(){
	for(int i=0; i< size; ++i){
		if (i==0){
			for(int l=0; l<size; ++l)cout<<"\t"<<l;
			cout<<endl;
		}
		for(int j=0; j< size; ++j){
			if (j==0)cout<<i<<"\t";
			cout<<q[i][j]<<"\t";
		}
		cout<<endl;
	}
}


int main(){
	srand(time(0));
	int nepisodes=200;
	int maxq, imaxq;
	int nextstate, nextstate_, inxst;
	for(int i=0; i< nepisodes; ++i){
		state=rand()%size;
		//cout<<"cheat!!, put initial state manuallu-->";
		//cin>>state;
		cout<<"episode with initial state:"<<state<<endl;
		//while(state!=goalstate){			
		while(true){			
			nextstate_=(rand()%size) + 1;
			inxst=-1;//choose the next state
			while(nextstate_){				
				inxst++;
				inxst%=size;
				if (r[state][inxst]!=-1)
					nextstate_--;
			}
			nextstate=inxst;
			cout<<"next state:"<<nextstate<<endl;
			//cout<<"cheat!!, put next state manuallu-->";
			//cin>>nextstate;
			//we choose the max q action from the next state
			maxq=imaxq=0;
			for(int i=0; i< size; ++i){
				if (r[nextstate][i]!=-1){
					if (maxq<=q[nextstate][i]){
						maxq=q[nextstate][i];
						imaxq=i;
					}				
				}			
			}
			cout<<"max found in q at: ["<<nextstate<<"]["<<imaxq<<"] :"<<q[nextstate][imaxq]<<endl;
			//update q matrix
			q[state][nextstate]= r[state][nextstate] + gamma*q[nextstate][imaxq];
			if (state==goalstate) break;
			state=nextstate;
			//p();
		}
		cout<<"End episode "<<i<<endl;
		//p();
	}
	p();
}
