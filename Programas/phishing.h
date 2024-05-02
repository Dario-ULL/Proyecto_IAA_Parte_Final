/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial Avanzada
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    02/05/2024
 * @brief   Definicion de la clase vocavulario.
*/

#ifndef PHISHING_H_
#define PHISHING_H_

#include <fstream>
#include <iostream>
#include <string>
#include <map>

/**
 * @brief Clase phishing encargada de la lectura y filtración de los correos.
 * 
 * @param ficheroSalida_  - Nombre del archivo de salida.
 * @param diccionario_    - Mapa que guarda todas las palabras seleccionadas y su frecuencia.
 * @param numeroPalabras_ - Número total de palabras en el diccionario.
 * @param numCorreos_     - Número de correos en el diccionario de phishing.
 */
class phishing {
 private:
  std::string ficheroSalida_;
  std::map<std::string, int> diccionario_;
  int numeroPalabras_;
  int numCorreos_;
 public:
  phishing (std::string);
  void añadirPalabra (std::string);
  std::map<std::string, int> obtenerDiccionario ();
  void escribirDiccionario ();
  void setNumCorreos (int);
  int getNumCorreos ();
  int getNumPalabras ();
};

#endif