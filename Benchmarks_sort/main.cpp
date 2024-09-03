#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <random>
#include <filesystem>

using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;

// Función de bubbleSort obtenida de : https://www.geeksforgeeks.org/bubble-sort-in-cpp/
// la versión utilizada es bubbleSort normal, esto porque se mostraba uno que estaba optimizado
void bubbleSort(vector<int>& v) {
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

// Función de selectionSort obternida de :  https://www.geeksforgeeks.org/selection-sort-algorithm-2/
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(arr[min_idx], arr[i]);
        }
    }
}

// Función de mergeSort obtenidade: https://www.geeksforgeeks.org/merge-sort/
// compuesta por las funciones: merge, mergeSortHelper y mergeSort
// se aplicó una funcion mergeSortHelper porque habia problemas con la entrada, sigue manteniedo la forma original
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortHelper(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, left, mid);
    mergeSortHelper(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void mergeSort(vector<int>& arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
}

// Función de quickSort obtenida de : https://www.geeksforgeeks.org/cpp-program-for-quicksort/
// compuesta por las funciones: partition, quickSortHElper y quickSort
// quickSortHelper fue agregada poruqe habian problemas con la entrada
int partition(vector<int>& vec, int low, int high) {
    int pivot = vec[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[high]);
    return (i + 1);
}

void quickSortHelper(vector<int>& vec, int low, int high) {
    if (low < high) {
        int p = partition(vec, low, high);
        quickSortHelper(vec, low, p - 1);
        quickSortHelper(vec, p + 1, high);
    }
}

void quickSort(vector<int>& vec) {
    quickSortHelper(vec, 0, vec.size() - 1);
}

// Función de std::sort de c++, nativa
void stdSort(vector<int>& vec) {
    std::sort(vec.begin(), vec.end());
}

// Función para leer el dataset.txt y obtener los valores de los vectores sin los simbolos, solo números
vector<vector<int>> leerDataset(const string& nombreArchivo) {
    vector<vector<int>> dataset;
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo de datos.\n";
        return dataset;
    }

    string linea;
    while (getline(archivo, linea)) {
        vector<int> vec;
        // Limpiar la línea de caracteres no deseados
        linea.erase(remove_if(linea.begin(), linea.end(), [](char c) { return !isdigit(c) && c != ',' && c != '{' && c != '}'; }), linea.end());
        
        // Eliminar llaves
        linea.erase(remove(linea.begin(), linea.end(), '{'), linea.end());
        linea.erase(remove(linea.begin(), linea.end(), '}'), linea.end());
        
        // Convertir la línea en enteros
        size_t pos = 0;
        while ((pos = linea.find(',')) != string::npos) {
            string token = linea.substr(0, pos);
            try {
                vec.push_back(stoi(token));
            } catch (const invalid_argument& e) {
                cerr << "Error de conversión en el archivo de datos: " << e.what() << " (token: " << token << ")\n";
            }
            linea.erase(0, pos + 1);
        }
        try {
            vec.push_back(stoi(linea));  // Último número
        } catch (const invalid_argument& e) {
            cerr << "Error de conversión en el archivo de datos: " << e.what() << " (token: " << linea << ")\n";
        }

        dataset.push_back(vec);
    }

    archivo.close();
    return dataset;
}

// Función para medir el tiempo de ejecución en microsegundos "us"
template<typename SortFunction>
void medirTiempo(vector<int>& vec, SortFunction sortFunction, const string& nombreArchivo, const string& nombreArchivoSalida) {
    auto inicio = high_resolution_clock::now();
    sortFunction(vec);
    auto fin = high_resolution_clock::now();
    auto duracion = duration_cast<microseconds>(fin - inicio).count();

    ofstream archivo(nombreArchivo, ios::app);
    if (archivo.is_open()) {
        archivo << vec.size() << "," << duracion << "\n";
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo para escritura.\n";
    }

    ofstream archivo2(nombreArchivoSalida, ios::app);
    if (archivo2.is_open()) {
        archivo2 << "{";
        for (size_t i = 0; i < vec.size(); ++i) {
            archivo2 << vec[i];
            if (i < vec.size() - 1) {
                archivo2 << ", ";
            }
        }
        archivo2 << "}" << "\n";
        archivo2.close();
    } else {
        cerr << "No se pudo abrir el archivo para escritura.\n";
    }


}

// Función principal
int main() {
    fs::create_directory("resultados"); // dir de .csv con vector.size() y tiempo de ejecución
    fs::create_directory("salida"); // dir de .txt con vectores ordenados por algoritmos

    vector<vector<int>> dataset = leerDataset("dataset.txt");

    // Bubble Sort
    ofstream bubbleFile("resultados/bubbleSort.csv");
    bubbleFile << "Tamaño,Tiempo\n";
    bubbleFile.close();
    for (auto& vec : dataset) {
        vector<int> v = vec;  // Copiar el vector
        medirTiempo(v, bubbleSort, "resultados/bubbleSort.csv","salida/bubbleSort.txt" );
    }

    // Selection Sort
    ofstream selectionFile("resultados/selectionSort.csv");
    selectionFile << "Tamaño,Tiempo\n";
    selectionFile.close();
    for (auto& vec : dataset) {
        vector<int> v = vec;  // Copiar el vector
        medirTiempo(v, selectionSort, "resultados/selectionSort.csv", "salida/selectionSort.txt");
    }

    // Merge Sort
    ofstream mergeFile("resultados/mergeSort.csv");
    mergeFile << "Tamaño,Tiempo\n";
    mergeFile.close();
    for (auto& vec : dataset) {
        vector<int> v = vec;  // Copiar el vector
        medirTiempo(v, mergeSort, "resultados/mergeSort.csv", "salida/mergeSort.txt");
    }

    // Quick Sort
    ofstream quickFile("resultados/quickSort.csv");
    quickFile << "Tamaño,Tiempo\n";
    quickFile.close();
    for (auto& vec : dataset) {
        vector<int> v = vec;  // Copiar el vector
        medirTiempo(v, quickSort, "resultados/quickSort.csv", "salida/quickSort.txt");
    }

   // Función std::sort de nativa de C++
    ofstream stdsortFile("resultados/std::sort.csv");
    stdsortFile << "Tamaño,Tiempo\n";
    stdsortFile.close();
    for (auto& vec : dataset) {
        vector<int> v = vec;  // Copiar el vector
        medirTiempo(v, quickSort, "resultados/std::sort.csv", "salida/std::sort.txt");
    } 

    return 0;
}
