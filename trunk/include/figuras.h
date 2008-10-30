#ifndef FIGURAS_H_INCLUDED
#define FIGURAS_H_INCLUDED

#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#define pi 3.141592

void screen_box(int, int, int);
void retangulo(int x1, int y1, int x2, int y2);
void quadrado(int xc, int yc, int lado);
void circulo(double xc, double yc, double r, double teta);


#endif // FIGURAS_H_INCLUDED
