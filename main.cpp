#include <cstdio>
#include <cmath>
#include <iostream>

#include "background.h"
#include "car.h"
#include "cqlearning.h"
#include "Graphics.h"

using namespace std;

int x=25, y=0;
float angle=90.0;
int rows=100, cols=100;

CCar car(x, y, angle);
CBackground bg(rows, cols, "pista.txt");
CQLearning q;


int main(int argc, char **argv) {
    p_bg = &bg; glcar = &car; glbg = &bg;
    q.set_r_matrix(bg.matrix, bg.rows, bg.cols);
    q.train(&car);




    GLmain();
    return 1;
}
