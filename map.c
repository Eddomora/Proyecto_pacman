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
  
  while (1) {
    e = fgetc(file);
    if(isdigit(e)){// Iniciamos un ciclo hasta que la lectura no sea exitosa 
      (*c)++;}
    else if (e =='\n' || e == EOF) {                      // Sumamos uno al contador por cada elemento encontrado hasta el salto de linea, para obtener las columnas
      return;  
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
