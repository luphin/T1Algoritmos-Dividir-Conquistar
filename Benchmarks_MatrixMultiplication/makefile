# Nombre del compilador
CXX = g++

# Opciones del compilador
CXXFLAGS = -Wall -std=c++17

# Nombre del archivo ejecutable
GENERATOR = generar_matrices

# Nombre del ejecutable principal
TARGET = multiplicacion

# Archivos fuente
SRC_GEN = generateDTS.cpp
SRC_MAIN = main.cpp

# Regla para compilar el generador de dataset
all: prepare $(GENERATOR)
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
	rm -f datasetMatrix.txt
	rm -f resultados/*.csv
	rm -f salida/*.txt

