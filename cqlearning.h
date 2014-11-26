#ifndef CQLEARNING_H
#define CQLEARNING_H

#include <cstdio>
#include <fstream>
#include <string>
#include "background.h"
#include "types.h"
#include "bfs.h"
#include "car.h"

using namespace std;
#define OUT_ROAD -1000
#define IN_ROAD 0


class CQLearning
{
    public:
        CQLearning() {
            alpha=0.1;gamma=0.9;nepisodes=10000;
        }
        virtual ~CQLearning() {}
        void set_r_matrix(int **_bg, int _rows, int _cols);
        void set_alpha_gamma(double _alpha, double _gamma);
        void set_nepisodes(int _nepisodes);
        void train(CCar *_car);
        Coord start;
    protected:
    private:
        double **r;
        int **bg;
        int rows, cols;
        int nepisodes;

        double alpha, gamma;
        void print_r_to_file(string filename);
        void reward_matrix_1();
};

void CQLearning::train(CCar *_car){


}




void CQLearning::set_alpha_gamma(double _alpha, double _gamma){
    alpha = _alpha;
    gamma = _gamma;
}
void CQLearning::set_nepisodes(int _nepisodes){
    nepisodes=_nepisodes;
}
void CQLearning::set_r_matrix(int **_bg, int _rows, int _cols){
    bg=_bg;
    cols = _cols;
    rows = _rows;
    //set r matriz size
    r= new double*[rows];
    for(int i=0; i< rows; ++i)
        r[i]= new double[cols];
    //load data
    /*for(int i=0; i< rows; ++i)
        for(int j=0; j< cols; ++j)
            r[i][j] = (bg->matrix[i][j]?OUT_ROAD:IN_ROAD);*/
    reward_matrix_1();
}
void CQLearning::reward_matrix_1(){
    BFS bfs;
    bfs.set_input_output_matrix(bg, r);
    bfs.set_rows_cols(rows, cols);
    bfs.B1();
    print_r_to_file("rmatrix.txt");
}

void CQLearning::print_r_to_file(string filename){
    ofstream out(filename.c_str());
    char *buffer= new char[30];
    for(int i=0; i< rows; ++i){
		for(int j=0; j< cols; ++j){
            sprintf(buffer, "%0.1f\t", r[i][j]);
            out<<buffer;
            //out<<r[i][j]<<"\t";
        }
        out<<endl;
	}
}


#endif // CQLEARNING_H
