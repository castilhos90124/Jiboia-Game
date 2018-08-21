#include <stdio.h>
#include <windows.h>
#define MAXVETOR 1000                        //define o tamanho maximo da matriz do mapa
#define PAREDES 177                          //codigo ASCII do caractere das paredes
#define COBRA 219                          //codigo ASCII do caractere da cobra
#define COMIDA1 46                          //codigo ASCII do caractere da comida 1
#define COMIDA2 111                          //codigo ASCII do caractere da comida 2
#define COMIDA3 153                          //codigo ASCII do caractere da comida 3


typedef struct{                                                                     //Estrutura para armazenar as informacoes do jogador e sua pontuacao
float pontos;
char nome[10];

}   DADOS;

void gotoxy(int x, int y){                          //Funcao que muda a posicao do cursor dentro do terminal
    COORD coordenada;  //variavel para armazenar do tipo coordenada
    coordenada.X = x;
    coordenada.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordenada);  // pega a posição atual do cursor, e troca pela prosição da coordenada;
}


//FUNCOES MAPA

void conversorMapa(char mapa[][MAXVETOR],int i,int z){                              //Converte os caracteres do mapa nos respectivos caracteres das comidas, da cobra e das paredes
     switch(mapa[i][z]){
                    case '0':printf(" ");break;
                    case '1':printf("%c",PAREDES);break;
                    case '2':printf("%c",COMIDA1);break;
                    case '3':printf("%c",COMIDA2);break;
                    case '4':printf("%c",COMIDA3);break;
                    case '5':printf("%c",COBRA);break;
                }
}

void printaMatriz (char mapa [][MAXVETOR],int contLinhas){                          //Funcao usada para debuggar o jogo, NAO é chamada por padrao!
    int i=0, z=0;

    for(i=0;i<contLinhas;i++)
    {
        while(mapa[i][z]!='\0')
        {
            printf("%c", mapa[i][z]);
            z++;
        }
        z=0;
    }
}

void printaMapa(char mapa[][MAXVETOR], int cordx[MAXVETOR], int cordy[MAXVETOR],int altura,int largura){                          //Funcao que define os limites da matriz mapa que sera printada
int i,z;
int lateraisxmin, lateraisxmax, lateraisymin, lateraisymax;


    if (altura>28 || largura>120){
    i=cordy[0]-14;
    z=cordx[0]-70;

        if(i<0 || i>(altura-28) || z<0 || z>(largura-140)){
            lateraisymin=cordy[0]-14;
            lateraisymax=cordy[0]+14;
            lateraisxmin=cordx[0]-70;
            lateraisxmax=cordx[0]+70;

            if(i<0){
                lateraisymin=0;
                lateraisymax=28;
            }
            if(z<0){
                lateraisxmin=0;
                lateraisxmax=140;
            }
            if(i>(altura-28)){
                lateraisymin=altura-28;
                lateraisymax=altura;
            }
            if(z>(largura-140)){
                lateraisxmin=largura-140;
                lateraisxmax=largura;
            }


            for(i=lateraisymin;i<lateraisymax;i++){

                for(z=lateraisxmin;z<lateraisxmax;z++)
                    conversorMapa(mapa,i,z);

                printf("\n");
            }
        }else{
            for(i=cordy[0]-14;i<cordy[0]+14;i++){
                for(z=cordx[0]-70;z<cordx[0]+70;z++)
                    conversorMapa(mapa,i,z);

                    printf("\n");
            }
        }

    }else{
        for(i=0;i<altura+1;i++){
            for(z=0;z<largura+1;z++)
                conversorMapa(mapa,i,z);
        printf("\n");
        }
    }
}

void poeMenuMapa2(){                          //ASCIIART MENU
    system("cls");
    printf("|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|\n");
    printf("-                    DIGITE O NOME DO ARQUIVO:                    -\n");
    printf("|                                                                 |\n");
    printf("-                                                                 -\n");
    printf("|                                                                 |\n");
    printf("-                                                                 -\n");
    printf("|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|\n\n\n");
}

void leMapa(char mapa[][MAXVETOR],int *contLinhas, int acionador){                          //Funcao que faz a primeira abertura do mapa, armazena-o em uma matriz, e captura o numero de linhas
char nome[30]="mapapadrao";
FILE *arq;
int i=0, z=0;

    if(acionador==1){                               //para só pedir que a pessoa digite o nome do mapa, se ela selecionou a opao de mapa personalizado
        poeMenuMapa2();
        gotoxy(25,3);
        fflush(stdin);
        gets(nome);
    }
    strcat(nome,".txt");
    arq = fopen(nome, "r");

    if(arq == NULL)
        printf("Erro de Abertura\n");
    else{
        while(fgets(mapa[*contLinhas],MAXVETOR, arq)!=NULL) //le e armazena o mapa na matriz
            (*contLinhas)++;

        fclose(arq);

    }

}

void poeMenuMapa(){                          //LAYOUT MENU PARA ESCOLHER MAPA
    system("cls");
    printf("|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|\n");
    printf("-                    ESCOLHA O MAPA DESEJADO:                     -\n");
    printf("|           1 - LEITURA DE MAPA EM ARQUIVO TXT                    |\n");
    printf("-                                                                 -\n");
    printf("|           2 - MAPA PADRAO                                       |\n");
    printf("-                                                                 -\n");
    printf("|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|\n\n\n");
    printf("                      ESCOLHA:   \n");
    printf("                             ---");
}


//MENUS E ASCIIASTRS

void poeASCIIArt(){                           //ASCIIART MENU PRINCIPAL







char linha2n[71+1]={"|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|"};
char linha1n[71+1]={"-                                                                     -"};
char linha0[71+1]={"|  -----------------------------------------------------------------  |"};
char linha1[71+1]={"- |      _ _ _           _                                          | -"};
char linha2[71+1]={"| |     (_|_) |__   ___ (_) __ _    __ _  __ _ _ __ ___   ___       | |"};
char linha3[71+1]={"- |     | | | '_ \ /  _  \| |/ _` |  / _` |/ _` | '_ ` _ \  / _ \       | -"};
char linha4[71+1]={"| |     | | | |_) | (_) | | (_| | | (_| | (_| | | | | | |  __/      | |"};
char linha5[71+1]={"- |    _/ |_|_.__/  ___/|_| \__,_|   \__,  |\__,_|_| |_| |_|\___|       | -"};
char linha6[71+1]={"| |   |__/                         |___/                            | |"};
char linha7[71+1]={"-  -----------------------------------------------------------------  -"};
    puts(linha2n);
    puts(linha1n);
    puts(linha0);
    puts(linha1);
    puts(linha2);
    puts(linha3);
    puts(linha4);
    puts(linha5);
    puts(linha6);
    puts(linha7);
    printf("|                                                            _V_      |\n");
    printf("-                                                           |___|     -\n");
    printf("|   _Y_                                                               |\n");
    printf("-  |   |           #########################################          -\n");
    printf("| |() ()|          #               MENU :                  #          |\n");
    printf("- |-___-|          #                                       #          -\n");
    printf("|   |§|            #                                       #          |\n");
    printf("-   |§|            #  'I' - PARA INICIAR O JOGO;           #          -\n");
    printf("|   |§|            #  'R' - PARA VER AS REGRAS;            #          |\n");
    printf("-   |§|            #  'S' - PARA SAIR                      #          -\n");
    printf("|   |§|           _#                                       #______    |\n");
    printf("-   |§|__________/§#                                       #§§§§§§>   -\n");
    printf("|   |§§§§§§§§§§§§§/#########################################          |\n");
    printf("-                                                                     -\n");
    printf("|                                                                     |\n");
    printf("-                                ESCOLHA:                             -\n");
    printf("|                                        ---                          |\n");
    printf("-                                                                     -\n");
    printf("|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|\n");
}

void poeDificuldade(){                          //LAYOUT PARA ESCOLHER DIFICULDADE DO JOGO







    system("cls");
    printf("|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|\n");
    printf("-                    ESCOLHA A DIFICULDADE!                       -\n");
    printf("|           1 - FRALDINHA                                         |\n");
    printf("-           2 - INICIANTE                                         -\n");
    printf("|           3 - INTERMEDIARIO                                     |\n");
    printf("-           4 - AVANCADO                                          -\n");
    printf("|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|\n\n\n");
    printf("                 DIFICULDADE:   \n");
    printf("                             ---");
}

void regras(){                          //LAYOUT COM PAINEL DE REGRAS DO JOGO

    system("cls");
        char linha1[71+1]={"|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|"};
        char linha2[71+1]={"-               _____ _____ _____ _____ _____ _____   _               -"};
        char linha3[71+1]={"|              | __  |   __|   __| __  |  _  |   __| |_|              |"};
        char linha4[71+1]={"-              |    -|   __|  |  |    -|     |__   |  _               -"};
        char linha5[71+1]={"|              |__|__|_____|_____|__|__|__|__|_____| |_|              |"};
        char linha6[71+1]={"-                                                                     -"};
        char linha7[71+1]={"|     1-A COBRA PODE SER MOVIMENTADA PELAS SETAS DO SEU TECLADO.      |"};
        char linha8[71+1]={"-                                                                     -"};
        char linha9[71+1]={"|     2-EXISTEM TRES TIPOS DE COMIDA NO JOGO E CADA UMA EH            |"};
        char linha10[71+1]={"-      REPRESENTADA POR UM SIMBOLO DIFERENTE E FAZ A COBRA CRESCER    -"};
        char linha11[71+1]={"|      UM QUANTIDADE DE SEGMENTOS.                                    |"};
        char linha12[71+1]={"-                                                                     -"};
        char linha13[71+1]={"|      TIPO            SIMBOLO              EFEITO                    |"};
        char linha14[71+1]={"-   COMIDA 1              .                 CRESCE 1 SEGMENTO         -"};
        char linha15[71+1]={"|   COMIDA 2              o                 CRESCE 2 SEGMENTOS        |"};
        //ESSA STRING FOI SUSBTITUIDA POR UM PRINTF POIS NAO HAVIA COMO PRINTAR O CARACTERE DA COMIDA 3 POR UMA STRING
        char linha17[71+1]={"|                                                                     |"};
        char linha18[71+1]={"-                                                                     -"};
        char linha19[71+1]={"|   3 - SE VOCE ESTIVER ANDANDO EM UM SENTIDO E IR DIRETAMENTE PARA   |"};
        char linha20[71+1]={"-       O OPOSTO, ACONTECERA A AUTOFAGOCITOSE DA COBRA.               -"};
        char linha21[71+1]={"|                                                                     |"};
        char linha22[71+1]={"-   DICA: VOCE PODE CRIAR MAPAS EM ARQUIVOS .TXT E USA-LOS NO JOGO.   -"};
        char linha23[71+1]={"|      CARACTERE                          SIGNIFICADO                 |"};
        char linha24[71+1]={"-                                                                     -"};
        char linha25[71+1]={"|         0                               ESPACO VAZIO                |"};
        char linha26[71+1]={"-         1                               PAREDE                      -"};
        char linha27[71+1]={"|         2                               COMIDA DO TIPO 1            |"};
        char linha28[71+1]={"-         3                               COMIDA DO TIPO 2            -"};
        char linha29[71+1]={"|         4                               COMIDA DO TIPO 3            |"};
        char linha30[71+1]={"-                                                                     -"};
        char linha31[71+1]={"|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|"};


        puts(linha1);
        puts(linha2);
        puts(linha3);
        puts(linha4);
        puts(linha5);
        puts(linha6);
        puts(linha7);
        puts(linha8);
        puts(linha9);
        puts(linha10);
        puts(linha11);
        puts(linha12);
        puts(linha13);
        puts(linha14);
        puts(linha15);
        printf("-   COMIDA 3              %c                 CRESCE 3 SEGMENTOS        -\n", COMIDA3);
        puts(linha17);
        puts(linha18);
        puts(linha19);
        puts(linha20);
        puts(linha21);
        puts(linha22);
        puts(linha23);
        puts(linha24);
        puts(linha25);
        puts(linha26);
        puts(linha27);
        puts(linha28);
        puts(linha29);
        puts(linha30);
        puts(linha31);

        printf("\n\n");
        system("pause");
    system("cls");
}

void poeASCIIArtPerde(){                          //ASCIIART PERDEU






    char linha1[]={""};
    char linha2[]={"-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-"};
    char linha3[]={"|     _ _  ___  ___  ___   ___   ___  ___  ___  ___  _ _   _          |"};
    char linha4[]={"-    | | || . ||  _>| __> | . ` | __>| . `| . `| __>| | | | |         -"};
    char linha5[]={"|    | ' || | || <__| _>  |  _/ | _> |   /| | || _> | ' | |_|         |"};
    char linha6[]={"-    |__/ `___'`___/|___> |_|   |___>|_|_||___/|___>`___'  _          -"};
    char linha7[]={"|                                                         |_|         |"};
    char linha8[]={"-                                                                     -"};
    char linha9[]={"|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|"};
    puts(linha1);
    puts(linha2);
    puts(linha3);
    puts(linha4);
    puts(linha5);
    puts(linha6);
    puts(linha7);
    puts(linha8);
    puts(linha9);
}


//RANKING

void retanguloNome(){                         //LAYOUT RETANGULO PARA POR NOME
system("cls");
    printf("|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|\n");
    printf("-       DIGITE UM NOME PARA SUA COBRA (ATE 9 CARACTERES)          -\n");
    printf("|                                                                 |\n");
    printf("-                                                                 -\n");
    printf("|                                                                 |\n");
    printf("-                                                                 -\n");
    printf("|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|\n\n\n");

}

void poeRanking(){                          //LAYOUS RANKING FINAL
FILE *ranking;
DADOS lido;
int colocacao=0;
int branco, i;

    system("cls");
    gotoxy(0,0);
    printf("|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|\n");
    printf("-              _____ _____ _____ _____ _____ _____ _____          -\n");
    printf("|             | __  |  _  |   | |  |  |     |   | |   __|         |\n");
    printf("-             |    -|     | | | |    -|-   -| | | |  |  |         -\n");
    printf("|             |__|__|__|__|_|___|__|__|_____|_|___|_____|         |\n");
    printf("-                                                                 -\n");
    printf("|                                                                 |\n");
    printf("-                                                                 -\n");
    printf("|                                                                 |\n");
    printf("-                                                                 -\n");
    printf("|                                                                 |\n");
    printf("-                                                                 -\n");
    printf("|                                                                 |\n");
    printf("-                                                                 -\n");
    printf("|                                                                 |\n");
    printf("-                                                                 -\n");
    printf("|                                                                 |\n");
    printf("-                                                                 -\n");
    printf("|                                                                 |\n");
    printf("-                                                                 -\n");
    printf("|                                                                 |\n");
    printf("-                                                                 -\n");
    printf("|                                                                 |\n");
    printf("-                                                                 -\n");
    printf("|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|\n\n\n");

        if (!(ranking = fopen("Ranking.bin", "rb")))
            printf("Erro ao abrir arquivo saida \n");
        else{
            gotoxy(17,5);
            printf("JOGADOR -------------------- PONTOS\n");
            while (!feof(ranking))
                if (fread(&lido, 1, sizeof(DADOS), ranking) != NULL )
                {
                    branco=10-strlen(lido.nome);
                    for(i=0;i<branco;i++)
                        strcat(lido.nome, " ");
                    if(colocacao<10){
                        gotoxy(11, colocacao+6);
                        colocacao++;
                        if(colocacao<10)
                            printf( "%d  -  %s                 %6.f\n",colocacao, lido.nome, lido.pontos);
                        else
                            printf( "%d  -  %s                 %5.f\n",colocacao, lido.nome, lido.pontos);
                    }
                }
            fclose (ranking);
        }
    gotoxy(0, 26);
    system("pause");


}

void ranking(DADOS *escore){                           //baseado no algoritmo de ordenaçao postado pelo professor no moodle
FILE *ranking;
int inseriu=0;
DADOS lido;



    if ((ranking = fopen("Ranking.bin", "rb")) != NULL) //testa se o arquivo existe
            fclose(ranking);                                 // se existe fecha
        else
            fclose ( fopen("Ranking.bin", "wb") );                                      // se nao existe cria vazio

        fflush(stdin);
        if(!(ranking=fopen("Ranking.bin", "r+b")))
            printf("ERRO NA ABERTURA DO ARQUIVO RANKING!");
        else{

            fseek( ranking, 0*sizeof(DADOS), SEEK_END );
            while (!feof(ranking) && !inseriu ){

                fseek( ranking, -1*sizeof(DADOS), SEEK_CUR );
                if (fread(&lido, 1, sizeof(DADOS), ranking) != NULL ){                   // leu pontos

                    if(escore->pontos < lido.pontos){                                   //grava aqui


                        fseek( ranking, 0*sizeof(DADOS), SEEK_CUR );
                        fwrite( escore, 1, sizeof(DADOS), ranking );
                        inseriu = 1;
                    }else{                                                                // caso geral de copiar para baixo


                        fseek( ranking, 0*sizeof(DADOS), SEEK_CUR );
                        fwrite( &lido, 1, sizeof(DADOS), ranking );
                        fseek( ranking, -2*sizeof(DADOS), SEEK_CUR );

                        if( ftell(ranking) == 0 ){                                       // se esta inserindo no inicio


                            fwrite( escore, 1, sizeof(DADOS), ranking );
                            inseriu = 1;
                        }
                    }
                }
                else if( !inseriu ){                                                     // se esta vazio

                    fseek( ranking, -1*sizeof(DADOS), SEEK_CUR );
                    fwrite( escore, 1, sizeof(DADOS), ranking );
                    inseriu = 1;
                }
            }
        }
        fclose(ranking);
}


//JOGO


void verificaCoordenadasComida(int *cordxcomida, int *cordycomida, int largura,int altura,char mapa[][MAXVETOR],char num_comida){                          //Funcao para evitar que comidas nasçam dentro da propria cobra ou dentro da parede.
    int i,j,ok,comida;
    do{
        ok=0;
        *cordxcomida=(rand()%(largura-2))+1;
        *cordycomida=(rand()%(altura-2))+1;
        j=*cordxcomida;
        i=*cordycomida;
        if(mapa[i][j]=='0')
        {
             ok=1;
             mapa[i][j]=num_comida;
        }
    }
    while(ok==0);
    switch(num_comida){
        case '2':comida=COMIDA1;break;
        case '3':comida=COMIDA2;break;
        case '4':comida=COMIDA3;break;
    }
}
