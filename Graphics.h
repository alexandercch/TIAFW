#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <GL/glut.h>

#include "TextureManager.h"
#include "background.h"
#include "car.h"

#define ECHAP 27

CCar *glcar;
CBackground *glbg;

GLvoid window_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // follow hero
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 100, 0, 100, -100, 100);

    glMatrixMode(GL_MODELVIEW);
    glbg->draw();
    glcar->draw();

    glutSwapBuffers();

    glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 100, 0, 100, -100, 100);

    glMatrixMode(GL_MODELVIEW);
}

GLvoid special_key(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            glcar->move_forward();
            break;

        case GLUT_KEY_DOWN:
            glcar->move_backward();
            break;

        case GLUT_KEY_LEFT:
            glcar->move_left();
            break;

        case GLUT_KEY_RIGHT:
            glcar->move_right();
            break;

        default:
            printf("La tecla %d no hace nada.\n", key);
            break;
    }
}

GLvoid keyboard_key(unsigned char key, int x, int y) {
    switch (key) {
        case 32:
            printf("SPACE");
            break;

        default:
            printf("La tecla %d no hace nada.\n", key);
            break;
    }
}

//function called on each frame
GLvoid window_idle() {
    glutPostRedisplay();
}

GLvoid initGL() {
    GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

    //enable light : try without it
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    //light 0 "on": try without it
    glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
    //shading model : try GL_FLAT
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);

    //enable material : try without it
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    // Commenting this line fixes color in the hero's sprite
    // glEnable(GL_COLOR_MATERIAL);

    //glClearColor(0, 0.3, 0.7, 0);
    glClearColor(0.4f, 0.4f, 0.4f, 0.2f); //(R, G, B, transparencia) en este caso un fondo negro

}
void GLmain(){
    int argc = 1;
    char *argv[1] = {(char*)"Something"};

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(700 , 700);
    glutInitWindowPosition(300, 0);
    glutCreateWindow("TIA - Final :9");
    initGL();
    glutDisplayFunc(&window_display);
    glutReshapeFunc(&window_reshape);
    glutKeyboardFunc(&keyboard_key);
    glutSpecialFunc(&special_key);
    glOrtho(0, 100, 0, 100, -100, 100);
    //function called on each frame
    glutIdleFunc(&window_idle);

    //preparacion de las texturas
    car_texture = TextureManager::Inst()->LoadTexture("car.png",GL_BGRA_EXT, GL_RGBA);
    background_texture = TextureManager::Inst()->LoadTexture("pasto.png",GL_BGR_EXT, GL_RGB);
    way_texture = TextureManager::Inst()->LoadTexture("pista.png",GL_BGR_EXT, GL_RGB);



    glutMainLoop();


}

#endif // GRAPHICS_H_INCLUDED
