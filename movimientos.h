#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Estructuras necesarias para organizar las posiciones de Pacman y los Fantasmas
struct posicion {
    int x;
    int y;
    int extra;
};

struct fantasmas {
    struct posicion Ft1;
    struct posicion Ft2;
    struct posicion Ft3;
    struct posicion Ft4;
};

// Declaración de funciones
void ingresar_posiciones(struct posicion *ente, int largo, int ancho, int **tablero, int num_ente);
int verificar(struct posicion *Pman, struct posicion *Ftma, int fnt_mov);
int verificar_todos(struct posicion *Pman, struct fantasmas *Enemys, int mov);
int mov_Fanta(int largo, int ancho, int **tablero, struct posicion *fant, struct posicion *Pma, int num_ente);
int mov_Pacman(int largo, int ancho, int **tablero, int move, struct posicion *pacm, struct fantasmas *enemy);

#endif
