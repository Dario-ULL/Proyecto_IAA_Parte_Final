/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial Avanzada
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    02/05/2024
 * @brief   Definicion de la clase clasificar
*/

#ifndef CLASIFICADOR_H_
#define CLASIFICADOR_H_

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <sstream>

/**
 * @brief Clase para clasificar correos electrónicos y generar un resumen de la clasificación.
 * 
 * @param ficheroClasificacion_ Nombre del archivo donde se guardarán los resultados de la clasificación.
 * @param ficheroResumen_ Nombre del archivo donde se guardará el resumen de la clasificación.
 */
class clasificar {
 private:
  std::string ficheroClasificacion_;
  std::string ficheroResumen_;
 public:
  clasificar (std::string, std::string);
  void clasificador (std::string&, std::string&, std::string&);
  void escribirResultados (std::string&, double&, double&, std::string&);
  std::map<std::string, double> calcularProbabilidad (std::string&);
  double probabilidadCorreoTipo (std::string&, std::map<std::string, double>&);
  void resumen ();
  void calcularAcierto ();
};

#endif