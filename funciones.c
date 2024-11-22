#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#define SIZE 30

// Funcion para mostrar texto

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
               
    


// Función para cargar texturas
SDL_Texture* cargarTextura(SDL_Renderer *renderer, const char *ruta) {           // Estafuncion va a recibir un renderer y una ruta para cargar cierta imagen
  SDL_Surface *imageSurface = IMG_Load(ruta);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, imageSurface);  //Creamos la textura y la devolvemo, luego liberamos la imagen usada
    SDL_FreeSurface(imageSurface);
    return texture;
}

// Funcion para renderizar el mapa
void RenderizarMapa(SDL_Renderer* renderer, 
		    textures textures[],       // Cambiado a Texturas[]
                    anima anima[],  
                    int tiempoAnimacion, 
                    int** M, 
                    int filas, 
                    int col, 
                    TTF_Font* font, 
                    int h, 
                    int v,
		    char mov1){
  
  for (int i = 0; i < filas; i++){
     for (int j = 0; j < col; j++) {
       SDL_Rect rect =  { j * SIZE, i * SIZE, SIZE, SIZE };                  //Se definen los rect para armar los bordes del mapa 
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

     for (int i = 530; i<= 600; i+=40){                             // En este ciclo se posiciona el icono de las vidas
       SDL_Rect rect0 =  {  SIZE+i,  SIZE+910, SIZE, SIZE };
       SDL_RenderCopy(renderer,anima[1].texture, NULL, &rect0);
     }
   
     for (int i = 0; i < filas; i++){                               // Este ciclo maneja los elementos variables en pantalla, como el pacman y los fantasmas
       for (int j = 0; j < col; j++) {
	 SDL_Rect rect =  { j * SIZE, i * SIZE, SIZE, SIZE };
	 switch(M[i][j]){
	   /* mostramos en pantalla las imagenes accediendo a los indices mediante la variable creada anteriormente, limitada por modulos para que no
	      tome una textura que no le corresponda*/
	 case 2:
	   if (mov1 == 'd'){
	   SDL_RenderCopy(renderer, anima[tiempoAnimacion % 3].texture, NULL, &rect);
	   }
	   else if (mov1 == 'w'){
	     SDL_RenderCopyEx(renderer,anima[tiempoAnimacion % 3].texture , NULL, &rect, 270, NULL, SDL_FLIP_NONE);
	   }
	   else if (mov1 == 's'){
	     SDL_RenderCopyEx(renderer,anima[tiempoAnimacion % 3].texture , NULL, &rect, 90, NULL, SDL_FLIP_NONE);
	   }
	   else if ( mov1 == 'a'){
	     SDL_RenderCopyEx(renderer,anima[tiempoAnimacion % 3].texture , NULL, &rect, 180, NULL, SDL_FLIP_NONE);
	   }
	   break;
	 case 3:
	   SDL_RenderCopy(renderer, anima[3 + (tiempoAnimacion % 2)].texture, NULL, &rect);
	   break;
	 case 4:
	   SDL_RenderCopy(renderer, anima[5 + (tiempoAnimacion % 2)].texture, NULL, &rect);
	   break;
	 case 5:
	   SDL_RenderCopy(renderer, anima[7 + (tiempoAnimacion % 2)].texture, NULL, &rect);
	   break;
	 case 6 :
	   SDL_RenderCopy(renderer, anima[9 + (tiempoAnimacion % 2)].texture, NULL, &rect);
	   break;
	 case 7:
	   SDL_RenderCopy(renderer,textures[4].texture, NULL, &rect);
	   break;
	 case 8:
	   SDL_RenderCopy(renderer,textures[5].texture, NULL, &rect);
	   break;
	 }
       }
     }
}
