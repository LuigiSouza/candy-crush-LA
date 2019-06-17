#ifndef __Jogo__
#define __Jogo__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "GL/glut.h"
#include "GL/freeglut_ext.h" //callback da wheel do mouse.

// Função Principal que inicia o jogo quando solicitado
int Iniciar(int x);

// Função que busca em todo o tabuleiro por combinações
int Combinar(void);

// Função que desce cada peça para baixo caso houver espaços livres
int ShiftDown(void);

// Função que reconhece a posição do mouse e marca a jogada
void Marcar(int mx, int my);

// Função que Desenha cada figura conforme a numeração
void IMG(int num, int posx, int posy, int *pos);

// Função que troca duas posições selecioandas
void troca(int posy1, int posx1, int posx2, int posy2);

// Função que implementa a peça especial de alinhar 5 doces da mesma cor
void Bolacha(int explos);

// Função que exibe mensagens conforme a combinação efetuada
void Comemoracao(int valor);

// Função que emprime na tela os Pontos do Usuário
void MarcaPonto(int pontos);

#endif
