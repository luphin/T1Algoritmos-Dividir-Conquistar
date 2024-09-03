#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath> // Para la función pow

using namespace std;

// Función para generar una matriz de tamaño aleatorio y rellenarla con números enteros aleatorios
vector<vector<int>> generarMatrizAleatoria(int filas, int columnas, int minVal, int maxVal) {
    vector<vector<int>> matriz(filas, vector<int>(columnas));
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matriz[i][j] = minVal + rand() % (maxVal - minVal + 1);
        }
    }
    return matriz;
}

// Función para guardar pares de matrices en un archivo
void guardarParesDeMatricesEnArchivo(const string& nombreArchivo, int cantidadPares, int minN, int maxN, int minVal, int maxVal) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    for (int i = 0; i < cantidadPares; ++i) {
        // Generar un valor aleatorio para n entre minN y maxN
        int n = minN + rand() % (maxN - minN + 1);
        int tamano = pow(2, n);  // Calcular 2^n

        // Generar matrices A y B
        vector<vector<int>> matrizA = generarMatrizAleatoria(tamano, tamano, minVal, maxVal);
        vector<vector<int>> matrizB = generarMatrizAleatoria(tamano, tamano, minVal, maxVal);

        // Guardar la matriz A
        archivo << "Matriz A" << " (" << tamano << "x" << tamano << "):" << endl;
        for (const auto& fila : matrizA) {
            for (int val : fila) {
                archivo << val << " ";
            }
            archivo << endl;
        }

        archivo << endl;

        // Guardar la matriz B
        archivo << "Matriz B" << " (" << tamano << "x" << tamano << "):" << endl;
        for (const auto& fila : matrizB) {
            for (int val : fila) {
                archivo << val << " ";
            }
            archivo << endl;
        }

        archivo << endl;
    }

    archivo.close();
    cout << "Pares de matrices guardados en " << nombreArchivo << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));  // Inicializar la semilla aleatoria

    string nombreArchivo = "datasetMatrix.txt";
    int cantidadPares = 50;
    int minN = 1;  // Valor mínimo de n
    int maxN = 7;  // Valor máximo de n
    int minVal = -100; // Valor mínimo de los elementos de la matriz
    int maxVal = 100;  // Valor máximo de los elementos de la matriz

    guardarParesDeMatricesEnArchivo(nombreArchivo, cantidadPares, minN, maxN, minVal, maxVal);

    return 0;
}
