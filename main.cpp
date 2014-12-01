#include <thread>
#include <cstdio>
#include <cmath>
#include <iostream>

#include "background.h"
#include "car.h"
#include "cqlearning.h"
#include "Graphics.h"

using namespace std;

int x=25, y=0;


Coord fin(99, 28);

float angle=90.0;
int rows=100, cols=100;

CCar car(x, y, angle);


CBackground bg(rows, cols, "pista.txt");
CQLearning q;


int main(int argc, char **argv) {
    car.set_fin(fin);
    p_bg = &bg; glcar = &car; glbg = &bg;
    q.set_r_matrix(bg.matrix, bg.rows, bg.cols);
    thread  t1([](){q.train(&car); q.q_drive(&car);}),
            t2([](){GLmain();});
    t1.join();
    t2.join();
    //q.train(&car);
    //GLmain();
    return 1;
}
