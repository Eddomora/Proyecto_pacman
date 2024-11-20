#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <ctype.h>
#include <unistd.h>


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

int verificar(struct posicion *Pman, struct posicion *Ftma, int fnt_mov){ 
    switch (fnt_mov){
    case 0:
        if ((Pman->x == Ftma->x) && (Pman->y == Ftma->y-1))
        return 1;
    case 1:
        if ((Pman->x == Ftma->x) && (Pman->y == Ftma->y+1))
        return 1;
    case 2:
        if ((Pman->x == Ftma->x+1) && (Pman->y == Ftma->y))
        return 1;
    case 3:
        if ((Pman->x == Ftma->x-1) && (Pman->y == Ftma->y))
        return 1;
    default:
        break;
    }
    return 0;
}


void pos_inicial(int largo, int ancho, int tablero[largo][ancho],struct posicion *PM , struct fantasmas *All_enemies){
//guarda el lugar inicial
}



int mov_Fanta(int largo, int ancho, int tablero[largo][ancho], struct posicion *fant, struct posicion *Pma ){
    int mov_aleatorio = rand()%4;

    switch (mov_aleatorio){
 
    case 0:
        if (verificar(Pma, fant, 0)){
            return 0;
        } else if (tablero[((fant->y)-1+largo)%largo][fant->x]==1 || tablero[((fant->y)-1+largo)%largo][fant->x]==0){
            tablero[fant->y][fant->x]= fant->extra;
            if (tablero[((fant->y)-1+largo)%largo][fant->x]==1) fant->extra=1; 
            else fant->extra=0;
            fant->y = ((fant->y)-1+largo)%largo;
            tablero[fant->y][fant->x]=Fantasma;
        }
        break;

    case 1:

        if (verificar(Pma, fant, 1)){
            return 0;
        } else if (tablero[((fant->y)+1+largo)%largo][fant->x]==1 || tablero[((fant->y)+1+largo)%largo][fant->x]==0){
            tablero[fant->y][fant->x]= fant->extra;
            if (tablero[((fant->y)+1+largo)%largo][fant->x]==1) fant->extra=1; 
            else fant->extra=0;
            fant->y = ((fant->y)+1+largo)%largo;
            tablero[fant->y][fant->x]=Fantasma;
        }
        break;

    case 2:
        if (verificar(Pma, fant, 2)){
            return 0;
        } else if (tablero[fant->y][((fant->x)+1+ancho)%ancho]==1 || tablero[fant->y][((fant->x)+1+ancho)%ancho]==0){
            tablero[fant->y][fant->x]= fant->extra;
            if (tablero[fant->y][((fant->x)+1+ancho)%ancho]==1) fant->extra=1; 
            else fant->extra=0;
            fant->x = ((fant->x)+1+ancho)%ancho;
            tablero[fant->y][fant->x]=Fantasma;
        }
        break;

    case 3:
        if (verificar(Pma, fant, 3)){
            return 0;
        } else if (tablero[fant->y][((fant->x)-1+ancho)%ancho]==1 || tablero[fant->y][((fant->x)-1+ancho)%ancho]==0){
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

    return 1;
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
    int tablero[10][10]={0};//Esto se pide del anterior tablero
    tablero[3][3]=Pacman; //Esto igual
//Todo esto igual
    Pm.x=3; Pm.y=3; Pm.extra=0;

    Fant_all.Ft1.x=6; Fant_all.Ft1.y=6; Fant_all.Ft1.extra=1;
    Fant_all.Ft2.x=7; Fant_all.Ft2.y=6; Fant_all.Ft2.extra=1;
    Fant_all.Ft3.x=1; Fant_all.Ft3.y=6; Fant_all.Ft3.extra=1;
    Fant_all.Ft4.x=5; Fant_all.Ft4.y=6; Fant_all.Ft4.extra=1;

    tablero[Fant_all.Ft1.y][Fant_all.Ft1.x] = Fantasma;
    tablero[Fant_all.Ft2.y][Fant_all.Ft2.x] = Fantasma;
    tablero[Fant_all.Ft3.y][Fant_all.Ft3.x] = Fantasma;
    tablero[Fant_all.Ft4.y][Fant_all.Ft4.x] = Fantasma;
    
    char mov,fm1=0,fm2=0,fm3=0,fm4=0;
    int GameOver=0;
    //int difficult=1; 1 2 o 3, que el es el tiempo de espera a acción, o colocar el usleep(), que mide en milisegundos en vez de segundos
    while (!GameOver && !fm1 && !fm2 && !fm3 && !fm4 ) {
        imprimir(10, 10, tablero);
        scanf(" %c", &mov);
        GameOver = !mov_Pacman(10, 10, tablero, mov, &Pm);
        fm1 = !mov_Fanta(10,10,tablero,&(Fant_all.Ft1),&Pm);
        fm2 = !mov_Fanta(10,10,tablero,&(Fant_all.Ft2),&Pm);
        fm3 = !mov_Fanta(10,10,tablero,&(Fant_all.Ft3),&Pm);
        fm4 = !mov_Fanta(10,10,tablero,&(Fant_all.Ft4),&Pm);
        //sleep(difficult);
    }
    printf("\nPuntaje total: %d",Pm.extra);
}
/*
switch (mov) {
    case 'w':
        GameOver = !mov_Pacman(10, 10, tablero, w, &Pm);
        //render
        //cambio a arriba el pacman
        break;
    case 's':
        GameOver = !mov_Pacman(10, 10, tablero, s, &Pm);
        //render
        //cambio a abajo el pacman
        break;
    case 'a':
        GameOver = !mov_Pacman(10, 10, tablero, a, &Pm);
        //render
        //cambio a izq el pacman
        break;
    case 'd':
        GameOver = !mov_Pacman(10, 10, tablero, d, &Pm);
        //render
        //cambio a derecha el pacman
        break;

    default:
        break;
}
*/
