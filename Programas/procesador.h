/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial Avanzada
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    02/05/2024
 * @brief   Definicion de la clase procesador y del unordered_set "stopwords".
*/

#ifndef PROCESADOR_H_
#define PROCESADOR_H_

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <regex>
#include <map>
#include <cmath>

#include "vocavulario.h"
#include "phishing.h"
#include "safe.h"

class vocavulario;
class phishing;
class safe;

/**
 * @brief Clase procesador que estara a cargo de la lectura y filtracion de los correos leidos.
 * 
 * @param ficheroEntrada_                   -  Atributo privado que guarda el nombre del fichero que se debe leer.
 * @param ficheroModeloLenguajeSafe_        -  Atributo privado que guarda el nombre del fichero donde se va a escribir el Modelo de Lenguaje Safe.
 * @param ficheroModeloLenguajePhishing_    -  Atributo privado que guarda el nombre del fichero donde se va a escribir el Modelo de Lenguaje Phishing.
*/
class procesador {
 private:
  std::string ficheroEntrada_;
  std::string ficheroModeloLenguajeSafe_;
  std::string ficheroModeloLenguajePhishing_;
 public:
  procesador (std::string, std::string, std::string);
  void procesarArchivo (vocavulario&, phishing&, safe&);
  void eliminarSignos (std::string&);
  void convertirMinusculas (std::string&);
  void eliminarEspaciosDobles (std::string&);
  void eliminarPalabrasResevadas (std::string&);
  void eliminarEmojisYEmoticonos (std::string&);
  void elimianrEnlaces(std::string&);
  void elimianrhashtags(std::string&);
  void eliminarNumeros(std::string&);
  void eliminarCaracteresNoImprimibles(std::string&);
  void añadirAlDiccionario (vocavulario&, const std::string&);
  void añadirAlCorpusP (phishing&, const std::string&);
  void añadirAlCorpusS (safe&, const std::string&);

  std::map<std::string, double> generarModeloLenguajeSafe (vocavulario&, safe&);
  std::map<std::string, double> generarModeloLenguajePhishing (vocavulario&, phishing&);
  void escribirModeloLenguajeSafe (vocavulario&, safe&, std::map<std::string, double>&);
  void escribirModeloLenguajePhishing (vocavulario&, phishing&, std::map<std::string, double>&);
};


// Definición de palabras reservadas (stopwords) en inglés
const std::unordered_set<std::string> stopwords = {
  "a", "able", "about", "across", "after", "all", "almost", "also", "am", "among",
  "an", "and", "any", "are", "as", "at", "b", "be", "because", "been", "but", "by",
  "can", "cannot", "could", "dear", "did", "do", "does", "either", "else", "ever",
  "every", "for", "from", "get", "got", "had", "has", "have", "he", "her", "hers",
  "him", "his", "how", "however", "i", "if", "in", "into", "is", "it", "its", "just",
  "least", "let", "like", "likely", "may", "me", "might", "most", "must", "my",
  "neither", "no", "nor", "not", "of", "off", "often", "on", "only", "or", "other",
  "our", "own", "rather", "said", "say", "says", "she", "should", "since", "so",
  "some", "than", "that", "the", "their", "them", "then", "there", "these", "they",
  "this", "tis", "to", "too", "twas", "us", "wants", "was", "we", "were", "what",
  "when", "where", "which", "while", "who", "whom", "why", "will", "with", "would",
  "yet", "you", "your"
};

#endif