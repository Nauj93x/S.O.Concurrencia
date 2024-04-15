/*
  Fecha: 04/04/04
  Autor: Juan Pablo Hernández Ceballos
  Materia: Sistemas Operativos
  Tema: Concurrencia
  Desarrollar una metodología para implementar la multiplicación de matrices utilizando paralelismo a través de la biblioteca Pthreads. Se empleará el algoritmo clásico de
  multiplicación de matrices, adaptado para operar específicamente con matrices cuadrada
  |----  mm_v01.c  ----|
    1. Reserva espacio de memoria
    2. Creación de punteros de tipo double para matrices
    3. Asignando memoria
    4. Procesando los argumentos de entrada
  |----  mm_v02.c  ----|
    1. Configuración inicial de las matrices
    2. Visualización de las matrices
    3. Método para establecer los valores iniciales de las matrices
    4. Procedimiento para mostrar las matrices
    5. Realización de la multiplicación de las matrices
  |----  mm_v03.c  ----|
    1. Declaracion de vectores de hilos
  |----  mm_v04.c  ----|
  1. Implementación de paralelismo:resolución de la multiplicación de matrices
  2. Se crea el vector de los hilos
  3. Se considera la exclusión de hilos
  4. Se confieren a globales las matrices
  |----  mm_v05.c  ----|
  1. Implementación de Paralelismo en la Multiplicación de Matrices
  2. Vector de Hilos: Se establece para coordinar la ejecución paralela.
  3. Exclusión Mutua: Implementada para garantizar acceso seguro a recursos compartidos.
  4. Matrices Globales: Las matrices (`mA`, `mB`, `mC`) son globales para facilitar el acceso       de los hilos.
  5. Encapsulación de Datos: Datos para la multiplicación se organizan en la estructura             `datosMM`.
  6. Desencapsulación en MxM: Dentro de la función `MxM`, se extraen los datos de `datosMM`         para la operación.

*/
// Librerias utilizadas en el programa

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

//Resevar memoria
#define RESERVA (1024*128*64*8)

struct datosMM{
  int N; 		//Dimensión matriz (NxN)
  int H;		//Número de hilos 
  int idH;	//Identidad de hilos 
};

double *mA, *mB, *mC;

static double MEM_CHUNK[RESERVA]; 
//Funciones
void *multiplicacionMatriz(void *argMM){
  struct datosMM *intValor = (struct datosMM *)argMM;	
  int n = intValor->N;
  int h = intValor->H;
  int idH = intValor->idH;

  int ini = idH * (n / h);
  int fin = (idH == h-1) ? n : (idH + 1) * (n / h);

  printf("Hilos= %d ; IdHilo= %d ; ini=%d; fin=%d \n", h, idH, ini, fin);

  for(int i=ini; i<fin; i++){
    for(int j=0; j<n; j++){
      double sumaTemp, *pA, *pB;
      sumaTemp = 0.0;
      pA = mA + i*n;
      pB = mB + j;
      for(int k=0; k<n; k++, pA++, pB+=n){
        sumaTemp += *pA * *pB;
      }
      mC[j+i*n] = sumaTemp;
    }
  }

  pthread_exit(NULL);
};


void initMatrices(int n){ 
  for(int i=0; i<n*n; i++){
    mA[i] = i*1.1;
    mB[i] = i*2.2;
    mC[i] = i;
  }
};

void imprMatrices(int n, double *matriz){
  if(n<9){
    for(int i=0; i<n*n; i++){
      if(i%n==0) printf("\n");
      printf(" %f ", matriz[i]);
    }
    printf("\n#######################################################\n");
  } else {
    printf("\n#######################################################\n");
  }
};

int main(int argc, char *argv[]) {
  if(argc<=2){
      printf("Numero argumentos incorrectos\n");
      printf("\n\t $ejecutable.exe DIM NumHilos\n");
    return -1;	
  }

  int N = (int) atof(argv[1]);	
  int H = (int) atof(argv[2]);	
  if(N<=0 || H <=0){
      printf("\n Valores deben ser mayor que cero\n");
    return -1;	
  };

  pthread_t hilos[H];
  int ids[H];  // Array para guardar los identificadores de los hilos

  mA = MEM_CHUNK;
  mB = mA + N*N;
  mC = mB + N*N;

  initMatrices(N);

  imprMatrices(N, mA);
  //imprMatrices(N, mB);


  for(int h=0; h<H; h++){
    struct datosMM *valoresMM = (struct datosMM *)malloc(sizeof(struct datosMM));
    valoresMM->N = N;
    valoresMM->H = H;
    valoresMM->idH = h;
    pthread_create(&hilos[h],NULL,multiplicacionMatriz,valoresMM);	
    ids[h] = h;
  }

  // Ordenar los identificadores de los hilos
  for (int i = 0; i < H - 1; i++) {
    for (int j = i + 1; j < H; j++) {
      if (ids[i] > ids[j]) {
        int temp = ids[i];
        ids[i] = ids[j];
        ids[j] = temp;
      }
    }
  }

  // Imprimir la información de cada hilo en el orden correcto
  for(int i = 0; i < H; i++) {
    pthread_join(hilos[ids[i]], NULL);
  }
  
  /*for(int h=0; h<H; h++){
    pthread_join(hilos[h],NULL);	
  }
*/

  //imprMatrices(N, mC);

  printf("\n\tFin del programa.............!\n");

  pthread_exit(NULL);
}