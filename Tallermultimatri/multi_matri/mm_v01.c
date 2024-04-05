/*
  Fecha: 04/04/04
  Autor: Juan Pablo Hernández Ceballos
  Materia: Sistemas Operativos
  Tema: Concurrencia
  Objetivo: Desarrollar una aplicación que implemente el algoritmo clásico de multiplicación de matrices mediante paralelismo utilizando la biblioteca Pthreads.
  Reserva de memoria.
  Creación del main para el ingreso de variables (argumentos).
  Validación de los argumentos de entrada.
  Creación de punteros para las matrices.
  Reserva de memoria para las matrices NxM.
  Inicialización de las matrices.
  Implementación del algoritmo de multiplicación de matrices clásico.
  Implementación del paralelismo utilizando Pthreads.
  Impresión de las matrices.
  Nota: Se asume que las matrices ingresadas son cuadradas (NxN).
*/
// Librerias utilizadas en el programa
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

// Reserva de memoria.
// Definicion de 'RESERVA' para representar el tamaño del espacio de memoria.
#define RESERVA (1024*128*64*8)
// Creación de un vector cuyo tamano sera igual a RESERVA
static double MEM_CHUNK[RESERVA];

int main(int argc, char *argv[]){
  //Verificacion de los argumentos de entrada
  if( argc < 3){
    printf("No se ingresaron suficientes elementos\n");
    return 1;
  }else if(atoi(argv[1]) <= 0 && atoi(argv[2]) <= 0){
    printf("Los elementos son menores o iguales a 0\n");
    return 1;
  }
  // Creacion de punteros para las matrices
  int N = atoi(argv[1]); // Tam matriz
  int H = atoi(argv[2]); // Tam Hilos

  //printf("The size of the vector is: %d y %d\n", N, H);

  // Declaración de punteros para referenciar diferentes espacios de memoria
  double *mA, *mB, *mC;
  // Definicion de los espacios de memoria a los que van a hacer referencia los punteros.
  //los punteros.
  mA = MEM_CHUNK;
  mB= mA + ( N*N );
  mC= mB + ( N*N );


  printf("Fin del programa\n");
  return 0;
}