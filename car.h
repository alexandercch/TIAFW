#ifndef CAR_H
#define CAR_H


#include <cmath>
#include <cstdio>

#include "background.h"
#include "TextureManager.h"
#include "types.h"

using namespace std;

GLint car_texture;

CBackground *p_bg;

class CCar{
public:
    float x, y;
    float velocity;
    int angle;
    CCar(float _x, float _y, float _angle, float _velocity);
    void draw();
    void draw_car();
    void move_forward();
    void move_backward();
    void move_left();
    void move_right();
private:
    int width, large;
    float lx, ly;
    int langle;
    Point p1, p2, p3, p4, pcentral;
};

inline double degrees_to_radians(double angle){return angle * PI/180.0f;}
inline double d2g(double angle){ return degrees_to_radians(angle);}

inline Point rotate_point(Point p, double angle){
    Point p_;
    p_.X = p.X * cos(d2g(angle)) - p.Y * sin(d2g(angle));
    p_.Y = p.X * sin(d2g(angle)) + p.Y * cos(d2g(angle));
    return p_;
}

CCar::CCar(float _x=0, float _y=0, float _angle=90.0, float _velocity=0.0):x(_x), y(_y), angle(_angle), velocity(_velocity){
    width=9; large=16;
    pcentral=Point(x, y);
};
void CCar::draw_car(){
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//funcion de transparencia
    glEnable(GL_BLEND);//utilizar transparencia
    glBindTexture(GL_TEXTURE_2D, car_texture);
    glBegin(GL_QUADS);
        //coordenadas de textura
        glTexCoord2f(0.0f ,0);
        glVertex3d(-width/2.0, 0, 10);

        glTexCoord2f(0.0f , 1);
        glVertex3d(-width/2.0, large, 10);

        glTexCoord2f(1, 1);
        glVertex3d(width/2.0, large, 10);

        glTexCoord2f(1, 0);
        glVertex3d(width/2.0, 0, 10);
    glEnd();
    glDisable(GL_BLEND);
    glColor3f(0, 1.0, 0);
    glPointSize(4.0);
    glRotatef(-(angle-90.0), 0, 0, 1);
    glTranslatef(-x, -y, 0);
    glBegin(GL_POINTS);
        glVertex3d(p1.X, p1.Y, 11);
        glVertex3d(p2.X, p2.Y, 11);
        glVertex3d(p3.X, p3.Y, 11);
        glVertex3d(p4.X, p4.Y, 11);
    glEnd();
}
void CCar::draw(){
    glTranslatef(x, y, 0);
    glRotatef(angle-90.0, 0, 0, 1);
    draw_car();
    if (x!=lx || y!=ly || angle != langle){
        lx=x; ly=y; langle=angle;
        printf("x y º: %4.3f %4.3f %4.0d\n", x, y, angle);
        p1 = rotate_point(Point(-width/2.0, 0.0), angle-90.0);
        p1.X+=x;p1.Y+=y;
        p2 = rotate_point(Point(-width/2.0, large), angle-90.0);
        p2.X+=x;p2.Y+=y;
        p3 = rotate_point(Point(width/2.0, large), angle-90.0);
        p3.X+=x;p3.Y+=y;
        p4 = rotate_point(Point(width/2.0, 0), angle-90.0);
        p4.X+=x;p4.Y+=y;

        /*cout<<"p1:"<<p1.X<<" "<<p1.Y<<endl;
        cout<<"p2:"<<p2.X<<" "<<p2.Y<<endl;
        cout<<"p3:"<<p3.X<<" "<<p3.Y<<endl;
        cout<<"p4:"<<p4.X<<" "<<p4.Y<<endl;*/
        //if (p_bg->matrix[p1.Y][p1.X])
        cout<<"p1"<<p_bg->matrix[(int)p1.Y][(int)p1.X]<<endl;
        cout<<"p2"<<p_bg->matrix[(int)p2.Y][(int)p2.X]<<endl;
        cout<<"p3"<<p_bg->matrix[(int)p3.Y][(int)p3.X]<<endl;
        cout<<"p4"<<p_bg->matrix[(int)p4.Y][(int)p4.X]<<endl;

    }
}
void CCar::move_forward(){
    //cout<<sin((90.0f * PI)/180.0f)<<" "<<cos((90.0f * PI)/180.0f)<<endl;
    //cout<<x<<" "<<y<<" "<<angle<<":"<<endl;
    x+= cos(degrees_to_radians(angle));
    y+= sin(degrees_to_radians(angle));

}
void CCar::move_backward(){
    x-= cos(degrees_to_radians(angle));
    y-= sin(degrees_to_radians(angle));
}
void CCar::move_left(){
    move_forward();
    angle+=3.0;
    if (angle>=MAX_ANGLE) angle-=MAX_ANGLE;
}
void CCar::move_right(){
    move_forward();
    angle-=3.0;
    if (angle<0) angle+=360;
}

#endif
