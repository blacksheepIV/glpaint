#include "pick.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

#define PLUS 20
#define MINUS 21

int pick(int x, int y, int wh, int ww)
{
	y = wh - y;

	// Verifica se y esta' na parte superior da tela
	// onde estao os botões de selecao das ferramentas
	// Entao retorna a ferramenta sob a posicao x,y
	if (y < wh-ww/10) return 0;
        else if(x < ww/10   ) return LINE;
        else if(x < ww/5    ) return RECTANGLE;
        else if(x < 3*ww/10 ) return TRIANGLE;
        else if(x < 2*ww/5  ) return POINTS;
        else if(x < ww/2    ) return TEXT;
	    else if(x < 3*ww/5  ) return CIRCLE;
	    else if(x < 7*ww/10 ) return ERASER;
        else return 0;
}


int pick_color(int x, int y, int wh, int ww)
{
	y = wh - y;

	// Verifica se y esta na parte inferior onde estao as cores
	// Se estiver retorna a cor sob a posição x,y
	if(y > ((ww/10 + ww/15))||(y < (ww/10)-ww/15)||(x < ww/10)) return 0;
	else if((x >= ww/10) && (x <= (ww/10+ww/15)) && (y > ww/10)) return RED;
	else if((x > ww/10) && (x < (ww/10+ww/15)) && (y < ww/10)) return GREEN;
	else if(x < (ww/10+2*(ww/15)) && (y> ww/10)) return BLUE;
	else if(x < (ww/10+2*(ww/15)) && (y< ww/10)) return CYAN;
	else if(x < (ww/10+3*(ww/15)) && (y> ww/10)) return MAGENTA;
	else if(x < (ww/10+3*(ww/15)) && (y< ww/10)) return YELLOW;
	else if(x < (ww/10+4*(ww/15)) && (y> ww/10)) return ORANGE;
	else if(x < (ww/10+4*(ww/15)) && (y< ww/10)) return BLACK;
	else if(x < (ww/10+5*(ww/15)) && (y> ww/10)) return GRAY;
	else if(x < (ww/10+5*(ww/15)) && (y< ww/10)) return WHITE;

	return 0;

}


int pick_size(int x, int y, int wh, int ww){
    GLint lwidth,psize;

	// Verifica se y esta na parte onde estao os botões + e -
	// Então verifica se esta sob o botão de + ou de - e faz o incremento
	// ou decremento
	if(y > (ww/10) || (x > (ww/2+ww/5+ww/20)) || ( x <(ww/2+ww/5))) return 0;
    else if(y<ww/20) {
            glGetIntegerv(GL_LINE_WIDTH,&lwidth);
            glGetIntegerv(GL_POINT_SIZE,&psize);
            glLineWidth(lwidth+1);
            glPointSize(psize+1);
            return 1;
    } else {
        glGetIntegerv(GL_LINE_WIDTH,&lwidth);
        glGetIntegerv(GL_POINT_SIZE,&psize);
        glLineWidth(lwidth-1);
        glPointSize(psize-1);
        return 1;
    }
    return 0;
}
