#include "movimientos.h"

//Funcion que recibe el arreglo y busca el numero de donde está el ente pedido al llamar
void ingresar_posiciones(struct posicion *ente, int largo, int ancho, int **tablero,int num_ente){
    for (int i = 0; i < largo; i++) {
        for (int j = 0; j < ancho; j++){
            if (tablero[i][j]==num_ente){ //Si corresponde el numero a la identificacion del ente se ingresan en la estructura correspondiente
                ente->x=j;
                ente->y=i;            
            }
        }
    }   
}

//Funcion que verifica si en el siguiente movimiento está el fantasma
int verificar(struct posicion *Pman, struct posicion *Ftma, int fnt_mov, int largo, int ancho){ 
    //Switch que en va simulando cada movimiento, arriba, abajo ,derecha e izquierda
    switch (fnt_mov){
        case 0:
            if ((Pman->x == Ftma->x) && (Pman->y == (Ftma->y)-1+largo)%largo)
            return 1;
        case 1:
            if ((Pman->x == Ftma->x) && (Pman->y == ((Ftma->y)+1+largo)%largo))
            return 1;
        case 2:
            if ((Pman->x == ((Ftma->x)+1+ancho)%ancho) && (Pman->y == Ftma->y))
            return 1;
        case 3:
            if ((Pman->x == ((Ftma->x)-1+ancho)%ancho) && (Pman->y == Ftma->y))
            return 1;
        default:
            break;
        }
    return 0;
}

//Función que verifica si cuando Pacman se mueve a cierta dirección existe alguno de los 4 fantasmas
int verificar_todos(struct posicion *Pman, struct fantasmas *Enemys, int mov, int largo, int ancho) {
    switch (mov) {
    case '0': //Verificacion hacia Arriba
        if (Pman->x == Enemys->Ft1.x && ((Pman->y)-1+largo)%largo == Enemys->Ft1.y) {
            return 1;
        }
        if (Pman->x == Enemys->Ft2.x && ((Pman->y)-1+largo)%largo == Enemys->Ft2.y) {
            return 1;
        }
        if (Pman->x == Enemys->Ft3.x && ((Pman->y)-1+largo)%largo == Enemys->Ft3.y) {
            return 1;
        }
        if (Pman->x == Enemys->Ft4.x && ((Pman->y)-1+largo)%largo == Enemys->Ft4.y) {
            return 1;
        }
            break;
    case '1': //Verificacion hacia abajo
        if (Pman->x == Enemys->Ft1.x && ((Pman->y)+1+largo)%largo == Enemys->Ft1.y) {
            return 1;
        }
        if (Pman->x == Enemys->Ft2.x && ((Pman->y)+1+largo)%largo == Enemys->Ft2.y) {
            return 1;
        }
        if (Pman->x == Enemys->Ft3.x && ((Pman->y)+1+largo)%largo == Enemys->Ft3.y) {
            return 1;
        }
        if (Pman->x == Enemys->Ft4.x && ((Pman->y)+1+largo)%largo == Enemys->Ft4.y) {
            return 1;
        }
            break;
    case '2': //Verificacion hacia la Derecha
        if (((Pman->x)+1+ancho)%ancho == Enemys->Ft1.x && Pman->y == Enemys->Ft1.y) {
            return 1;
        }
        if (((Pman->x)+1+ancho)%ancho == Enemys->Ft2.x && Pman->y == Enemys->Ft2.y) {
            return 1;
        }
        if (((Pman->x)+1+ancho)%ancho == Enemys->Ft3.x && Pman->y == Enemys->Ft3.y) {
            return 1;
        }
        if (((Pman->x)+1+ancho)%ancho == Enemys->Ft4.x && Pman->y == Enemys->Ft4.y) {
            return 1;
        }
            break;
    case '3': //Verificacion hacia la Izquierda
        if (((Pman->x)-1+ancho)%ancho == Enemys->Ft1.x && Pman->y == Enemys->Ft1.y) {
            return 1;
        }
        if (((Pman->x)-1+ancho)%ancho == Enemys->Ft2.x && Pman->y == Enemys->Ft2.y) {
            return 0;
        }
        if (((Pman->x)-1+ancho)%ancho == Enemys->Ft3.x && Pman->y == Enemys->Ft3.y) {
            return 0;
        }
        if (((Pman->x)-1+ancho)%ancho == Enemys->Ft4.x && Pman->y == Enemys->Ft4.y) {
            return 0;
        }
            break;   
    default:
        break;
    }
    return 0;
}

//Función que emula el movimiento aleatorio del fantasma
int mov_Fanta(int largo, int ancho, int **tablero, struct posicion *fant, struct posicion *Pma ,int num_ente ){
    int mov_aleatorio = rand()%4;

    switch (mov_aleatorio){
 
    case 0: //Movimiento hacia Arriba
        if (verificar(Pma, fant, 0, largo, ancho)){
            return 0;
        } else if (tablero[((fant->y)-1+largo)%largo][fant->x]==7 || tablero[((fant->y)-1+largo)%largo][fant->x]==0 || tablero[((fant->y)-1+largo)%largo][fant->x]==8){
            tablero[fant->y][fant->x]= fant->extra;
            if (tablero[((fant->y)-1+largo)%largo][fant->x]==7) fant->extra=7; 
            else if (tablero[((fant->y)-1+largo)%largo][fant->x]==8) fant->extra=8; 
            else fant->extra=0;
            fant->y = ((fant->y)-1+largo)%largo;
            tablero[fant->y][fant->x]=num_ente;
        }
        break;

    case 1: //Movimiento hacia Abajo
        if (verificar(Pma, fant, 1, largo ,ancho)){
            return 0;
        } else if (tablero[((fant->y)+1+largo)%largo][fant->x]==7 || tablero[((fant->y)+1+largo)%largo][fant->x]==0 || tablero[((fant->y)+1+largo)%largo][fant->x]==8){
            tablero[fant->y][fant->x]= fant->extra;
            if (tablero[((fant->y)+1+largo)%largo][fant->x]==7) fant->extra=7;
            else if (tablero[((fant->y)+1+largo)%largo][fant->x]==8) fant->extra=8;
            else fant->extra=0;
            fant->y = ((fant->y)+1+largo)%largo;
            tablero[fant->y][fant->x]=num_ente;
        }
        break;

    case 2: //Movimiento hacia la Derecha
        if (verificar(Pma, fant, 2, largo, ancho)){
            return 0;
        } else if (tablero[fant->y][((fant->x)+1+ancho)%ancho]==7 || tablero[fant->y][((fant->x)+1+ancho)%ancho]==0 || tablero[fant->y][((fant->x)+1+ancho)%ancho]==8){
            tablero[fant->y][fant->x]= fant->extra;
            if (tablero[fant->y][((fant->x)+1+ancho)%ancho]==7) fant->extra=7; 
            else if (tablero[fant->y][((fant->x)+1+ancho)%ancho]==8) fant->extra=8;
            else fant->extra=0;
            fant->x = ((fant->x)+1+ancho)%ancho;
            tablero[fant->y][fant->x]=num_ente;
        }
        break;

    case 3: //Movimiento hacia la Izquierda
        if (verificar(Pma, fant, 3, largo, ancho)){
            return 0;
        } else if (tablero[fant->y][((fant->x)-1+ancho)%ancho]==7 || tablero[fant->y][((fant->x)-1+ancho)%ancho]==0 || tablero[fant->y][((fant->x)-1+ancho)%ancho]==8){
            tablero[fant->y][fant->x]= fant->extra;
            if (tablero[fant->y][((fant->x)-1+ancho)%ancho]==7) fant->extra=7;
            else if (tablero[fant->y][((fant->x)-1+ancho)%ancho]==8) fant->extra=8;  
            else fant->extra=0;
            fant->x = ((fant->x)-1+ancho)%ancho;
            tablero[fant->y][fant->x]=num_ente;
        }
        break;

    default:
        break;
    }

    return 1;
}

//Funcion que hace el pacman
int mov_Pacman(int largo, int ancho ,int **tablero ,int move ,struct posicion *pacm, struct fantasmas *enemy){
    move=tolower(move);
    switch (move){
        case 'a': //Movimiento hacia la Izquierda
            if (verificar_todos(pacm,enemy,3,largo,ancho)){
                return 0;
            } else if (tablero[pacm->y][((pacm->x)-1+ancho)%ancho]==7 || tablero[pacm->y][((pacm->x)-1+ancho)%ancho]==0 || tablero[pacm->y][((pacm->x)-1+ancho)%ancho]==8){
            tablero[pacm->y][pacm->x]=0;
            if (tablero[pacm->y][((pacm->x)-1+ancho)%ancho]==7) (pacm->extra)+=10; 
            else if (tablero[pacm->y][((pacm->x)-1+ancho)%ancho]==8) (pacm->extra)+=50; 
            pacm->x = ((pacm->x)-1+ancho)%ancho;
            tablero[pacm->y][pacm->x]=2;
            }
            break;
        
        case 'd': //Movimiento hacia la Derecha
            if (verificar_todos(pacm,enemy,2,largo,ancho)){ 
                    return 0;
            } else if (tablero[pacm->y][((pacm->x)+1+ancho)%ancho]==7 || tablero[pacm->y][((pacm->x)+1+ancho)%ancho]==0 || tablero[pacm->y][((pacm->x)+1+ancho)%ancho]==8){
                tablero[pacm->y][pacm->x]=0;
                if (tablero[pacm->y][((pacm->x)+1+ancho)%ancho]==7) (pacm->extra)+=10; 
                else if (tablero[pacm->y][((pacm->x)+1+ancho)%ancho]==8) (pacm->extra)+=50; 
                pacm->x = ((pacm->x)+1+ancho)%ancho;
                tablero[pacm->y][pacm->x]=2;
            }
            break;

        case 'w': //Movimiento hacia Arriba
            if (verificar_todos(pacm,enemy,0,largo,ancho)){
                    return 0;
            } else if (tablero[((pacm->y)-1+largo)%largo][pacm->x]==7 || tablero[((pacm->y)-1+largo)%largo][pacm->x]==0 || tablero[((pacm->y)-1+largo)%largo][pacm->x]==8){
                tablero[pacm->y][pacm->x]=0;
                if (tablero[((pacm->y)-1+largo)%largo][pacm->x]==7) (pacm->extra)+=10; 
                else if (tablero[((pacm->y)-1+largo)%largo][pacm->x]==8) (pacm->extra)+=50; 
                pacm->y = ((pacm->y)-1+largo)%largo;
                tablero[pacm->y][pacm->x]=2;
            }
            break;

        case 's': //Movimiento hacia Abajo
            if (verificar_todos(pacm,enemy,1,largo,ancho)){
                    return 0;
            } else if (tablero[((pacm->y)+1+largo)%largo][pacm->x]==7 || tablero[((pacm->y)+1+largo)%largo][pacm->x]==0 || tablero[((pacm->y)+1+largo)%largo][pacm->x]==8){
                tablero[pacm->y][pacm->x]=0;
                if (tablero[((pacm->y)+1+largo)%largo][pacm->x]==7) (pacm->extra)+=10; 
                else if (tablero[((pacm->y)+1+largo)%largo][pacm->x]==8) (pacm->extra)+=50; 
                pacm->y = ((pacm->y)+1+largo)%largo;
                tablero[pacm->y][pacm->x]=2;
            }
            break;

        case 'p':
            return 0;
        default:
            break;
        }
    return 1;
}
