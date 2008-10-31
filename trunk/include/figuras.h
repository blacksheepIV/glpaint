#ifndef FIGURAS_H_INCLUDED
#define FIGURAS_H_INCLUDED

#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#define pi 3.141592

void screen_box(int, int, int);
void retangulo(int x1, int y1, int x2, int y2);
void quadrado(int xc, int yc, float lado);
void borracha(int xc, int yc, float lado);
void circulo(int xc, int yc, double r);
void circulo_cheio(int xc, int yc, double r);


#endif // FIGURAS_H_INCLUDED
