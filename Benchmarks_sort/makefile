# Nombre del compilador
CXX = g++

# Bandera para mostrar todos los errores y advertencias
CXXFLAGS = -Wall -std=c++17

# Nombre del ejecutable para el generador de dataset
GENERATOR = generateDTS

# Nombre del ejecutable principal
TARGET = ordenamiento

# Archivos fuente
SRC_GEN = generateDTS.cpp
SRC_MAIN = main.cpp

# Regla para compilar el generador de dataset
dataset: $(GENERATOR)
	./$(GENERATOR)

$(GENERATOR): $(SRC_GEN)
	$(CXX) $(CXXFLAGS) -o $(GENERATOR) $(SRC_GEN)

# Regla para compilar el programa principal
$(TARGET): $(SRC_MAIN)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC_MAIN)

# Regla para ejecutar el programa principal
run: $(TARGET)
	./$(TARGET)

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET) $(GENERATOR)

# Regla para preparar el entorno antes de generar el dataset
prepare:
	rm -f dataset.txt
	rm -f resultados/*.csv
	rm -f salida/*.txt

# Regla por defecto que compila, genera el dataset y el ejecutable
all: prepare dataset $(TARGET)
