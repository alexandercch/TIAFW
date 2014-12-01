#ifndef BFS_H
#define BFS_H

#include <algorithm>
#include <queue>

#include "types.h"

using namespace std;

class BFS
{
    public:
        BFS() {
            max_dist=-100;
        }
        virtual ~BFS() {}

        void B1();
        void prepare();
        void set_input_output_matrix(int **_matrix, double **_output);
        void set_rows_cols(int _rows, int _cols);
        int rows, cols;
        int **matrix, **dist, **vis;
        double **output;

    protected:
    private:
        void print_to_matrix();
        inline bool is_in(point p);

        queue<point> q;
        int max_dist;
};

int nsteps = 8;
int rs[]={-1, -1, -1, 0, 1, 1, 1, 0}, cs[]={-1, 0, 1, 1, 1, 0, -1, -1};
//int rs[]={0, 0, 1, -1}, cs[]={1, -1, 0, 0};

inline bool BFS::is_in(point p){return p.R >= 0 && p.C >= 0 && p.R < rows && p.C < cols;}

void BFS::set_input_output_matrix(int **_matrix, double **_output){
    matrix=_matrix;
    output=_output;
}

void BFS::set_rows_cols(int _rows, int _cols){
    rows = _rows;
    cols = _cols;
}
double f(int val, int maxd){
    maxd=pow(3, maxd);
	double res= pow(3, val);
	res/=maxd;
	return res;
}
void BFS::print_to_matrix(){
	for(int i=0; i< rows; ++i){
		for(int j=0; j< cols; ++j)
			if (matrix[i][j]==IN)
				output[i][j]= f(dist[i][j], max_dist);
			else
				output[i][j]=-1000;
	}
}

void BFS::prepare(){
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
					//cout<<"border:"<<i<<" "<<j<<endl;
					q.push(point(i, j));
					dist[i][j]=0;
					vis[i][j]=1;
					break;
				}
			}
		}
	}
}


void BFS::B1(){
    //cout<<"preparing..."<<endl;
	prepare();//unqueue();
	int d=-1;
	//cout<<"visiting..."<<endl;
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
				max_dist = max(max_dist, dist[nextp.R][nextp.C]);
				q.push(nextp);
				vis[nextp.R][nextp.C]=1;
			}
		}
	}
	print_to_matrix();
}

#endif // BFS_H
