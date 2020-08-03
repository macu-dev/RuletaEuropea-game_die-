// Este programa simula el juego de la ruleta europea.

//librerias
#include <stdio.h>
#include <stdlib.h> // sirve para la funcion system 
#include <time.h> // para obtener el tiempo lo cual me ayuda a crear la semilla
#include "funciones.h"
#define terminal_formats_active  //para activar el formato de salida
#include "formats.h"
// fin librerias

//macros
#define MAXIMO_RONDAS 20
#define MAXIMO_APUESTAS 10
//fin macros

//prototipos de mis funciones
void JugarRondas();
void JugarRonda(int ronda, int rondas, int *p_cantidadApuesta,int gananciasPorRonda[], int perdidasPorRonda[], int numerosGanadores[]); // ronda actual que se esta jugando
void menuApuestas(int apuesta[], int cantidadFichas[], int ronda, int rondas, int *p_cantidadApuesta);
//fin prototipos de mis funciones

//funcion main
int main(void){
  printf(BLINK COLOR_172 BOLD_W "\t\t\t\tBIENVENIDO AL CASINO MEGA STAR\n\n" NORMAL_W DEFAULT_C);
  //semilla // inicializar la semilla
  srand(time(NULL));
  //funcion principal de mi programa
  JugarRondas();

  return 0;
}
//fin funcion main
//-- DEFINICIONES DE FUNCIONES ---

//funcion principal de mi programa
void JugarRondas(){ 
  int rondas;  // cantidad de rondas
  int cantidadApuestas = 0;
  int numerosGanadores[MAXIMO_RONDAS];
  int perdidasPorRonda[MAXIMO_RONDAS];
  int gananciasPorRonda[MAXIMO_RONDAS];
  int totalPerdidas = 0;
  int totalGanancias = 0;
  int ret; // auxiliar variable declarar
  
  printf("\t\t\t\tMaximo numero de rondas: %d\n", MAXIMO_RONDAS);
  
  // for para verificar que ingrese un numero de rondas correctas
  //while()
  for(int i = 0; i < 1; i++) {
    
    // aqui le preguntamos al usuario cuantas veces quiere jugar
    printf("\n\t\t\t¿Cuantas rondas usted va a jugar en esta mesa? ==>  ");
    scanf("%d", &rondas);
    printf("\n");

    if(rondas < 1 || rondas > MAXIMO_RONDAS){
      printf(RED_C BOLD_W "\t\t\tEl maximo de numero de rondas es %d, vuelva intentarlo\n" NORMAL_W DEFAULT_C, MAXIMO_RONDAS );
      i--;
    }else{
      clear;
      printf("\nQue empiece las apuestas c: !!\n\n");
      // x  numeros de rondas indicadas por el usuario
      printf("Usted jugará %d %s en la ruleta europea \n\n", rondas, (rondas > 1 ? "rondas" : "ronda"));
      
      // bucle de las Rondas (principal del juego)
      for(int ronda = 0; ronda < rondas; ronda++){
        JugarRonda(ronda, rondas, &cantidadApuestas, gananciasPorRonda, perdidasPorRonda, numerosGanadores);
        totalPerdidas += perdidasPorRonda[ronda];
        totalGanancias += gananciasPorRonda[ronda];
      }

      printf(
        "\nLa Mesa tuvo una "COLOR_46 BOLD_W"ganancia de %d fichas"NORMAL_W", y una "RED_C BOLD_W"perdida de %d fichas"NORMAL_W" en el juego.\n\n",
        totalGanancias, totalPerdidas
      );
      // al finalizar con la totalidad de las rondas, se tiene que indicar las perdidas y ganancias totales
      
      if(totalPerdidas < totalGanancias){
        printf(COLOR_46 BOLD_W"\nMESA GANADORA C: !!\n"NORMAL_W);
      }else if(totalPerdidas == totalGanancias){
        printf(COLOR_220 BOLD_W"\nMESA NO CONFORME :/ !!\n"NORMAL_W);
      }else{
        printf(RED_C BOLD_W"\nMESA EN PROBLEMAS :o !!\n"NORMAL_W);
      }

      printf("\nEl promedio de apuestas por ronda fue: %.2f.\n", ((float)cantidadApuestas)/((float)rondas));

      ret = contarColor(numerosGanadores, rondas);
      switch(ret) {
        case 1: printf("El numero "RED_C BOLD_W"rojo"NORMAL_W" ha salido mas de 5 veces seguidas!\n"); break;
        case 0: printf("El numero "BLACK_C WHITE_B BOLD_W"negro"NORMAL_W" ha salido mas de 5 veces seguidas!\n"); break;
        case 2: printf("El numero "BLACK_C BOLD_W WHITE_B"negro"NORMAL_W" y "RED_C BOLD_W"rojo"NORMAL_W" han salido mas de 5 veces seguidas!"); break;
      }
      
      printf(BLUE_C BOLD_W"En este juego salieron %d bolas con valores primos.\n" NORMAL_W, contarPrimos(numerosGanadores, rondas));

      printf("\nGracias por jugar!.\n");
    }
  }
}
// fin de la funcion principal de mi programa

//segunda funcion principal
void JugarRonda(int ronda, int rondas, int *p_cantidadApuesta,int gananciasPorRonda[], int perdidasPorRonda[], int numerosGanadores[]){
  int apuesta[MAXIMO_APUESTAS];
  int cantidadFichas[MAXIMO_APUESTAS]; //valor de la apuesta
  int numeroDeBola = (-1);

  menuApuestas(apuesta, cantidadFichas, ronda, rondas, p_cantidadApuesta );

  printf(COLOR_226 BOLD_W"Lanzamiento de la bola\n"NORMAL_W );
  printf("\n");
  //lanzarBola
  numeroDeBola = lanzarBola();

  //guardamos el numero que salio ganador en la ronda
  numerosGanadores[ronda] = numeroDeBola;
  perdidasPorRonda[ronda] = 0;
  gananciasPorRonda[ronda] = 0;

  //recorre las apuestas y contabiliza(suma) las ganancias y perdidas de la MESA.
  // PARA SABER CUAL ES LA ULTIMA APUESTAS => 99

   for (int i = 0; apuesta[i] != 99 && i < MAXIMO_APUESTAS; i++){
     if(apuesta[i] >=0 && apuesta[i] <= 36 ){
       //pleno
      if(apuesta[i] == numeroDeBola){
        //Si gana el usuario la mesa pierde
        perdidasPorRonda[ronda] += cantidadFichas[i] * 35;
      }else{
        gananciasPorRonda[ronda] += cantidadFichas[i];
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
          perdidasPorRonda[ronda] += cantidadFichas[i] * 3;
        }else{
          gananciasPorRonda[ronda] += cantidadFichas[i];
        }
     }else if (
       apuesta[i] == 37 || apuesta[i] == 38 || // pares/impares
       apuesta[i] == 39 || apuesta[i] == 40 || // rojo/negro
       apuesta[i] == 44 || apuesta[i] == 45    // falta/pasa
      ){
       // rojo/negro par/impar 
        if(
           (apuesta[i] == 37 && (numeroDeBola)%2 == 0)                 || // pares
           (apuesta[i] == 38 && (numeroDeBola)%2 == 1)                 || // impares
           (apuesta[i] == 39 && numeroEsRojo(numeroDeBola))            || // rojo
           (apuesta[i] == 40 && !numeroEsRojo(numeroDeBola))           || // negro
           (apuesta[i] == 44 && 1<= numeroDeBola && numeroDeBola <=18) || // falta
           (apuesta[i] == 45 && 19<=numeroDeBola && numeroDeBola <=36)    // pasa
        ){
          perdidasPorRonda[ronda] += cantidadFichas[i] * 2;
        }else{
          gananciasPorRonda[ronda] += cantidadFichas[i];
        }
     }
   }
   
   printf(
     "La Mesa tuvo una "COLOR_46 BOLD_W"ganancia de %d fichas"NORMAL_W", y una "RED_C BOLD_W"perdida de %d fichas"NORMAL_W" en la ronda %d.\n\n",
     gananciasPorRonda[ronda], perdidasPorRonda[ronda], ronda+1
   );


}
//fin segunda funcion principal

// tercera funcion principal
void menuApuestas(int apuesta[], int cantidadFichas[], int ronda, int rondas, int *p_cantidadApuesta){
  int opcion = (-1);
  int contador = 0; // las apuestas que ya hizo
  // int valorDeApuesta;

  do{
    printf(BOLD_W"Usted esta jugando la ronda %d/%d\n\n"NORMAL_W, ronda + 1, rondas);
    printf(BOLD_W"Usted puede realizar %d apuestas\n\n"NORMAL_W, MAXIMO_APUESTAS - contador);
    //le decimos al usuario que cuantas apuestas le quedan   

    //menu de opciones 
    printf("Seleccione su apuesta\n\n");
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
    }else if(opcion == 37) {
      clear;
      printf("Ingrese el numero de fichas a apostar al %d de "BLUE_C BOLD_W "PARES:" NORMAL_W"\n\n\n", opcion);
    }else if(opcion == 38){
      clear;
      printf("Ingrese el numero de fichas a apostar al %d de "COLOR_202 BOLD_W"IMPARES:" NORMAL_W"\n\n\n", opcion);
    }else if(opcion == 39){
      clear; 
      printf("Ingrese el numero de fichas a apostar al %d de "RED_C BOLD_W"ROJO" NORMAL_W"\n\n\n", opcion);
    }else if(opcion == 40){
      clear;
      printf("Ingrese el numero de fichas a apostar al %d de "WHITE_B BLACK_C "NEGRO" NORMAL_W DEFAULT_B DEFAULT_C"\n\n\n", opcion);
    }else if(opcion == 41){
      clear;
      printf("Ingrese el numero de fichas a apostar al %d de "COLOR_172 BOLD_W"PRIMEROS 12"NORMAL_W"\n\n\n", opcion);
    }else if(opcion == 42){
      clear;
      printf("Ingrese el numero de fichas a apostar al %d de "COLOR_14 BOLD_W"SEGUNDOS 12"NORMAL_W"\n\n\n", opcion);
    }else if(opcion == 43){
      clear;
      printf("Ingrese el numero de fichas a apostar al %d de "COLOR_118 BOLD_W"TERCEROS 12"NORMAL_W"\n\n\n", opcion);
    }else if(opcion == 44){
      clear;
      printf("Ingrese el numero de fichas a apostar al %d de "COLOR_83 BOLD_W"NÚMEROS FALTA"NORMAL_W"\n\n\n", opcion);
    }else if(opcion == 45){
      clear;
      printf("Ingrese el numero de fichas a apostar al %d de "COLOR_170 BOLD_W"NÚMEROS PASA"NORMAL_W"\n\n\n", opcion);
    }else if(opcion == 46){
      clear;
      printf("Ingrese el numero de fichas a apostar al %d de "COLOR_198 BOLD_W"COLUMNA 1" NORMAL_W"\n\n\n", opcion);
    }else if(opcion == 47){
      clear;
      printf("Ingrese el numero de fichas a apostar al %d de "COLOR_149 BOLD_W"COLUMNA 2"NORMAL_W"\n\n\n", opcion);
    }else if(opcion == 48){
      clear;
      printf("Ingrese el numero de fichas a apostar al %d de "COLOR_30 BOLD_W"COLUMNA 3"NORMAL_W"\n\n\n", opcion);
    }else if(opcion == 99){ 
      clear;
      printf("\n\n\t\tNo va mas!\n\n");

    }else{
      printf(RED_C BOLD_W"Ingrese una opcion correcta."NORMAL_W);
      contador--;
      continue;
    }

    apuesta[contador] = opcion;
    
    if(opcion != 99) {
      pedir_verificarFicha(cantidadFichas, contador, opcion, apuesta);
      clear;
      contador++;
    }
    
  }while(opcion != 99 && contador < MAXIMO_APUESTAS);
  *p_cantidadApuesta += contador; // contabilizar el total de las apuestas para sacar el promedio
}
// fin de la tercera funcion principal