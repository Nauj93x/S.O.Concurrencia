# S.O.Concurrencia
#  Documentación Algoritmo de Multiplicación de Matrices

Este proyecto utiliza la biblioteca Pthreads en C para acelerar la multiplicación de matrices cuadradas. Desarrollado como parte de un curso de Sistemas Operativos, su enfoque está en mostrar cómo dividir la carga de trabajo entre varios hilos puede mejorar el rendimiento de operaciones complejas.

## Detalles Generales

- **Fecha de Creación:** 4 de abril de 2024
- **Autor:** Juan Pablo Hernández Ceballos
- **Curso:** Sistemas Operativos
- **Tema:** Concurrencia
- **Objetivo:** Implementar la multiplicación de matrices cuadradas utilizando paralelismo con Pthreads.


## Requisitos

Para compilar y ejecutar este programa, necesitas:

- Un compilador de C, como GCC.
- La biblioteca Pthreads instalada en tu sistema.

## Compilación y Ejecución

Para compilar el programa, utiliza el siguiente comando en la terminal:

```bash
cd multi_matri

gcc mv.005.c -o mm_v05

-- ejemplo./mm_v05 #Hilos #Procesos
./mm_v05 10 5
```

## Descripción del Código

El código implementa la multiplicación de matrices cuadradas utilizando paralelismo con la biblioteca Pthreads en C. A continuación, se describen las principales funciones y estructuras utilizadas en el programa:

- Declaración de Estructuras: El programa define una estructura llamada datosMM, que encapsula los datos necesarios para la multiplicación de matrices. Esta estructura contiene el tamaño de las matrices (‘N’) y punteros a las matrices de entrada (‘mA y mB’) y salida (‘mC’). La estructura datosMM facilita el paso de datos a las funciones de manera organizada.

- Reserva de Memoria: Se asigna una reserva estática de memoria para almacenar las matrices implicadas en la operación de multiplicación.

- Estructura datosMM: Esta estructura organiza los datos necesarios para realizar la multiplicación de matrices, incluyendo el tamaño de las matrices y punteros a las matrices de entrada y salida.

- Inicialización de Matrices: La función inicializarMatrices asigna valores predefinidos a las matrices de entrada ‘mA’ y ‘mB’, así como a la matriz de salida ‘mC’.

- Impresión de Matrices: La función imprimirMatriz muestra en la consola los elementos de una matriz, facilitando la visualización de los resultados.

- Multiplicación de Matrices: La función multiplicacionMatriz realiza la multiplicación de matrices cuadradas utilizando los punteros a las matrices de entrada y salida contenidos en la estructura datosMM. Esta función se ejecuta de manera paralela utilizando hilos de la biblioteca Pthreads, lo que mejora el rendimiento del programa al distribuir la carga de trabajo entre múltiples hilos de ejecución.

- Creación de Hilos: En la función principal del programa, se crea un número específico de hilos para realizar la multiplicación de matrices de manera paralela. Cada hilo ejecuta la función multiplicacionMatriz con una parte de los datos de entrada, distribuyendo así la carga de trabajo entre los hilos.

- Identificación y Distribución de Hilos: Se integra un identificador único para cada hilo (idH), lo que permite una división más precisa de las tareas entre los hilos y optimiza el paralelismo en la multiplicación de matrices.
