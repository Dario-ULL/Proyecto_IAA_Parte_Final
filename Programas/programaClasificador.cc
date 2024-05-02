/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial Avanzada
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    02/05/2024
 * @brief   Main del programa clasificado. Iniciara el proceso de lectura de texto y calculara el tiempo total trancurrido.
*/

#include <iostream>
#include <string>
#include <chrono>

#include "clasificar.h"

int main() {
  std::string nombreArchivoEntrada = "../Ficheros/Comprobar.csv";
  std::string nombreArchivoModeloPhishing = "../Ficheros/modelo_lenguaje_P.txt";
  std::string nombreArchivoModeloSafe = "../Ficheros/modelo_lenguaje_S.txt";
  std::string nombreArchivoClasificador = "../Ficheros/clasificacion_alu0101408095.csv";
  std::string nombreArchivoResumen = "../Ficheros/resumen_alu0101408095.csv";
  clasificar clasificador(nombreArchivoClasificador, nombreArchivoResumen);
  
  //Vaciar archivo
  std::ofstream vaciarArchivo(nombreArchivoClasificador);
  if (!vaciarArchivo.is_open()) {
      std::cerr << "Error al abrir el archivo." << std::endl;
      return 1;
  }
  vaciarArchivo.close();  
  
  //Generar la clasificacion
  auto start = std::chrono::high_resolution_clock::now();
  clasificador.clasificador(nombreArchivoEntrada, nombreArchivoModeloPhishing, nombreArchivoModeloSafe);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  double segundos = duration.count() / 1000000.0;
  std::cout << "Tiempo de ejecución para generar la clasificaion: " << segundos << " segundos" << std::endl;

  //Generar el resumen
  start = std::chrono::high_resolution_clock::now();
  clasificador.resumen();
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  segundos = duration.count() / 1000000.0;
  std::cout << "Tiempo de ejecución para generar el resumen: " << segundos << " segundos" << std::endl;

  //Calcular aciertos
  clasificador.calcularAcierto();
  return 0;
}