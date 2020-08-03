
#include "funciones.h"

#include <stdio.h>
#include <stdlib.h>
#define terminal_formats_active  //para activar el formato de salida
#include "formats.h"


int esApuestaConGanaciaDoble(int opcion) {
  return  opcion == 44 || opcion == 45 || 
    opcion == 39 || opcion == 40 || 
    opcion == 37 || opcion == 38 ; 
}

// verificarFicha
void pedir_verificarFicha(int arreglo[], int contador, int opcion,int apuestas []){
  int ficha;
  while (1) {
    obtenerFicha(&ficha);
    // la ficha elegida debe ser distinto a cero , porque no puede apostar cero.
    if(ficha > 0 ){
      arreglo[contador] = ficha;
      
      if(esApuestaConGanaciaDoble(opcion)) {
        int resultado;
        resultado = perteneceArrYApuestaDoble(ficha, arreglo, contador, apuestas);
        // si la ficha pertenece
        if(resultado == 1){
          clear;
          printf(BACKGROUND_RED WHITE BOLD_W"El valor %d ya ha sido usado en una apuesta con ganancia doble, por favor ingrese una valor diferente\n\n" NORMAL_W, ficha);
         continue;
        }
      }

      break;
    }else{
      clear;
      printf(RED_C BOLD_W"\nIngrese una cantidad de fichas mayor a cero\n\n"NORMAL_W);
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
      return 1; // si es rojo
      break;
    case 0:
     return -1; // no es ninguno de los dos 
    default:
      return 0; // no es rojo
  }
}
// fin de la funcion numero es rojo

// lanzar la bola
int lanzarBola(){
  int numeroRandom;
  numeroRandom = 12;// rand()%37;
  system("sleep 2s"); // retardo de 2s

  printf(
    "y el numero que sale en la ruleta es  ==> %s %d\n\n" NORMAL_W DEFAULT_C,
    (numeroEsRojo(numeroRandom) ? RED_C BOLD_W : BLACK_C BOLD_W WHITE_B), numeroRandom
    // si es true el numero se imprime de color rojo si no se imprime de color negro
  );
  return numeroRandom;
}
// fin de la funcion de lanzar bola

//funcion pertenece
int perteneceArrYApuestaDoble(int ficha, int arreglo[], int limite, int apuestas[]){
   for( int i = 0; i < limite ; i++){
    if(arreglo[i] == ficha && esApuestaConGanaciaDoble(apuestas[i])){
      return 1; // pertenece     
    }
  }
  return 0; // no pertenece
}
// fin de la funcion pertenece

//obtener ficha      // le paso un puntero , donde se va guardar la ficha obtenida
void obtenerFicha(int *ficha){
  int input;
  int suma = 0;

  do {
    printf("Usted puede ingresar las siguientes fichas: 1, 2, 5, 10, 50, 100.\n"MAGENTA_C BOLD_W"Para terminar la carga, ingrese 0."NORMAL_W"\n");
    printf("Total cargado %d.\n\n", suma);
    printf("Ingrese ficha ===> ");
    scanf("%d", &input);
    if(input == 0 ){
      break;
    } else if (input == 1 || input == 2 || input == 5 || input == 10 || input == 50 || input == 100){
      suma +=  input;
      clear;
    } else {
      clear;
      printf(RED_C BOLD_W"\nIngrese una ficha correcta.\n\n"NORMAL_W);
    }  
  } while (1); // se puede equivocar o se puede seguir ingresando fichas, en el programa no estblecis limite de fichas
  *ficha = suma;
}
//fin de la funcion obtener ficha

int contarColor(int arreglo[], int dimension) {
  int contadorRojo = 1;
  int contadorNegro = 1;
  int ultimoNumero;
  
  for (int i=1; i < dimension; i++ ) {

    ultimoNumero = numeroEsRojo(arreglo[i]);
    if(ultimoNumero != numeroEsRojo(arreglo[i-1])){
      // se resetea el contador si el contador rojo o negro es menor a 5
      if (contadorRojo < 5){
        contadorRojo = 0;
      }
      if (contadorNegro < 5) {
        contadorNegro = 0;
      }
    }
    if(ultimoNumero) {
      contadorRojo ++;
    }else {
      contadorNegro++;
    }  
  }

  if(contadorRojo > 5 && contadorNegro > 5){
    return 2; 
  }else if(contadorRojo > 5 || contadorNegro > 5){
    return ultimoNumero; 
  }
  return -1; // no aparece mas de 5 veces
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