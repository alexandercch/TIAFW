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

#define CAR_MOVES 3
#define ANGLE_STEP 3

class CCar{
public:
    double x, y;
    double velocity;
    int angle;
    CCar(double _x, double _y, double _angle, double _velocity);
    bool is_in_road();
    void draw();
    void draw_car();
    void move_forward();
    void move_backward();
    void move_right();
    void move_left();

    void set_fin(Coord _fin);

    //fake functions just to help qlearning algorithm
    //choose wich action is the best without moving
    //the actual car
    void move_forward_action();
    void move_right_action();
    void move_left_action();
    double x_action, y_action;
    int angle_action;
    void calculate_perimeter();
    bool end_reached();
    void drive_from_q(double ****q);
//private:
    double width, large;
    double lx, ly;
    int langle;
    Point p1, p2, p3, p4, pcentral;
    Coord fin;

    int n_moves;

};


void CCar::set_fin(Coord _fin){
    fin = _fin;
}

bool CCar::end_reached(){
    int dist=abs(fin.X-x) + abs(fin.Y-y);
    return dist<15;
}

inline double degrees_to_radians(double angle){return angle * PI/180.0f;}
inline double d2g(double angle){ return degrees_to_radians(angle);}

inline Point rotate_point(Point p, double angle){
    Point p_;
    p_.X = p.X * cos(d2g(angle)) - p.Y * sin(d2g(angle));
    p_.Y = p.X * sin(d2g(angle)) + p.Y * cos(d2g(angle));
    return p_;
}

CCar::CCar(double _x=0, double _y=0, double _angle=90.0, double _velocity=0.0):x(_x), y(_y), angle(_angle), velocity(_velocity), n_moves(CAR_MOVES){
    width=9; large=16;
    pcentral=Point(x, y);
};

void CCar::drive_from_q(double ****q){
}

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
    calculate_perimeter();
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
    /*if (x!=lx || y!=ly || angle != langle){
        lx=x; ly=y; langle=angle;
        printf("x y º: %4.3f %4.3f %4.0d\n", x, y, angle);
        p1 = rotate_point(Point(-width/2.0, 0.0), angle-90.0);
        p1.X+=x;p1.Y+=y;
        p2 = rotate_point(Point(-width/2.0, large), angle-90.0);
        p2.X+=x;p2.Y+=y;
        p3 = rotate_point(Point(width/2.0, large), angle-90.0);
        p3.X+=x;p3.Y+=y;
        p4 = rotate_point(Point(width/2.0, 0), angle-90.0);
        p4.X+=x;p4.Y+=y;*/

        /*cout<<"p1:"<<p1.X<<" "<<p1.Y<<endl;
        cout<<"p2:"<<p2.X<<" "<<p2.Y<<endl;
        cout<<"p3:"<<p3.X<<" "<<p3.Y<<endl;
        cout<<"p4:"<<p4.X<<" "<<p4.Y<<endl;*/
        //if (p_bg->matrix[p1.Y][p1.X])
        /*cout<<"p1"<<p_bg->matrix[(int)p1.Y][(int)p1.X]<<endl;
        cout<<"p2"<<p_bg->matrix[(int)p2.Y][(int)p2.X]<<endl;
        cout<<"p3"<<p_bg->matrix[(int)p3.Y][(int)p3.X]<<endl;
        cout<<"p4"<<p_bg->matrix[(int)p4.Y][(int)p4.X]<<endl;

    }*/
}
void CCar::calculate_perimeter(){
    p1 = rotate_point(Point(-width/2.0, 0.0), angle-90.0);
    p1.X+=x;p1.Y+=y;
    p2 = rotate_point(Point(-width/2.0, large), angle-90.0);
    p2.X+=x;p2.Y+=y;
    p3 = rotate_point(Point(width/2.0, large), angle-90.0);
    p3.X+=x;p3.Y+=y;
    p4 = rotate_point(Point(width/2.0, 0), angle-90.0);
    p4.X+=x;p4.Y+=y;
    pcentral.X= (p1.X + p2.X + p3.X + p4.X)/4.0;
    pcentral.Y= (p1.Y + p2.Y + p3.Y + p4.Y)/4.0;
}

bool CCar::is_in_road(){
    calculate_perimeter();
    return !(p_bg->matrix[(int)p1.Y][(int)p1.X] ||
            p_bg->matrix[(int)p2.Y][(int)p2.X] ||
            p_bg->matrix[(int)p3.Y][(int)p3.X] ||
            p_bg->matrix[(int)p4.Y][(int)p4.X]);
}
void CCar::move_forward(){

    //cout<<sin((90.0f * PI)/180.0f)<<" "<<cos((90.0f * PI)/180.0f)<<endl;
    //cout<<x<<" "<<y<<" "<<angle<<":"<<endl;
    x+= cos(degrees_to_radians(angle));
    y+= sin(degrees_to_radians(angle));
    calculate_perimeter();
}
void CCar::move_backward(){
    x-= cos(degrees_to_radians(angle));
    y-= sin(degrees_to_radians(angle));
}
void CCar::move_left(){
    angle += ANGLE_STEP;
    move_forward();

    if (angle>=MAX_ANGLE) angle-=MAX_ANGLE;
}
void CCar::move_right(){
    angle -= ANGLE_STEP;
    move_forward();

    if (angle<0) angle+=360;
}

void CCar::move_forward_action(){
    angle_action = angle;
    x_action = x + cos(degrees_to_radians(angle_action));
    y_action = y + sin(degrees_to_radians(angle_action));
}
void CCar::move_right_action(){
    angle_action= angle - ANGLE_STEP;
    if (angle_action < 0) angle_action += 360;
    x_action = x + cos(degrees_to_radians(angle_action));
    y_action = y + sin(degrees_to_radians(angle_action));
}
void CCar::move_left_action(){
    angle_action = angle + ANGLE_STEP;
    if (angle_action >= MAX_ANGLE) angle_action -= MAX_ANGLE;

    x_action = x + cos(degrees_to_radians(angle_action));
    y_action = y + sin(degrees_to_radians(angle_action));

}


#endif
