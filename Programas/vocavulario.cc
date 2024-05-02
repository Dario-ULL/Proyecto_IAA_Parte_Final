/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial Avanzada
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    02/05/2024
 * @brief   Implementacion de las funciones de la clase vocavulario.
*/

#include "vocavulario.h"

/**
 * @brief Constructor de la clase vocavulario.
 * 
 * Inicializa el número de palabras del diccionario en 0.
 */
vocavulario::vocavulario(std::string ficheroSalida) {
  ficheroSalida_ = ficheroSalida;
  numeroPalabrasUnicas_ = 0;
}

/**
 * @brief Añade una palabra al diccionario.
 * 
 * @param palabra La palabra que se añadirá al diccionario.
 */
void 
vocavulario::añadirPalabra(std::string palabra) {
	auto it = diccionario_.find(palabra);
	if (it == diccionario_.end()) {
		diccionario_.insert(palabra);
		numeroPalabrasUnicas_++;
	}
}

/**
 * @brief Obtiene el diccionario de palabras.
 * 
 * @return Un conjunto de cadenas que representa el diccionario de palabras.
 */
std::set<std::string> 
vocavulario::obtenerDiccionario() {
	return diccionario_;
}

/**
 * @brief Escribe el diccionario en un archivo.
 * 
 * @param fichero El nombre del archivo donde se escribirá el diccionario.
 */
void 
vocavulario::escribirDiccionario() {
	std::ofstream archivo(ficheroSalida_);
	if (archivo.is_open()) {
		archivo << "Numero de palabras: " << numeroPalabrasUnicas_ << std::endl;
		for (const auto& elemento : diccionario_) {
      archivo << elemento << std::endl;
    }
		archivo.close();
	} else {
		std::cerr << "Error al abrir el archivo." << std::endl;
	}
}

/**
 * @brief Obtiene el número total de palabras únicas en el diccionario.
 * 
 * @return El número total de palabras únicas en el diccionario.
 */
int 
vocavulario::getNumPalabrasUnicas () {
	return numeroPalabrasUnicas_;
}
