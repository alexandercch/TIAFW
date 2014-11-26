#ifndef CQLEARNING_H
#define CQLEARNING_H

#include "background.h"

class CQLearning
{
    public:
        CQLearning() {}
        virtual ~CQLearning() {}
        void set_r_matrix(CBackground *bg);
    protected:
    private:
        int **r;
        int rows, cols;
};

void  CQLearning::set_r_matrix(CBackground *bg){
    cols = bg->cols;
    rows = bg->rows;
    r= new int*[rows];
    for(int i=0; i< rows; ++i)
        r[i]= new int[cols];

}










#endif // CQLEARNING_H
