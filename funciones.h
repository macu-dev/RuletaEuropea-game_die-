#ifndef FUNCIONES
#define FUNCIONES

void obtenerFicha(int *ficha);
void pedir_verificarFicha(int arreglo[], int contador, int opcion, int apuesta[]);
int esApuestaConGanaciaDoble(int opcion);
int lanzarBola();
int numeroEsRojo(int numero);
int perteneceArrYApuestaDoble(int ficha, int arreglo[], int limite, int apuestas[]);
int contarColor(int arreglo[], int dimension);
int contarPrimos(int arreglo[], int dimension);
int esPrimo(int numero);
#endif