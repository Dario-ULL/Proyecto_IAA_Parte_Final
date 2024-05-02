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

Procesar: procesador clear
Clasificar: clasificador clear

procesador: programaProcesador.o vocavulario.o procesador.o phishing.o safe.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clasificador: programaClasificador.o clasificar.o
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