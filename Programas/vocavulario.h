/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial Avanzada
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    02/05/2024
 * @brief   Definicion de la clase vocavulario.
*/

#ifndef VOCAVULARIO_H_
#define VOCAVULARIO_H_

#include <fstream>
#include <iostream>
#include <string>
#include <set>

/**
 * @brief Clase lectorArchivo que estara a cargo de la lectura y filtracion de los correos leidos.
 * 
 * @param ficheroSalida_          - Nombre del archivo de salida.
 * @param diccionario_            - Conjunto que guarda todas las palabras seleccionadas.
 * @param numeroPalabrasUnicas_   - Número total de palabras únicas en el diccionario.
 */

class vocavulario {
 private:
  std::string ficheroSalida_;
  std::set<std::string> diccionario_;
  int numeroPalabrasUnicas_;
 public:
  vocavulario (std::string);
  void añadirPalabra (std::string);
  std::set<std::string> obtenerDiccionario ();
  void escribirDiccionario ();
  int getNumPalabrasUnicas ();
};

#endif