#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <random>
#include <filesystem>
#include <sstream>

using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;

vector<vector<int>> iterativoCubicoTradicional(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int m = A.size();
    int n = A[0].size();
    int p = B[0].size();
    vector<vector<int>> C(m, vector<int>(p, 0));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

vector<vector<int>> trasponer(const vector<vector<int>>& B) {
    int n = B.size();
    int p = B[0].size();
    vector<vector<int>> B_T(p, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            B_T[j][i] = B[i][j];
        }
    }

    return B_T;
}

vector<vector<int>> iterativoCubicoOptimizado(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int m = A.size();
    int n = A[0].size();
    int p = B[0].size();
    vector<vector<int>> B_T = trasponer(B);
    vector<vector<int>> C(m, vector<int>(p, 0));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B_T[j][k];
            }
        }
    }

    return C;
}

// Función para sumar dos matrices
vector<vector<int>> sumarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

// Función para restar dos matrices
vector<vector<int>> restarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

// Función para multiplicar dos matrices utilizando el algoritmo de Strassen
vector<vector<int>> strassenMultiplicacion(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();

    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int mid = n / 2;
    vector<vector<int>> A11(mid, vector<int>(mid)), A12(mid, vector<int>(mid)),
        A21(mid, vector<int>(mid)), A22(mid, vector<int>(mid)),
        B11(mid, vector<int>(mid)), B12(mid, vector<int>(mid)),
        B21(mid, vector<int>(mid)), B22(mid, vector<int>(mid));

    // Dividiendo las matrices en submatrices
    for (int i = 0; i < mid; ++i) {
        for (int j = 0; j < mid; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mid];
            A21[i][j] = A[i + mid][j];
            A22[i][j] = A[i + mid][j + mid];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mid];
            B21[i][j] = B[i + mid][j];
            B22[i][j] = B[i + mid][j + mid];
        }
    }

    // Calculando las 7 multiplicaciones de Strassen
    vector<vector<int>> M1 = strassenMultiplicacion(sumarMatrices(A11, A22), sumarMatrices(B11, B22));
    vector<vector<int>> M2 = strassenMultiplicacion(sumarMatrices(A21, A22), B11);
    vector<vector<int>> M3 = strassenMultiplicacion(A11, restarMatrices(B12, B22));
    vector<vector<int>> M4 = strassenMultiplicacion(A22, restarMatrices(B21, B11));
    vector<vector<int>> M5 = strassenMultiplicacion(sumarMatrices(A11, A12), B22);
    vector<vector<int>> M6 = strassenMultiplicacion(restarMatrices(A21, A11), sumarMatrices(B11, B12));
    vector<vector<int>> M7 = strassenMultiplicacion(restarMatrices(A12, A22), sumarMatrices(B21, B22));

    // Calculando los cuadrantes de la matriz resultante
    vector<vector<int>> C11 = sumarMatrices(restarMatrices(sumarMatrices(M1, M4), M5), M7);
    vector<vector<int>> C12 = sumarMatrices(M3, M5);
    vector<vector<int>> C21 = sumarMatrices(M2, M4);
    vector<vector<int>> C22 = sumarMatrices(restarMatrices(sumarMatrices(M1, M3), M2), M6);

    // Combinando los cuadrantes en una única matriz
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < mid; ++i) {
        for (int j = 0; j < mid; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i + mid][j] = C21[i][j];
            C[i + mid][j + mid] = C22[i][j];
        }
    }

    return C;
}

vector<pair<vector<vector<int>>, vector<vector<int>>>> leerMatrices(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        exit(1);
    }

    vector<pair<vector<vector<int>>, vector<vector<int>>>> dataset;
    string linea;

    while (getline(archivo, linea)) {
        if (linea.find("Matriz A") != string::npos) {
            int m, n;
            sscanf(linea.c_str(), "Matriz A (%dx%d):", &m, &n);
            vector<vector<int>> A(m, vector<int>(n));

            for (int i = 0; i < m; ++i) {
                getline(archivo, linea);
                stringstream ss(linea);
                for (int j = 0; j < n; ++j) {
                    ss >> A[i][j];
                }
            }

            getline(archivo, linea); // Lee la línea en blanco después de la Matriz A

            getline(archivo, linea); // Lee la línea de la Matriz B
            int p;
            sscanf(linea.c_str(), "Matriz B (%dx%d):", &n, &p);
            vector<vector<int>> B(n, vector<int>(p));

            for (int i = 0; i < n; ++i) {
                getline(archivo, linea);
                stringstream ss(linea);
                for (int j = 0; j < p; ++j) {
                    ss >> B[i][j];
                }
            }

            dataset.emplace_back(A, B);
        }
    }

    archivo.close();
    return dataset;
}



// Función para medir el tiempo de ejecución de un algoritmo de multiplicación de matrices
template<typename Func>
void medirTiempo(Func algoritmo, const pair<vector<vector<int>>, vector<vector<int>>>& matrices, int numero, const string& archivoCSV, const string& archivoSalida) {
    const vector<vector<int>>& A = matrices.first;
    const vector<vector<int>>& B = matrices.second;

    auto inicio = high_resolution_clock::now();
    vector<vector<int>> C = algoritmo(A, B);
    auto fin = high_resolution_clock::now();

    double tiempo = duration_cast<nanoseconds>(fin - inicio).count();

    // Guardar el resultado en el archivo CSV
    ofstream fileCSV(archivoCSV, ios::app);
    fileCSV << A.size() << "x" << A[0].size() << "," << B.size() << "x" << B[0].size() << "," << tiempo << endl;
    fileCSV.close();

    // Guardar la matriz resultante en el archivo de salida
    ofstream fileSalida(archivoSalida, ios::app);
    fileSalida << "Conjunto " << numero << ": Matriz A (" << A.size() << "x" << A[0].size() << "), Matriz B (" << B.size() << "x" << B[0].size() << ")" << endl;
    for (const auto& fila : C) {
        for (int val : fila) {
            fileSalida << val << " ";
        }
        fileSalida << endl;
    }
    fileSalida << endl;
    fileSalida.close();
}


int main() {
    fs::create_directory("resultados"); // Crear directorio para .csv
    fs::create_directory("salida"); // Crear directorio para las matrices resultantes

    // Leer el archivo datasetMatrix.txt
    vector<pair<vector<vector<int>>, vector<vector<int>>>> dataset = leerMatrices("datasetMatrix.txt");

    // Algoritmo Iterativo Cúbico Tradicional
    ofstream cubicoFile("resultados/iterativoCubicoTradicional.csv");
    cubicoFile << "Tamaño Matriz A,Tamaño Matriz B,Tiempo\n";
    cubicoFile.close();
    int i = 1;
    for (const auto& matrices : dataset) {
        medirTiempo(iterativoCubicoTradicional, matrices, i++, "resultados/iterativoCubicoTradicional.csv", "salida/iterativoCubicoTradicional.txt");
    }

    // Algoritmo Iterativo Cúbico Optimizado
    ofstream optimizadoFile("resultados/iterativoCubicoOptimizado.csv");
    optimizadoFile << "Tamaño Matriz A,Tamaño Matriz B,Tiempo\n";
    optimizadoFile.close();
    i = 1;
    for (const auto& matrices : dataset) {
        medirTiempo(iterativoCubicoOptimizado, matrices, i++, "resultados/iterativoCubicoOptimizado.csv", "salida/iterativoCubicoOptimizado.txt");
    }

    // Algoritmo de Strassen
    ofstream strassenFile("resultados/strassen.csv");
    strassenFile << "Tamaño Matriz A,Tamaño Matriz B,Tiempo\n";
    strassenFile.close();
    i = 1;
    for (const auto& matrices : dataset) {
        medirTiempo(strassenMultiplicacion, matrices, i++, "resultados/strassen.csv", "salida/strassen.txt");
    }

    return 0;
}

