/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial Avanzada
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    02/05/2024
 * @brief   Main del programa procesador de Datos. Iniciara el proceso de lectura de texto y calculara el tiempo total trancurrido.
*/

#include <iostream>
#include <string>
#include <chrono>

#include "vocavulario.h"
#include "phishing.h"
#include "safe.h"
#include "procesador.h"

int main() {
  std::string nombreArchivoEntrada = "../Ficheros/Prueba.csv";
  std::string nombreArchivoSalidaVocavulario = "../Ficheros/vocavulario.txt";
  std::string nombreArchivoSalidaPhishing = "../Ficheros/corpus_P.txt";
  std::string nombreArchivoSalidaSafe = "../Ficheros/corpus_S.txt";
  std::string nombreArchivoModeloPhishing = "../Ficheros/modelo_lenguaje_P.txt";
  std::string nombreArchivoModeloSafe = "../Ficheros/modelo_lenguaje_S.txt";
  vocavulario vocavularioGeneral(nombreArchivoSalidaVocavulario);
  phishing vocavularioPhishing(nombreArchivoSalidaPhishing);
  safe vocavularioSafe(nombreArchivoSalidaSafe);
  procesador procesador(nombreArchivoEntrada, nombreArchivoModeloSafe, nombreArchivoModeloPhishing);

  //Generear vocavulario y corpus
  auto start = std::chrono::high_resolution_clock::now();
  procesador.procesarArchivo(vocavularioGeneral, vocavularioPhishing, vocavularioSafe);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  double segundos = duration.count() / 1000000.0;
  std::cout << "Tiempo de ejecución generar vocavulario y corpus: " << segundos << " segundos" << std::endl;

  //Generar Modelo de Lenguaje
  start = std::chrono::high_resolution_clock::now();
  std::map<std::string, double> modeloSafe = procesador.generarModeloLenguajeSafe(vocavularioGeneral, vocavularioSafe);
  std::map<std::string, double> modeloPhishing = procesador.generarModeloLenguajePhishing(vocavularioGeneral, vocavularioPhishing);
  procesador.escribirModeloLenguajeSafe(vocavularioGeneral, vocavularioSafe, modeloSafe);
  procesador.escribirModeloLenguajePhishing(vocavularioGeneral, vocavularioPhishing, modeloPhishing);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  segundos = duration.count() / 1000000.0;
  std::cout << "Tiempo de ejecución Modelo de Lenguaje: " << segundos << " segundos" << std::endl;
  return 0;
}