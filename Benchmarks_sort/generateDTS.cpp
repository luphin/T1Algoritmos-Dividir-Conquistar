#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

void generarVectorAleatorio(vector<int>& vec, int tamano) {
    vec.clear();
    for (int j = 0; j < tamano; ++j) {
        vec.push_back(rand() % 100);  // Números aleatorios entre 0 y 99
    }
}

void generarVectorSemiordenado(vector<int>& vec, int tamano) {
    vec.clear();
    for (int j = 0; j < tamano; ++j) {
        vec.push_back(j);
    }
    // Desordenar parcialmente
    for (int j = 0; j < tamano / 10; ++j) {
        swap(vec[j], vec[rand() % tamano]);
    }
}

void generarVectorParcialmenteOrdenado(vector<int>& vec, int tamano) {
    vec.clear();
    // Parte ordenada
    for (int j = 0; j < tamano / 2; ++j) {
        vec.push_back(j);
    }
    // Parte desordenada
    for (int j = tamano / 2; j < tamano; ++j) {
        vec.push_back(rand() % 100);
    }
}

void generarVectorOrdenadoInversa(vector<int>& vec, int tamano) {
    vec.clear();
    for (int j = tamano - 1; j >= 0; --j) {
        vec.push_back(j);
    }
}

void generarDataset(const string& nombreArchivo, int cantidad) {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para escritura.\n";
        return;
    }

    // Semilla para la generación de números aleatorios
    srand(time(0));

    // Generar 50 vectores aleatorios
    for (int i = 0; i < cantidad; ++i) {
        int tamano = 10 + rand() % 991;  // Rango entre 10 y 1000
        vector<int> vector;
        generarVectorAleatorio(vector, tamano);

        archivo << "Aleatorio {";
        for (int j = 0; j < tamano; ++j) {
            archivo << vector[j];
            if (j < tamano - 1) {
                archivo << ", ";
            }
        }
        archivo << "}\n";
    }

    // Generar 50 vectores semiordenados
    for (int i = 0; i < cantidad; ++i) {
        int tamano = 10 + rand() % 991;  // Rango entre 10 y 1000
        vector<int> vector;
        generarVectorSemiordenado(vector, tamano);

        archivo << "Semiordenado {";
        for (int j = 0; j < tamano; ++j) {
            archivo << vector[j];
            if (j < tamano - 1) {
                archivo << ", ";
            }
        }
        archivo << "}\n";
    }

    // Generar 50 vectores parcialmente ordenados
    for (int i = 0; i < cantidad; ++i) {
        int tamano = 10 + rand() % 991;  // Rango entre 10 y 1000
        vector<int> vector;
        generarVectorParcialmenteOrdenado(vector, tamano);

        archivo << "ParcialmenteOrdenado {";
        for (int j = 0; j < tamano; ++j) {
            archivo << vector[j];
            if (j < tamano - 1) {
                archivo << ", ";
            }
        }
        archivo << "}\n";
    }

    // Generar 50 vectores ordenados a la inversa
    for (int i = 0; i < cantidad; ++i) {
        int tamano = 10 + rand() % 991;  // Rango entre 10 y 1000
        vector<int> vector;
        generarVectorOrdenadoInversa(vector, tamano);

        archivo << "OrdenadoInverso {";
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
    cout << "-- Se crearon: " << cantidad << " vectores aleatorios, " << cantidad << " vectores semiordenados, " << cantidad << " vectores parcialmente ordenados y " << cantidad << " vectores invertidos" << endl;  
}

int main() {
    generarDataset("dataset.txt", 150);
    return 0;
}
