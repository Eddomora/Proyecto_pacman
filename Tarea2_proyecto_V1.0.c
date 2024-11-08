#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <ctype.h>

#define Pacman 3;
#define Fantasma 4;
#define max 10000;

struct posicion{
    int x;
    int y;
    int extra;
};

struct fantasmas{
    struct posicion Ft1;
    struct posicion Ft2;
    struct posicion Ft3;
    struct posicion Ft4;
};


void pos_inicial(int largo, int ancho, int tablero[largo][ancho],struct posicion *PM , struct fantasmas *All_enemies){
    int cuarto=largo/4;
    int posX=rand()%cuarto,posY=rand()%cuarto;
}



int mov_Fanta(int largo, int ancho, int tablero[largo][ancho], struct posicion *fant ){
    int mov_aleatorio = randint()%4;

    switch (mov_aleatorio){

    case 0:
        if (tablero[((fant->y)-1+largo)%largo][fant->x]==1 || tablero[((fant->y)-1+largo)%largo][fant->x]==0){
            tablero[fant->y][fant->x]= fant->extra;
            if (tablero[((fant->y)-1+largo)%largo][fant->x]==1) fant->extra=1; 
            else fant->extra=0;
            fant->y = ((fant->y)-1+largo)%largo;
            tablero[fant->y][fant->x]=Fantasma;
        }
        break;

    case 1:
        if (tablero[((fant->y)+1+largo)%largo][fant->x]==1 || tablero[((fant->y)+1+largo)%largo][fant->x]==0){
            tablero[fant->y][fant->x]= fant->extra;
            if (tablero[((fant->y)+1+largo)%largo][fant->x]==1) fant->extra=1; 
            else fant->extra=0;
            fant->y = ((fant->y)+1+largo)%largo;
            tablero[fant->y][fant->x]=Fantasma;
        }
        break;

    case 2:
        if (tablero[fant->y][((fant->x)+1+ancho)%ancho]==1 || tablero[fant->y][((fant->x)+1+ancho)%ancho]==0){
            tablero[fant->y][fant->x]= fant->extra;
            if (tablero[fant->y][((fant->x)+1+ancho)%ancho]==1) fant->extra=1; 
            else fant->extra=0;
            fant->x = ((fant->x)+1+ancho)%ancho;
            tablero[fant->y][fant->x]=Fantasma;
        }
        break;

    case 3:
        if (tablero[fant->y][((fant->x)-1+ancho)%ancho]==1 || tablero[fant->y][((fant->x)-1+ancho)%ancho]==0){
            tablero[fant->y][fant->x]= fant->extra;
            if (tablero[fant->y][((fant->x)-1+ancho)%ancho]==1) fant->extra=1; 
            else fant->extra=0;
            fant->x = ((fant->x)-1+ancho)%ancho;
            tablero[fant->y][fant->x]=Fantasma;
        }
        break;

    default:
        break;
    }

    return 0;
}

int mov_Pacman(int largo, int ancho ,int tablero[largo][ancho] ,int move ,struct posicion *pacm ){
    move=tolower(move);

    switch (move){
    
    case 'a':
        if (tablero[pacm->y][((pacm->x)-1+ancho)%ancho]==1 || tablero[pacm->y][((pacm->x)-1+ancho)%ancho]==0){
            tablero[pacm->y][pacm->x]=0;
            if (tablero[pacm->y][((pacm->x)-1+ancho)%ancho]==1) pacm->extra++; 
            pacm->x = ((pacm->x)-1+ancho)%ancho;
            tablero[pacm->y][pacm->x]=Pacman;
        }
        break;
    
    case 'd':
        if (tablero[pacm->y][((pacm->x)+1+ancho)%ancho]==1 || tablero[pacm->y][((pacm->x)+1+ancho)%ancho]==0){
            tablero[pacm->y][pacm->x]=0;
            if (tablero[pacm->y][((pacm->x)+1+ancho)%ancho]==1) pacm->extra++; 
            pacm->x = ((pacm->x)+1+ancho)%ancho;
            tablero[pacm->y][pacm->x]=Pacman;
        }
        break;

    case 'w':
        if (tablero[((pacm->y)-1+largo)%largo][pacm->x]==1 || tablero[((pacm->y)-1+largo)%largo][pacm->x]==0){
            tablero[pacm->y][pacm->x]=0;
            if (tablero[((pacm->y)-1+largo)%largo][pacm->x]==1) pacm->extra++; 
            pacm->y = ((pacm->y)-1+largo)%largo;
            tablero[pacm->y][pacm->x]=Pacman;
        }
        break;

    case 's':
        if (tablero[((pacm->y)+1+largo)%largo][pacm->x]==1 || tablero[((pacm->y)+1+largo)%largo][pacm->x]==0){
            tablero[pacm->y][pacm->x]=0;
            if (tablero[((pacm->y)+1+largo)%largo][pacm->x]==1) pacm->extra++; 
            pacm->y = ((pacm->y)+1+largo)%largo;
            tablero[pacm->y][pacm->x]=Pacman;
        }
        break;

    case 'p':
        return 0;
    default:
        break;
    }
    return 1;
}

typedef struct posicion posicion_t;
typedef struct fantasmas fantasmas_t;

int main(){
    srand(time(0));
    posicion_t Pm;
    fantasmas_t Fant_all;
    int tablero[10][10];//Esto se pide del anterior tablero
    char movimiento;
    int GameOver=0
    while (1){
        scanf("%c",&movimiento);
        do{
        GameOver = mov_Pacman(10 ,10 ,tablero[10][10],movimiento ,&Pm) break; //modo de pausar el juego, la funcion tiene retorno 1 y 0
        mov_Fanta(&(Fant_all.Ft1));
        mov_Fanta(&(Fant_all.Ft2));
        mov_Fanta(&(Fant_all.Ft3));
        mov_Fanta(&(Fant_all.Ft4));

        } while (GameOver || );
    }
}
