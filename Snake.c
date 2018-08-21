#include <stdio.h>                          //BIBLIOTECA PARA USAR COMANDOS DE ENTRADA E SAIDA DE DADOS
#include <windows.h>                          //BIBLIOTECA UTILIZADA PARA FUNCOES DO SISTEMA, COMO A DE TROCAR AS CORES DE FUNDO
#include "snakelib.h"                        //BIBLIOTECA CRIADA POR NÓS, ENVIADA NO ARQUIVO.RAR
#define SLEEP 700                          //tempo para atualizacao do mapa
#define MAXVETOR 1000                        //define o tamanho maximo da matriz do mapa
#define PAREDES 177                          //codigo ASCII do caractere das paredes
#define COBRA 219                          //codigo ASCII do caractere da cobra
#define COMIDA1 46                          //codigo ASCII do caractere da comida 1
#define COMIDA2 111                          //codigo ASCII do caractere da comida 2
#define COMIDA3 153                          //codigo ASCII do caractere da comida 3



void movimentacao(int *direcao, int *morte, int cordx[MAXVETOR], int cordy[MAXVETOR], int *tamanho, int *cordxcomida1, int *cordycomida1, int *cordxcomida2, int *cordycomida2, int *cordxcomida3, int *cordycomida3,int largura,int altura,char mapa[][MAXVETOR],int *contComida){                          //Funcao responsavel por toda a parde relacionada a movimentacao e manipulacao das cordenadas dos segmentos da cobra
    int k,i,j;


    for(k=*tamanho;k>0;k--){
        cordx[k] = cordx[k-1];
        cordy[k] = cordy[k-1];
    }
    switch(*direcao){
        case 0:cordx[0]++;break;      //direita
        case 1:cordx[0]--;break;      //esquerda
        case 2:cordy[0]++;break;      //baixo
        case 3:cordy[0]--;break;      //cima
    }
        j=cordx[0];
        i=cordy[0];
        if(mapa[i][j]!='0')      //verifica colisoes
        {
             switch(mapa[i][j])
             {
                 case '5':
                 case '1':*morte=1;Sleep(SLEEP);break;
                 case '2':(*tamanho)++; verificaCoordenadasComida(&cordxcomida1,&cordycomida1,largura,altura,mapa,'2');*contComida=(*contComida)+1;break;
                 case '3':*tamanho=(*tamanho)+2;verificaCoordenadasComida(&cordxcomida2,&cordycomida2,largura,altura,mapa,'3');*contComida=(*contComida)+2;break;
                 case '4':*tamanho=(*tamanho)+3;verificaCoordenadasComida(&cordxcomida3,&cordycomida3,largura,altura,mapa,'4');*contComida=(*contComida)+3;break;

             }

        }


            if(*morte!=1){

                mapa[i][j]='5';

                if(*contComida==0)
                {
                    i=cordy[*tamanho];
                    j=cordx[*tamanho];
                    mapa[i][j]='0';

                }else
                    (*contComida)--;

                gotoxy(0,0);
                printaMapa(mapa, cordx, cordy, altura, largura);

            }
}

void jogo(int *velocidade,char mapa[][MAXVETOR],int altura, DADOS *escore){                          //Funcao articuladora do jogo
    int direcao=0,i=0,j=0,largura=0,l=0;
    int contComida=0;
    int morte=0;
    int tamanho=4;
    int cordx[500],cordy[500];
    int cordxcomida1, cordycomida1, cordxcomida2, cordycomida2, cordxcomida3, cordycomida3;

    system("color 2F");                                             //muda a cor para fundo VERDE e letras BRANCAS
    system("mode 650");                                             //faz a tela ficar no modo fullscreen quando o jogo inicia


    while (mapa[0][i]!='\0')
    {
        largura=i;                                                  //pega a largura do mapa
        i++;
    }
    altura;

    cordx[0]=(largura/2);
    cordx[1]=((largura/2)-1);
    cordx[2]=((largura/2)-2);
    cordx[3]=((largura/2)-3);

    cordy[0]=(altura/2);
    cordy[1]=(altura/2);
    cordy[2]=(altura/2);
    cordy[3]=(altura/2);
    for(i=0;i<4;i++){

        mapa[cordy[i]][cordx[i]]='5';                               //insere na matriz os primeiros quatro segmentos da cobra
    }
    system("cls");
    printaMapa(mapa, cordx, cordy, altura, largura);
    fflush(stdin);
    while(morte==0){                                                //recebe as setas do teclado e ajeita a direçao correspondente enquanto a cobra tiver viva
        if(GetAsyncKeyState(39))
            direcao=0;
        if(GetAsyncKeyState(37))
            direcao=1;
        if(GetAsyncKeyState(40))
            direcao=2;
        if(GetAsyncKeyState(38))
            direcao=3;
        fflush(stdin);
        movimentacao(&direcao, &morte, cordx, cordy, &tamanho, &cordxcomida1, &cordycomida1, &cordxcomida2, &cordycomida2, &cordxcomida3, &cordycomida3,largura,altura,mapa,&contComida);
        Sleep(*velocidade);
        fflush(stdin);
    }

    system("cls");
    system("color 4F");                      //muda a cor para fundo VERMELHO e letras BRANCAS
    poeASCIIArtPerde();
    gotoxy(20, 7);
    escore->pontos=tamanho;
    printf("SEU TAMANHO MAXIMO FOI: %3.f\n\n\n\n", escore->pontos);
    system("pause");
    ranking(escore);
    poeRanking(escore);

}

int main(){                          //Funcao main, que possui o menu inicial do jogo
    char escolha1,mapa[MAXVETOR][MAXVETOR];
    int velocidade, escolha2,escolha3;
    DADOS escore;
    int altura=0, acionador=0;



    srand(time(NULL));                                   //gera as seeds para a posicao das comidas;
    while(escolha1!='s'){
        escolha2=0;
        escolha3=0;
        altura=0;
        system("color 2F");
        system("cls");
        poeASCIIArt();
        fflush(stdin);
        gotoxy(42,25);
        scanf("%c", &escolha1);
        fflush(stdin);
            switch(toupper(escolha1)){
                    case 'I':{
                        system("color 2F");

                        while(escolha3!=1 && escolha3!=2){                                          //switch para escolha do mapa
                            system("cls");
                            poeMenuMapa();
                            gotoxy(30, 9);
                            scanf("%d", &escolha3);
                            fflush(stdin);
                            switch(escolha3){
                                case 1: system("cls");
                                        acionador=1;
                                        leMapa(mapa,&altura, acionador);
                                        break;
                                case 2: system("cls");
                                        acionador=0;
                                        leMapa(mapa,&altura, acionador);
                                        break;

                                default: gotoxy(17, 9);
                                         printf(" DIGITE UM NUMERO VALIDO!");
                                         Sleep(SLEEP);
                            }
                        }
                        retanguloNome();
                        gotoxy(25,3);
                        gets(escore.nome);                                                          //armazena o nome na struct

                        while(escolha2!=1 && escolha2!=2 && escolha2!=3 && escolha2!=4){
                            poeDificuldade();
                            gotoxy(30, 9);
                            scanf("%d", &escolha2);
                            fflush(stdin);
                            switch(escolha2){                                                       //switch para escolha da velociade com que a cobra ira deslizar
                                case 1: velocidade=1000/7; break;
                                case 2: velocidade=1000/15; break;
                                case 3: velocidade=1000/30; break;
                                case 4: velocidade=1000/50; break;
                                default: gotoxy(17, 9);
                                         printf(" DIGITE UM NUMERO VALIDA!");                       //caso o numero digitado nao seja nem 1, 2 ou 3
                                         gotoxy(29, 10);
                                         printf("   ");
                                         Sleep(SLEEP);
                            }
                            fflush(stdin);
                        }

                            system("cls");
                            jogo(&velocidade, mapa, altura, &escore);
                            break;
                    }

                    case 'R': regras();break;
                    case 'S': system("cls");
                              break;
                    default:
                        gotoxy(25, 25);
                        printf(" DIGITE UMA LETRA VALIDA!");
                        gotoxy(41, 26);
                        printf("   ");
                        Sleep(SLEEP);
            }
    }
    return 0;
}
