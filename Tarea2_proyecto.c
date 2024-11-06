#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//PREGUNTAR SI PUEDE SUPERPONERSE 2 ARREGLOS QUE TENGAN EL MISMO MAPA

#define Pacman 3;
#define Fantasma 4;
#define max 10000;



struct pacman
  {
      int posy_Pm;
      int posx_Pm;
  } variable;
/*
forma para ver los fantasmas diferenciados
#define Fant1 5;
#define Fant2 6;
#define Fant3 7;
#define Fant4 8;
*/

//movimientos con a=izq, w=arriba, d=derecha, s=abajo
//ocupar tiempo para el movimiento de todo
//random para posicion y movimiento de los fantasmas
//"p" para pausar

void pos_inicial(int largo, int ancho, int tablero[largo][ancho]){
    //posicion inicial fantasmas, 1/4 del tablero arriba
    int cuarto=largo/4;
    int posX=rand()%cuarto,posY=rand()%cuarto;


    //posicion inicial pacman, 1/4 del tablero abajo
    
}

int mov_Fanta(int largo, int ancho, int tablero[largo][ancho], int *posX_Fant, int *posY_Fant){

//Ver la idea de que haya 2 tableros, uno para pacman y que vaya recolectando, y otro con el movimiento de los fantasmas
//para asi no preocuparse de borrar o rellenar un punto que debe recolectar pacman cada vez que se mueven los fantasmas

//Que vaya hasta la pared cercana con el movimiento que hizo

    int mov_aleatorio = rand()%4;
//    while (1){ ver si implementar esto que es para obligar a que haga el movimiento hasta que resulte, puede ser con una variable
//que cambie si se hizo el cambio de coordenada del fantasma

    switch (mov_aleatorio){  /* 0= arriba ; 1= abajo ; 2= derecha ; 3= izquierda */

    case 0:
        if (tablero[(*posY_Fant-1+largo)%largo][*posX_Fant]==1 || tablero[(*posY_Fant-1+largo)%largo][*posX_Fant]==0) {
            //tablero[(*posY_Fant-1+largo)%largo][*posX_Fant]=0;
            *posY_Fant=(*posY_Fant-1+largo)%largo;
            tablero[*posY_Fant][*posX_Fant]=Fantasma; //Ver si agregar el fantasma como individual o como 4 en 1
        }
        break;

    case 1:
        if (tablero[(*posY_Fant+1)%largo][*posX_Fant]==1 || tablero[(*posY_Fant+1)%largo][*posX_Fant]==0){
            //tablero[(*posY_Fant+1)%largo][*posX_Fant]=0;
            *posY_Fant=(*posY_Fant+1)%largo;
            tablero[*posY_Fant][*posX_Fant]=Fantasma;
        }
        break;

    case 2:
        if (tablero[*posY_Fant][(*posX_Fant+1)%ancho]==1 || tablero[*posY_Fant][(*posX_Fant+1)%ancho]==0){
            //tablero[*posY_Fant][(*posX_Fant+1)%ancho]=0;
            *posX_Fant=(*posX_Fant+1)%ancho;
            tablero[*posY_Fant][*posX_Fant]=Fantasma;
        }
        break;

    case 3:
        if (tablero[*posY_Fant][(*posX_Fant-1+ancho)%ancho]==1 || tablero[*posY_Fant][(*posX_Fant-1+ancho)%ancho]==0){
            //tablero[*posY_Fant][(*posX_Fant-1+ancho)%ancho]=0;
            *posX_Fant=(*posX_Fant-1+ancho)%ancho;
            tablero[*posY_Fant][*posX_Fant]=Fantasma;
        }
        break;

    default:
        break;
    }
 //   }
    return 0;
}


void mov_Pacman(int largo, int ancho ,int tablero[largo][ancho] ,int move ,int *posx_Pm ,int *posy_Pm ,int *puntaje){ //se debe pedir con &posy_pm (y con x)

    move=tolower(move);

    switch (move){//solo se debe cambiar el inicio del case para flechas o lo que se requiera

    //hacer un .h con movimiento mejor, en vez de esto que es codigo en si para cada posicion
    
    case 'a': //Izquierda
        if (tablero[*posy_Pm][(*posx_Pm-1+ancho)%ancho]==1 || tablero[*posy_Pm][(*posx_Pm-1+ancho)%ancho]==0){
            tablero[*posy_Pm][(*posx_Pm-1+ancho)%ancho]=0;
            if (tablero[*posy_Pm][(*posx_Pm-1+ancho)%ancho]==1) *puntaje++; //de esta forma ver el sumar puntaje
            *posx_Pm=(*posx_Pm-1+ancho)%ancho;
            tablero[*posy_Pm][*posx_Pm]=Pacman;
        }
        break;
    
    case 'd': //Derecha
        if (tablero[*posy_Pm][(*posx_Pm+1)%ancho]==1 || tablero[*posy_Pm][(*posx_Pm+1)%ancho]==0){
            tablero[*posy_Pm][(*posx_Pm+1)%ancho]=0;
            if (tablero[*posy_Pm][(*posx_Pm+1)%ancho]==1) *puntaje++;
            *posx_Pm=(*posx_Pm+1)%ancho;
            tablero[*posy_Pm][*posx_Pm]=Pacman;
        }
        break;

    case 'w': //Arriba
        if (tablero[(*posy_Pm-1+largo)%largo][*posx_Pm]==1 || tablero[(*posy_Pm-1+largo)%largo][*posx_Pm]==0){
            tablero[(*posy_Pm-1+largo)%largo][*posx_Pm]=0;
            if (tablero[(*posy_Pm-1+largo)%largo][*posx_Pm]==1) *puntaje++;
            *posy_Pm=(*posy_Pm-1+largo)%largo;
            tablero[*posy_Pm][*posx_Pm]=Pacman;
        }
        break;

    case 's': //Abajo
        if (tablero[(*posy_Pm+1)%largo][*posx_Pm]==1 || tablero[(*posy_Pm+1)%largo][*posx_Pm]==0){
            tablero[(*posy_Pm+1)%largo][*posx_Pm]=0;
            if (tablero[(*posy_Pm+1)%largo][*posx_Pm]==1) *puntaje++; 
            *posy_Pm=(*posy_Pm+1)%largo;
            tablero[*posy_Pm][*posx_Pm]=Pacman;
        }
        break;

    case 'p':
        //stop timer de funcion principal que detenga los movimientos y guarde el progreso en un archivo
        break;
    default:
        break;
    }
    return 0;
}



int main(){
    srand(time(0));// esto debe hacerse en el main principal del proyecto solo una vez sin necesidad de llamarlo en otras funciones
    int total=0;
    int *puntaje=&total;
}

/*
FORMA DE APLICAR 2 GRAFICOS AL MAIN:

#include <stdio.h>

#define FILAS 10
#define COLUMNAS 10

int main() {
    // Inicialización de ambos arreglos
    int particula1[FILAS][COLUMNAS] = {0}; // 0 indica que no hay nada
    int particulas_otros[FILAS][COLUMNAS] = {0};

    // Posición inicial de la partícula principal
    particula1[2][3] = 1; // 1 indica la presencia de la partícula principal

    // Posiciones de otras partículas (simuladas)
    particulas_otros[5][6] = 1; // Otra partícula
    particulas_otros[2][3] = 1; // Partícula que coincide con la principal

    // Simulación de movimiento y superposición
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (particula1[i][j] == 1 && particulas_otros[i][j] == 1) {
                printf("¡Game Over! Colisión en la posición (%d, %d)\n", i, j);
                return 0;
            }
        }
    }

    return 0;
}
*/


/*
forma de aplicar los 2 graficos en sdl:

#include <SDL2/SDL.h>
#include <stdio.h>

#define FILAS 10
#define COLUMNAS 10
#define TAMANO_CELDA 50 // Tamaño de cada celda

int main() {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Crear ventana y renderizador
    SDL_Window *window = SDL_CreateWindow("Partículas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                          COLUMNAS * TAMANO_CELDA, FILAS * TAMANO_CELDA, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Inicialización de los arreglos 2D
    int particula1[FILAS][COLUMNAS] = {0};
    int particulas_otros[FILAS][COLUMNAS] = {0};

    // Colocar partículas en posiciones iniciales
    particula1[2][3] = 1;  // Partícula principal
    particulas_otros[5][6] = 1;  // Otra partícula
    particulas_otros[2][3] = 1;  // Partícula que causará "Game Over"

    int gameOver = 0;

    // Bucle de juego
    SDL_Event e;
    int running = 1;

    while (running) {
        // Procesar eventos
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Limpiar pantalla
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Blanco
        SDL_RenderClear(renderer);

        // Dibujar las partículas
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                if (particula1[i][j] == 1 || particulas_otros[i][j] == 1) {
                    SDL_Rect rect = { j * TAMANO_CELDA, i * TAMANO_CELDA, TAMANO_CELDA, TAMANO_CELDA };
                    
                    if (particula1[i][j] == 1 && particulas_otros[i][j] == 1) {
                        // Colisión detectada, marcar como "Game Over"
                        gameOver = 1;
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Rojo para colisión
                    } else if (particula1[i][j] == 1) {
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Verde para la partícula principal
                    } else {
                        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // Azul para las otras partículas
                    }

                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }

        // Actualizar pantalla
        SDL_RenderPresent(renderer);

        // Verificar si hay "Game Over"
        if (gameOver) {
            printf("¡Game Over! Colisión detectada.\n");
            SDL_Delay(3000);  // Pausa de 3 segundos antes de cerrar
            running = 0;
        }

        SDL_Delay(100);  // Controlar la velocidad del juego (ajustar según necesidad)
    }

    // Limpiar recursos de SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
*/