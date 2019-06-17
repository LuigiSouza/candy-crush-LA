#include <windows.h>
#include "GL/glut.h"
#include "GL/freeglut_ext.h"

#include "jogo.h"
#include "gl_canvas2d.h"

#define DIM_TELA 600
//468 de Altura
#define FIM_JOG 529
#define INI_JOG 61
//468 de Comprimento
#define TELA_TOP 488
#define TELA_BAX 20
//Medidas de Cada setor e seu centro
#define AUX (FIM_JOG - INI_JOG)/9
#define METADE AUX/2
//52x52 px cada quadrado
#define FIGURAS 6
//Numero de Doces

//variaveis globais

int JOGO[9][9];
int bolachao[9][9];

int xaux=0, yaux=0;

int pontos, erro = 1;
int *selec = 0;
int *selec2 = 0;
int *x=0, pontuacao, comando;
int control;

float corDaBolacha=0;
float corDaBolacha2=0;
float corDaBolacha3=0;

//Converter Pontos para Constant Char
void MarcaPonto(int pontos){

    int i, j, margem;
    int resultado[10];

    int Ipontos = pontuacao;

    //Zerar Vetor e Evitar Lixo
    for(i=0;i<10;i++){
        resultado[i] = -1;
    }
    //Transformar cada "casa" da pontuação em uma posição de vetor
    for(i=0;Ipontos>=10;i++){
        resultado[i] = Ipontos % 10;
        Ipontos = Ipontos / 10;
        i++;
    }

    resultado[i] = Ipontos;

    margem=0;
    //Escrever o Vetor
    for(j=i;j>=0;j--){
        if(resultado[j]==9){
            text(375+(margem*8),520,"9");
        }
        else if(resultado[j]==8){
            text(375+(margem*8),520,"8");
        }
        else if(resultado[j]==7){
            text(375+(margem*8),520,"7");
        }
        else if(resultado[j]==6){
            text(375+(margem*8),520,"6");
        }
        else if(resultado[j]==5){
            text(375+(margem*8),520,"5");
        }
        else if(resultado[j]==4){
            text(375+(margem*8),520,"4");
        }
        else if(resultado[j]==3){
            text(375+(margem*8),520,"3");
        }
        else if(resultado[j]==2){
            text(375+(margem*8),520,"2");
        }
        else if(resultado[j]==1){
            text(375+(margem*8),520,"1");
        }
        else if(resultado[j]==0){
            text(375+(margem*8),520,"0");
        }
        margem++;
    }
}

//Função para chamar textos de Comemoração na tela conforme a pontução do jogador
void Comemoracao(int valor){

    if(valor >= 9){
        color(1, 1, 0);
        text(INI_JOG,545,"Candy Crush");
    }
    else if(valor == 8){
        color(1, 0, 0);
        text(INI_JOG,545,"Lendario");
    }
    else if(valor == 0.2){
        color(1, 0.6, 0);
        text(INI_JOG,545,"Mestre");
    }
    else if(valor == 6){
        color(1, 0.4, 0.2);
        text(INI_JOG,545,"Profissional");
    }
    else if(valor == 5){
        color(1, 0.6, 0.6);
        text(INI_JOG,545,"Magnifico");
    }
    else if(valor == 4){
        color(1, 0.8, 0.6);
        text(INI_JOG,545,"Gostosuras");
    }
    else if(valor == 3){
        color(1, 1, 1);
        text(INI_JOG,545,"Doces");
    }
}

//Função para realizar a queda dos blocos quando houver espaços em branco
int ShiftDown(void){
    int i, j, k=0;
    // Realizar o Shift exceto na primeira linha
    for(i=1;i<9;i++){
        for(j=0;j<9;j++){
            if(JOGO[i][j]==6){
                if(JOGO[i-1][j]==6){
                    JOGO[i-1][j]=rand()%FIGURAS;
                }
                JOGO[i][j]=JOGO[i-1][j];
                JOGO[i-1][j]=6;
                k=1;
                return k;
            }
        }
    }
    // Sortear primeira Linha
    for(i=0;i<9;i++){
        if(JOGO[0][i]==6){
            JOGO[0][i]=rand()%FIGURAS;
            // Evitar muitas figuras iguais
            while(JOGO[0][i] == JOGO[0][i-1] || JOGO[0][i] == JOGO[0][i+1]){
                JOGO[0][i]=rand()%FIGURAS;
            }
            k=1;
            return k;
        }
    }

    return k;
}

//Função que percorre todo vetor Buscando combinaçõs
int Combinar(void){
    int i, j, k, z=0;
    int linha;
    int coluna;
    int teste;

    for(i=0;i<9;i++){
        for(j=0;j<7;j++){
            //Busca de combinações lineares de três peças
            if(JOGO[i][j] == JOGO[i][j+1] && JOGO[i][j] != 6 && JOGO[i][j] != 7){
                if(JOGO[i][j+1]==JOGO[i][j+2] && JOGO[i][j+1] != 6 && JOGO[i][j+1] != 7){
                    pontos = 3;
                    linha = j+2;
                    pontuacao += 40;
                    //Busca de combinações lineares de mais que três peças
                    while(JOGO[i][linha] == JOGO[i][linha+1] && JOGO[i][linha] != 6 && (linha+1)<9 && JOGO[i][linha] != 7){
                        pontos++;
                        if(linha==j+3){
                            bolachao[i][linha+1]=7;
                        }
                        pontuacao += 80;
                        linha++;
                    }
                    int pontosaux = pontos;
                    //Busca de combinações de linhas verticais concorrentes e iguais a primeira linha encontrada
                    for(k=0; k<pontosaux; k++){
                        teste = 0;
                        //Identifiação de um cruz
                        if(JOGO[i][j+k] == JOGO[i+1][j+k] && JOGO[i-1][j+k] == JOGO[i+1][j+k] && i+1<9 && i-1>=0 ){
                            teste = 1;
                            pontuacao+=30;
                        }
                        if(JOGO[i][j+k]==JOGO[i+1][j+k] && JOGO[i][j+k] != 6 && i+1 < 9 && JOGO[i][j+k] != 7){
                            if(JOGO[i+1][j+k]==JOGO[i+2][j+k] && JOGO[i+1][j+k] != 6 && i+2 < 9 && JOGO[i+1][j+k] != 7){
                                pontos+=2;
                                pontuacao +=60;
                                coluna = i+2;
                                // Reconhecimento de combinações com cinco peças
                                if(teste==1 && (JOGO[coluna][j+k] == JOGO[coluna+1][j+k] || JOGO[coluna][j+k] == JOGO[coluna-1][j+k])){
                                    bolachao[coluna][j+k]=7;
                                }
                                while(JOGO[coluna][j+k] == JOGO[coluna+1][j+k] && JOGO[coluna][j+k] != 6 && JOGO[coluna][j+k] != 7 && (coluna+1)<9){
                                    pontos++;
                                    pontuacao += 80;
                                    JOGO[coluna+1][j+k]=7;
                                    coluna++;
                                }
                                if(teste==0 && coluna>=i+3){
                                    bolachao[coluna][j+k]=7;
                                }
                                JOGO[i+1][j+k]=7;
                                JOGO[i+2][j+k]=7;
                            }
                        }
                        if(JOGO[i][j+k]==JOGO[i-1][j+k] && JOGO[i][j+k] != 6 && JOGO[i][j+k] != 7){
                            if(JOGO[i-1][j+k]==JOGO[i-2][j+k] && JOGO[i-1][j+k] != 6 && JOGO[i-1][j+k] != 7){
                                pontos+=2;
                                pontuacao +=60;
                                coluna = i-2;
                                if(teste==1 && JOGO[coluna][j+k] == JOGO[coluna-1][j+k]){
                                    bolachao[coluna][j+k]=7;
                                }
                                else{
                                    bolachao[linha+1][i]=-1;
                                }
                                while(JOGO[coluna][j+k] == JOGO[coluna-1][j+k] && JOGO[coluna][j+k] != 6 && JOGO[coluna][j+k] != 7 && (coluna-1)>=0){
                                    pontos++;
                                    pontuacao += 80;
                                    if(teste==0 && coluna==i-3){
                                        bolachao[coluna][j+k]=7;
                                    }
                                    else{
                                        bolachao[linha+1][i]=-1;
                                    }
                                    JOGO[coluna-1][j+k]=7;
                                    coluna--;
                                }
                                if(coluna>=0){
                                    JOGO[coluna][j+k]=7;
                                }
                                JOGO[i-2][j+k]=7;
                                JOGO[i-1][j+k]=7;
                            }
                        }
                        if(teste==1){
                            if(JOGO[i-1][j+k] != 7){
                                pontos++;
                            }
                            if(JOGO[i+1][j+k] != 7){
                                pontos++;
                            }
                            JOGO[i-1][j+k] = 7;
                            JOGO[i+1][j+k] = 7;
                        }
                        JOGO[i][j+k] = 7;
                    }
                    z = 1;
                    return z;
                }
            }
        }
    }
    //Percorrer o vetor em buscas de combinações apenas verticais
    for(i=0;i<9;i++){
        for(j=0;j<7;j++){
            //Busca de Trincas
            if(JOGO[j][i]==JOGO[j+1][i] && JOGO[j][i] != 6 && JOGO[j+1][i] != 7){
                if(JOGO[j+1][i]==JOGO[j+2][i] && JOGO[j+1][i] != 6 && JOGO[j+1][i] != 7){
                    pontos = 3;
                    linha = j+2;
                    pontuacao += 40;
                    //Busca de maiores combinações
                    while(JOGO[linha][i] == JOGO[linha+1][i] && JOGO[linha][i] != 6 && (linha+1)<9 && JOGO[linha][i] != 7){
                        pontos++;
                        if(linha==j+3){
                            bolachao[linha+1][i]=7;
                        }
                        else{
                            bolachao[linha+1][i]=-1;
                        }
                        pontuacao += 80;
                        linha++;
                    }
                    for(k=0; k<pontos; k++){
                        JOGO[j+k][i] = 7;
                    }
                    z = 1;
                    return z;
                }
            }
        }
    }
    return z;
}

//Peça especial
void Bolacha(int explos){
    int i, j;

    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if((int)JOGO[j][i]==explos){
                JOGO[j][i]=7;
                pontuacao += 15;
            }
            else if(explos==-1){
                //Caso dois especias se unam, todos blocam são excluídos
                JOGO[j][i]=7;
                pontuacao += 15;
            }
        }
    }
}

//Função para trocar dois Blocos
void troca(int posy1, int posx1, int posx2, int posy2){
    int aux, resul;

    aux = JOGO[posx1][posy1];
    JOGO[posx1][posy1]=JOGO[posx2][posy2];
    JOGO[posx2][posy2]=aux;

    // Verificar se alguma figura trocada é o Bolachão
    if(JOGO[posx1][posy1]==8 || JOGO[posx2][posy2]==8){
        if(JOGO[posx2][posy2]==JOGO[posx1][posy1]){
            Bolacha(-1);
        }
        else if(JOGO[posx1][posy1]==8){
            Bolacha((int)JOGO[posx2][posy2]);
            JOGO[posx1][posy1]=7;
        }
        else if(JOGO[posx2][posy2]==8){
            Bolacha((int)JOGO[posx1][posy1]);
            JOGO[posx2][posy2]=7;
        }
        selec = 0;
        selec2 = 0;
        return;
    }

    resul = Combinar();
    // Se a trocar não permitir combinações, as posições serão mantidas
    if(resul == 0){
        aux = JOGO[posx2][posy2];
        JOGO[posx2][posy2]=JOGO[posx1][posy1];
        JOGO[posx1][posy1]=aux;
        selec2 = &erro;
    }
    else{
        selec = 0;
        selec2 = 0;
    }
}
//Desenho de Cada Imagem na posição
void IMG(int num, int posx, int posy, int *pos){

    float ExpX[16]={(float)posx-15,(float)posx-8,(float)posx-7,(float)posx-3,(float)posx-1,(float)posx-1,(float)posx+4,(float)posx,(float)posx+4,(float)posx-2,(float)posx-4,(float)posx-5,(float)posx-7,(float)posx-6,(float)posx-10,(float)posx-10};
    float ExpY[16]={(float)posy-10,(float)posy-2,(float)posy-12,(float)posy-2,(float)posy-9,(float)posy,(float)posy+2,(float)posy+4,(float)posy+12,(float)posy+6,(float)posy+13,(float)posy+7,(float)posy+11,(float)posy+5,(float)posy+8,(float)posy};

    float hexx[7]={(float)posx-9,(float)posx+9,(float)posx+16,(float)posx+9,(float)posx-9,(float)posx-16};
    float hexy[7]={(float)posy-14,(float)posy-14,(float)posy,(float)posy+14,(float)posy+14,(float)posy};

    float xz[4]={(float)posx-14,(float)posx+14,(float)posx};
    float y[4]={(float)posy-14,(float)posy-14,(float)posy+13};

    if(num==0){
        color(1, 1, 0);
        circleFill(posx, posy, 13, 30);
    }
    else if(num==1){
        color(0, 0.5, 1);
        circleFill(posx, posy, 13, 30);
    }
    else if(num==2){
        color(0.7, 0, 1);
        polygonFill(xz, y , 3);
    }
    else if(num==3){
        color(0, 1, 0);
        rectFill(posx-13,posy-13,posx+13,posy+13);
    }
    else if(num==4){
        color(1, 0, 0);
        rectFill(posx-13,posy-13,posx+13,posy+13);
    }
    else if(num==5){
        color(0.75, 1, 0.55);
        polygonFill(hexx, hexy , 6);
    }
    //Posição Nula
    else if(num==6){
        color(0, 0, 0);
        rectFill(posx-13,posy-13,posx+13,posy+13);
    }
    //Imagem de Explosão
    else if(num==7){
        color(1,0,0);
        polygonFill(ExpX, ExpY , 16);
        color(1,1,0);
        polygon(ExpX, ExpY , 16);
    }
    else if(num==8){
        corDaBolacha += 0.02;
        corDaBolacha2 += 0.08;
        corDaBolacha3 += 0.04;

        color((sin(corDaBolacha2)+1)/2, (sin(corDaBolacha3)+1)/2, (sin(corDaBolacha)+1)/2);
        circleFill(posx, posy, 13, 30);
        color(((sin(corDaBolacha)+1)/2),(sin(corDaBolacha2)+1)/2, (sin(corDaBolacha3)+1)/2);
        line(posx+3,posy-11,posx+3,posy+11);
        line(posx-3,posy-11,posx-3,posy+11);
        line(posx+2,posy-10,posx+2,posy+10);
        line(posx-2,posy-10,posx-2,posy+10);
        line(posx,posy-14,posx,posy+14);
        line(posx-11,posy-3,posx+11,posy-3);
        line(posx-11,posy+3,posx+11,posy+3);
        line(posx-10,posy-2,posx+10,posy-2);
        line(posx-10,posy+2,posx+10,posy+2);
        line(posx-14,posy,posx+14,posy);
    }
    else{
        color(1, 1, 1);
        line(posx-13,posy-13,posx+13,posy+13);
        line(posx-13,posy+13,posx+13,posy-13);
    }
    //Piscar em vermelho caso a troca seja inválida
    if(selec == pos && selec2 == &erro){
        color(1, 0, 0);
        rect(posx-21,posy-21,posx+21,posy+21);
        rect(posx-22,posy-22,posx+22,posy+22);
        comando = 1;
    }
    else if(selec==pos){
        color(1, 1, 0);
        rect(posx-21,posy-21,posx+21,posy+21);
        rect(posx-22,posy-22,posx+22,posy+22);
        rect(posx-23,posy-23,posx+23,posy+23);
        rect(posx-24,posy-24,posx+24,posy+24);
    }
    else if(selec == 0){
        color(0, 0, 0);
        rect(posx-24,posy-24,posx+24,posy+24);
    }
}
//Identificar em qual posição do Vetor principal o Mouse clicou
void Marcar(int mx, int my){
    int ii, j, k, l=0, ll, auxy;

    auxy = METADE;
    // Impede a seleção de peças caso o jogo esteja realizando o shiftDown
    if(control==0){
        return;
    }

    for(ii=0;ii<9;ii++){
        ll = 0;
        k = AUX;
        for(j=0;j<9;j++){
            if(mx>INI_JOG+ll && mx<INI_JOG+k && my<TELA_TOP-l && my>TELA_TOP-auxy){
                if(selec!=0){
                    //Identificar se a posição selecionada é válida ou não
                    if(selec == &JOGO[ii][j]){
                        selec = 0;
                        return;
                    }
                    selec2 = &JOGO[ii][j];
                    if(selec2==selec){
                        xaux=-1;
                        yaux=-1;
                        selec=0;
                        selec2=0;
                        return;
                    }
                    if((j==xaux && ii-1 == yaux) || (j==xaux && ii+1 == yaux) || (ii==yaux && j-1 == xaux) || (ii==yaux && j+1 == xaux)){
                        troca(xaux, yaux, ii, j);
                        return;
                    }
                    else{
                        selec = selec2;
                        selec2 = 0;
                        xaux = j;
                        yaux = ii;
                        return;
                    }
                }
                selec = &JOGO[ii][j];
                xaux=j;
                yaux=ii;
                return;
            }
            k += AUX;
            ll += AUX;
        }
        auxy += AUX;
        l += AUX;
    }
}

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis
//globais que podem ser setadas pelo metodo keyboard()

int Iniciar(int x){

    srand (time(NULL));

    int i, j, k, auxy;
    int key=0, key2=1;

    if(comando == 1){
        Sleep(250);
        selec2=0;
        selec=0;
        comando=0;
    }

    //Desenhar Figuras em suas posições
    if(x==2){
        //Desenhar Vetor Principal
        j = 0;
        for(i=0;i<10;i++){
            color(1, 1, 1);
            line(INI_JOG+j, TELA_BAX,INI_JOG+j,TELA_TOP);
            j += AUX;
        }
        j = 0;
        for(i=0;i<10;i++){
            color(1, 1, 1);
            line(INI_JOG, TELA_BAX+j,FIM_JOG,TELA_BAX+j);
            j += AUX;
        }
        auxy = METADE;
        for(i=0;i<9;i++){
            j = METADE;
            for(k=0;k<9;k++){
                IMG(JOGO[i][k],INI_JOG+j,TELA_TOP-auxy,&JOGO[i][k]);
                j += AUX;
                if(JOGO[i][k]==7){
                    if(bolachao[i][k]==7){
                        JOGO[i][k]=8;
                        bolachao[i][k]=-1;
                    }
                    else{
                        JOGO[i][k]=6;
                    }
                }
                else if(JOGO[i][k]==6){
                    key = 1;
                }
            }
            auxy += AUX;
        }
    }
    //Sortear Valores Para a primeira Jogada
    else if(x==1){
        pontuacao = 0;
        auxy = METADE;
        for(i=0;i<9;i++){
            j=METADE;
            for(k=0;k<9;k++){
                JOGO[i][k] = rand()%FIGURAS;
                IMG(JOGO[i][k],INI_JOG+j,TELA_TOP-auxy,&JOGO[i][k]);
                j += AUX;
            }
            auxy += AUX;
        }
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                bolachao[i][j]=-1;
            }
        }
        x=2;
    }
    else{
        text(150,300,"Pressione Enter para Comecar...");
        pontuacao=0;
        selec=0;
        selec2=0;
    }

    //Controle para que a busca de Combinações só seja realizada quando
    //todos os ShiftDown tenham sido Efetuados
    if(key==1){
        Comemoracao(pontos);
        Sleep(125);
        key = ShiftDown();
        control = 0;
    }
    if(key2==1 && key==0){
        Sleep(50);
        key2 = Combinar();
        control = 0;
    }
    // Permite o Jogador voltar a selecionar peças
    if(key2 == 0 && key == 0){
        control = 1;
    }

    color(1, 0, 1);
    MarcaPonto(pontuacao);

    return x;
}
