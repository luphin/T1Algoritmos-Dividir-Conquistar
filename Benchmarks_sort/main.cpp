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
    // Largo de vector
    int n = v.size();
    // Iterar en todo el vector
    for (int i = 0; i < n - 1; i++) {
        // Iterar hasta el penúltimo elemento
        for (int j = 0; j < n - i - 1; j++) { 
            // Comparacion entre elementos
            if (v[j] > v[j + 1]) { 
                swap(v[j], v[j + 1]); // Cambio
            }
        }
    }
}

// Función de selectionSort obternida de :  https://www.geeksforgeeks.org/selection-sort-algorithm-2/
void selectionSort(vector<int>& arr) {
    // Largo de vector
    int n = arr.size();
    // Iterar en todo el vector
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;  // Minimo elemento encontrado
        // Iterar entre el elemento siguiente y el último
        for (int j = i + 1; j < n; j++) {
            //  CAmbiar valor de min_idx si existe un valor menor que el actual
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // CAmbiar el valor actual con el menor encontrado
        if (min_idx != i) {
            swap(arr[min_idx], arr[i]);
        }
    }
}

// Función de mergeSort obtenidade: https://www.geeksforgeeks.org/merge-sort/
// compuesta por las funciones: merge, mergeSortHelper y mergeSort
// se aplicó una funcion mergeSortHelper porque habia problemas con la entrada, sigue manteniedo la forma original

// Función que fusiona dos arreglos ordenados en un solo arreglo ordenado
void merge(vector<int>& arr, int left, int mid, int right) {
    // Calcular tamaño de secuencias
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Arreglos para almacenar secuencias
    vector<int> L(n1), R(n2);

    // Copiar parte izquierda del arreglo
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    // Copiar parte derecha del arreglo
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    // Juntar secuancias ordenadas
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
    // Copiar elementos de subsecuencia izquierda
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    // Copiar elementos de subsecuencia derecha
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
// Función recursiva que ordena una subsecuencia del arreglo
void mergeSortHelper(vector<int>& arr, int left, int right) {
    // Caso base. un solo elemento, ordenado
    if (left >= right) {
        return;
    }
    // Cálculo índice medio pra subconjuntos
    int mid = left + (right - left) / 2;
    // Ordenar subconjunto izquierdo/derecho
    mergeSortHelper(arr, left, mid);
    mergeSortHelper(arr, mid + 1, right);
    // Juntar subconjuntos
    merge(arr, left, mid, right);
}
// Función principal que ordena el arreglo
void mergeSort(vector<int>& arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
}

// Función de quickSort obtenida de : https://www.geeksforgeeks.org/cpp-program-for-quicksort/
// compuesta por las funciones: partition, quickSortHElper y quickSort
// quickSortHelper fue agregada porque habian problemas con la entrada

// Función que particiona el arreglo en dos subarreglos
int partition(vector<int>& vec, int low, int high) {
    // Último elemeto va aser pivot
    int pivot = vec[high];
    // indice de partición
    int i = (low - 1);
    // Paricionar Arreglo
    for (int j = low; j <= high - 1; j++) {
        // Elemento actual menor que el pivot, lo mueve a la izquierda
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }
    // Mover piot a posicion final
    swap(vec[i + 1], vec[high]);
    // Retornar indice pivot
    return (i + 1);
}

// Función recursiva que ordena la subsecuencia
void quickSortHelper(vector<int>& vec, int low, int high) {
    // CAso base
    if (low < high) {
        // Particionar subsecuencia
        int p = partition(vec, low, high);
        // Odenar subsecuencias izquierda/derecha
        quickSortHelper(vec, low, p - 1);
        quickSortHelper(vec, p + 1, high);
    }
}
// Función principal que ordena el arreglo
void quickSort(vector<int>& vec) {
    // Llama a la función recursiva con los índices inferior y superior del arreglo original
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
    // Medir tiempo de ejecución
    auto inicio = high_resolution_clock::now();
    sortFunction(vec);
    auto fin = high_resolution_clock::now();
    auto duracion = duration_cast<microseconds>(fin - inicio).count();
    
    // Escritura de los resultados de los tiempos medidos
    ofstream archivo(nombreArchivo, ios::app);
    if (archivo.is_open()) {
        archivo << vec.size() << "," << duracion << "\n";
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo para escritura.\n";
    }
    // Escritura de llos vectores una vez ordenados
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
