#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "TextureManager.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
GLint background_texture, way_texture;
const int msize=100;

class CBackground{
    public:
    CBackground();
    void draw();
    void draw_grass();
    void draw_way(int x, int y);
    int matrix[msize][msize];
};
CBackground::CBackground(){
    ifstream in("pista.txt");
    string line;
    int r=0;
    while(in>>line){
        for(int i=0; i< msize; ++i)
            matrix[msize - r - 1][i]=(int)(line[i]=='1');
        r++;
    }
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
        glVertex3d(0, 100, -10);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3d(100, 100, -10);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3d(100, 0, -10);

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
    for(int i=0; i< msize; ++i){
        for(int j=0; j< msize; ++j){
            if (matrix[i][j]) continue;
            draw_way(j, i);            
        }
    }
}
#endif
