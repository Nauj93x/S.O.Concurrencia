/*
  Fecha: 04/04/04
  Autor: Juan Pablo Hernández Ceballos
  Materia: Sistemas Operativos
  Tema: Concurrencia
  Desarrollar una metodología para implementar la multiplicación de matrices utilizando paralelismo a través de la biblioteca Pthreads. Se empleará el algoritmo clásico de
  multiplicación de matrices, adaptado para operar específicamente con matrices cuadrada
  ----mm_v01.c
    1. Reserva espacio de memoria
    2. Creación de punteros de tipo double para matrices
    3. Asignando memoria
    4. Procesando los argumentos de entrada
  ----mm_v02.c
    1. Configuración inicial de las matrices
    2. Visualización de las matrices
    3. Método para establecer los valores iniciales de las matrices
    4. Procedimiento para mostrar las matrices
    5. Realización de la multiplicación de las matrices
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

//Firma de funciones
void inicializarMatrices(int n, double* mA, double* mB, double* mC){
  //Inicializacion de matrices
  for (int i = 0; i < n*n; i++) {
    mA[i] = i*1.1;
    mB[i] = i*2.2;
    mC[i] = i;
  }
}
void imprimirMatriz(int n, double* m){
  //Impresion de matriz
  if(n<9){
      for (int i = 0; i < n*n; i++) {
        if(i%n == 0){printf("\n");}
        printf("%f ", m[i]);
      }
      printf("\n*******************************************************\n");
  }else{
      printf("\n*******************************************************\n");
  }

}

void* multiplicacionMatriz(int N, double* mA, double* mB,double *mC){
  double *pA, *pB, sumaTemp;
  for (int i = 0; i < N; i++)
  {
      for (int j = 0; j < N; j++)
      {
        pA = mA + (i*N);
        pB = mB +j;
        for (int k = 0; k < N; k++, pA++, pB+=N)
        {
          sumaTemp += *pA * *pB;
        }
        mC[(j+i)*N] = sumaTemp;
      }
  }
  return 0;
}

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
  // Definicion de los espacios de memoria a los que van a hacer referencia los punteros
  //los punteros
  mA = MEM_CHUNK;
  mB= mA + ( N*N );
  mC= mB + ( N*N );
  
  //Inicializacion de matrices
  inicializarMatrices(N, mA, mB, mC);

  //Impresion de cada una de las matrices
  printf("Matriz A\n");
  imprimirMatriz(N, mA);
  printf("Matriz B\n");
  imprimirMatriz(N, mB);
  // printf("Matriz C\n");
  // imprimirMatriz(N, mC);

  printf("Matriz Producto mA * mB\n");
  // double *mF;
  multiplicacionMatriz(N, mA, mB, mC);
  // //imprimirMatriz(N, mF);

  imprimirMatriz(N, mC);
  printf("\nFin del programa\n");
  return 0;
}

