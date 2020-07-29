
#include "funciones.h"

#include <stdio.h>
#include <stdlib.h>
#define terminal_formats_active  //para activar el formato de salida
#include "formats.h"


// verificarFicha
void verificarFicha(int *ficha, int arreglo[], int contador, int opcion){
  while (1) {
    obtenerFicha(ficha);
    // la ficha elegida debe ser distinto a cero , porque no puede apostar cero.
    if(*ficha > 0 ){
      arreglo[contador] = *ficha;
      
      if(
        opcion == 44 || opcion == 45 || 
        opcion == 39 || opcion == 40 || 
        opcion == 37 || opcion == 38 
      ) {
        int resultado;
        resultado = perteneceArr(*ficha, arreglo, contador);

        if(resultado == 1){
          clear;
          printf("El valor %d ya ha sido usado en una apuesta con ganancia doble, por favor ingrese una valor diferente\n", *ficha);
         continue;
        }
      }

      break;
    }else{
      clear;
      printf("\n");
      printf(RED_C BOLD_W"Ingrese una cantidad de fichas mayor a cero\n\n"NORMAL_W);
    }
  }
}
//fin de la funcion verificar ficha

//numero es rojo
int numeroEsRojo(int numero){
  switch(numero){
    case 1: case 3: case 5: case 7: case 9: case 12:
    case 14: case 16: case 18: case 19: case 21: case 23:
    case 25: case 27: case 30: case 32: case 34: case 36:
      return 1;
    default:
      return 0;
  }
}
// fin de la funcion numero es rojo

// lanzar la bola
int lanzarBola(){
  int numeroRandom;
  numeroRandom = rand()%37;
  system("sleep 2s"); // retardo

  printf(
    "y el numero que sale en la ruleta es  ==> %s %d\n\n" NORMAL_W DEFAULT_C,
    (numeroEsRojo(numeroRandom) ? RED_C BOLD_W : BLACK_C BOLD_W WHITE_B), numeroRandom
  );
  return numeroRandom;
}
// fin de la funcion de lanzar bola

//funcion pertenece
int perteneceArr(int ficha, int arreglo[], int limite){
   for( int i = 0; i < limite ; i++){
    if(arreglo[i] == ficha){
      return 1;     
    }
  }
  return 0;
}
// fin de la funcion pertenece

//obtener ficha
int obtenerFicha(int *ficha){
  int input;
  int suma=0;
  do {
    printf("Usted puede ingresar las siguientes fichas: 1, 2, 5, 10, 50, 100.\n"MAGENTA_C BOLD_W"Para terminar la carga, ingrese 0."NORMAL_W"\n");
    printf("Total cargado %d.\n", suma);
    printf("Ingrese ficha ===> ");
    scanf("%d", &input);
    if(input == 0 ){
      break;
    } else if (input == 1 || input == 2 || input == 5 || input == 10 || input == 50 || input == 100){
      suma +=  input;
      clear;
    } else {
      clear;
      printf(RED_C BOLD_W"Ingrese una ficha correcta.\n"NORMAL_W);
    }  
  } while (1);
  *ficha = suma;
  return *ficha;
}
//fin de la funcion obtener ficha

int contarColor(int arreglo[], int dimension) {
  int contador = 1;
  int ultimoEsRojo;

  for (int i=1; i<dimension; i++ ) {
    ultimoEsRojo = numeroEsRojo(arreglo[i]);
    if(ultimoEsRojo != numeroEsRojo(arreglo[i-1])){
      contador =0;
    }
    contador ++;
    if(contador == 5){
      return ultimoEsRojo;
    }
  }
  return -1;
}

int contarPrimos(int arreglo[], int dimension) {
  int contador = 0;

  for (int i = 0; i < dimension; i++){
    if(esPrimo(arreglo[i])){
      contador ++;
    }
  }
 
  return contador;
}

int esPrimo (int numero) {
  
  for(int i = 2; i< numero; i++){
    if(numero%i == 0){
      return 0;
    }
  }
  
  return 1;
}