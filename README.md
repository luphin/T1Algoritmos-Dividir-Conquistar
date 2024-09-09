# TAREA 1: Algoritmos dividir y conquistar
En este repositorio se encuentra el desarrollo de una tarea destinada a comprobar la eficiencia de algoritmos de ordenamiento y multiplicación con vectores y matrices de diferentes tamaños y características. Las implementaciones están organizadas en carpetas separadas. Dentro de cada una de ellas, se pueden observar los resultados obtenidos en la carpeta `resultados`, donde se almacenan los `tiempos de ejecución` para ordenar los vectores o multiplicar las matrices de un tamaño determinado `n`. En la carpeta `salida`, se generan archivos TXT con las soluciones retornadas por los algoritmos, lo que permite verificar que las implementaciones se han realizado correctamente y producen los resultados esperados.

## Ejecución de los algoritmos
### 1. Ingresar al directorio correspondiente
Seleccione el directorio del conjunto de algoritmos que desea ejecutar:

Para algoritmos de ordenamiento:
```
cd T1Algoritmos-Dividir-Conquistar/Benchanarks_sort
```
Para algoritmos de multiplicación de matrices:
```
cd T1Algoritmos-Dividir-Conquistar/Benchmarks_MatrixMultiplication
```

### 2. Ejecutar el Makefile
Ejecute el siguiente comando para compilar el directorio:
```
make 
```
Este comando eliminará las carpetas `resutados` y `salida`, luego se generará un nuevo dataset de manera aleatoria.

```
make run
```
Este comando ejecutará las pruebas en función de los algoritmos presentes en cada directorio. La ejecución puede tardar un tiempo considerable. Está configurado para que en `Benchmarks_sort` (algoritmos de ordenamiento) se generen 600 casos de prueba (150 para cada uno de los 4 tipos diferentes de ordenamiento de los vectores) y en `Benchmarks_MatrixMultiplication` (algoritmos de multiplicación de matrices) se generen 200 casos aleatorios. Si desea cambiar el número de casos, puede modificar el archivo `generateDTS.cpp` correspondiente.

## Estructura archivos 

```
├── Benchmarks_MatrixMultiplication
│   ├── datasetMatrix.txt
│   ├── generar_matrices
│   ├── generateDTS.cpp
│   ├── main.cpp
│   ├── makefile
│   ├── multiplicacion
│   ├── resultados
│   │   ├── iterativoCubicoOptimizado.csv
│   │   ├── iterativoCubicoTradicional.csv
│   │   └── strassenMultiplicacion.csv
│   └── salida
│       ├── iterativoCubicoOptimizado.txt
│       ├── iterativoCubicoTradicional.txt
│       └── strassenMultiplicacion.txt
├── Benchmarks_sort
│   ├── dataset.txt
│   ├── generateDTS
│   ├── generateDTS.cpp
│   ├── main.cpp
│   ├── makefile
│   ├── ordenamiento
│   ├── resultados
│   │   ├── bubbleSort.csv
│   │   ├── mergeSort.csv
│   │   ├── quickSort.csv
│   │   ├── selectionSort.csv
│   │   └── std::sort.csv
│   └── salida
│       ├── bubbleSort.txt
│       ├── mergeSort.txt
│       ├── quickSort.txt
│       ├── selectionSort.txt
│       └── std::sort.txt
├── README.md

```

### Algoritmos Ordenamiento
Para este conjunto de algoritmos se utilizaron implementaciones existentes de [GeeksforGeeks](https://www.geeksforgeeks.org/), ajustando ciertas partes para que coincidieran con la entrada de los vectores de prueba. Los algoritmos utilizados son los siguientes:

- Selection sort.[Geeksforgeeks: Selection Sort](https://www.geeksforgeeks.org/selection-sort-algorithm-2/?ref=header_outind)
- Bubble sort. [Geeksforgeeks: Bubble Sort](https://www.geeksforgeeks.org/bubble-sort-in-cpp/) 
- Mergesort. [Geeksforgeeks: Merge Sort](https://www.geeksforgeeks.org/merge-sort/?ref=header_outind) 
- Quicksort. [Geeksforgeeks: Quick Sort](https://www.geeksforgeeks.org/quick-sort-algorithm/?ref=header_outind)
- Funcion sorting de biblioteca estandar de C++. [Geeksforgeeks: std::sort](https://www.geeksforgeeks.org/sort-c-stl/) y [cppreference](https://en.cppreference.com/w/cpp/algorithm/sort)


### Algoritmos Multiplicacion de Matrices
Para los algoritmos de multiplicación de matrices, se utilizaron diferentes fuentes para formular los algoritmos. Los algoritmos implementados son:

- Algoritmo iterativo cubico tradicional 
- Algoritmo iterativo cubico optimizado.

Referencias utilizadas:
    - [betterprogramming: Better-than-Cubic Complexity for Matrix Multiplication in Rust. Autor Mike Cvet](https://betterprogramming.pub/better-than-cubic-complexity-for-matrix-multiplication-in-rust-cf8dfb6299f6)
    - [medium.com: Toward An Optimal Matrix Multiplication Algorithm. Autor Kilichbek Haydarov](https://medium.com/@kilichbekhaydarov/toward-an-optimal-matrix-multiplication-algorithm-4f024baa1206)
    - [Geeksforgeeks: Matrix Multiplication](https://www.geeksforgeeks.org/matrix-multiplication/) 
- Algoritmo Strassen. 

Referencias consultadas:
    - [Geeksforgeeks: Strassen’s Matrix Multiplication Algorithm | Implementation](https://www.geeksforgeeks.org/strassens-matrix-multiplication-algorithm-implementation/)
    - [tutorialspiont: Strassen’s Matrix Multiplication](https://www.tutorialspoint.com/data_structures_algorithms/strassens_matrix_multiplication_algorithm.htm )
    - [Geeksforgeeks: Divide and Conquer | Set 5 (Strassen’s Matrix Multiplication)](https://www.geeksforgeeks.org/strassens-matrix-multiplication/?ref=header_outind)


## Autor 
Luis Zegarra Stuardo. 

