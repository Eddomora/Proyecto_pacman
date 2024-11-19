#include <stdio.h>
#include <SDL2/SDL.h>
#include<stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "funciones.h"
#define SIZE 30



int main(){  
  int filas = 0, col = 0;                           // Definimos filas y columnas como 0, luego le damos valores mediante nuestra funcion dimen
  dimen("mapa1.txt", &filas, &col);
    
  int WIDTH = col * SIZE;                        //Definimos el porte de la pantalla en base a nuestro numero de filas y columnas 
  int HEIGHT = filas *SIZE;
  
  int **M = malloc(filas * sizeof(int*));      //Creamos una matriz M mediante memoria dinamica
  for (int i = 0; i < filas; i++) {
    M[i] = malloc(col * sizeof(int));
  }
  cargarMapa("mapa1.txt", M , filas , col);       // Llamamos a la funcion para cargar el mapa en la matriz M
   

  //Iniciamos SDL,SDL Image y TTF para texto
  
  if (SDL_Init(SDL_INIT_EVERYTHING) !=0) { 
        return EXIT_FAILURE;
    }
  if ((IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) == 0) { 
        SDL_Quit();
        return EXIT_FAILURE;
    }
  if (TTF_Init() == -1) {
    return EXIT_FAILURE;
  }

  TTF_Font *font = TTF_OpenFont("/home/bryan/Escritorio/Progra/Tarea semestral/stocky.ttf", 26); // cargamos la fuente para usarla mas adelante
  
  // Creamos una ventana para visualizar todo
  
  SDL_Window *window;                                                  
  window = SDL_CreateWindow("PACMAN",SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED,WIDTH ,HEIGHT +100,
			    SDL_WINDOW_SHOWN);
  //Creamos un rederer
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
   textures textures[] = {
        {"/home/bryan/Escritorio/Progra/Tarea semestral/Paredes/E1.png", NULL},
        {"/home/bryan/Escritorio/Progra/Tarea semestral/Paredes/E2.png", NULL},
        {"/home/bryan/Escritorio/Progra/Tarea semestral/Paredes/E3.png", NULL},
        {"/home/bryan/Escritorio/Progra/Tarea semestral/Paredes/E4.png", NULL},
	{"/home/bryan/Escritorio/Progra/Tarea semestral/Items/ball.png", NULL},
	{"/home/bryan/Escritorio/Progra/Tarea semestral/Items/s.png", NULL},	
    };
   anima anima[] = {
     {"/home/bryan/Escritorio/Progra/Tarea semestral/Items/pacman.png", NULL},
     {"/home/bryan/Escritorio/Progra/Tarea semestral/Items/pacman2.png", NULL},
     {"/home/bryan/Escritorio/Progra/Tarea semestral/Items/pacman3.png", NULL},
     {"/home/bryan/Escritorio/Progra/Tarea semestral/Items/blinky.png", NULL},
     {"/home/bryan/Escritorio/Progra/Tarea semestral/Items/blinky1.png", NULL},
     {"/home/bryan/Escritorio/Progra/Tarea semestral/Items/clyde.png", NULL},
     {"/home/bryan/Escritorio/Progra/Tarea semestral/Items/clyde1.png", NULL},
     {"/home/bryan/Escritorio/Progra/Tarea semestral/Items/inky.png", NULL},
     {"/home/bryan/Escritorio/Progra/Tarea semestral/Items/inky1.png", NULL},
     {"/home/bryan/Escritorio/Progra/Tarea semestral/Items/pinky.png", NULL},
     {"/home/bryan/Escritorio/Progra/Tarea semestral/Items/pinky1.png", NULL},
    };

   // Dentro de la estrcutura ponemos todas las rutas de las imagenes a usar, seguidos NULL, ya que hasta este punto no se ha cargado nada
   
  
   // Con los ciclo anterior, recorremos toda la estructura, reemplazando cada lugar de null por la textura correspondiente entregada por la funcion

   //Ciclo para mostrar todo
   int run = 1;
   SDL_Event event;
   int v = 2;                       // Variables para las vidas y el puntaje
   int h = 10;
   

   Uint32 tiempoAnterior = 0; 
   int tiempoAnimacion = 0;
   
   while (run) {
     for (int i = 0; i < sizeof(textures) / sizeof(textures[0]); i++) {
     textures[i].texture = cargarTextura(renderer, textures[i].r);
   }
   for(int i = 0; i< sizeof(anima)/sizeof(anima[0]); i++){
     anima[i].texture = cargarTextura(renderer, anima[i].r);
   }
   
      Uint32 tiempoActual = SDL_GetTicks();  // Obtener el tiempo actual en milisegundos
      int tiempoTranscurrido = (tiempoActual - tiempoAnterior) / 200;  // Convertir a un valor optimo
       if (tiempoTranscurrido != tiempoAnimacion) {
        tiempoAnimacion = tiempoTranscurrido;  // Actualizar la animación cada segundo
    }

     while(SDL_PollEvent(&event)){   //Ciclo para que la ventan este activa hasta que se cierre manualmente 
       if (event.type == SDL_QUIT){ 
	 run = 0;
       }
     }
     SDL_RenderClear(renderer);                    // Limpiamos la pantalla
     RenderizarMapa(renderer, textures, anima, tiempoAnimacion, M, filas, col, font, h, v);
     Rendtexto(renderer, font, h, v); // Llamamos a la funcion
     SDL_RenderPresent(renderer);
     for (int i = 0; i < sizeof(textures) / sizeof(textures[0]); i++) {
       SDL_DestroyTexture(textures[i].texture);
   }
   for(int i = 0; i< sizeof(anima)/sizeof(anima[0]); i++){
     SDL_DestroyTexture(anima[i].texture);
   }
   }
   free(M);
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
 
}

