#include <stdio.h>
#include <SDL2/SDL.h>
#include<stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#define SIZE 30
// Funcion para determinar las dimensiones del mapa

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
  
  while (fscanf(file, "%d", &temp1) == 1) {            // Iniciamos un ciclo hasta que la lectura no sea exitosa 
    (*c)++;
    e = fgetc(file);                                
    if (e == '\n' || e == EOF) {                      // Sumamos uno al contador por cada elemento encontrado hasta el salto de linea, para obtener las columnas
      break;  
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


void Rendtexto(SDL_Renderer *renderer, TTF_Font *font, int h, int v) {
  SDL_Color color = {255, 255, 255, 255}; // Para mostrar el texto en color blanco
  char textoFinal[100]; // Aqui se almacena el texto
    sprintf(textoFinal, "Puntaje: %d                           Vidas: %d", h, v);
    // Crear la superficie de texto
    SDL_Surface *text1 = TTF_RenderText_Solid(font, textoFinal, color);
    SDL_Texture *textTextura = SDL_CreateTextureFromSurface(renderer, text1);
    SDL_Rect textRect = {10, 940, text1->w, text1->h};
    SDL_RenderCopy(renderer, textTextura, NULL, &textRect);         // Renderizamos todo
    SDL_FreeSurface(text1);                                    // Liberamos lo que ya no se usa
}
               
    
typedef struct {                                                     // Definimos una estrucutra, que sera de la forma char , textura
  const char * r;
  SDL_Texture *texture;
} Texturas;

// Función para cargar texturas
SDL_Texture* cargarTextura(SDL_Renderer *renderer, const char *ruta) {           // Estafuncion va a recibir un renderer y una ruta para cargar cierta imagen
  SDL_Surface *imageSurface = IMG_Load(ruta);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, imageSurface);  //Creamos la textura y la devolvemo, luego liberamos la imagen usada
    SDL_FreeSurface(imageSurface);
    return texture;
}


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
   

  //Iniciamos SDL e SDL Image
  
  if (SDL_Init(SDL_INIT_EVERYTHING) !=0) { 
        return EXIT_FAILURE;
    }
  if ((IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) == 0) { 
        SDL_Quit();
        return EXIT_FAILURE;
    }
  // Creamos una ventana para visualizar todo
  
  SDL_Window *window;                                                  
  window = SDL_CreateWindow("PACMAN, Funciona porfa te lo pido flaco",SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED,WIDTH ,HEIGHT +100,
			    SDL_WINDOW_SHOWN);
  //Creamos un rederer
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
   Texturas textures[] = {
        {"/home/bryan/Escritorio/Progra/Tarea semestral/Paredes/E1.png", NULL},
        {"/home/bryan/Escritorio/Progra/Tarea semestral/Paredes/E2.png", NULL},
        {"/home/bryan/Escritorio/Progra/Tarea semestral/Paredes/E3.png", NULL},
        {"/home/bryan/Escritorio/Progra/Tarea semestral/Paredes/E4.png", NULL},
	{"/home/bryan/Escritorio/Progra/Tarea semestral/Items/pacman.png", NULL},
	{"/home/bryan/Escritorio/Progra/Tarea semestral/Items/blinky.png", NULL},
	{"/home/bryan/Escritorio/Progra/Tarea semestral/Items/clyde.png", NULL},
	{"/home/bryan/Escritorio/Progra/Tarea semestral/Items/inky.png", NULL},
	{"/home/bryan/Escritorio/Progra/Tarea semestral/Items/pinky.png", NULL},
	{"/home/bryan/Escritorio/Progra/Tarea semestral/Items/ball.png", NULL},
	{"/home/bryan/Escritorio/Progra/Tarea semestral/Items/s.png", NULL},	
    };
   // Dentro de la estrcutura ponemos todas las rutas de las imagenes a usar, seguidos NULL, ya que hasta este punto no se ha cargado nada
   
   for (int i = 0; i < sizeof(textures) / sizeof(textures[0]); i++) { 
     textures[i].texture = cargarTextura(renderer, textures[i].r);
   }
   // Con el ciclo anterior, recorremos toda la estructura, reemplazando cada lugar de null por la textura correspondiente entregada por la funcion

   //Ciclo para armar el mapa
   
   for (int i = 0; i < filas; i++){
     for (int j = 0; j < col; j++) {
       SDL_Rect rect =  { j * SIZE, i * SIZE, SIZE, SIZE };
       SDL_Rect rect1 =  { j * SIZE, i * SIZE+15, SIZE, SIZE };
       SDL_Rect rect2 =  { j * SIZE, i * SIZE-15, SIZE, SIZE };
       SDL_Rect rect3 =  { j * SIZE-15, i * SIZE+15, SIZE,SIZE };
       SDL_Rect rect4 =  { j * SIZE+15, i * SIZE+15, SIZE,SIZE };
      
       if ((M[i][j] == 1 && j == 0 && i == 0) || (M[i][j] == -1)) {                               
	 SDL_RenderCopyEx(renderer, textures[0].texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
        }
        else if ((M[i][j] == 1 && i == 0 && j == (col - 1)) || (M[i][j] == -2)) {
	  SDL_RenderCopyEx(renderer, textures[0].texture, NULL, &rect, 90, NULL, SDL_FLIP_NONE);
        }
        else if ((M[i][j] == 1 && i == (filas - 1) && j == (col - 1)) || (M[i][j] == -3)) {
	  SDL_RenderCopyEx(renderer, textures[0].texture, NULL, &rect, 180, NULL, SDL_FLIP_NONE);
        }
        else if (((M[i][j] == 1 && i == (filas - 1) && j == 0)) || ((M[i][j] == -4))) {
	  SDL_RenderCopyEx(renderer, textures[0].texture, NULL, &rect, 270, NULL, SDL_FLIP_NONE);
        }
        else if ((M[i][j] == 1 && i == 0) || (M[i][j] == -5)) {
	  SDL_RenderCopyEx(renderer, textures[1].texture, NULL, &rect, 270, NULL, SDL_FLIP_NONE); 
        }
        else if ((M[i][j] == 1 && i == (filas - 1)) || (M[i][j] == -6)) {
	  SDL_RenderCopyEx(renderer, textures[1].texture, NULL, &rect, 90, NULL, SDL_FLIP_NONE); 
        }
        else if ((M[i][j] == 1 && j == 0) || (M[i][j] == -7)) {
	  SDL_RenderCopyEx(renderer, textures[1].texture, NULL, &rect, 180, NULL, SDL_FLIP_NONE); 
        }
        else if ((M[i][j] == 1 && j == (col - 1)) || (M[i][j] == -8)) {
           SDL_RenderCopyEx(renderer, textures[1].texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE); 
        }
        else if (M[i][j] == -9) {
	  SDL_RenderCopyEx(renderer, textures[0].texture, NULL, &rect1, 90, NULL, SDL_FLIP_NONE);
        }
        else if (M[i][j] == 9) {
	  SDL_RenderCopyEx(renderer, textures[1].texture, NULL, &rect2, 0, NULL, SDL_FLIP_NONE); 
        }
        else if (M[i][j] == 10) {
	  SDL_RenderCopyEx(renderer, textures[0].texture, NULL, &rect2, 180, NULL, SDL_FLIP_NONE);  
        }
        else if (M[i][j] == 11) {
            SDL_RenderCopyEx(renderer, textures[1].texture, NULL, &rect2, 90, NULL, SDL_FLIP_NONE); 
        }
        else if (M[i][j] == 12) {
             SDL_RenderCopyEx(renderer, textures[0].texture, NULL, &rect2, 180, NULL, SDL_FLIP_NONE);
        }
        else if (M[i][j] == 13) {
            SDL_RenderCopyEx(renderer, textures[1].texture, NULL, &rect1, 0, NULL, SDL_FLIP_NONE);
        }
        else if (M[i][j] == 14) {
             SDL_RenderCopyEx(renderer, textures[0].texture, NULL, &rect1, 90, NULL, SDL_FLIP_NONE);
        }
        else if (M[i][j] == 15) {
            SDL_RenderCopyEx(renderer, textures[1].texture, NULL, &rect1, 270, NULL, SDL_FLIP_NONE); 
        }
        else if (M[i][j] == 16) {
            SDL_RenderCopyEx(renderer, textures[0].texture, NULL, &rect1, 0, NULL, SDL_FLIP_NONE);
        }
        else if (M[i][j] == 17) {
             SDL_RenderCopyEx(renderer, textures[1].texture, NULL, &rect2, 180, NULL, SDL_FLIP_NONE);  
        }
        else if (M[i][j] == 18) {
            SDL_RenderCopyEx(renderer, textures[0].texture, NULL, &rect2, 270, NULL, SDL_FLIP_NONE); 
        }
        else if (M[i][j] == 19) {
             SDL_RenderCopyEx(renderer, textures[1].texture, NULL, &rect2, 90, NULL, SDL_FLIP_NONE);  
        }
        else if (M[i][j] == 20) {
            SDL_RenderCopyEx(renderer, textures[0].texture, NULL, &rect2, 270, NULL, SDL_FLIP_NONE);
        }
        else if (M[i][j] == 21) {
            SDL_RenderCopyEx(renderer, textures[1].texture, NULL, &rect1, 180, NULL, SDL_FLIP_NONE);
        }
        else if (M[i][j] == 22) {
            SDL_RenderCopyEx(renderer, textures[0].texture, NULL, &rect1, 0, NULL, SDL_FLIP_NONE);  
        }
        else if (M[i][j] == 23) {
            SDL_RenderCopyEx(renderer, textures[1].texture, NULL, &rect1, 270, NULL, SDL_FLIP_NONE); 
        }
        else if (M[i][j] == 24) {
	  SDL_RenderCopyEx(renderer, textures[2].texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);  
        }
        else if (M[i][j] == 25) {
	  SDL_RenderCopyEx(renderer, textures[3].texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
        }
        else if (M[i][j] == 26) {
	  SDL_RenderCopyEx(renderer, textures[2].texture, NULL, &rect, 180, NULL, SDL_FLIP_NONE); 
        }
        else if (M[i][j] == 27) {
	  SDL_RenderCopyEx(renderer, textures[2].texture, NULL, &rect, 270, NULL, SDL_FLIP_NONE);  
        }
        else if (M[i][j] == 28) {
	  SDL_RenderCopyEx(renderer, textures[3].texture, NULL, &rect, 90, NULL, SDL_FLIP_NONE); 
        }
        else if (M[i][j] == 29) {
	  SDL_RenderCopyEx(renderer, textures[2].texture, NULL, &rect, 90, NULL, SDL_FLIP_NONE);  
        }
     }
   }
 
   for (int i = 0; i < filas; i++){
     for (int j = 0; j < col; j++) {
       SDL_Rect rect =  { j * SIZE, i * SIZE, SIZE, SIZE };
       switch(M[i][j]){
       case 2:
	 SDL_RenderCopy(renderer,textures[4].texture, NULL, &rect);
	 break;
       case 3:
	 SDL_RenderCopy(renderer,textures[5].texture, NULL, &rect);
	  break;
       case 4:
	 SDL_RenderCopy(renderer,textures[6].texture, NULL, &rect);
	  break;
       case 5:
	 SDL_RenderCopy(renderer,textures[7].texture, NULL, &rect);
	  break;
       case 6 :
	 SDL_RenderCopy(renderer,textures[8].texture, NULL, &rect);
	  break;
       case 7:
	 SDL_RenderCopy(renderer,textures[9].texture, NULL, &rect);
	  break;
       case 8:
	 SDL_RenderCopy(renderer,textures[10].texture, NULL, &rect);
	  break;
       }
     }
   }
 
  for (int i = 530; i<= 600; i+=40){                             // En este ciclo se posiciona el icono de las vidas
    SDL_Rect rect0 =  {  SIZE+i,  SIZE+910, SIZE, SIZE };
    SDL_RenderCopy(renderer,textures[4].texture, NULL, &rect0);
  }
  
  int v = 2;
  int h = 10000;

  // Iniciamos TTF para mostrar texto
  
  if (TTF_Init() == -1) {
    return EXIT_FAILURE;
  }

  TTF_Font *font = TTF_OpenFont("/home/bryan/Escritorio/Progra/Tarea semestral/stocky.ttf", 26); // cargamos la fuente
   Rendtexto(renderer, font, h, v); // Llamamos a la funcion 
  
  SDL_RenderPresent(renderer);
  int run = 1;
  SDL_Event event;
  while (run) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { 
                run = 0;
            }
        }
  }
}
