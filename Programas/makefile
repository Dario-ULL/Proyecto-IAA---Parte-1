# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Asignatura: INTELIGENCIA ARTIFICIAL AVANZADA
# Curso: 3º
# Práctica: Proyecto IAA (Parte 1)
# Autores: Dario Dominguez Gonzalez
# Correos: alu0101408095@ull.edu.es
# Fecha: 18/04/2024
# Archivo GNUMakefile


CXX = g++
CXXFLAGS = -std=c++17 -g
LDFLAGS =

all: programa clear

programa: programa.o vocavulario.o lectorArchivo.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean
	$(CXX) $(CXXFLAGS) -c $<

clear: 
	rm -rf *.o
	
clean :
	find . -name '*.o' -type f -delete
	rm -rf *~ basura b i
	rm -rf a.out main
	find . -name '*~' -exec rm {} \;
	find . -name basura -exec rm {} \;