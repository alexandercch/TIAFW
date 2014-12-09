#include <thread>
#include <cstdio>
#include <cmath>
#include <iostream>

#include "background.h"
#include "car.h"
#include "cqlearning.h"
#include "Graphics.h"

using namespace std;

CCar *car;
CBackground *bg;
CQLearning *q;

int main(int argc, char **argv) {
    freopen("in2.txt", "r", stdin);
    //freopen("in.txt", "r", stdin);

    int x, y, angle;
    int rows, cols;
    string road;

    cin>>road;
    cin>>x>>y>>angle;
    cin>>rows>>cols;

    car= new CCar(x, y, angle);
    bg = new CBackground(rows, cols, road.c_str());
    q  = new CQLearning;
    glcols = cols; glrows = rows;

    cin>>x>>y;
    Coord fin(x, y);

    car->set_fin(fin);
    p_bg = bg; glcar = car; glbg = bg;

    q->set_r_matrix(bg->matrix, bg->rows, bg->cols);

    thread  t1([](){q->train(car); q->q_drive(car);}),
            t2([](){GLmain();});
    t1.join();
    t2.join();
    //q.train(&car);
    //GLmain();
    return 1;
}
