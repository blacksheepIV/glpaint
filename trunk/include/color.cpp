#include "color.h"
#include "figuras.h"
#include "definicoes.h"

void colorpalete(int cor, int bcor, int wh, int ww){
//        int shift=0;
//	int aux = cor;


	glPushAttrib(GL_ALL_ATTRIB_BITS);

    // Draw a square painted with selected color
	glColor3f(1.0,1.0,1.0);
	screen_box(10,ww/10,ww/15);

	set_color(cor,&cor);
	screen_box(1+10,1+ww/10,ww/15-2);
	//set_color(aux,cor);

	// Draw a square painted with selected background color
	glColor3f(1.0,1.0,1.0);
	screen_box(10,ww/10-ww/15,ww/15);

	set_color(bcor, &cor);
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

void set_color(int color, int* cor)
{
	switch (color)
	{
		case (RED): {glColor3f(1.0,0.0,0.0); *cor=color;/*colorpalete();*/} break;
		case (GREEN): {glColor3f(0.0,1.0,0.0); *cor=color; /*colorpalete();*/} break;
		case (BLUE): {glColor3f(0.0,0.0,1.0); *cor=color; /*colorpalete();*/} break;
		case (CYAN): {glColor3f(0.0,1.0,1.0); *cor=color; /*colorpalete();*/} break;
		case (MAGENTA): {glColor3f(1.0,0.0,1.0); *cor=color; /*colorpalete();*/} break;
		case (YELLOW): {glColor3f(1.0,1.0,0.0); *cor=color; /*colorpalete();*/} break;
		case (ORANGE): {glColor3f(1.0,0.5,0.0); *cor=color; /*colorpalete();*/} break;
		case (GRAY): {glColor3f(0.5,0.5,0.5); *cor=color; /*colorpalete();*/} break;
		case (WHITE): {glColor3f(1.0,1.0,1.0); *cor=color; /*colorpalete();*/} break;
		case (BLACK): {glColor3f(0.0,0.0,0.0); *cor=color; /*colorpalete();*/} break;

		default: break;
	}

	glFlush();
}

void set_bgcolor(int color, int* bcor, GLfloat* rb, GLfloat* gb, GLfloat* bb)
{
	switch (color)
	{
		case (RED): {*rb=1.0;*gb=0.0;*bb=0.0; *bcor=color;/*colorpalete();*/} break;
		case (GREEN): {*rb=0.0;*gb=1.0;*bb=0.0; *bcor=color; /*colorpalete();*/} break;
		case (BLUE): {*rb=0.0,*gb=0.0,*bb=1.0; *bcor=color; /*colorpalete();*/} break;
		case (CYAN): {*rb=0.0,*gb=1.0,*bb=1.0; *bcor=color; /*colorpalete();*/} break;
		case (MAGENTA): {*rb=1.0,*gb=0.0,*bb=1.0; *bcor=color; /*colorpalete();*/} break;
		case (YELLOW): {*rb=1.0,*gb=1.0,*bb=0.0; *bcor=color; /*colorpalete();*/} break;
		case (ORANGE): {*rb=1.0,*gb=0.5,*bb=0.0; *bcor=color; /*colorpalete();*/} break;
		case (GRAY): {*rb=0.5,*gb=0.5,*bb=0.5; *bcor=color; /*colorpalete();*/} break;
		case (WHITE): {*rb=1.0,*gb=1.0,*bb=1.0; *bcor=color;/* colorpalete();*/} break;
		case (BLACK): {*rb=0.0,*gb=0.0,*bb=0.0; *bcor=color; /*colorpalete();*/} break;

		default: break;
	}
}

