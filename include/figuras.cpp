#include "figuras.h"


void retangulo(int x1, int y1, int x2, int y2)
{
    glBegin(GL_LINE_LOOP);
        glVertex2i(x1,y1);
        glVertex2i(x2,y1);
        glVertex2i(x2,y2);
        glVertex2i(x1,y2);
    glEnd();
}

void quadrado(int xc, int yc, int lado)
{
    glBegin(GL_POLYGON);
        glVertex2i(xc-lado/2,yc-lado/2);
        glVertex2i(xc+lado/2,yc-lado/2);
        glVertex2i(xc+lado/2,yc+lado/2);
        glVertex2i(xc-lado/2,yc+lado/2);
    glEnd();
}

void screen_box(int x, int y, int s)
{
	glBegin(GL_QUADS);
	glVertex2i(x,   y  );
	glVertex2i(x+s, y  );
	glVertex2i(x+s, y+s);
	glVertex2i(x,   y+s);
	glEnd();
}


/*
 * (xc,yc) -> coordenadas do centro do circulo
 * r -> raio do circulo
 * teta -> arco entre dois pontos consecutivos do polígono ("circulo")

 */

void circulo_cheio(int xc, int yc, double r)
{

    double i = (pi * 1/180);
    double fi = 0;

    glBegin(GL_POLYGON);

    while (fi <= 2*pi)
    {
        glVertex2f(xc + r*cos(fi), yc + r*sin(fi));
        fi = fi + i;
    }

    glEnd();
}

void circulo(int xc, int yc, double r)
{

    double i = (pi * 1/180);
    double fi = 0;

    glBegin(GL_LINE_LOOP);

    while (fi <= 2*pi)
    {
        glVertex2f(xc + r*cos(fi), yc + r*sin(fi));
        fi = fi + i;
    }

    glEnd();
}

