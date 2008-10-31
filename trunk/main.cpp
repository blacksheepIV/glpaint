/* newpaint.c   */

/* E. Angel, Interactive Computer Graphics			*/
/* A Top-Down Approach with OpenGL, Third Edition	*/
/* Addison-Wesley Longman, 2003						*/


/* paint program from chapter 3  */

/* This program illustrates the use of the glut library for
interfacing with a window system */

#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <string.h>

#include "include/figuras.h"
#include "include/pick.h"
#include "include/definicoes.h"
#include "include/color.h"

void mouse(int, int, int, int);
void key(unsigned char, int, int);
void display(void);
void drawSquare(int, int);
void myReshape(GLsizei, GLsizei);

void myinit(void);

void right_menu(int);
void middle_menu(int);
void color_menu(int);
void pixel_menu(int);
void fill_menu(int);
void drawButtons(int a, int b, int c, int d, int e, int f, int h);
bool area_de_desenho(void);

/* globals */

GLsizei wh = 500, ww = 500; /* initial window size			*/
GLfloat size = 3.0;			/* half side length of square	*/
int draw_mode = 0;			/* drawing mode					*/
int rx, ry;					/* raster position				*/

GLfloat r = 1.0, g = 1.0, b = 1.0;	/* drawing color */
GLfloat rb = 0.0, gb = 0.0, bb = 0.0; /* background color */

int cor=WHITE,bcor=BLACK;

int fill = 0;						/* fill flag	 */

int cont = 0;
int xp[2],yp[2];

// tamanho inicial ta borracha
int tamanho=20;

int mpm = 0;
int idle = 1;

int cont_motion = 0;

// posição do mouse (a última posição onde o mouse ficou ocioso)
// possui uma defasagem com relação à posição atual
// nas funções mouse_motion e mouse_passive_motion
// são utilizados para apagar figuras temporárias (modo XOR)
int xi,yi;

int cont_idle = 0; // flag para evitar um loop na função mouse_idle


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

// essa função no diz se o mouse está sobre os menus (opções ou paleta)
bool area_de_desenho(int x, int y)
{
	int opcoes = pick(x,y,wh,ww);
	int cores = pick_color(x,y,wh,ww);
	int sizes = pick_size(x,y,wh,ww);

	if ((!opcoes) && (!cores) && (!sizes)) return true;
	else return false;
}


// o picking vai acontecer direto! sempre que o mouse estiver ocioso
void mouse_idle()
{

/*<<<<<<< .mine
    if(area_de_desenho())
    {

	if ((idle==1) & (cont_idle==0) & (draw_mode == ERASER))
=======*/
	if (cont_idle==0 && idle!= 0)
//>>>>>>> .r33
	{

		if(area_de_desenho(xi, yi))
		{
  //         puts("desenho");

		    if ((draw_mode == ERASER) && (idle==1))
			{

			    int aux = cor;
				glPushAttrib(GL_ALL_ATTRIB_BITS);
                        //puts("idlefunc");

				glEnable(GL_COLOR_LOGIC_OP);

				glLogicOp(GL_XOR);

				set_color(bcor,&cor);

				quadrado(xi,wh-yi,tamanho);

				set_color(aux,&cor);

				glDisable(GL_XOR);

				glPopAttrib();
			}
            // evitar um loop desnecessario (quando o mouse estiver parado)
			cont_idle = 1;
		}

		else
		{
			cont_idle = 1;
		}
	}

	glFlush();
}

void mouse_passive_motion(int x, int y)
{
	glFlush();
   //puts("passive_motion");


	glPushAttrib(GL_ALL_ATTRIB_BITS);

        // se não estiver sobre os menus
	if(area_de_desenho(x,y))
	{

        // na primeira vez que entrar nesta função

//<<<<<<< .mine
//=======
/*<<<<<<< .mine
        where = pick(x,y);
        wherec = pick_color(x,y);
        // se não estiver sobre os menus
        if((where == 0) & (wherec == 0))
        {
=======*/
            // na primeira vez que entrar nesta função
//>>>>>>> .r33

//>>>>>>> .r34
		cont_idle = 0;


		if (mpm==0)
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
				{

                       int aux = cor;
					set_color(bcor,&cor);

					glEnable(GL_COLOR_LOGIC_OP);

					glLogicOp(GL_XOR);

                        // desenha borracha temporaria
					quadrado(x,wh-y,tamanho);
                      //   glFlush();

                        glDisable(GL_COLOR_LOGIC_OP);

                       set_color(aux,&cor);

                        // guarda a posição da borracha
					xi=x;
					yi=y;

				} break;

				default: break;
			}




			glPopAttrib();
			glFlush();
                // printf("%s\n","estou na motion");
               // glDisable(GL_COLOR_LOGIC_OP);
		}
	}

//    }

}


void mouse_motion(int x, int y)
{

//    printf("cor: %d",cor);

    if (area_de_desenho(x,y))
    {

	puts("mouse_motion");

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glEnable(GL_COLOR_LOGIC_OP);

	glLogicOp(GL_XOR);

    // primeiro movimento após clicar com o mouse (segurando o botão)
	if (cont_motion == 0)
	{
		xi=xp[0];
		yi=yp[0];

		cont_motion++;
	}


/*<<<<<<< .mine
        if((where != 0) & (wherec!=0))
        {
          //cont = 0;
            draw_mode = where;
        }
=======*/
	switch(draw_mode)
	{
		case(LINE):
//>>>>>>> .r33

			if(cont_motion!=0)
			{
				printf("cor: %d",cor);


                // desenha (apaga) por cima da linha anterior
				glBegin(GL_LINES);
				glVertex2i(xi,wh-yi);
				glVertex2i(xp[0],wh-yp[0]);
				glEnd();

                // guarda o ponto final da linha atual
				xi=x;
				yi=y;

                // desenha linha temporária
				glBegin(GL_LINES);
				glVertex2i(x,wh-y);
				glVertex2i(xp[0],wh-yp[0]);
				glEnd();


//                        glFlush();

			} break;

		case(RECTANGLE):



             // desenha (apaga) por cima do retângulo anterior

			if (fill) glRecti(xi,wh-yi,xp[0],wh-yp[0]);
			else retangulo(xi,wh-yi,xp[0],wh-yp[0]);

			if(cont_motion!=0)
			{
                // guarda o ponto final da linha atual
				xi=x;
				yi=y;

                // desenha retângulo temporário
				if (fill) glRecti(x,wh-y,xp[0],wh-yp[0]);
				else retangulo(x,wh-y,xp[0],wh-yp[0]);

			} break;

		case(TRIANGLE):

            if (cont_motion!=0)
            {

                    // desenha linha temporária
                    glBegin(GL_LINES);
                    glVertex2i(xi,wh-yi);
                    glVertex2i(xp[0],wh-yp[0]);
                    glEnd();

                    // guarda o ponto final da linha atual
                    xi=x;
                    yi=y;

                    // desenha (apaga) por cima da linha anterior
                    glBegin(GL_LINES);
                    glVertex2i(x,wh-y);
                    glVertex2i(xp[0],wh-yp[0]);
                    glEnd();

            } break;

        case (ERASER):
		{
		    if (!area_de_desenho(x-tamanho/2,y) || !area_de_desenho(x+tamanho/2,y) || !area_de_desenho(x,y-tamanho/2) || !area_de_desenho(x,y+tamanho/2)) break;

			glPushAttrib(GL_ALL_ATTRIB_BITS);
			glDisable(GL_COLOR_LOGIC_OP);

                    // Aplica a cor de background
       //             int aux = cor;

			set_color(bcor,&cor);
			quadrado(x,wh-y,tamanho);

			glPopAttrib();
//                    glFlush();
        //            set_color(aux);

		} break;

		default: break;
	}




	glPopAttrib();
	glFlush();
          // printf("%s\n","estou na motion");
        //glDisable(GL_COLOR_LOGIC_OP);
   }
}


void mouse(int btn, int state, int x, int y)
{
	//int opcao;
   // int cor;
   printf("cont %d\n", cont);


	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		puts("mouse down");

		//printf("%d",pick_color(x,y));

		// define a cor de desenho
		if ((!area_de_desenho(x,y)) && (pick_color(x,y,wh,ww) !=0))
		{
		//	puts("setei a cor");

			set_color(pick_color(x,y,wh,ww),&cor);

		//	printf("cor: %d\n", cor);

            // redesenha a paleta
			colorpalete(cor,bcor,wh,ww);
		}


        // define o modo de desenho
		if((!area_de_desenho(x,y)) && (pick(x,y,wh,ww)!=0))
		{
		    pick_size(x,y,wh,ww);
			draw_mode = pick(x,y,wh,ww);
		}


//        if (!area_de_desenho(x,y)) cont=0;
		if(area_de_desenho(x,y))
		{


			switch(draw_mode)
			{
				case(LINE):
				{

              // defino o ponto inicial da linha (ao clicar)
					xp[0] = x;
					yp[0] = y;

                } break;

				case(RECTANGLE):
				{
                    // defino o ponto inicial do retângulo (ao clicar)

					xp[0] = x;
					yp[0] = y;

                } break;

				case (TRIANGLE):
				{

                    if(cont==0)
                    {
                        // defino o ponto inicial da linha (ao clicar)
                        xp[0] = x;
                        yp[0] = y;
                        cont++;
                    }
                    else
                    {
                        printf("x =%d e y=%d\n",x,y);
                        printf("x[0] =%d e y[0]=%d\n",xp[0],yp[0]);
                        printf("x[1] =%d e y[1]=%d\n",xp[1],yp[1]);

                        puts("jeghrjagjh");
                        glBegin(GL_LINES);
                            glVertex2i(x,wh-y);
                            glVertex2i(xp[0],wh-yp[0]);
                        glEnd();

                        glBegin(GL_LINES);
                            glVertex2i(x,wh-y);
                            glVertex2i(xp[1],wh-yp[1]);
                        glEnd();

                        cont = 0;
                    }
				} break;

				case(POINTS):
				{
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
				} break;

				case (ERASER):
				{
				    if (!area_de_desenho(x-tamanho/2,y) || !area_de_desenho(x+tamanho/2,y) || !area_de_desenho(x,y-tamanho/2) || !area_de_desenho(x,y+tamanho/2)) break;
				    //glColor3f(rb,gb,bb);
					int aux = cor;
					set_color(bcor,&cor);

					quadrado(x,wh-y,tamanho);

                    set_color(aux,&cor);
				} break;

				default : break;
			}
		}

	}

	if(btn==GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
		puts("mouse up");


/*<<<<<<< .mine
		if ((xp[0]!=0) & (yp[0]!=0) & (pick(x,y)==0))
=======*/

		if ((xp[0]!=0) && (yp[0]!=0) && (pick(x,y,wh,ww)==0) && (cont!=0))
//>>>>>>> .r33
		{
                // aqui eu desenho as figuras definitivas (ao soltar o botão)
			switch (draw_mode) {

				case(LINE):

				{

					glBegin(GL_LINES);
					glVertex2i(x,wh-y);
					glVertex2i(xp[0],wh-yp[0]);
					glEnd();

					cont=0;


				} break;

				case(RECTANGLE):

				{
					if (fill)
					{
                        // desenha retângulo temporário
						glRecti(x,wh-y,xp[0],wh-yp[0]);
					}
					else retangulo(x,wh-y,xp[0],wh-yp[0]);

					cont=0;

				} break;

				case(TRIANGLE):

				{
				    if (cont==1)
				    {
                        xp[1]=x;
                        yp[1]=y;

                        glBegin(GL_LINES);
                        glVertex2i(x,wh-y);
                        glVertex2i(xp[0],wh-yp[0]);
                        glEnd();
                    }


				} break;

				default: break;

			} // fim do swicth
		}

		glPushAttrib(GL_ALL_ATTRIB_BITS);

		glLineWidth(3);

        // marcar com um X a opção escolhida
		switch(draw_mode){
			case(LINE):
				drawButtons(0,1,1,1,1,1,1);
				glColor3f(1.0,0.0,0.0);
				glBegin(GL_LINES);
				glVertex2f(0.0,wh-ww/10);
				glVertex2f(ww/10,wh);
				glVertex2f(ww/10,wh-ww/10);
				glVertex2f(0.0,wh);
				glEnd();
				break;
			case(RECTANGLE):
				drawButtons(1,0,1,1,1,1,1);
				glColor3f(1.0,1.0,0.0);
				glBegin(GL_LINES);
				glVertex2f(ww/10.0,wh-ww/10);
				glVertex2f(2*ww/10,wh);
				glVertex2f(2*ww/10,wh-ww/10);
				glVertex2f(ww/10.0,wh);
				glEnd();
				break;
			case(TRIANGLE):
				drawButtons(1,1,0,1,1,1,1);
				glColor3f(0.0,0.0,1.0);
				glBegin(GL_LINES);
				glVertex2f(ww/5.0,wh-ww/10);
				glVertex2f(3*ww/10.0,wh);
				glVertex2f(3*ww/10.0,wh-ww/10);
				glVertex2f(ww/5.0,wh);
				glEnd();
				break;
			case(POINTS):
				drawButtons(1,1,1,0,1,1,1);
				glColor3f(1.0,1.0,1.0);
				glBegin(GL_LINES);
				glVertex2f(3*ww/10.0,wh-ww/10);
				glVertex2f(4*ww/10.0,wh);
				glVertex2f(4*ww/10.0,wh-ww/10);
				glVertex2f(3*ww/10.0,wh);
				glEnd();
				break;
			case(TEXT):
				drawButtons(1,1,1,1,0,1,1);
				glColor3f(1.0,0.0,0.0);
				glBegin(GL_LINES);
				glVertex2f(2*ww/5,wh-ww/10);
				glVertex2f(ww/2,wh);
				glVertex2f(ww/2,wh-ww/10);
				glVertex2f(2*ww/5,wh);
				glEnd();
				break;
            case(CIRCLE):
				drawButtons(1,1,1,1,1,0,1);
				glColor3f(1.0,0.0,0.0);
				glBegin(GL_LINES);
				glVertex2f(ww/2,wh-ww/10);
				glVertex2f(3*ww/5,wh);
				glVertex2f(3*ww/5,wh-ww/10);
				glVertex2f(ww/2,wh);
				glEnd();
				break;
            case(ERASER):
                drawButtons(1,1,1,1,1,1,0);
				glColor3f(1.0,0.0,0.0);
				glBegin(GL_LINES);
				glVertex2f(ww/2+ww/10,wh-ww/10);
				glVertex2f(3*ww/5+ww/10,wh);
				glVertex2f(3*ww/5+ww/10,wh-ww/10);
				glVertex2f(ww/2+ww/10,wh);
				glEnd();
				break;
		}



cont_motion=0;
		glPopAttrib();
		glFlush();
	}

    /*if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
	bcor = pick_color(x,y);
	if (bcor!=0)
	set_bgcolor(cor);
}*/

	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	{
		if ((!area_de_desenho(x,y)) && (pick_color(x,y,wh,ww)!=0))
		{
			puts("setei a cor de fundo");

			set_bgcolor(pick_color(x,y,wh,ww),&bcor, &rb, &gb, &bb);

	        // redesenha a paleta de cores
			colorpalete(cor, bcor, wh, ww);
		}
        //retangulo(5,wh-5,30,wh-30);
	}

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
	//display();
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


void drawButtons(int a, int b, int c, int d, int e, int f, int h){
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
    // Draw a yellow box for the text menu
		glColor3f(1.0, 1.0, 0.0);
		screen_box(2*ww/5,wh-ww/10,ww/10);
	}

	if(f==1){
    // Draw a box for the circle
		glColor3f(1.0, 0.5, 0.0);
		screen_box(ww/2,wh-ww/10,ww/10);
	}

	if(h==1){
    // Draw a box for the eraser menu
		glColor3f(0.0, 0.8, 1.0);
		screen_box(ww/2+ww/10,wh-ww/10,ww/10);
	}

	// Draw the plus menu
	glColor3f(1.0,0.8,0.8);
		screen_box(ww/2+ww/5,wh-ww/20,ww/20);
	glColor3f(1.0,1.0,1.0);
		screen_box(ww/2+ww/5,wh-ww/10,ww/20);
    glColor3f(0.0,0.0,0.0);
        glLineWidth(2);
        glBegin(GL_LINES);
            glVertex2f(ww/2+ww/5+ww/60,wh-ww/40);
            glVertex2f(ww/2+ww/5+ww/30,wh-ww/40);
            glVertex2f((ww/2+ww/5+ww/40),wh-ww/65);
            glVertex2f((ww/2+ww/5+ww/40),wh-ww/28);

            glVertex2f(ww/2+ww/5+ww/60,wh-ww/13);
            glVertex2f(ww/2+ww/5+ww/30,wh-ww/13);
        glEnd();


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
	    // Draw a circle
	    glPushAttrib(GL_LINE_WIDTH|GL_COLOR);
	    glLineWidth(2);
	    glColor3f(0.0,0.5,1.0);
            circulo(5*ww/9,wh-ww/20,ww/30,15);
	    glPopAttrib();
	}

	if(g==1){
    // Draw an eraser menu box
		glColor3f(1.0,0.0,0.0);
		screen_box(6*ww/10+ww/40,wh-ww/10+ww/40,3*ww/80);

		glColor3f(1.0,1.0,1.0);
		glRectf((6*ww/10+ww/40)+3*ww/80,(wh-ww/10+ww/40),(6*ww/10+ww/40)+ww/20,(wh-ww/10+ww/40)+3*ww/80);

	}
	glFlush();
	glPopAttrib();
}



void display(void){
	glClearColor (0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	drawButtons(1,1,1,1,1,1,1);
	colorpalete(cor,bcor, wh,ww);

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
	glutCreateWindow("glPaint - by C.H. Sindeaux e D.R. Matos");

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
	/*glutCreateMenu(right_menu);
	glutAddMenuEntry("quit", 1);
	glutAddMenuEntry("clear",2);
	// Attach the menu just created to the right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);*/

	// Create a pop-up menu for selecting color, pixel resize or fill mode
	glutCreateMenu(middle_menu);
	glutAddSubMenu("Colors",     c_menu);
	glutAddSubMenu("Pixel Size", p_menu);
	glutAddSubMenu("Fill",       f_menu);
	// Attach the menu just created to the middle mouse button
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

	glutIdleFunc(mouse_idle);

	// Enter the event loop
	glutMainLoop();

	return 0;
}
