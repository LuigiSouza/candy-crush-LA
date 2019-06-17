/*********************************************************************
//  Implementação de Canvas para desenho - Versao C.
//  de Cesar Tadeu Pozzer
//
//  Jogo Candy Crush
//
//  Autor: Luigi Perotti Souza
//         06/2019
//  Objetivo:
//    Utilização do mouse para seleção de peças iguais e formar assim
//    combinações e acumular pontos
//  Instruções:
//	  Todo o jogo é controlado a partir do clique esquerdo do mouse,
//    deve-se clicar na peça desejada e a seguir uma adjacente na horizontal
//    ou vertival para realizar a troca de posição dessas duas peças. A
//    troca só é efetuada caso uma combinação for formada após a jogada.
//    Para interromper o jogo basta pressionar a tecla "Esc", para se
//    reiniciar basta pressionar o "Enter" novamente.
// *********************************************************************/
#include <windows.h>
#include "GL/glut.h"
#include "GL/freeglut_ext.h" //callback da wheel do mouse.


#include <stdio.h>
#include <stdlib.h>


#include "jogo.h"
#include "gl_canvas2d.h"
#define DIM_TELA 600
//468 de Altura
#define FIM_JOG 529
#define INI_JOG 61
//468 de Comprimento
#define TELA_TOP 488
#define TELA_BAX 20

//variaveis globais

int repet=0;
int xIniciar;

float corDoMenu=0;

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis
//globais que podem ser setadas pelo metodo keyboard()

void render()
{
    clear(0,0,0);

    corDoMenu += 0.20;

    color((sin(corDoMenu)+1)/2, 0, (sin(corDoMenu)+1)/2);

    xIniciar = Iniciar(xIniciar);

    color(1, 0, 1);

    text(300,520,"Pontos: ");
    text(INI_JOG,520,"Candy Crush - UFSM");
}

//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key)
{
   switch(key)
   {
      case 13: //Iniciar Jogo
          xIniciar=1;

        break;
      case 27: //finaliza programa
	     exit(0);
        break;
   }
}
//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
}


//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int xm, int ym)
{
   ym = DIM_TELA - ym;

    //Controle Para evitar o Click Duplo
   repet++;
   if(repet>=2){
       repet=0;
       return;
   }
   //Chamar a função sempre que o mouse clicar dentro do Vetor Principal
   if(button == 0 && xm>INI_JOG && xm<FIM_JOG && ym<TELA_TOP && ym>TELA_BAX){
       Marcar(xm, ym);
   }

}

int main(void)
{

   initCanvas(DIM_TELA, DIM_TELA, "Implementação Candy Crush");

   runCanvas();

}
