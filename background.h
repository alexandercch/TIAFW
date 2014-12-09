#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "TextureManager.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

GLint background_texture, way_texture;

class CBackground{
public:
    CBackground(int _rows, int _cols, string filename);
    void draw();
    void draw_grass();
    void draw_way(int x, int y);
    int rows, cols;
    int **matrix;
    string roadfile;
};
CBackground::CBackground(int _rows, int _cols, string filename):
    rows(_rows), cols(_cols), roadfile(filename)
{
    cout<<":9"<<endl;
    matrix= new int*[rows];
    for(int i=0; i< rows; ++i)
         matrix[i]= new int[cols];
    ifstream in(roadfile.c_str());
    string line;
    int r=0;
    while(in>>line){

        for(int i=0; i< cols; ++i)
            matrix[rows - r - 1][i]=(int)(line[i]=='1');
        r++;
    }
    cout<<":9"<<endl;
    /*cout<<"matrix:"<<endl;
    for(int i=0; i< msize; ++i){
        for(int j=0; j< msize; ++j)
            cout<<matrix[i][j];
        cout<<endl;
    }*/
}
void CBackground::draw_grass(){
    glBindTexture(GL_TEXTURE_2D, background_texture);
    glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3d(0, 0, -10);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3d(0, rows, -10);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3d(cols, rows, -10);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3d(cols, 0, -10);

    glEnd();
}
void CBackground::draw_way(int x, int y){
    glBindTexture(GL_TEXTURE_2D, way_texture);
    glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3d(x+0, y+0, -9);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3d(x+0, y + 1, -9);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3d(x+1,y + 1, -9);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3d(x+1, y + 0, -9);
    glEnd();
}

void CBackground::draw(){
    glLoadIdentity();
    draw_grass();
    for(int i=0; i< rows; ++i){
        for(int j=0; j<cols; ++j){
            if (matrix[i][j]) continue;
            draw_way(j, i);
        }
    }
}
#endif
