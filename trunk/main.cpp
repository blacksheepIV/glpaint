#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

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
int sizei=1;

int fill = 0;						/* fill flag	 */

int cont = 0;
int xp[2],yp[2];

// tamanho inicial ta borracha
int tamanho=20;

int idle = 0;

int cont_motion = 0;

// posição do mouse (a última posição onde o mouse ficou ocioso)
// possui uma defasagem com relação à posição atual
// nas funções mouse_motion e mouse_passive_motion
// são utilizados para apagar figuras temporárias (modo XOR)
int xi,yi;

int cont_idle = 1; // flag para evitar um loop na função mouse_idle


void drawSquare(int x, int y)
{
	y=wh-y;
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
/*	int opcoes = pick(x,y,wh,ww);
	int cores = pick_color(x,y,wh,ww);
	int sizes = pick_size(x,y,wh,ww);
*/
	if (/*(!opcoes) && (!cores) && (!sizes) && */y > 1+ww/10 && y < wh-1-ww/6) return true;
	else return false;
}



// estas funções (idle e passive motion) serviriam para
// mostrar ao usuario a posição da borracha ou de um cursor personalizado

void mouse_idle()
{


	if (idle==1 && cont_idle==0 && draw_mode==ERASER)
	{
	    //if (!area_de_desenho(xi-tamanho/2,yi) || !area_de_desenho(xi+tamanho/2,yi) || !area_de_desenho(xi,yi-tamanho/2) || !area_de_desenho(xi,yi+tamanho/2)) return;

		glPushAttrib(GL_ALL_ATTRIB_BITS);

		glEnable(GL_COLOR_LOGIC_OP);

		glLogicOp(GL_XOR);

      /*      glPushAttrib(GL_ALL_ATTRIB_BITS);//

            glLineWidth(1);

            glColor3i(1,1,1);//set_color(WHITE,&cor);//
       //     printf("cor %d\n",cor);

            quadrado(xi,wh-yi,tamanho-1);

            glPopAttrib();//*/

		set_color(bcor/*,&cor*/);

	//	  printf("cor %d\n",cor);

		borracha(xi,wh-yi,tamanho-2);

		glPopAttrib();

		cont_idle=1;

	}
}


void mouse_passive_motion(int x, int y)
{

   // se não estiver sobre os menus
	if(area_de_desenho(x,y) && draw_mode==ERASER)
	{

		glPushAttrib(GL_ALL_ATTRIB_BITS);

		glEnable(GL_COLOR_LOGIC_OP);

        glLogicOp(GL_XOR);

		cont_idle = 0;


		if (idle==0)
		{
			xi=x;
			yi=y;

			//
			idle=1;
		}

		switch(draw_mode)
		{

			case (ERASER):
			{
//if (!area_de_desenho(x-tamanho/2,y) || !area_de_desenho(x+tamanho/2,y) || !area_de_desenho(x,y-tamanho/2) || !area_de_desenho(x,y+tamanho/2)) break;
			/*    glPushAttrib(GL_ALL_ATTRIB_BITS);//

                    glLineWidth(1);

                   // glColor3i(1,1,1);
                   set_color(WHITE);//
                   //cor=WHITE;
                //      printf("cor %d\n",cor);

                    quadrado(x,wh-y,tamanho-1);

                glPopAttrib();//*/


				set_color(bcor/*,&cor*/);
			//	  printf("cor %d\n",cor);

                // desenha borracha temporária
				borracha(x,wh-y,tamanho-2);


                    // guarda a posição da borracha
				xi=x;
				yi=y;


			} break;

			default: break;
		}

		glPopAttrib();
		glFlush();

	}
}

void mouse_motion(int x, int y)
{

//    printf("cor: %d",cor);

	if (area_de_desenho(x,y))
	{

        // primeiro movimento após clicar com o mouse (segurando o botão)
		if (cont_motion == 0)
		{
			xi=xp[0];
			yi=yp[0];

			cont_motion++;
		}



		switch(draw_mode)
		{
			case(LINE):
			{

				if(cont_motion!=0)
				{

					glPushAttrib(GL_ALL_ATTRIB_BITS);

					glEnable(GL_COLOR_LOGIC_OP);

					glLogicOp(GL_XOR);

                    // VERBOSE
                    //printf("cor: %d",cor);


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

					glPopAttrib();

				}           //glFlush();

			} break;

			case(RECTANGLE):
			{

				glPushAttrib(GL_ALL_ATTRIB_BITS);

				glEnable(GL_COLOR_LOGIC_OP);

				glLogicOp(GL_XOR);


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
				}

				glPopAttrib();

			} break;

			case(TRIANGLE):
			{

				if (cont_motion!=0)
				{
					glPushAttrib(GL_ALL_ATTRIB_BITS);

					glEnable(GL_COLOR_LOGIC_OP);

					glLogicOp(GL_XOR);



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

					glPopAttrib();

				}

			} break;

			case (ERASER):
			{
				if (!area_de_desenho(x,y+tamanho/2) || !area_de_desenho(x,y-tamanho/2)/* || !area_de_desenho(x,y-tamanho/2) || !area_de_desenho(x,y+tamanho/2)*/) break;

				glPushAttrib(GL_ALL_ATTRIB_BITS);
                //glDisable(GL_COLOR_LOGIC_OP);

                        // Aplica a cor de background
           //             int aux = cor;

				set_color(bcor/*,&cor*/);
				  printf("cor %d\n",cor);
				borracha(x,wh-y,tamanho);

				glPopAttrib();
                      //  glFlush();
            //            set_color(aux);

			} break;

			case (CIRCLE):
			{

				glPushAttrib(GL_ALL_ATTRIB_BITS);

				glEnable(GL_COLOR_LOGIC_OP);

				glLogicOp(GL_XOR);
                // desenha (apaga) por cima do circulo anterior

				double d = sqrt(pow((xi-xp[0]),2)+pow((yi-yp[0]),2));

				if (fill) circulo_cheio(xp[0],wh-yp[0],d);
				else circulo(xp[0],wh-yp[0],d);

				if(cont_motion!=0)
				{
                    // guarda o ponto final da linha atual
					xi=x;
					yi=y;

					double d2 = sqrt(pow((x-xp[0]),2)+pow((y-yp[0]),2));

                    // desenha circulo temporário
					if (fill) circulo_cheio(xp[0],wh-yp[0],d2);
					else circulo(xp[0],wh-yp[0],d2);
				}

				glPopAttrib();

			} break;

			default: break;
		}

		glFlush();
          // printf("%s\n","estou na motion");
        //glDisable(GL_COLOR_LOGIC_OP);
	}
}



void mouse(int btn, int state, int x, int y)
{

	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{

		// define a cor de desenho
		if ((!area_de_desenho(x,y)) && (pick_color(x,y,wh,ww) !=0))
		{
		//	puts("setei a cor");


			set_color(pick_color(x,y,wh,ww)/*,&cor*/);
			cor = pick_color(x,y,wh,ww);

		//	printf("cor: %d\n", cor);

            // redesenha a paleta
			colorpalete(cor,bcor,wh,ww);
			puts("441");
		}


        // define o modo de desenho
		if(!area_de_desenho(x,y)&& (pick(x,y,wh,ww)!=0))
		{
			draw_mode = pick(x,y,wh,ww);
		//	if(pick_size(x,y,wh,ww)!=0) drawButtons(1,1,1,1,1,1,1);
		}

        // Define o tamanho
		if(!area_de_desenho(x,y)&&(pick_size(x,y,wh,ww)!=0))
		{
			set_size(pick_size(x,y,wh,ww),&sizei);

			if ((pick_size(x,y,wh,ww)==1) && tamanho<=60)
			{
			    tamanho+=5;
			}

			else if ((pick_size(x,y,wh,ww)==2) && tamanho>=20)
			{
			    tamanho-=5;
			}
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

					printf("%d down\n", cont);

					if(cont==0)
					{
                        // defino o ponto inicial da linha (ao clicar)
						xp[0] = x;
						yp[0] = y;

					}
					else
					{

						if(!fill){glBegin(GL_LINES);
							glVertex2i(x,wh-y);
							glVertex2i(xp[0],wh-yp[0]);
							glEnd();

							glBegin(GL_LINES);
							glVertex2i(x,wh-y);
							glVertex2i(xp[1],wh-yp[1]);
							glEnd();
						} else {
							glBegin(GL_TRIANGLES);
							glVertex2f(xp[0], wh-yp[0]);
							glVertex2f(xp[1],wh-yp[1]);
							glVertex2f(x,wh- y);
							glEnd();
						}

						cont = 0;

					}

				} break;

				case(POINTS):
				{
					{
						glBegin(GL_POINTS);
                        //drawSquare(x,y);
						glVertex2f(x,wh-y);
						glEnd();
						cont++;
					}
					break;
					case(TEXT):
					{
						rx=x;
						ry=wh-y;

                         // Desenha um ponto para marcar o inicio do texto
						glPushAttrib(GL_POINT_SIZE);
						glPointSize(2);
						glBegin(GL_POINTS);
						glVertex2f(rx,ry);
						glEnd();
						glPopAttrib();

						glRasterPos2i(rx,ry);
						cont=0;
					}
				} break;

				case (ERASER):
				{
				    if (!area_de_desenho(x,y+tamanho/2) || !area_de_desenho(x,y-tamanho/2)) break;
				   // if (!area_de_desenho(x-tamanho/2,y) || !area_de_desenho(x+tamanho/2,y) || !area_de_desenho(x,y-tamanho/2) || !area_de_desenho(x,y+tamanho/2)) break;
				    //glColor3f(rb,gb,bb);

					glPushAttrib(GL_ALL_ATTRIB_BITS);
					set_color(bcor/*,&cor*/);
					  printf("cor %d\n",cor);

					borracha(x,wh-y,tamanho);
					//puts("eraser");
					glPopAttrib();


				} break;

				case (CIRCLE):
				{
					puts("centro");
				    // defino o centro do circulo

					xp[0] = x;
					yp[0] = y;
				} break;

				default : break;
			}
		}

    // necessario para imprimir logo apos clicar com o mouse
		glFlush();
	}

	if(btn==GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
	    if (!area_de_desenho(x,y)) { cont=0; cont_motion=0; }
//puts("up");

		else if ((xp[0]!=0) && (yp[0]!=0) && (pick(x,y,wh,ww)==0) && (cont_motion!=0))

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
					if (cont==0)
					{
						xp[1]=x;
						yp[1]=y;
						if(!fill){
							glBegin(GL_LINES);
							glVertex2i(x,wh-y);
							glVertex2i(xp[0],wh-yp[0]);
							glEnd();
						} else {
							glVertex2f(xp[1],wh-yp[1]);
							glEnd();
						}

						cont++;
					}


				} break;

				case(CIRCLE):

				{
				    //puts("aqui");
					double d = sqrt(pow((x-xp[0]),2)+pow((y-yp[0]),2));

					if (fill) circulo_cheio(xp[0],wh-yp[0],d);
					else circulo(xp[0],wh-yp[0],d);

					cont=0;

				} break;

				default: {cont =0;} break;

			} // fim do swicth
		}



    if (draw_mode!=0)
    {
        // repinta a paleta
		//colorpalete(cor, bcor, wh, ww);
//int cor_aux = cor;
		glPushAttrib(GL_ALL_ATTRIB_BITS); // push 1
printf("681   cor %d, bcor%d\n", cor, bcor);
		colorpalete(cor, bcor, wh, ww);
		puts("682");


        glColor3i(1,1,1);
        glRectf(0,wh-ww/10,ww,wh);

            //glPopAttrib(); // pop 2

		glLineWidth(3);

        // marcar com um X a opção escolhida
		switch(draw_mode){
			case(LINE):
				drawButtons(1,1,1,1,1,1,1);
				glColor3f(1.0,0.0,0.0);
				glBegin(GL_LINES);
				glVertex2f(0.0,wh-ww/10);
				glVertex2f(ww/10,wh);
				glVertex2f(ww/10,wh-ww/10);
				glVertex2f(0.0,wh);
				glEnd();
				break;
			case(RECTANGLE):
				drawButtons(1,1,1,1,1,1,1);
				glColor3f(1.0,1.0,0.0);
				glBegin(GL_LINES);
				glVertex2f(ww/10.0,wh-ww/10);
				glVertex2f(2*ww/10,wh);
				glVertex2f(2*ww/10,wh-ww/10);
				glVertex2f(ww/10.0,wh);
				glEnd();
				break;
			case(TRIANGLE):
				drawButtons(1,1,1,1,1,1,1);
				glColor3f(0.0,0.0,1.0);
				glBegin(GL_LINES);
				glVertex2f(ww/5.0,wh-ww/10);
				glVertex2f(3*ww/10.0,wh);
				glVertex2f(3*ww/10.0,wh-ww/10);
				glVertex2f(ww/5.0,wh);
				glEnd();
				break;
			case(POINTS):
				drawButtons(1,1,1,1,1,1,1);
				glColor3f(1.0,1.0,1.0);
				glBegin(GL_LINES);
				glVertex2f(3*ww/10.0,wh-ww/10);
				glVertex2f(4*ww/10.0,wh);
				glVertex2f(4*ww/10.0,wh-ww/10);
				glVertex2f(3*ww/10.0,wh);
				glEnd();
				break;
			case(TEXT):
				drawButtons(1,1,1,1,1,1,1);
				glColor3f(1.0,0.0,0.0);
				glBegin(GL_LINES);
				glVertex2f(2*ww/5,wh-ww/10);
				glVertex2f(ww/2,wh);
				glVertex2f(ww/2,wh-ww/10);
				glVertex2f(2*ww/5,wh);
				glEnd();
				break;
			case(CIRCLE):
				drawButtons(1,1,1,1,1,1,1);
				glColor3f(1.0,0.0,0.0);
				glBegin(GL_LINES);
				glVertex2f(ww/2,wh-ww/10);
				glVertex2f(3*ww/5,wh);
				glVertex2f(3*ww/5,wh-ww/10);
				glVertex2f(ww/2,wh);
				glEnd();
				break;
			case(ERASER):
				drawButtons(1,1,1,1,1,1,1);
				glColor3f(1.0,0.0,0.0);
				glBegin(GL_LINES);
				glVertex2f(ww/2+ww/10,wh-ww/10);
				glVertex2f(3*ww/5+ww/10,wh);
				glVertex2f(3*ww/5+ww/10,wh-ww/10);
				glVertex2f(ww/2+ww/10,wh);
				glEnd();

				  printf("cor %d\n",cor);
				break;
		}



		cont_motion=0;

		glPopAttrib(); // pop 1
    }
		glFlush();

	}


	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	{
		if ((!area_de_desenho(x,y)) && (pick_color(x,y,wh,ww)!=0))
		{
		    // VERBOSE
			// puts("setei a cor de fundo");

			set_bgcolor(pick_color(x,y,wh,ww),&bcor, &rb, &gb, &bb);

	        // redesenha a paleta de cores
			colorpalete(cor, bcor, wh, ww);
			puts("788");
		}
        //retangulo(5,wh-5,30,wh-30);

		glFlush();
	}

}





void key(unsigned char k, int xx, int yy)
{
    // Tecla f ativa ou desativa o modo fill
	if(draw_mode!=TEXT)
{
	    if((k=='f')||(k='F')) {
	        if (fill==0) fill = 1;
	        else fill = 0;
} else return;
}
	else
{
		glRasterPos2i(rx,ry);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, k);
		glFlush();
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
            circulo(5*ww/9,wh-ww/20,ww/30);
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
	colorpalete(cor,bcor,wh,ww);
puts("967");

	glFlush();
}


int main(int argc, char** argv)
{
    //int c_menu, p_menu, f_menu;

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
