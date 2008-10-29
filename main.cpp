/* newpaint.c   */

/* E. Angel, Interactive Computer Graphics			*/
/* A Top-Down Approach with OpenGL, Third Edition	*/
/* Addison-Wesley Longman, 2003						*/


/* paint program from chapter 3  */

/* This program illustrates the use of the glut library for
interfacing with a window system */


#define NULL		0
#define LINE		1
#define RECTANGLE	2
#define TRIANGLE	3
#define POINTS		4
#define TEXT		5
#define ERASER		6


#define RED         10
#define GREEN       11
#define BLUE        12
#define CYAN        13
#define MAGENTA     14
#define YELLOW      15
#define ORANGE      16
#define GRAY        17
#define WHITE       18
#define BLACK       19


#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <string.h>

#include "figuras.h"

void mouse(int, int, int, int);
void key(unsigned char, int, int);
void display(void);
void drawSquare(int, int);
void myReshape(GLsizei, GLsizei);

void myinit(void);

void screen_box(int, int, int);
void right_menu(int);
void middle_menu(int);
void color_menu(int);
void pixel_menu(int);
void fill_menu(int);
int  pick(int, int);
void drawButtons(int a, int b, int c, int d, int e, int f);
void collorpalete(void);

/* globals */

GLsizei wh = 500, ww = 500; /* initial window size			*/
GLfloat size = 3.0;			/* half side length of square	*/
int draw_mode = 0;			/* drawing mode					*/
int rx, ry;					/* raster position				*/

GLfloat r = 1.0, g = 1.0, b = 1.0;	/* drawing color */
int fill = 0;						/* fill flag	 */

int cont = 0;
int xp[2],yp[2];

// tamanho inicial ta borracha
int tamanho=20;


int mpm = 0;
int idle = 1;

int xi,yi;
int cont_idle = 1;

void drawSquare(int x, int y)
{
	y=wh-y;
        //glColor3ub( (char) rand()%256, (char) rand()%256, (char) rand()%256);
	glBegin(GL_POLYGON);
	glVertex2f(x+size, y+size);
	glVertex2f(x-size, y+size);
	glVertex2f(x-size, y-size);
	glVertex2f(x+size, y-size);
	glEnd();
}


/* rehaping routine called whenever window is resized or moved */

void myReshape(GLsizei w, GLsizei h)
{

	/* adjust clipping box */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* adjust viewport and  clear */

	glViewport(0,0,w,h);
	glClearColor (0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//display();
	glFlush();

	/* set global size for use by drawing routine */

	ww = w;
	wh = h;
}

void myinit(void)
{

	glViewport(0,0,ww,wh);


/* Pick 2D clipping window to match size of X window
	This choice avoids having to scale object coordinates
	each time window is resized */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble) ww , 0.0, (GLdouble) wh , -1.0, 1.0);

	/* set clear color to black and clear window */

	glClearColor (0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}


void teste()
{
    //mpm = 0;
    //cont_idle--;

	if (idle!=0 & cont_idle==0)
	{

		puts("idlefunc");

		glEnable(GL_COLOR_LOGIC_OP);

		glLogicOp(GL_XOR);

		quadrado(xi,wh-yi,tamanho);

		glDisable(GL_COLOR_LOGIC_OP);

		cont_idle=1;

	}
}

void mouse_passive_motion(int x, int y)
{

	puts("mouse_passive_motion");

   // static int x_ant,y_ant;
	int where;

	where = pick(x,y);

   // se não estiver sobre os menus
	if(where == 0)
	{

		cont_idle = 0;


		if (mpm=0)
		{
			xi=x;
			yi=y;

			//
			mpm=1;

			idle = 0;
			puts("idle1");
		}

		else
		{
			switch(draw_mode)
			{

				case (ERASER):

					glEnable(GL_COLOR_LOGIC_OP);

					glLogicOp(GL_XOR);

                    // desenha borracha temporária
					quadrado(x,wh-y,tamanho);

                    // guarda a posição da borracha
					xi=x;
					yi=y;

					if(mpm!=0)
					{

                        // desenha por cima da anterior
                       // quadrado(x_ant,wh-y_ant,tamanho);

					} break;

					break;

					default: break;
			}




//glPopAttrib();
			glFlush();
      // printf("%s\n","estou na motion");
			glDisable(GL_COLOR_LOGIC_OP);
		}
	}

}


void mouse_motion(int x, int y)
{
	puts("mouse_motion");

	static int x_ant,y_ant;

	glEnable(GL_COLOR_LOGIC_OP);

	glLogicOp(GL_XOR);

    // primeiro movimento após clicar com o mouse (segurando o botão)
	if (cont == 0)
	{
		x_ant=xp[0];
		y_ant=yp[0];

		cont++;
	}

	int where;

	where = pick(x,y);
	glColor3f(r, g, b);

	if(where != 0)
	{
      //cont = 0;
		draw_mode = where;
	}

	else {

		switch(draw_mode)
		{
			case(LINE):

               // desenha linha temporária
				glBegin(GL_LINES);
				glVertex2i(x_ant,wh-y_ant);
				glVertex2i(xp[0],wh-yp[0]);
				glEnd();

				if(cont!=0)
				{
                   // guarda o ponto final da linha atual
					x_ant=x;
					y_ant=y;

                   // desenha (apaga) por cima da linha anterior
					glBegin(GL_LINES);
					glVertex2i(x,wh-y);
					glVertex2i(xp[0],wh-yp[0]);
					glEnd();

				} break;

			case(RECTANGLE):

                // desenha retângulo temporário

				glRecti(x_ant,wh-y_ant,xp[0],wh-yp[0]);

				if(cont!=0)
				{
                    // guarda o ponto final da linha atual
					x_ant=x;
					y_ant=y;

                    // desenha (apaga) por cima do retângulo anterior
					glRecti(x,wh-y,xp[0],wh-yp[0]);

				} break;

			case(TRIANGLE):

               // desenha linha temporária
				glBegin(GL_LINES);
				glVertex2i(x_ant,wh-y_ant);
				glVertex2i(xp[0],wh-yp[0]);
				glEnd();

				switch (cont){

					case (1):
					{
                       // guarda o ponto final da linha atual
						x_ant=x;
						y_ant=y;

                       // desenha (apaga) por cima da linha anterior
						glBegin(GL_LINES);
						glVertex2i(x,wh-y);
						glVertex2i(xp[0],wh-yp[0]);
						glEnd();

					} break;

					case (2):
					{

					} break;

					default: break;

				}

			case (ERASER):
				glDisable(GL_COLOR_LOGIC_OP);

				quadrado(x,wh-y,tamanho);
				break;

				default: break;
		}

	}


//glPopAttrib();
	glFlush();
      // printf("%s\n","estou na motion");
	glDisable(GL_COLOR_LOGIC_OP);
}


void mouse(int btn, int state, int x, int y)
{
	int where;

	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		puts("mouse down");

		glPushAttrib(GL_ALL_ATTRIB_BITS);

		where = pick(x,y);
		glColor3f(r, g, b);

		if(where != 0)
		{
			cont = 0;
			draw_mode = where;
		}

		else
		{
			switch(draw_mode)
			{
				case(LINE):

              // defino o ponto inicial da linha (ao clicar)
					xp[0] = x;
					yp[0] = y;

					break;

				case(RECTANGLE):

              // defino o ponto inicial do retângulo (ao clicar)
					xp[0] = x;
					yp[0] = y;

					break;

				case (TRIANGLE):
					switch(cont)
					{
						case(0):
							cont++;
							xp[0] = x;
							yp[0] = y;

					  // Desenha um ponto para marcar o 1o vertice do triangulo
							glBegin(GL_POINTS);
							glVertex2f(xp[0],wh-yp[0]);
							glEnd();
							break;
						case(1):
							cont++;
							xp[1] = x;
							yp[1] = y;

					  // Desenha um ponto para marcar o 2o vertice do triangulo
							glBegin(GL_POINTS);
							glVertex2f(xp[1],wh-yp[1]);
							glEnd();
							break;
						case(2):

							if(fill) glBegin(GL_POLYGON);
							else glBegin(GL_LINE_LOOP);
							glVertex2i(xp[0],wh-yp[0]);
							glVertex2i(xp[1],wh-yp[1]);
							glVertex2i(x,wh-y);
							glEnd();
							draw_mode=0;
							cont=0;
					}
					break;
				case(POINTS):
				{
					drawSquare(x,y);
					cont++;
				}
				break;
				case(TEXT):
				{
					rx=x;
					ry=wh-y;

					 // Desenha um ponto para marcar o inicio do texto
					glBegin(GL_POINTS);
					glVertex2f(rx,ry);
					glEnd();

					glRasterPos2i(rx,ry);
					cont=0;
				}
			}
		}

		glPopAttrib();
		glFlush();
	}

	if(btn==GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
		puts("mouse up");

		cont=0;

		if (xp[0]!=0 & yp[0]!=0 & pick(x,y)==0)
		{
                // aqui eu desenho as figuras definitivas (ao soltar o botão)
			switch (draw_mode) {

				case(LINE):

				{
					glBegin(GL_LINES);
					glVertex2i(x,wh-y);
					glVertex2i(xp[0],wh-yp[0]);
					glEnd();
				} break;

				case(RECTANGLE):

				{
                            // desenha retângulo temporário
					glRecti(x,wh-y,xp[0],wh-yp[0]);
				} break;

				defaut: break;

			} // fim do swicth
		}

		glPushAttrib(GL_ALL_ATTRIB_BITS);
		where = pick(x,y);
		glLineWidth(3);




        /*if(where != 0)
		{
		cont = 0;
		draw_mode = where;
	}*/
		switch(where){
			case(LINE):
				drawButtons(0,1,1,1,1,1);
				glColor3f(1.0,0.0,0.0);
				glBegin(GL_LINES);
				glVertex2f(0.0,wh-ww/10);
				glVertex2f(ww/10,wh);
				glVertex2f(ww/10,wh-ww/10);
				glVertex2f(0.0,wh);
				glEnd();
				break;
			case(RECTANGLE):
				drawButtons(1,0,1,1,1,1);
				glColor3f(1.0,1.0,0.0);
				glBegin(GL_LINES);
				glVertex2f(ww/10.0,wh-ww/10);
				glVertex2f(2*ww/10,wh);
				glVertex2f(2*ww/10,wh-ww/10);
				glVertex2f(ww/10.0,wh);
				glEnd();
				break;
			case(TRIANGLE):
				drawButtons(1,1,0,1,1,1);
				glColor3f(0.0,0.0,1.0);
				glBegin(GL_LINES);
				glVertex2f(ww/5.0,wh-ww/10);
				glVertex2f(3*ww/10.0,wh);
				glVertex2f(3*ww/10.0,wh-ww/10);
				glVertex2f(ww/5.0,wh);
				glEnd();
				break;
			case(POINTS):
				drawButtons(1,1,1,0,1,1);
				glColor3f(1.0,1.0,1.0);
				glBegin(GL_LINES);
				glVertex2f(3*ww/10.0,wh-ww/10);
				glVertex2f(4*ww/10.0,wh);
				glVertex2f(4*ww/10.0,wh-ww/10);
				glVertex2f(3*ww/10.0,wh);
				glEnd();
				break;
			case(TEXT):
				drawButtons(1,1,1,1,0,1);
				glColor3f(1.0,0.0,0.0);
				glBegin(GL_LINES);
				glVertex2f(2*ww/5,wh-ww/10);
				glVertex2f(ww/2,wh);
				glVertex2f(ww/2,wh-ww/10);
				glVertex2f(2*ww/5,wh);
				glEnd();
				break;
		}

		glPopAttrib();
		glFlush();
	}

}


int pick(int x, int y)
{
	y = wh - y;

    printf("x=%d, y=%d.\n",x,y);
	// Verifica se y esta' na parte superior da tela
	// onde estao os botões de selecao das ferramentas
	if (y > wh-ww/10) {
        if(x < ww/10   ) return LINE;
        else if(x < ww/5    ) return RECTANGLE;
        else if(x < 3*ww/10 ) return TRIANGLE;
        else if(x < 2*ww/5  ) return POINTS;
        else if(x < ww/2    ) return TEXT;
	    else if(x < 3*ww/5  ) return ERASER;
        else return 0;
	}
	// Verifica se y esta na parte inferior onde estao as cores
	if(y > ww/10 + ww/15) {printf("entrei aqui!\n");return 0;}
	else if((x >= ww/10) && (x <= (ww/10+ww/15)) && (y > ww/10)) {r=1.0;g=0.0;b=0.0;collorpalete(); return RED;}
	else if(x > ww/10 && x < (ww/10+ww/15) && y < ww/10) {r=0.0;g=1.0;b-0.0;collorpalete();return GREEN;}
	else if(x < (ww/10+2*(ww/15)) && y> ww/10) {r=0.0,g=0.0,b=1.0;collorpalete();return BLUE;}
	else if(x < (ww/10+2*(ww/15)) && y< ww/10) {r=0.0,g=1.0,b=1.0;collorpalete();return CYAN;}
	else if(x < (ww/10+3*(ww/15)) && y> ww/10) {r=1.0,g=0.0,b=1.0;collorpalete();return MAGENTA;}
	else if(x < (ww/10+3*(ww/15)) && y< ww/10) {r=1.0,g=1.0,b=0.0;collorpalete();return YELLOW;}
	else if(x < (ww/10+4*(ww/15)) && y> ww/10) {r=1.0,g=0.5,b=0.0;collorpalete();return ORANGE;}
	else if(x < (ww/10+4*(ww/15)) && y< ww/10) {r=0.0,g=0.0,b=0.0;collorpalete();return BLACK;}
	else if(x < (ww/10+5*(ww/15)) && y> ww/10) {r=0.5,g=0.5,b=0.5;collorpalete();return GRAY;}
	else if(x < (ww/10+5*(ww/15)) && y< ww/10) {r=1.0,g=1.0,b=1.0;collorpalete();return WHITE;}
	else return 0;

}

void right_menu(int id)
{
	if(id == 1) exit(0);
	else display();
}

void middle_menu(int id)
{

}

void color_menu(int id)
{
	if     (id == 1) {r = 1.0; g = 0.0; b = 0.0;}  // red
	else if(id == 2) {r = 0.0; g = 1.0; b = 0.0;}  // green
	else if(id == 3) {r = 0.0; g = 0.0; b = 1.0;}  // blue
	else if(id == 4) {r = 0.0; g = 1.0; b = 1.0;}  // cyan
	else if(id == 5) {r = 1.0; g = 0.0; b = 1.0;}  // magenta
	else if(id == 6) {r = 1.0; g = 1.0; b = 0.0;}  // yellow
	else if(id == 7) {r = 1.0; g = 1.0; b = 1.0;}  // white
	else if(id == 8) {r = 0.0; g = 0.0; b = 0.0;}  // black
	else if(id == 9) {r = 1.0; g = 0.5; b = 0.0;}  // orange
	else if(id == 10){r = 0.5; g = 0.5; b = 0.5;}  // gray
	display();
}


void pixel_menu(int id)
{
	if      (id  == 1) size = 2 * size;
	else if (size > 1) size = size/2;
}

void fill_menu(int id)
{
	if (id == 1) fill = 1;
	else         fill = 0;
}

void key(unsigned char k, int xx, int yy)
{
	if(draw_mode!=TEXT)
	{
		return;
	}
	else
	{
		//glColor3f(1.0,1.0,0.5);
		glRasterPos2i(rx,ry);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, k);
		glFlush();
		//glutStrokeCharacter(GLUT_STROKE_ROMAN,k);
		rx+=glutBitmapWidth(GLUT_BITMAP_9_BY_15,k);
	}

}


void drawButtons(int a, int b, int c, int d, int e, int f){
	int shift=0;

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	if(a==1){
    // Draw a White box for the line menu
		glColor3f(1.0, 1.0, 1.0);
		screen_box(0,wh-ww/10,ww/10);
	}

	if(b==1){
    // Draw a Red box for the rectangle menu
		glColor3f(1.0, 0.0, 0.0);
		screen_box(ww/10,wh-ww/10,ww/10);
	}

	if(c==1){
    // Draw a Green box for the triangle menu
		glColor3f(0.0, 1.0, 0.0);
		screen_box(ww/5,wh-ww/10,ww/10);
	}

	if(d==1){
    // Draw a Blue box for the point menu
		glColor3f(0.0, 0.0, 1.0);
		screen_box(3*ww/10,wh-ww/10,ww/10);
	}

	if(e==1){
    // Draw a yellow box for the point menu
		glColor3f(1.0, 1.0, 0.0);
		screen_box(2*ww/5,wh-ww/10,ww/10);
	}

	if(f==1){
    // Draw a box for the eraser menu
		glColor3f(0.0, 0.8, 1.0);
		screen_box(ww/2,wh-ww/10,ww/10);
	}

	if(a==1){
    // Draw a Black line on the line menu box
		glLineWidth(2);
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex2i(wh/40,wh-ww/20);
		glVertex2i(wh/40+ww/20,wh-ww/20);
		glEnd();
	}

	if(b==1){
    // Draw a Black rectangle on the rectangle menu box
		glColor3f(0.0,0.0,0.0);
		screen_box(ww/10+ww/40,wh-ww/10+ww/40,ww/20);
	}

	if(c==1){
    // Draw a Black triangle in the triangle menu box
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_TRIANGLES);
		glVertex2i(ww/5+ww/40,wh-ww/10+ww/40);
		glVertex2i(ww/5+ww/20,wh-ww/40);
		glVertex2i(ww/5+3*ww/40,wh-ww/10+ww/40);
		glEnd();
	}

	if(d==1){
    // Draw a Black point in the point menu	box
		glColor3f(0.0,0.0,0.0);
		glPointSize(3.0);
		glBegin(GL_POINTS);
		glVertex2i(3*ww/10+ww/20, wh-ww/20);
		glEnd();
	}

	if(e==1){
    // Draw a Black text string on the text menu box
		glColor3f(0.0,0.0,0.0);
		glRasterPos2i(2*ww/5 + 10,wh-ww/20);
		glutBitmapCharacter  (GLUT_BITMAP_9_BY_15, 'A');
		shift=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'A');

		glRasterPos2i(2*ww/5+ 10+shift,wh-ww/20);
		glutBitmapCharacter   (GLUT_BITMAP_9_BY_15, 'B');
		shift+=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'B');

		glRasterPos2i(2*ww/5+ 10+shift,wh-ww/20);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
	}

	if(f==1){
    // Draw an eraser menu box
		glColor3f(1.0,0.0,0.0);
		screen_box(5*ww/10+ww/40,wh-ww/10+ww/40,3*ww/80);

		glColor3f(1.0,1.0,1.0);
		glRectf((5*ww/10+ww/40)+3*ww/80,(wh-ww/10+ww/40),(5*ww/10+ww/40)+ww/20,(wh-ww/10+ww/40)+3*ww/80);

	}
    glFlush();
	glPopAttrib();
}



void collorpalete(void){
//        int shift=0;

	glPushAttrib(GL_ALL_ATTRIB_BITS);

    // Draw the a square painted with selected color
	glColor3f(r, g, b);
	screen_box(10,ww/10,ww/15);

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

	/*glColor3f(0.5,1.0,1.0);
	//screen_box(200,40,30);
	screen_box(ww/10+5*(ww/15),ww/10,ww/15);

	glColor3f(1.0,0.5,0.0);
	screen_box(ww/10+5*(ww/15),ww/10-ww/15,ww/15);*/

	glPopAttrib();

}



void display(void){
	glClearColor (0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	drawButtons(1,1,1,1,1,1);
	collorpalete();

	glFlush();
}


int main(int argc, char** argv)
{
	int c_menu, p_menu, f_menu;

	// Negotiate window session
	glutInit(&argc,argv);

	// Defines the display properties of the window to be created
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

	// Defines the size of the window to be created
	glutInitWindowSize(500, 500);

	// Creates a window with the Title ("square")
	glutCreateWindow("square");

	// Register the Display callback function (display)
	glutDisplayFunc(display);

	// Create a color selection pop-up menu and a function associated with it
	c_menu = glutCreateMenu(color_menu);
	glutAddMenuEntry("Red",    1);
	glutAddMenuEntry("Green",  2);
	glutAddMenuEntry("Blue",   3);
	glutAddMenuEntry("Cyan",   4);
	glutAddMenuEntry("Magenta",5);
	glutAddMenuEntry("Yellow", 6);
	glutAddMenuEntry("White",  7);
	glutAddMenuEntry("Black",  8);
	glutAddMenuEntry("Orange",  9);
	glutAddMenuEntry("Gray",  10);

	// Create a pixel resize pop-up menu and a function associated with it
	p_menu = glutCreateMenu(pixel_menu);
	glutAddMenuEntry("increase pixel size", 1);
	glutAddMenuEntry("decrease pixel size", 2);

	// Create a fill selection mode pop-up menu	and function associated with it
	f_menu = glutCreateMenu(fill_menu);
	glutAddMenuEntry("fill on",  1);
	glutAddMenuEntry("fill off", 2);

	// Create a pop-up menu for clearing or quitting and function associated with it
	glutCreateMenu(right_menu);
	glutAddMenuEntry("quit", 1);
	glutAddMenuEntry("clear",2);
	// Attach the menu just created to the right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Create a pop-up menu for selecting color, pixel resize or fill mode
	glutCreateMenu(middle_menu);
	glutAddSubMenu("Colors",     c_menu);
	glutAddSubMenu("Pixel Size", p_menu);
	glutAddSubMenu("Fill",       f_menu);
	// Attach the menu just created to the right mouse button
	glutAttachMenu(GLUT_MIDDLE_BUTTON);


	// Initialization OpenGL commands
	myinit ();

	// Register callback function myReshape to be called when the window is resized
	glutReshapeFunc (myReshape);

	// Register callback function key to be called when a key is depressed
	glutKeyboardFunc(key);

	// Register callback function mouse to be called when a mouse event occurs
	glutMouseFunc (mouse);

	glutMotionFunc (mouse_motion);

	glutPassiveMotionFunc(mouse_passive_motion);

	glutIdleFunc(teste);

	// Enter the event loop
	glutMainLoop();

	return 0;
}
