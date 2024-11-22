#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define SIZE 30
typedef struct {            // Definimos una estructura, que sera de la forma char , textura
  const char * r;
  SDL_Texture *texture;
} textures;

typedef struct {                                                    
  const char * r;
  SDL_Texture *texture;
} anima;

void Rendtexto(SDL_Renderer *renderer, TTF_Font *font, int h, int v);
SDL_Texture* cargarTextura(SDL_Renderer *renderer, const char *ruta);
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
		    char mov1);


#endif
