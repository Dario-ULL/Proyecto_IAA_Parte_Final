/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial Avanzada
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    02/05/2024
 * @brief   Implentacion de las funciones de la clase clasificar
*/

#include "clasificar.h"

/**
 * @brief Constructor de la clase Clasificar.
 * 
 * @param ficheroClasificacion Nombre del archivo donde se guardarán los resultados de la clasificación.
 * @param ficheroResumen Nombre del archivo donde se guardará el resumen de la clasificación.
 */
clasificar::clasificar (std::string ficheroClasificacion, std::string ficheroResumen) {
  ficheroClasificacion_ = ficheroClasificacion;
  ficheroResumen_ = ficheroResumen;
}

/**
 * @brief Función que realiza la clasificación de correos.
 * 
 * @param listadoCorreos Nombre del archivo que contiene el listado de correos a clasificar.
 * @param modeloPhishing Nombre del archivo que contiene el modelo de lenguaje para correos de phishing.
 * @param modeloSafe Nombre del archivo que contiene el modelo de lenguaje para correos seguros.
 */
void 
clasificar::clasificador (std::string& listadoCorreos, std::string& modeloPhishing, std::string& modeloSafe) {
  std::ifstream archivoCorreos(listadoCorreos);
  std::map<std::string, double> tablaProbabilidadesPH = calcularProbabilidad(modeloPhishing);
  std::map<std::string, double> tablaProbabilidadesS = calcularProbabilidad(modeloSafe);
  if (!archivoCorreos.is_open()) {
    std::cerr << "Error al abrir el archivo " << listadoCorreos << std::endl;
    exit(1);
  }
  std::string linea;
  std::string correo;
  std::string tipo;
  bool primerSegmento = true;
  bool segundoSegmento = false;
  std::getline(archivoCorreos, linea);
  while (std::getline(archivoCorreos, linea)) {
    bool procesar = false;
    int it = 0;
    if (primerSegmento == true) {
      primerSegmento = false;
      segundoSegmento = true;
      while (linea[it] != ';') {
        if (it == linea.size()) {
          break;
        }
        it++;
      }
      if (it != linea.size()) {
        linea.erase(0, it + 1);
      } 
    }    
    it = linea.size();
    if (segundoSegmento == true) {
      bool cortar = false;
      while (it != 0) {
        it--;
        if (linea[it] == ';') {
          cortar = true;
          break;
        }
      }
      if (cortar == true) {
        for (int i = it + 1; i < linea.size(); i++) {
          tipo.push_back(linea[i]);
        }
        linea.erase(linea.begin() + it, linea.end());
        procesar = true;
        primerSegmento = true;
        segundoSegmento = false;
      }      
    }
    if (!linea.empty()) {
      correo += linea;
    }       
    if (procesar == true) {
      double proabilidadPH = probabilidadCorreoTipo(correo, tablaProbabilidadesPH);
      double proabilidadS = probabilidadCorreoTipo(correo, tablaProbabilidadesS);
      proabilidadPH = (proabilidadPH * 100) / 100;
      proabilidadS = (proabilidadS * 100) / 100;
      std::string primeros_10_caracteres = correo.substr(0, 10);
      escribirResultados(primeros_10_caracteres, proabilidadS, proabilidadPH, tipo);
      tipo.clear();
      correo.clear();
    }
  }
  archivoCorreos.close();    
}

/**
 * @brief Función que escribe los resultados de la clasificación en un archivo.
 * 
 * @param caracteres Primeros 10 caracteres del correo.
 * @param probS Probabilidad del correo de ser seguro.
 * @param probPH Probabilidad del correo de ser phishing.
 * @param tipo Tipo de correo clasificado.
 */
void 
clasificar::escribirResultados (std::string& caracteres, double& probS, double& probPH, std::string& tipo) {
  std::ofstream archivoSalida(ficheroClasificacion_, std::ios::app);
  if (archivoSalida.is_open()) {
		archivoSalida << caracteres << "," << probS << "," << probPH << "," << tipo << std::endl;
		archivoSalida.close();
	} else {
		std::cerr << "Error al abrir el archivo." << std::endl;
	}
}

/**
 * @brief Función que calcula la probabilidad de un correo de ser de cierto tipo.
 * 
 * @param correo Correo a clasificar.
 * @param tablaProbabilidades Tabla de probabilidades de palabras.
 * @return Probabilidad del correo de ser del tipo especificado.
 */
std::map<std::string, double> 
clasificar::calcularProbabilidad (std::string& fichero) {
  std::ifstream archivoCorreos(fichero);
  std::map<std::string, double> tablaProbabilidades;
  if (!archivoCorreos.is_open()) {
    std::cerr << "Error al abrir el archivo " << fichero << std::endl;
    exit(1);
  }
  std::string linea;
  std::getline(archivoCorreos, linea);
  std::getline(archivoCorreos, linea);
  while (std::getline(archivoCorreos, linea)) {
    std::stringstream ss(linea);
    std::string prefijo, palabra;
    int frecuencia;
    double log_probabilidad;
    ss >> prefijo;
    ss >> palabra;
    ss >> prefijo >> frecuencia;
    ss >> prefijo;
    ss >> log_probabilidad;
    tablaProbabilidades.insert(std::pair<std::string, double>(palabra, log_probabilidad));
  }
  return tablaProbabilidades;
}

/**
 * @brief Función que calcula la probabilidad de un correo de ser de cierto tipo.
 * 
 * @param correo Correo a clasificar.
 * @param tablaProbabilidades Tabla de probabilidades de palabras.
 * @return Probabilidad del correo de ser del tipo especificado.
 */
double 
clasificar::probabilidadCorreoTipo (std::string& correo, std::map<std::string, double>& tablaProbabilidades) {
  double resultado = 0;
  std::stringstream ss(correo);
  std::string palabra;
  while (ss >> palabra) {
    if (tablaProbabilidades.find(palabra) != tablaProbabilidades.end()) {
      resultado += tablaProbabilidades[palabra];
    } else {
      resultado += tablaProbabilidades["tokenUnknow"];
    }
  }
  return resultado;
}

/**
 * @brief Función que genera un resumen de la clasificación y lo guarda en un archivo.
 */
void 
clasificar::resumen () {
  std::ifstream archivoClasificacion(ficheroClasificacion_);
  std::ofstream archivoResumen(ficheroResumen_);
  std::map<std::string, double> tablaProbabilidades;
  if (!archivoClasificacion.is_open()) {
    std::cerr << "Error al abrir el archivo " << ficheroClasificacion_ << std::endl;
  }
  if (!archivoResumen.is_open()) {
		std::cerr << "Error al abrir el archivo." << ficheroResumen_ << std::endl;
    exit(1);
	}
  std::string linea;
  while (std::getline(archivoClasificacion, linea)) {
    std::stringstream ss(linea);
    std::string aux;
    double probPH, probS;
    int contador = 0;
    while (std::getline(ss, aux, ',')) {
      contador++;
      if (contador == 2) {
        std::stringstream(aux) >> probS;
      } else if (contador == 3) {
        std::stringstream(aux) >> probPH;
      }
    }
    if (probPH < probS) {
      archivoResumen << "Safe Email" << std::endl;
    } else {
      archivoResumen << "Phishing Email" << std::endl;
    }
  }
}

/**
 * @brief Función que calcula el porcentaje de aciertos en la clasificación.
 */
void
clasificar::calcularAcierto () {
  std::ifstream archivoClasificacion(ficheroClasificacion_);
  std::ifstream archivoResumen(ficheroResumen_);
  std::string lineaClasificacion, lineaResumen;
  double numAciertos = 0;
  int numLineas = 0;
  while (std::getline(archivoClasificacion, lineaClasificacion)) {
    size_t finalLinea = lineaClasificacion.find_last_of(',');
    std::string tipoCorreo;
    if (finalLinea != std::string::npos) {
      tipoCorreo = lineaClasificacion.substr(finalLinea + 1);
    }
    std::getline(archivoResumen, lineaResumen);
    if (lineaResumen == tipoCorreo) {
      numAciertos++;
    }
    numLineas++;
  }
  std::cout << "Porcentaje de aciertos: " << (numAciertos / numLineas) * 100 << "%" << std::endl;
}