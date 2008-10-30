#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void colorpalete(int cor, int bcor, int wh, int ww);
void set_color(int color, int* cor);
void set_bgcolor(int color, int* bcor, GLfloat* rb, GLfloat* gb, GLfloat* bb);

#endif // COLOR_H_INCLUDED
