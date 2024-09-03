#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

void generarDataset(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para escritura.\n";
        return;
    }

    // Semilla para la generación de números aleatorios
    srand(time(0));

    for (int i = 0; i < 100; ++i) {
        // Generar un tamaño aleatorio para el vector
        int tamano = 10 + rand() % 991;  // Rango entre 10 y 1000

        vector<int> vector;

        // Generar los elementos aleatorios del vector
        for (int j = 0; j < tamano; ++j) {
            vector.push_back(rand() % 100);  // Números aleatorios entre 0 y 99
        }

        // Escribir el vector en el archivo
        archivo << "{";
        for (int j = 0; j < tamano; ++j) {
            archivo << vector[j];
            if (j < tamano - 1) {
                archivo << ", ";
            }
        }
        archivo << "}\n";
    }

    archivo.close();
    cout << "Dataset generado exitosamente en " << nombreArchivo << endl;
}

int main() {
    generarDataset("dataset.txt");
    return 0;
}
