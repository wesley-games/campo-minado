/*Elaborado por Wesley Allan Rocha e João Paulo Herrera - abril de 2011
Ultima atualização do projeto: 06/09/11
Hora: 15:27
Por: HR Software*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define ALTMAX 20
#define LARMAX 20

//declarei essa matriz fora das funcoes pra ela ser vista pelas outras 
int campodatela[ALTMAX][LARMAX], campodebombas[ALTMAX][LARMAX];
int a, l, bombs;

imprimenatela() //essa funcao imprime o a matriz de pontos na tela 
{
      int i, j;
      printf("  ");           
      for( j=0; j<l; j++ )
           printf("%3d", j);
      printf("\n");     
      for( i=0; i<a; i++ ){
           printf("%d ", i);
           for( j=0; j<l; j++ ){
                if( i < 10 && j == 0 )
                     printf(" %2c ", campodatela[i][j]);
                else
                     printf("%2c ", campodatela[i][j]);
           }
           printf(" %d", i);  
           switch (i){
                  case 0:
                       printf("    **MENU**");
                       break;
                  case 1:
                       printf("    EXIT (x)");
                       break;     
           }   
           printf("\n");
      }         
}

montacampo() //essa funcao gera e impime o campo pontilhado que e visivel
{            
      int i, j;
      for( i=0; i<a; i++ )
           for( j=0; j<l; j++ ){
                campodebombas[i][j]=0;
                campodatela[i][j]='.';
      }
      imprimenatela();
}

colocabombas( int *pganhou, int *pcontador )
{
      srand(time(NULL)); //Funcao que gera um numero aleatorio em funcao do tempo.
        
      int i=0, altura, largura;        
      while( i < bombs ){
           altura = rand()%a;                     
           largura = rand()%l;
           while(campodebombas[altura][largura] == 1){
                altura = rand()%a;
                largura = rand()%l;
           }
           campodebombas[altura][largura]=1;
           i++;                                              
      }
      *pganhou = bombs;
}                                                                                                                 
                                                             
bombasaoredor(int x,int y)//essa funcao verifica se tem bombas ao redor da coordenada digitada
{
      int numbombas = 0, i, j, ac, bc;
      for(i=-1;i<=1;i++)                               // [A-1][L-1]   [A-1][L]   [A-1][L+1]
           for(j=-1;j<=1;j++){                         //  [A][L-1]     [A][L]     [A][L+1]
                ac = x + i;                            // [A+1][L-1]   [A+1][L]   [A+1][L+1]
                bc = y + j;                  
                if( ac>=0 && bc>=0 && ac<a && bc<l )
                     if(campodebombas[ac][bc]==1) 
                          numbombas += 1;
           }                 
      campodatela[x][y] = 48 + numbombas;
      if( numbombas == 0 )
           abrecasas(x,y);
}

abrecasas(int x,int y)
{
      int i, j, ac, bc;
      for(i=-1;i<=1;i++)
           for(j=-1;j<=1;j++){
                ac = x + i; 
                bc = y + j;
                if( ac>=0 && bc>=0 && ac<a && bc<l )
                     if(campodatela[ac][bc]=='.')
                          bombasaoredor(ac,bc);
           }
}

definebombas()                 //funcao que assume para as bombas o caractere 'x'.
{
      int i,j;
      for(i=0;i<a;i++){
           for(j=0;j<l;j++){
                if(campodebombas[i][j]==1)
                     campodatela[i][j] = 120;
           }
      }
} 

limpabombas()                //funcao que limpa as bombas da matriz.
{
      int x=0,y=0;
      for(x=0;x<a;x++){
           for(y=0;y<l;y++){
                if(campodebombas[x][y]==1)
                     campodebombas[x][y]=0;
           }
      }
}

recebeletra( int *px, int *py )//funcao que recebe uma string e organiza as coordenadas
{
      char palavra[10], num1[3], num2[3];
      int digito, coord1, coord2, deucerto=0;
      char mostratudo[10] = {"showmeall"};
      
      do{
           coord1 = -1; coord2 = -1;
           printf("Digite a coordenada na forma ( x,y )  x = linha, y = coluna\n");
           scanf("%s", palavra);
           digito = strlen(palavra);
           switch( digito ){
                case 1:
                     if( palavra[0] == 'x' )
                          exit(1);   
                     break;
                case 3:
                     if( palavra[1] == ',' )
                          if( palavra[0] >= '0' && palavra[0] <= '9')
                               if( palavra[2] >= '0' && palavra[2] <= '9'){
                                    num1[0] = palavra[0];
                                    num2[0] = palavra[2];
                                    coord1 = atoi( num1 );
                                    coord2 = atoi( num2 );
                               }
                     break;
                case 4:
                     if( palavra[1] == ',' ){
                          if( palavra[0] >= '0' && palavra[0] <= '9')
                               if( palavra[2] >= '0' && palavra[2] <= '9')
                                    if( palavra[3] >= '0' && palavra[3] <= '9'){
                                         num1[0] = palavra[0];
                                         num2[0] = palavra[2];
                                         num2[1] = palavra[3];
                                         coord1 = atoi( num1 );
                                         coord2 = atoi( num2 );
                               }
                     }else{
                          if( palavra[2] == ',' ){
                               if( palavra[0] >= '0' && palavra[0] <= '9')
                                    if( palavra[1] >= '0' && palavra[1] <= '9')
                                         if( palavra[3] >= '0' && palavra[3] <= '9'){
                                              num1[0] = palavra[0];
                                              num1[1] = palavra[1];
                                              num2[0] = palavra[3];
                                              coord1 = atoi( num1 );
                                              coord2 = atoi( num2 );
                                         }
                          }
                     }
                     break;
                case 5:
                     if( palavra[2] == ',' )
                          if( palavra[0] >= '0' && palavra[0] <= '9')
                               if( palavra[1] >= '0' && palavra[1] <= '9')
                                    if( palavra[3] >= '0' && palavra[3] <= '9')
                                         if( palavra[4] >= '0' && palavra[4] <= '9'){
                                              num1[0] = palavra[0];
                                              num1[1] = palavra[1];
                                              num2[0] = palavra[3];
                                              num2[1] = palavra[4];
                                              coord1 = atoi( num1 );
                                              coord2 = atoi( num2 );
                               }
                     break;
                case 9:
                     if ( strcmp( palavra, mostratudo) == 0){
                          system("cls");
                          definebombas();
                          imprimenatela();
                     }
                     break;
           }
           if ( coord1 != -1 && coord2 != -1 ){
                if ( coord1>=0 && coord2>=0 && coord1<a && coord2<l ){
                     if (campodatela[coord1][coord2]=='.' || campodatela[coord1][coord2]=='x'){
                          deucerto = 1;
                          *px = coord1; 
                          *py = coord2;
                     }else{
                          system("cls");
                          imprimenatela(); 
                          printf("Esta coordenada ja foi digitada, digite outra\n");
                     }
                }else{
                     system("cls");
                     imprimenatela();  
                     printf("Esta coordenada nao pertence a matriz, digite outra\n");
                }
           }else{
                system("cls");
                imprimenatela();  
                printf("a coordenada digitada nao esta correta, digite outra\n");
           }
      }while( deucerto != 1 );        
}

venceu()
{
      printf("\n\n\n");
      printf("     0   0  000   0000 00000    0   0 00000 0   0  0000 00000 0   0    0\n");
      printf("     0   0 0   0 0     0        0   0 0     00  0 0     0     0   0    0\n");
      printf("     0   0 0   0 0     00000    0   0 00000 0 0 0 0     00000 0   0    0\n");
      printf("      0 0  0   0 0     0         0 0  0     0  00 0     0     0   0     \n");
      printf("       0    000   0000 00000      0   00000 0   0  0000 00000  000     0\n");
      printf("\n\n\n");
}

perdido()
{
      printf("\n\n\n");
      printf("     0   0  000   0000 00000    0000  00000 0000  0000  00000 0   0    0\n");
      printf("     0   0 0   0 0     0        0   0 0     0   0 0   0 0     0   0    0\n");
      printf("     0   0 0   0 0     00000    0000  00000 0000  0   0 00000 0   0    0\n");
      printf("      0 0  0   0 0     0        0     0     0  0  0   0 0     0   0     \n");
      printf("       0    000   0000 00000    0     00000 0   0 0000  00000  000     0\n");
      printf("\n\n\n");
}
seraqueganhou()
{
      int i, j, cont = 0;
      for( i=0; i<a; i++ )
           for( j=0; j<l; j++ )
                if( campodatela[i][j] == '.' || campodatela[i][j] == 'x' )
                     cont = cont + 1;
      return cont;               
}         

tamanhodojogo()
{
      char ch;
      int maxbombs;
      printf("\nEscolha uma opcao de jogo abaixo para iniciar :\n");
      printf("[f]Facil  [m]Medio  [d]Dificil  [p]Personalizado\n");
      ch = getche();
      switch(ch){
           case 'x':
                exit(1);
                break;      
           case 'f':
                a = 10; l = 10; bombs = 10; system("cls");
                break;
           case 'm':
                a = 15; l = 15; bombs = 40; system("cls");
                break;
           case 'd':
                a = 20; l = 20; bombs = 100;system("cls");
                break;
           case 'p':
                printf("\nEscolha quantas linhas tera o campo minado ( MIN = 2 e MAX = 20 ) : ");
                scanf("%d", &a);
                while( a <= 1 || a > 20 ){
                     printf("\nEscolha quantidade de linhas no intervalo ( MIN = 2 e MAX = 20 ) : ");
                     scanf("%d", &a);
                }
                printf("Escolha quantas colunas tera o campo minado ( MIN = 2 e MAX = 20 ) : ");
                scanf("%d", &l);
                while( l <= 1 || l > 20 ){
                     printf("\nEscolha quantidade de colunas no intervalo ( MIN = 2 e MAX = 20 ) : ");
                     scanf("%d", &l);
                }
                printf("Escolha quantas bombas tera o campo minado ( MAX = %d ) : ", (a*l)-1);
                scanf("%d", &bombs);
                while( bombs > ( maxbombs = (a*l)-1 )){
                     printf("Seu campo tera %d casas, escolha menos bombas : ", a*l);
                     scanf("%d", &bombs);
                }
                system("cls");
                break;
           default:
                printf("\nDigite apenas opcoes validas, tente novamente:\n");
                tamanhodojogo();   
                break; 
      }                            
      
}         

main()
{
      int i, j, x, y, numbombas;
      int perdeu=0, ganhou, contador = 0;
      char decisao;
      
      printf("     ***** Bem-Vindo ao jogo Campo Minado *****\n");
      
      tamanhodojogo();
      
      montacampo();
      colocabombas( &ganhou, &contador );
      
      do{
           if( contador == ganhou ){
                printf("voce ganhou\n");
                goto fim;
           }
           
           recebeletra( &x, &y );
           if(campodebombas[x][y]==1){//se voce acertou um bomba...
                system("cls");
                definebombas(x,y);
                imprimenatela(x,y);
                perdido();
                
                printf("Jogar Novamente? [S/N]\n");
                scanf("%s",&decisao);
     
                while(decisao != 's' && decisao != 'n' && decisao != 'S' && decisao != 'N'){
                     printf("Caractere invalido, insira apenas 's' ou 'n'.\n");
                     scanf("%s",&decisao);
                }        
                if(decisao == 's' || decisao == 'S'){
                     system("cls");
                     limpabombas();tamanhodojogo();
                     montacampo();
                     colocabombas( &ganhou, &contador );
                     system("cls");
                     imprimenatela();
                }
                if(decisao== 'n' || decisao== 'N')
                     perdeu++;//uma gambiarra que eu usei (preguica de pensar)
                     
           }else{//...se voce nao acertou uma bomba...
                contador = seraqueganhou();
                if ( contador == (ganhou + 1) ){//... e ganhou o jogo!
                     fim:
                     system("cls");
                     bombasaoredor(x,y);
                     definebombas(x,y);
                     imprimenatela();
                     venceu();
                     //seria uma funcao que ve se voce quer continuar jogando...
                          printf("Jogar Novamente? [S/N]\n");
                          scanf("%s",&decisao);

                          while(decisao != 's' && decisao != 'n' && decisao != 'S' && decisao != 'N'){
                               printf("Caractere invalido, insira apenas 's' ou 'n'.\n");
                               scanf("%s",&decisao);
                          }        
                          if(decisao == 's' || decisao == 'S'){
                               system("cls");
                               limpabombas();tamanhodojogo();
                               montacampo();
                               colocabombas( &ganhou, &contador );
                               system("cls");
                               imprimenatela();
                          }
                          if(decisao== 'n' || decisao== 'N')
                          perdeu++;      //... e vai ate aqui
                     
                }else{//... e ainda nao ganhou o jogo
                     system("cls");
                     bombasaoredor(x,y);
                     imprimenatela();
                }
         }
      
      contador = seraqueganhou();
      
      }while(perdeu==0);
      printf("Pressione qualquer tecla para finalizar o programa.\n");
      getch();
}
