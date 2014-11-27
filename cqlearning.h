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

struct qstate{int r, c, angle, action;};

class CQLearning
{
    public:
        CQLearning() {
            alpha=0.5;gamma=0.5;nepisodes=1000000;
        }
        virtual ~CQLearning() {}
        void set_r_matrix(int **_bg, int _rows, int _cols);
        void set_alpha_gamma(double _alpha, double _gamma);
        void set_nepisodes(int _nepisodes);
        void train(CCar *car);
        qstate start;
    protected:
    private:
        void print_r_to_file(string filename);
        void reward_matrix_1();
        void init_q();
        inline bool is_in_road(qstate &state);
        double R(qstate s, CCar *car);
        double **r, ****q;
        int **bg;
        int rows, cols;
        int nepisodes;
        double alpha, gamma;
};

inline bool CQLearning::is_in_road(qstate &state){return bg[state.r][state.c]==IN;}
void p_state(qstate q){
    cout<<q.r<<" "<<q.c<<" "<<q.angle<<" "<<q.action<<endl;
}
void CQLearning::init_q(){
    q= new double***[rows];
    for(int i=0; i< rows; ++i){
        q[i]= new double**[cols];
        for(int j=0; j<cols; ++j){
            q[i][j] = new double*[ANGLES];
            for(int k=0; k< ANGLES; ++k){
                q[i][j][k]= new double[CAR_MOVES];
                for(int l=0; l< CAR_MOVES; ++l)
                    q[i][j][k][l]=0.0;
            }
        }
    }
}
double CQLearning::R(qstate s, CCar *car){
    double res= (r[(int)car->p1.X][(int)car->p1.Y] +
                r[(int)car->p2.X][(int)car->p2.Y] +
                r[(int)car->p3.X][(int)car->p3.Y] +
                r[(int)car->p4.X][(int)car->p4.Y] +
                r[(int)car->pcentral.X][(int)car->pcentral.Y])/5.0;
    return res;
}
void CQLearning::train(CCar *car){
    init_q();
    start = qstate {car->y, car->x, car->angle, 0};

    void (CCar::*actions[])()={ &CCar::move_forward_action,
                                &CCar::move_left_action,
                                &CCar::move_right_action};
    void (CCar::*real_actions[])()={ &CCar::move_forward,
                                &CCar::move_left,
                                &CCar::move_right};

    //[] = {car->*move_forward, car->*move_left, car->*move_right};
    //functions actions[] = {(void)car->move_forward, car->move_left, car->move_right};

    for(int i=0; i< nepisodes; ++i){
        qstate current_state=start;
        //reset car position

        qstate next_state;
        while(car->is_in_road()){
            //int i_next_state= rand()%CAR_MOVES;
            int best_action_index=0;
            double best_action_value=-100000.0;
            cout<<"q actions:";
            for(int ia=0; ia< CAR_MOVES; ++ia){//select best action
                (car->*actions[ia])();
                qstate state={car->y_action, car->x_action,car->angle_action, ia};
                cout<<q[state.r][state.c][state.angle][ia]<<"\t";
                if (q[state.r][state.c][state.angle][ia] > best_action_value){
                    best_action_value = q[state.r][state.c][state.angle][ia];
                    next_state = state;
                }
            }
            cout<<endl;
            //update q matrix
            cout<<"reward used!:"<<r[next_state.r][next_state.c]<<endl;
            /*q[current_state.r][current_state.c][current_state.angle][current_state.action]+=
                alpha * ( r[next_state.r][next_state.c] +
                gamma * (q[next_state.r][next_state.c][next_state.angle][next_state.action]) -
                q[current_state.r][current_state.c][current_state.angle][current_state.action]);*/
            q[current_state.r][current_state.c][current_state.angle][current_state.action]+=
                alpha * ( R(next_state, car) +
                gamma * (q[next_state.r][next_state.c][next_state.angle][next_state.action]) -
                q[current_state.r][current_state.c][current_state.angle][current_state.action]);

            cout<<"qvalue: "<<q[current_state.r][current_state.c][current_state.angle][current_state.action]<<endl;
            current_state = next_state;
            p_state(next_state);
            (car->*real_actions[current_state.action])();
            //cin.get();
        }
        cout<<"episode:"<<i<<endl;
        car->y=start.r; car->x=start.c; car->angle=start.angle;
    }
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
