/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial Avanzada
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    02/05/2024
 * @brief   Implementacion de las funciones de la clase safe.
*/

#include "safe.h"

/**
 * @brief Constructor de la clase safe.
 * 
 * Inicializa el número de palabras del diccionario en 0.
 */
safe::safe(std::string ficheroSalida) {
  ficheroSalida_ = ficheroSalida;
  numeroPalabras_ = 0;
}

/**
 * @brief Añade una palabra al diccionario.
 * 
 * @param palabra La palabra que se añadirá al diccionario.
 */
void 
safe::añadirPalabra(std::string palabra) {
	auto it = diccionario_.find(palabra);
	if (it == diccionario_.end()) {
		diccionario_.insert(std::pair<std::string, int>(palabra, 1));
		numeroPalabras_++;
	} else {
    it->second++;
  }
}

/**
 * @brief Obtiene el diccionario de palabras.
 * 
 * @return Un conjunto de cadenas que representa el diccionario de palabras.
 */
std::map<std::string, int> 
safe::obtenerDiccionario() {
  return diccionario_;
}

/**
 * @brief Escribe el diccionario en un archivo.
 * 
 * @param fichero El nombre del archivo donde se escribirá el diccionario.
 */
void 
safe::escribirDiccionario() {
	std::ofstream archivo(ficheroSalida_);
	if (archivo.is_open()) {
		archivo << "Numero de palabras del corpus Safe: " << numeroPalabras_ << std::endl;
		for (const auto& par : diccionario_) {
      archivo << "Palabra: " << par.first << "  Frec: " << par.second << std::endl;
    }
		archivo.close();
	} else {
		std::cerr << "Error al abrir el archivo." << std::endl;
	}
}

/**
 * @brief Establece el número de correos en el diccionario seguro.
 * 
 * @param numFicheros El número de correos a establecer.
 */
void
safe::setNumCorreos (int numFicheros) {
	numCorreos_ = numFicheros;
}

/**
 * @brief Obtiene el número de correos en el diccionario seguro.
 * 
 * @return El número de correos en el diccionario seguro.
 */
int 
safe::getNumCorreos () {
	return numCorreos_;
}

/**
 * @brief Obtiene el número total de palabras en el diccionario seguro.
 * 
 * @return El número total de palabras en el diccionario seguro.
 */
int 
safe::getNumPalabras () {
	return numeroPalabras_;
}