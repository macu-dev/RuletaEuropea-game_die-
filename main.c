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

int numerosGanadores[MAXIMO_RONDAS];
int gananciasPorRonda[MAXIMO_RONDAS];
int perdidasPorRondas[MAXIMO_RONDAS];
int totalGanacias = 0;
int totalPerdidas = 0;

//prototipos de mis funciones
void ronda();
int apuestas(int ronda, int rondas);
int menu(int apuesta[], int cantidadFichas[], int ronda, int rondas);
int obtenerFicha(int *ficha);
void verificarFicha(int *ficha, int arreglo[], int contador);
int lanzarBola();
int numeroEsRojo(int numero);
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

    if(rondas < 1 || rondas > 20){
      printf(RED_C BOLD_W "\t\t\tEl maximo de numero de rondas es %d, vuelva intentarlo\n" NORMAL_W DEFAULT_C, MAXIMO_RONDAS );
      i--;
    }else{
      clear;
      printf("\n");
      printf("Que empiece las apuestas c: !!\n");
      printf("\n");
      // x  numeros de rondas indicadas por el usuario
      printf("Usted jugará %d %s en la ruleta europea \n\n", rondas, (rondas > 1 ? "rondas" : "ronda"));
      // bucle de las apuestas
      for(int i = 0; i < rondas; i++){
        apuestas(i, rondas);
        totalGanacias += gananciasPorRonda[i];
        totalPerdidas += perdidasPorRondas[i];
      }

     printf(
       "\nLa Mesa tuvo una ganancia de %d fichas, y una perdida de %d fichas en el juego.\n",
       totalPerdidas, totalGanacias
     );

    printf("Gracias por jugar!.");

    }
  }
}
// fin de la funcion principal de mi programa

//segunda funcion principal
int apuestas(int ronda, int rondas){
  int apuesta[DIMENSION];
  int cantidadFichas[DIMENSION];
  int numeroDeBola = -1;

  menu(apuesta, cantidadFichas, ronda, rondas);

  clear;
  printf("\n\n\t\tNo va Mas!\n");
  printf("\n");
  printf(COLOR_226 BOLD_W"Lanzamiento de la bola\n"NORMAL_W );
  printf("\n");
  //lanzarBola
  numeroDeBola = lanzarBola();

  //guardamos el numero que salio ganador en la ronda
  numerosGanadores[ronda] = numeroDeBola;
  gananciasPorRonda[ronda] = 0;
  perdidasPorRondas[ronda] = 0;

  //recorre las apuestas y contabiliza(suma) las ganacias y perdidas del JUGADOR.
   for (int i = 0; apuesta[i] != 99 && i < DIMENSION; i++){
     if(apuesta[i] >=0 && apuesta[i] <= 36 ){
       //pleno
      if(apuesta[i] == numeroDeBola){
        gananciasPorRonda[ronda] += cantidadFichas[i] * 35;
      }else{
        perdidasPorRondas[ronda] += cantidadFichas[i];
      }
     }else if(
       apuesta[i] == 41 || apuesta[i] == 42 || apuesta[i] == 43 || // docenas
       apuesta[i] == 46 || apuesta[i] == 47 || apuesta[i] == 48    // Columnas
     ){
       // docenas y columnas
        if(
           (apuesta[i] == 41 && 1 <=numeroDeBola && numeroDeBola <=12) ||
           (apuesta[i] == 42 && 13 <=numeroDeBola && numeroDeBola <=24) ||
           (apuesta[i] == 43 && 25 <=numeroDeBola && numeroDeBola <=36) ||
           (apuesta[i] == 46 && (numeroDeBola-1)%3 == 0) ||
           (apuesta[i] == 47 && (numeroDeBola-2)%3 == 0) ||
           (apuesta[i] == 48 && (numeroDeBola-3)%3 == 0)
        ){
          gananciasPorRonda[ronda] += cantidadFichas[i] * 3;
        }else{
          perdidasPorRondas[ronda] += cantidadFichas[i];
        }
     }else if (
       apuesta[i] == 37 || apuesta[i] == 38 || // pares/impares
       apuesta[i] == 39 || apuesta[i] == 40 || // rojo/negro
       apuesta[i] == 44 || apuesta[i] == 45    // falta/pasa
      ){
       // rojo/negro par/impar 
        if(
           (apuesta[i] == 37 && numeroDeBola%2 == 0)                   || // pares
           (apuesta[i] == 38 && (numeroDeBola)%2 == 1)                 || // impares
           (apuesta[i] == 39 && numeroEsRojo(numeroDeBola))            || // rojo
           (apuesta[i] == 40 && !numeroEsRojo(numeroDeBola))           || // negro
           (apuesta[i] == 44 && 1<= numeroDeBola && numeroDeBola <=18) || // falta
           (apuesta[i] == 45 && 19<=numeroDeBola && numeroDeBola <=36)    // pasa
        ){
          gananciasPorRonda[ronda] += cantidadFichas[i] * 2;
        }else{
          perdidasPorRondas[ronda] += cantidadFichas[i];
        }
     }
     
   }
   
   printf(
     "La Mesa tuvo una ganancia de %d fichas, y una perdida de %d fichas en la ronda %d.\n",
     perdidasPorRondas[ronda], gananciasPorRonda[ronda], ronda+1
     );

}
//fin segunda funcion principal

// tercera funcion principal
int menu(int apuesta[], int cantidadFichas[], int ronda, int rondas){
  int opcion = (-1);
  int contador = 0;
  int fichaElegida;

  do{
    //menu de opciones 

    printf(BOLD_W"Usted esta jugando la ronda %d/%d\n\n"NORMAL_W, ronda + 1, rondas);
    printf(BOLD_W"Usted puede realizar %d apuestas\n\n"NORMAL_W, 10 - contador);

    printf("Seleccione su apuesta\n\n");
    //le decimos al usuario que cuantas apuestas le quedan   
    printf(
      "- Ingrese un numero del "BOLD_W"0 al 36"NORMAL_W" para apostar a un "COLOR_131 BOLD_W"NÚMERO PLENO"NORMAL_W"\n"
      "- Ingrese "BOLD_W"37"NORMAL_W" para apostar a "BLUE_C BOLD_W "PARES" NORMAL_W" o "BOLD_W"38"NORMAL_W" para apostar a "COLOR_202 BOLD_W"IMPARES\n" NORMAL_W
      "- Ingrese "BOLD_W"39"NORMAL_W" para apostar al color " RED_C BOLD_W"ROJO" NORMAL_W" o "BOLD_W"40"NORMAL_W" para apostar al color "WHITE_B BLACK_C "NEGRO" NORMAL_W DEFAULT_B DEFAULT_C"\n"
      "- Ingrese "BOLD_W"41"NORMAL_W" para apostar a los "COLOR_172 BOLD_W"PRIMEROS 12"NORMAL_W"\n"
      "- Ingrese "BOLD_W"42"NORMAL_W" para apostar a los "COLOR_14 BOLD_W"SEGUNDOS 12"NORMAL_W"\n"
      "- Ingrese "BOLD_W"43"NORMAL_W" para apostar a los "COLOR_118 BOLD_W"TERCEROS 12"NORMAL_W"\n"
      "- Ingrese "BOLD_W"44"NORMAL_W" para apostar a los "COLOR_83 BOLD_W"NÚMEROS FALTA"NORMAL_W" (1 al 18)\n"
      "- Ingrese "BOLD_W"45"NORMAL_W" para apostar a los "COLOR_170 BOLD_W"NÚMEROS PASA"NORMAL_W" (19 al 36 )\n"
      "- Ingrese "BOLD_W"46"NORMAL_W" para apostar a la "COLOR_198 BOLD_W"COLUMNA 1" NORMAL_W" (2 a 1)" WHITE_B NORMAL_W
      "\n"
      "- Ingrese "BOLD_W"47"NORMAL_W" para apostar a la "COLOR_149 BOLD_W"COLUMNA 2"NORMAL_W" (2 a 1)\n"
      "- Ingrese "BOLD_W"48"NORMAL_W" para apostar a la "COLOR_30 BOLD_W"COLUMNA 3"NORMAL_W" (2 a 1)\n"
      "- Para dejar de apostar ingrese "BOLD_W"99"NORMAL_W".\n"
      "\n"
    );

    printf("Su elección es ====>  ");
    scanf("%d", &opcion);
    
   // si simplemente elije un numero del 0 al 39 
   // entonces quiere decir que esta apostando a ese numero.
   if( opcion >= 0  && opcion <= 36) {
     clear;
     printf("Ingrese el numero de fichas a apostar al %d de "COLOR_131 BOLD_W"NÚMERO PLENO:"NORMAL_W"\n\n\n", opcion);
     verificarFicha(&fichaElegida, cantidadFichas, contador);
     clear;
   }else if(opcion == 37) {
     clear;
     printf("Ingrese el numero de fichas a apostar al %d de "BLUE_C BOLD_W "PARES:" NORMAL_W"\n\n\n", opcion);
     verificarFicha(&fichaElegida, cantidadFichas, contador);
     clear;
   }else if(opcion == 38){
     clear;
     printf("Ingrese el numero de fichas a apostar al %d de "COLOR_202 BOLD_W"IMPARES:" NORMAL_W"\n \n", opcion);
     printf("\n");
     verificarFicha(&fichaElegida, cantidadFichas, contador);
     clear;
   }else if(opcion == 39){
     clear; 
     printf("Ingrese el numero de fichas a apostar al %d de "RED_C BOLD_W"ROJO" NORMAL_W"\n \n", opcion);
     printf("\n");
     verificarFicha(&fichaElegida, cantidadFichas, contador);
     clear;
   }else if(opcion == 40){
     clear;
     printf("Ingrese el numero de fichas a apostar al %d de "WHITE_B BLACK_C "NEGRO" NORMAL_W DEFAULT_B DEFAULT_C"\n\n", opcion);
     printf("\n");
     verificarFicha(&fichaElegida, cantidadFichas, contador);
     clear;
   }else if(opcion == 41){
     clear;
     printf("Ingrese el numero de fichas a apostar al %d de "COLOR_172 BOLD_W"PRIMEROS 12"NORMAL_W"\n\n", opcion);
     printf("\n");
     verificarFicha(&fichaElegida, cantidadFichas, contador);
     clear;
   }else if(opcion == 42){
     clear;
     printf("Ingrese el numero de fichas a apostar al %d de "COLOR_14 BOLD_W"SEGUNDOS 12"NORMAL_W"\n\n", opcion);
     printf("\n");
     verificarFicha(&fichaElegida, cantidadFichas, contador);
     clear;
   }else if(opcion == 43){
     clear;
     printf("Ingrese el numero de fichas a apostar al %d de "COLOR_118 BOLD_W"TERCEROS 12"NORMAL_W"\n\n", opcion);
     printf("\n");
     verificarFicha(&fichaElegida, cantidadFichas, contador);
     clear;
   }else if(opcion == 44){
     clear;
     printf("Ingrese el numero de fichas a apostar al %d de "COLOR_83 BOLD_W"NÚMEROS FALTA"NORMAL_W"\n\n", opcion);
     printf("\n");
     verificarFicha(&fichaElegida, cantidadFichas, contador);
     clear;
   }else if(opcion == 45){
     clear;
     printf("Ingrese el numero de fichas a apostar al %d de "COLOR_170 BOLD_W"NÚMEROS PASA"NORMAL_W"\n\n", opcion);
     printf("\n");
     verificarFicha(&fichaElegida, cantidadFichas, contador);
     clear;
   }else if(opcion == 46){
     clear;
     printf("Ingrese el numero de fichas a apostar al %d de "COLOR_198 BOLD_W"COLUMNA 1" NORMAL_W"\n\n", opcion);
     printf("\n");
     verificarFicha(&fichaElegida, cantidadFichas, contador);
     clear;
   }else if(opcion == 47){
     clear;
     printf("Ingrese el numero de fichas a apostar al %d de "COLOR_149 BOLD_W"COLUMNA 2"NORMAL_W"\n\n", opcion);
     printf("\n");
     verificarFicha(&fichaElegida, cantidadFichas, contador);
     clear;
   }else if(opcion == 48){
     clear;
     printf("Ingrese el numero de fichas a apostar al %d de "COLOR_30 BOLD_W"COLUMNA 3"NORMAL_W"\n\n", opcion);
     printf("\n");
     verificarFicha(&fichaElegida, cantidadFichas, contador);
     clear;
   }else if(opcion == 99){
     clear;
     // calcular el juego
   }else{
     printf(RED_C BOLD_W"Ingrese una opcion correcta."NORMAL_W);
     contador--;
     continue;
   }
   apuesta[contador] = opcion;
   contador++;
   
  }while(opcion != 99 && contador < 10);

}
// fin de la tercera funcion principal

//obtener ficha
int obtenerFicha(int *ficha){
  int input;
  int suma=0;
  do {

    printf("Usted puede ingresar las siguientes fichas: 1, 2, 5, 10, 50, 100.\nPara terminar la carga ingrese 0.\n");
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
      printf(RED_C BOLD_W"Ingrese una cantidad de fichas mayor a cero\n\n"NORMAL_W);
    }
  }
}
//fin de la funcion verificar ficha

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

// lanzar la bola
int lanzarBola(){
  int numeroRandom;
  numeroRandom = rand()%37;
  system("sleep 2s"); // retardo

  printf(
    "y el numero que sale en la ruleta es  ==> %s %d\n" NORMAL_W DEFAULT_C,
    (numeroEsRojo(numeroRandom) ? RED_C BOLD_W : BLACK_C WHITE_B), numeroRandom
  );

  return numeroRandom;
}
// fin de la funcion de lanzar bola