// Este programa simula el juego de la ruleta europea.

//librerias
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
// fin librerias

//macros
#define terminal_formats_active  //para activar el formato de salida
#include "formats.h"
#define MAXIMO_RONDAS 20
#define DIMENSION 10

#ifdef __unix__ //para resetear la consola
  #define clear system("clear")
#elif 
  #define clear system("cls")
#endif
//fin macros


//prototipos de mis funciones
void ronda();
int apuestas(int ronda, int rondas);
int menu(int apuesta[], int cantidadFichas[], int ronda, int rondas);
int obtenerFicha(int *ficha);
void verificarFicha(int *ficha, int arreglo[], int contador);
int lanzarBola();
//fin prototipos de mis funciones

//funcion main
int main(void){
  printf(BLINK COLOR_172 BOLD_W "\t\t\t\tBIENVENIDO AL CASINO MEGA STAR\n" NORMAL_W DEFAULT_C);
  printf("\n");
  //semilla 
  srand(time(NULL));
  //funcion principal de mi programa
  ronda();
}
//fin funcion main


//-- DEFINICIONES DE FUNCIONES ---

//funcion principal de mi programa
void ronda(){
  int rondas;
  // aqui le preguntamos al usuario cuantas veces quiere jugar
  printf("\t\t\t\tMaximo numero de rondas: %d\n", MAXIMO_RONDAS);
  for(int i = 0; i < 1; i++){
    printf("\n");
    printf("\t\t\t¿Cuantas rondas usted va a jugar en esta mesa? ==>  ");
    scanf("%d", &rondas);
    printf("\n");

    if(rondas > 1 && rondas > 20){
      printf(RED_C BOLD_W "\t\t\tEl maximo de numero de rondas es %d, vuelva intentarlo\n" NORMAL_W DEFAULT_C, MAXIMO_RONDAS );
      i--;
    }else if(rondas == 0){
      printf("\t\t\t\t\tEl juego termino :c\n");
      printf("\n");
      return;
    }else{
      clear;
      printf("\n");
      printf("Que empiece las apuestas c: !!\n");
      printf("\n");
      // x  numeros de rondas indicadas por el usuario
      for(int i = 0; i < rondas; i++){
        printf("Usted jugará %d %s en la ruleta europea \n\n", rondas - i, (rondas > 1 ? "rondas" : "ronda"));
        apuestas(i, rondas);
      }
    }
  }
}
// fin de la funcion principal de mi programa

//segunda funcion principal
int apuestas(int ronda, int rondas){
  int apuesta[DIMENSION];
  int cantidadFichas[DIMENSION];
  menu(apuesta, cantidadFichas, ronda, rondas);
}
//fin segunda funcion principal

// tercera funcion principal
int menu(int apuesta[], int cantidadFichas[], int ronda, int rondas){
  int opcion = (-1);
  int contador = 0;
  int fichaElegida;
  int numeroDeBola = -1;

  do{
    clear;
    //menu de opciones 
    //printf("ganancias de la mesa: , perdidas de la mesa:")
    //printf("ganancias del jugador: , perdidas del jugador:")

    printf(""BOLD_W"Usted esta jugando la ronda %d/%d"NORMAL_W"\n\n", ronda + 1, rondas); 

    printf(""BOLD_W"Usted puede realizar %d apuestas"NORMAL_W"\n\n", 10 - contador); 
    printf("Seleccione su apuesta\n\n");
    //le decimos al usuario que cuantas apuestas le quedan   
    printf("- Ingrese un numero del "BOLD_W"0 al 39"NORMAL_W" para apostar a un "COLOR_131 BOLD_W"NÚMERO PLENO"NORMAL_W"\n");
    printf("- Ingrese "BOLD_W"40"NORMAL_W" para apostar a "BLUE_C BOLD_W "PARES" NORMAL_W" o "BOLD_W"41"NORMAL_W" para apostar a "COLOR_202 BOLD_W"IMPARES\n" NORMAL_W);
    printf("- Ingrese "BOLD_W"42"NORMAL_W" para apostar al color " RED_C BOLD_W"ROJO" NORMAL_W" o "BOLD_W"43"NORMAL_W" para apostar al color "WHITE_B BLACK_C "NEGRO" NORMAL_W DEFAULT_B DEFAULT_C"\n");
    printf("- Ingrese "BOLD_W"44"NORMAL_W" para apostar a los "COLOR_172 BOLD_W"PRIMEROS 12"NORMAL_W"\n");
    printf("- Ingrese "BOLD_W"45"NORMAL_W" para apostar a los "COLOR_14 BOLD_W"SEGUNDOS 12"NORMAL_W"\n");
    printf("- Ingrese "BOLD_W"46"NORMAL_W" para apostar a los "COLOR_118 BOLD_W"TERCEROS 12"NORMAL_W"\n");
    printf("- Ingrese "BOLD_W"47"NORMAL_W" para apostar a los "COLOR_83 BOLD_W"NÚMEROS FALTA"NORMAL_W" (1 al 18)\n");
    printf("- Ingrese "BOLD_W"48"NORMAL_W" para apostar a los "COLOR_170 BOLD_W"NÚMEROS PASA"NORMAL_W" (19 al 36 )\n");
    printf("- Ingrese "BOLD_W"49"NORMAL_W" para apostar a la "COLOR_198 BOLD_W"COLUMNA 1" NORMAL_W" (2 a 1)" WHITE_B NORMAL_W);
    printf("\n");
    printf("- Ingrese "BOLD_W"50"NORMAL_W" para apostar a la "COLOR_149 BOLD_W"COLUMNA 2"NORMAL_W" (2 a 1)\n");
    printf("- Ingrese "BOLD_W"51"NORMAL_W" para apostar a la "COLOR_30 BOLD_W"COLUMNA 3"NORMAL_W" (2 a 1)\n");
    printf("- Para dejar de apostar ingrese "BOLD_W"99"NORMAL_W".\n");
    printf("\n");
    printf("Su elección es ====>  ");
    scanf("%d", &opcion);
    
   // si simplemente elije un numero del 0 al 39 
   // entonces quiere decir que esta apostando a ese numero.
   if( 0 <= opcion  && opcion <= 39) {
    clear;
    printf("Ingrese el numero de fichas a apostar al %d de "COLOR_131 BOLD_W"NÚMERO PLENO:"NORMAL_W"\n \n", opcion);
    printf("\n");
    verificarFicha(&fichaElegida, cantidadFichas, contador);
   }else if(opcion == 40) {
    clear;
    printf("Ingrese el numero de fichas a apostar al %d de "BLUE_C BOLD_W "PARES:" NORMAL_W"\n \n", opcion);
    printf("\n");
    verificarFicha(&fichaElegida, cantidadFichas, contador);
   }else if(opcion == 41){
    clear;
    printf("Ingrese el numero de fichas a apostar al %d de "COLOR_202 BOLD_W"IMPARES:" NORMAL_W"\n \n", opcion);
    printf("\n");
    verificarFicha(&fichaElegida, cantidadFichas, contador);
   }else if(opcion == 42){
    clear; 
    printf("Ingrese el numero de fichas a apostar al %d de "RED_C BOLD_W"ROJO" NORMAL_W"\n \n", opcion);
    printf("\n");
    verificarFicha(&fichaElegida, cantidadFichas, contador);
   }else if(opcion == 43){
    clear;
    printf("Ingrese el numero de fichas a apostar al %d de "WHITE_B BLACK_C "NEGRO" NORMAL_W DEFAULT_B DEFAULT_C"\n\n", opcion);
    printf("\n");
    verificarFicha(&fichaElegida, cantidadFichas, contador);
   }else if(opcion == 44){
    clear;
    printf("Ingrese el numero de fichas a apostar al %d de "COLOR_172 BOLD_W"PRIMEROS 12"NORMAL_W"\n\n", opcion);
    printf("\n");
    verificarFicha(&fichaElegida, cantidadFichas, contador);
   }else if(opcion == 45){
    clear;
    printf("Ingrese el numero de fichas a apostar al %d de "COLOR_14 BOLD_W"SEGUNDOS 12"NORMAL_W"\n\n", opcion);
    printf("\n");
    verificarFicha(&fichaElegida, cantidadFichas, contador);
   }else if(opcion == 46){
    clear;
    printf("Ingrese el numero de fichas a apostar al %d de "COLOR_118 BOLD_W"TERCEROS 12"NORMAL_W"\n\n", opcion);
    printf("\n");
    verificarFicha(&fichaElegida, cantidadFichas, contador);
   }else if(opcion == 47){
    clear;
    printf("Ingrese el numero de fichas a apostar al %d de "COLOR_83 BOLD_W"NÚMEROS FALTA"NORMAL_W"\n\n", opcion);
    printf("\n");
    verificarFicha(&fichaElegida, cantidadFichas, contador);
   }else if(opcion == 48){
    clear;
    printf("Ingrese el numero de fichas a apostar al %d de "COLOR_170 BOLD_W"NÚMEROS PASA"NORMAL_W"\n\n", opcion);
    printf("\n");
    verificarFicha(&fichaElegida, cantidadFichas, contador);
   }else if(opcion == 49){
    clear;
    printf("Ingrese el numero de fichas a apostar al %d de "COLOR_198 BOLD_W"COLUMNA 1" NORMAL_W"\n\n", opcion);
    printf("\n");
    verificarFicha(&fichaElegida, cantidadFichas, contador);
   }else if(opcion == 50){
    clear;
    printf("Ingrese el numero de fichas a apostar al %d de "COLOR_149 BOLD_W"COLUMNA 2"NORMAL_W"\n\n", opcion);
    printf("\n");
    verificarFicha(&fichaElegida, cantidadFichas, contador);
   }else if(opcion == 51){
    clear;
    printf("Ingrese el numero de fichas a apostar al %d de "COLOR_30 BOLD_W"COLUMNA 3"NORMAL_W"\n\n", opcion);
    printf("\n");
    verificarFicha(&fichaElegida, cantidadFichas, contador);
   }else if(opcion == 99){

     // calcular el juego
   }else{
     printf(""RED_C BOLD_W"Ingrese una opcion correcta"NORMAL_W"\n");
     contador--;
     continue;
   }
   apuesta[contador] = opcion;
   contador++;

  }while(opcion != 99 && contador < 10);

    printf("\n\n\t\tNo va Mas!\n");
    printf("\n");
    printf(""COLOR_226 BOLD_W"Lanzamiento de la bola"NORMAL_W"\n");
    printf("\n");
    //lanzarBola
    numeroDeBola = lanzarBola();

}
// fin de la tercera funcion principal

//obtener ficha
int obtenerFicha(int *ficha){
  printf("Fichas que usted puede apostar: 1, 2, 5, 10, 50, 100\n\n");
  printf("Fichas ===> ");
  scanf("%d", ficha);
  return *ficha;
}
//fin de la funcion obtener ficha

// verificarFicha
void verificarFicha(int *ficha, int arreglo[], int contador){
  while (1) {
    obtenerFicha(ficha);
    // la ficha elegida debe ser distinto a cero , porque no puede apostar cero.
    if(*ficha > 0 ){
      arreglo[contador] = *ficha;
      //sale del bucle infinito
      break;
    }else{
      clear;
      printf("\n");
      printf(""RED_C BOLD_W"Ingrese un ficha mayor a cero"NORMAL_W"\n\n");
    }
  }
}
//fin de la funcion verificar ficha

// lanzar la bola
int lanzarBola(){
  int numeroRandom;
  numeroRandom = rand()%37;
  system("sleep 2s"); // retardo

  switch(numeroRandom){
    case 1: case 3: case 5: case 7: case 9: case 12:
    case 14: case 16: case 18: case 19: case 21: case 23:
    case 25: case 27: case 30: case 32: case 34: case 36:
      printf(RED_C BOLD_W"%d\n"NORMAL_W, numeroRandom);
      break;
    default:
      printf(BLACK_C BOLD_W"%d\n"NORMAL_W, numeroRandom);
  }
  return numeroRandom;
}