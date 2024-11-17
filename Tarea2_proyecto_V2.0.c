#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <ctype.h>
#include <unistd.h>
//#include <windows.h> esto sirve para ocupar 

#define Pacman 3
#define Fantasma 4
#define max 10000

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

int verificar_todos(struct posicion *Pman, struct fantasmas *Enemys){

    if ((Pman->x == Enemys->Ft1.x) && (Pman->y == Enemys->Ft1.y)) {
        return 1;
    }
    if ((Pman->x == Enemys->Ft2.x) && (Pman->y == Enemys->Ft2.y)) {
        return 1;
    }
    if ((Pman->x == Enemys->Ft3.x) && (Pman->y == Enemys->Ft3.y)) {
        return 1;
    }
    if ((Pman->x == Enemys->Ft4.x) && (Pman->y == Enemys->Ft4.y)) {
        return 1;
    }
    return 0;
}


void pos_inicial(int largo, int ancho, int tablero[largo][ancho],struct posicion *PM , struct fantasmas *All_enemies){
    int cuarto=largo/4;
    int posX=rand()%cuarto,posY=rand()%cuarto;
}



int mov_Fanta(int largo, int ancho, int tablero[largo][ancho], struct posicion *fant ){
    int mov_aleatorio = rand()%4;

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
            if (tablero[pacm->y][((pacm->x)-1+ancho)%ancho]==1) (pacm->extra)++; 
            pacm->x = ((pacm->x)-1+ancho)%ancho;
            tablero[pacm->y][pacm->x]=Pacman;
        }
        break;
    
    case 'd':
        if (tablero[pacm->y][((pacm->x)+1+ancho)%ancho]==1 || tablero[pacm->y][((pacm->x)+1+ancho)%ancho]==0){
            tablero[pacm->y][pacm->x]=0;
            if (tablero[pacm->y][((pacm->x)+1+ancho)%ancho]==1) (pacm->extra)++; 
            pacm->x = ((pacm->x)+1+ancho)%ancho;
            tablero[pacm->y][pacm->x]=Pacman;
        }
        break;

    case 'w':
        if (tablero[((pacm->y)-1+largo)%largo][pacm->x]==1 || tablero[((pacm->y)-1+largo)%largo][pacm->x]==0){
            tablero[pacm->y][pacm->x]=0;
            if (tablero[((pacm->y)-1+largo)%largo][pacm->x]==1) (pacm->extra)++; 
            pacm->y = ((pacm->y)-1+largo)%largo;
            tablero[pacm->y][pacm->x]=Pacman;
        }
        break;

    case 's':
        if (tablero[((pacm->y)+1+largo)%largo][pacm->x]==1 || tablero[((pacm->y)+1+largo)%largo][pacm->x]==0){
            tablero[pacm->y][pacm->x]=0;
            if (tablero[((pacm->y)+1+largo)%largo][pacm->x]==1) (pacm->extra)++; 
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

void imprimir(int L, int A, int tablero[L][A]){
    printf("\n\n\n\n\n\n");
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < A; j++)
        {
            printf("%d ",tablero[i][j]);
        }
        printf("\n");
        
    }
    printf("\n\n");
}

typedef struct posicion posicion_t;
typedef struct fantasmas fantasmas_t;

int main(){
    srand(time(0));
    posicion_t Pm;
    fantasmas_t Fant_all;
    int tablero[10][10]={};//Esto se pide del anterior tablero
    tablero[3][3]=Pacman;
    Pm.x=3;
    Pm.y=3;
    char mov;
    int GameOver=0;
    int difficult=1;// 1 2 o 3, que el es el tiempo de espera a acción, o colocar el usleep(), que mide en milisegundos en vez de segundos
    while (!GameOver) {
        imprimir(10, 10, tablero);
        scanf(" %c", &mov);
        GameOver = !mov_Pacman(10, 10, tablero, mov, &Pm);
        mov_Fanta(10,10,tablero,&(Fant_all.Ft1));
        mov_Fanta(10,10,tablero,&(Fant_all.Ft2));
        mov_Fanta(10,10,tablero,&(Fant_all.Ft3));
        mov_Fanta(10,10,tablero,&(Fant_all.Ft4));
        sleep(difficult);
    }
}