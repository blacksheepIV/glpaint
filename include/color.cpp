#include "color.h"
#include "figuras.h"
#include "definicoes.h"
#include <stdio.h>

void colorpalete(int cor, int bcor, int wh, int ww){

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glColor3i(0,0,0);
	glRectf(0,0,ww,1+ww/6);

    // Draw a square painted with selected color
	glColor3f(1.0,1.0,1.0);
	screen_box(10,ww/10,ww/15);

	set_color(cor/*,&cor*/);
	screen_box(1+10,1+ww/10,ww/15-2);
	//set_color(aux,cor);

	// Draw a square painted with selected background color
	glColor3f(1.0,1.0,1.0);
	screen_box(10,ww/10-ww/15,ww/15);

	set_color(bcor/*, &cor*/);
	screen_box(1+10,1+ww/10-ww/15,ww/15-2);
	//set_color(aux,cor);

    // Draw a RED square
	glColor3f(1.0,0.0,0.0);
	screen_box(ww/10,ww/10,ww/15);

    // Draw a GREEN square
	glColor3f(0.0,1.0,0.0);
	screen_box(ww/10,ww/10-ww/15,ww/15);

    // Draw a BLUE square
	glColor3f(0.0,0.0,1.0);
	screen_box(ww/10+ww/15,ww/10,ww/15);

    // Draw a CYAN square
	glColor3f(0.0,1.0,1.0);
	screen_box(ww/10+ww/15,ww/10-ww/15,ww/15);

    // Draw a MAGENTA square
	glColor3f(1.0,0.0,1.0);
	screen_box(ww/10+ww/15+ww/15,ww/10,ww/15);

    // Draw a YELLOW square
	glColor3f(1.0,1.0,0.0);
	screen_box(ww/10+ww/15+ww/15,ww/10-ww/15,ww/15);

	// Draw a ORANGE square
	glColor3f(1.0,0.5,0.0);
	screen_box(ww/10+3*(ww/15),ww/10,ww/15);

    // Draw a BLACK square
	glColor3f(1.0,1.0,1.0);
	screen_box(ww/10+3*(ww/15),ww/10-ww/15,ww/15);
	glColor3f(0.0,0.0,0.0);
	screen_box(1+ww/10+3*(ww/15),1+ww/10-ww/15,ww/16);

    // Draw a GREY square
	glColor3f(0.5,0.5,0.5);
	screen_box(ww/10+4*(ww/15),ww/10,ww/15);

    // Draw a white square
	glColor3f(1.0,1.0,1.0);
	screen_box(ww/10+4*(ww/15),ww/10-ww/15,ww/15);

	glPopAttrib();

    // desenhar a paleta
	glFlush();

}


void set_color(int color)
{
	switch (color)
	{
		case (RED): {glColor3f(1.0,0.0,0.0); } break;
		case (GREEN): {glColor3f(0.0,1.0,0.0); } break;
		case (BLUE): {glColor3f(0.0,0.0,1.0); } break;
		case (CYAN): {glColor3f(0.0,1.0,1.0); } break;
		case (MAGENTA): {glColor3f(1.0,0.0,1.0); } break;
		case (YELLOW): {glColor3f(1.0,1.0,0.0); } break;
		case (ORANGE): {glColor3f(1.0,0.5,0.0); } break;
		case (GRAY): {glColor3f(0.5,0.5,0.5); } break;
		case (WHITE): {glColor3f(1.0,1.0,1.0); } break;
		case (BLACK): {glColor3f(0.0,0.0,0.0); } break;

		default: break;
	}

}

void set_bgcolor(int color, int* bcor, GLfloat* rb, GLfloat* gb, GLfloat* bb)
{
	switch (color)
	{
		case (RED): {*rb=1.0;*gb=0.0;*bb=0.0; *bcor=color; } break;
		case (GREEN): {*rb=0.0;*gb=1.0;*bb=0.0; *bcor=color; } break;
		case (BLUE): {*rb=0.0,*gb=0.0,*bb=1.0; *bcor=color; } break;
		case (CYAN): {*rb=0.0,*gb=1.0,*bb=1.0; *bcor=color; } break;
		case (MAGENTA): {*rb=1.0,*gb=0.0,*bb=1.0; *bcor=color; } break;
		case (YELLOW): {*rb=1.0,*gb=1.0,*bb=0.0; *bcor=color; } break;
		case (ORANGE): {*rb=1.0,*gb=0.5,*bb=0.0; *bcor=color; } break;
		case (GRAY): {*rb=0.5,*gb=0.5,*bb=0.5; *bcor=color; } break;
		case (WHITE): {*rb=1.0,*gb=1.0,*bb=1.0; *bcor=color; } break;
		case (BLACK): {*rb=0.0,*gb=0.0,*bb=0.0; *bcor=color; } break;

		default: break;
	}
}

