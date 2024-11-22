#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <ctype.h>
#include <unistd.h> //sirve para el time()
#include <conio.h>

#include "movimientos.h" //función donde está todo


void dimen(const char* nombreMapa, int* f, int* c){   // Funcion que recibe el nombre del mapa, y punteros hacia fila y col 
  *f = 0;
  *c = 0;
  int temp1;
  char e;
  FILE *file = fopen(nombreMapa, "r");                  // Creamos las variables necesarias y abrimos el archivo
  if (file == NULL) {
    printf("Error al abrir el archivo: %s\n", nombreMapa);
    return;
  }
  while ((e = fgetc(file)) != EOF) {                      // Contamos por cada salto de linea encontrado, para determinar la cantidad de filas 
    if (e == '\n') {
      (*f)++;  
        }
  }
  rewind(file);                                        //Devolvemos el puntero del archivo al inicio
  
  while (1) {
    e = fgetc(file);
    if(isdigit(e)){// Iniciamos un ciclo hasta que la lectura no sea exitosa 
      (*c)++;}
    else if (e =='\n' || e == EOF) {                      // Sumamos uno al contador por cada elemento encontrado hasta el salto de linea, para obtener las columnas
      return;  
    }
  }
  rewind(file);                                      //Cerramos todo
  fclose(file);
}

void cargarMapa(const char * nombreMapa, int ** A, int f, int c){         //Funcion que recibe el nombre del mapa, una matriz, filas y columnas 
  FILE *file = fopen(nombreMapa, "r");
  if (file == NULL) {
    printf("Error al abrir el archivo del mapa: %s\n", nombreMapa);
    return;
  }
  for (int i = 0; i < f; i++) {                                        // Abrimos el archivo y  rellenamos la matriz mediante un ciclo
    for (int j = 0; j < c; j++) {
      fscanf(file, "%d", &A[i][j]);
    }
  }
  fclose(file);
}


//Se definen las estructuras con otro nombre
typedef struct posicion posicion_t;
typedef struct fantasmas fantasmas_t;


void imprimir(int L, int A, int **tablero){
    printf("\n\n\n\n");
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < A; j++)
        {
            printf("%d  ",tablero[i][j]);
        }
        printf("\n");
        
    }
    printf("\n\n");
}


int main() {
    srand(time(0));
    posicion_t Pm;
    fantasmas_t Fant_all;

    Fant_all.Ft1.extra=0;
    Fant_all.Ft2.extra=0;
    Fant_all.Ft3.extra=0;
    Fant_all.Ft4.extra=0;
    Pm.extra=0;

    char mov,fm1=0,fm2=0,fm3=0,fm4=0;
    int GameOver=0;
    int difficult=1;
    
    int alto = 0;
    int ancho = 0;
    dimen("mapa2.txt", &alto, &ancho);
    int **tablero = malloc(alto * sizeof(int*));      
    for (int i = 0; i <alto; i++) {
    tablero[i] = malloc(ancho * sizeof(int));
    }
    cargarMapa("mapa2.txt", tablero , alto , ancho);  
         
   

    //parte de reconocer donde estan los entes (Pacman y fantasmas)
    ingresar_posiciones(&Pm, alto, ancho, tablero, 2);
    ingresar_posiciones(&(Fant_all.Ft1), alto, ancho, tablero, 3);
    ingresar_posiciones(&(Fant_all.Ft2), alto, ancho, tablero, 4);
    ingresar_posiciones(&(Fant_all.Ft3), alto, ancho, tablero, 5);
    ingresar_posiciones(&(Fant_all.Ft4), alto, ancho, tablero, 6);


    //Menu
//se ve despues

    // juego 
        //while(1){ cuando vaya al menu
            //todo el render y el mov
            char mov1 = 0;
            while (!GameOver && !fm1 && !fm2 && !fm3 && !fm4 ) {
                
                imprimir(alto,ancho,tablero);
                printf("\nPacman se mueve a: (%d, %d)\n", Pm.x,Pm.y);
                printf("\nft1 se mueve a: (%d, %d)", Fant_all.Ft1.x,Fant_all.Ft1.y);
                printf("\nft2 se mueve a: (%d, %d)", Fant_all.Ft2.x,Fant_all.Ft2.y);
                printf("\nft3 se mueve a: (%d, %d)", Fant_all.Ft3.x,Fant_all.Ft3.y);
                printf("\nft4 se mueve a: (%d, %d)", Fant_all.Ft4.x,Fant_all.Ft4.y);
              if (kbhit()) {
                mov1 = getch();
              }
                GameOver=!mov_Pacman(alto,ancho,tablero,mov1,&Pm,&Fant_all);
                /*
                switch (mov) {
                    case 'w':
                        GameOver = !mov_Pacman(alto, ancho, tablero, 'w', &Pm, &Fant_all);
                        //render
                        //cambio a arriba el pacman
                        break;
                    case 's':
                        GameOver = !mov_Pacman(alto, ancho, tablero, 's', &Pm, &Fant_all);
                        //render
                        //cambio a abajo el pacman
                        break;
                    case 'a':
                        GameOver = !mov_Pacman(alto, ancho, tablero, 'a', &Pm, &Fant_all);
                        //render
                        //cambio a izq el pacman
                        break;
                    case 'd':
                        GameOver = !mov_Pacman(alto, ancho, tablero, 'd', &Pm, &Fant_all);
                        //render
                        //cambio a derecha el pacman
                        break;

                    default:
                        break;
                }
                */
                fm1 = !mov_Fanta(alto,ancho,tablero,&(Fant_all.Ft1),&Pm, 3);
                fm2 = !mov_Fanta(alto,ancho,tablero,&(Fant_all.Ft2),&Pm, 4);
                fm3 = !mov_Fanta(alto,ancho,tablero,&(Fant_all.Ft3),&Pm, 5);
                fm4 = !mov_Fanta(alto,ancho,tablero,&(Fant_all.Ft4),&Pm, 6);
                sleep(difficult);

            }
        //}
return 0;
}

