/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial Avanzada
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    02/05/2024
 * @brief   Implentacion de las funciones de la clase procesador
*/

#include "procesador.h"


/**
 * @brief Constructor de la clase procesador.
 * 
 * @param nombreArchivoEntrada Nombre del archivo de entrada.
 * @param nombreArchivoSalida Nombre del archivo de salida.
 */
procesador::procesador(std::string nombreArchivoEntrada, std::string ficheroModeloLenguajeSafe, std::string ficheroModeloLenguajePhishing) {
  ficheroEntrada_ = nombreArchivoEntrada;
  ficheroModeloLenguajePhishing_ = ficheroModeloLenguajePhishing;
  ficheroModeloLenguajeSafe_ = ficheroModeloLenguajeSafe;
}

/**
 * @brief Procesa el texto del archivo, aplicando una serie de transformaciones y extrayendo las palabras
 * para añadirlas al diccionario.
 * 
 * @param diccionario Instancia de la clase vocavulario donde se añadirán las palabras procesadas.
 */
void 
procesador::procesarArchivo (vocavulario& diccionarioGeneral, phishing& diccionarioPhishing, safe& diccionarioSafe) {
  std::ifstream archivo(ficheroEntrada_);
  if (!archivo.is_open()) {
      std::cerr << "Error al abrir el archivo " << ficheroEntrada_ << std::endl;
      exit(1);
  }
  std::string linea;
  std::string correo;
  std::string tipo;
  bool primerSegmento = true;
  bool segundoSegmento = false;
  int numCorrerosSafe = 0;
  int numCorreosPhishing = 0;
  std::set<std::string> errores;
  std::getline(archivo, linea);
  while (std::getline(archivo, linea)) {
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
      convertirMinusculas(correo);
      eliminarSignos(correo);
      elimianrEnlaces(correo);
      elimianrhashtags(correo);
      eliminarPalabrasResevadas(correo);
      eliminarEmojisYEmoticonos(correo);
      eliminarNumeros(correo);
      eliminarCaracteresNoImprimibles(correo);
      eliminarEspaciosDobles(correo);
      añadirAlDiccionario(diccionarioGeneral, correo);
      if (tipo == "Safe Email") {
        añadirAlCorpusS(diccionarioSafe, correo);
        numCorrerosSafe++;
      } else if (tipo == "Phishing Email") {
        añadirAlCorpusP(diccionarioPhishing, correo);
        numCorreosPhishing++;
      }
      tipo.clear();
      correo.clear();
    }      
  }
  diccionarioGeneral.escribirDiccionario();
  diccionarioPhishing.escribirDiccionario();
  diccionarioSafe.escribirDiccionario();
  diccionarioPhishing.setNumCorreos(numCorreosPhishing);
  diccionarioSafe.setNumCorreos(numCorrerosSafe);
  archivo.close();
}

/**
 * @brief Elimina los signos de puntuación de una cadena de texto.
 * 
 * @param texto La cadena de texto de la que se eliminarán los signos de puntuación.
 */
void
procesador::eliminarSignos (std::string& texto) {
  std::regex patron("[[:punct:]]");
  texto = std::regex_replace(texto, patron, " ");
}

/**
 * @brief Convierte todos los caracteres de una cadena de texto a minúsculas.
 * 
 * @param texto La cadena de texto que se convertirá a minúsculas.
 */
void
procesador::convertirMinusculas (std::string& texto) {
  for (char& c : texto) {
    c = std::tolower(c);
  }
}

/**
 * @brief Elimina los espacios dobles de una cadena de texto.
 * 
 * @param texto La cadena de texto de la que se eliminarán los espacios dobles.
 */
void
procesador::eliminarEspaciosDobles (std::string& texto) {
  bool ultimoEspacio = false;
  int indice = 0;
  while (indice < texto.length()) {
    if (texto[indice] == ' ' && ultimoEspacio) {
      texto.erase(indice, 1);
    } else {
      ultimoEspacio = (texto[indice] == ' ');
      indice++;
    }
  }
}

/**
 * @brief Elimina las palabras reservadas de una cadena de texto.
 * 
 * @param texto La cadena de texto de la que se eliminarán las palabras reservadas.
 */
void
procesador::eliminarPalabrasResevadas (std::string& texto) {
  std::stringstream resultadoStream(texto);
  std::string palabra;
  texto.clear();
  while (resultadoStream >> palabra) {
    if (stopwords.find(palabra) == stopwords.end()) {
      if (!texto.empty()) {
        texto += " ";
      }
      texto += palabra;
    }
  }
}

/**
 * @brief Elimina emojis y emoticonos de una cadena de texto.
 * 
 * @param texto La cadena de texto de la que se eliminarán emojis y emoticonos.
 */
void
procesador::eliminarEmojisYEmoticonos (std::string& texto) {
  std::regex emojiRegex(u8"[\U0001F300-\U0001F9FF]");
  texto = std::regex_replace(texto, emojiRegex, " ");
}

/**
 * @brief Elimina enlaces URL de una cadena de texto.
 * 
 * @param texto La cadena de texto de la que se eliminarán los enlaces URL.
 */
void 
procesador::elimianrEnlaces(std::string& texto) {
  std::regex urlRegex(R"(https?://\S+|www\.\S+)");
  texto = std::regex_replace(texto, urlRegex, " ");
}

/**
 * @brief Elimina hashtags de una cadena de texto.
 * 
 * @param texto La cadena de texto de la que se eliminarán los hashtags.
 */
void 
procesador::elimianrhashtags(std::string& texto) {
  std::regex hashtagRegex(R"(\#\s?\w+)");
  texto = std::regex_replace(texto, hashtagRegex, " ");
}

/**
 * @brief Elimina números de una cadena de texto.
 * 
 * @param texto La cadena de texto de la que se eliminarán los números.
 */
void 
procesador::eliminarNumeros (std::string& texto) {
  texto.erase(std::remove_if(texto.begin(), texto.end(), [](char caracter) { 
    return std::isdigit(caracter); 
 }), texto.end());
}

/**
 * @brief Elimina caracteres no imprimibles de una cadena de texto.
 * 
 * @param texto La cadena de texto de la que se eliminarán los caracteres no imprimibles.
 */
void 
procesador::eliminarCaracteresNoImprimibles(std::string& texto) {
  std::regex regexCaracterNoDeseado("[[:cntrl:]]");
  texto = std::regex_replace(texto, regexCaracterNoDeseado, " ");
}

/**
 * @brief Añade las palabras de una cadena de texto al diccionario.
 * 
 * @param diccionario Instancia de la clase vocavulario donde se añadirán las palabras.
 * @param texto La cadena de texto de la que se extraerán las palabras.
 */
void 
procesador::añadirAlDiccionario (vocavulario& diccionario, const std::string& texto) {
  std::istringstream ss(texto);
  std::string palabra;
  while (ss >> palabra) {
    diccionario.añadirPalabra(palabra);
  }
}

/**
 * @brief Añade las palabras de una cadena de texto al diccionario.
 * 
 * @param diccionario Instancia de la clase vocavulario donde se añadirán las palabras.
 * @param texto La cadena de texto de la que se extraerán las palabras.
 */
void 
procesador::añadirAlCorpusP (phishing& diccionario, const std::string& texto) {
  std::istringstream ss(texto);
  std::string palabra;
  while (ss >> palabra) {
    diccionario.añadirPalabra(palabra);
  }
}

/**
 * @brief Añade las palabras de una cadena de texto al diccionario.
 * 
 * @param diccionario Instancia de la clase vocavulario donde se añadirán las palabras.
 * @param texto La cadena de texto de la que se extraerán las palabras.
 */
void 
procesador::añadirAlCorpusS (safe& diccionario, const std::string& texto) {
  std::istringstream ss(texto);
  std::string palabra;
  while (ss >> palabra) {
    diccionario.añadirPalabra(palabra);
  }
}

/**
 * @brief Genera un modelo de lenguaje seguro basado en un diccionario general y un diccionario de palabras seguras.
 * 
 * @param diccionarioGeneral Diccionario general de palabras.
 * @param diccionarioSafe Diccionario de palabras seguras.
 * @return Modelo de lenguaje seguro generado.
 */

std::map<std::string, double> 
procesador::generarModeloLenguajeSafe (vocavulario& diccionarioGeneral, safe& diccionarioSafe) {
  std::set<std::string> vocavulario = diccionarioGeneral.obtenerDiccionario();
  std::map<std::string, int> vocavularioSafe = diccionarioSafe.obtenerDiccionario();
  int numPalabrasTotalesCorpus = diccionarioSafe.getNumPalabras();
  int numPalabrasVocabulario = diccionarioGeneral.getNumPalabrasUnicas();
  std::map<std::string, double> modeloLenguajeSafe;
  modeloLenguajeSafe.insert(std::pair<std::string, double>("tokenUnknow", (1 / (numPalabrasTotalesCorpus + numPalabrasVocabulario))));
  for (const auto& elemento : vocavulario) {
    auto iterador = vocavularioSafe.find(elemento);
    if (iterador != vocavularioSafe.end()) {
      double aux = iterador->second + 1;
      aux = aux / (numPalabrasTotalesCorpus + numPalabrasVocabulario);
      aux = std::log(aux);
      modeloLenguajeSafe.insert(std::pair<std::string, double>(elemento, aux));
    } else {
      double aux = 1;
      aux = aux / (numPalabrasTotalesCorpus + numPalabrasVocabulario);
      aux = std::log(aux);
      modeloLenguajeSafe.insert(std::pair<std::string, double>(elemento, aux));
    }
  }
  return modeloLenguajeSafe;
}

/**
 * @brief Genera un modelo de lenguaje para phishing basado en un diccionario general y un diccionario de palabras de phishing.
 * 
 * @param diccionarioGeneral Diccionario general de palabras.
 * @param diccionarioPhishing Diccionario de palabras de phishing.
 * @return Modelo de lenguaje para phishing generado.
 */
std::map<std::string, double> 
procesador::generarModeloLenguajePhishing (vocavulario& diccionarioGeneral, phishing& diccionarioPhishing) {
  std::set<std::string> vocavulario = diccionarioGeneral.obtenerDiccionario();
  std::map<std::string, int> vocavularioPhishing = diccionarioPhishing.obtenerDiccionario();
  int numPalabrasTotalesCorpus = diccionarioPhishing.getNumPalabras();
  int numPalabrasVocabulario = diccionarioGeneral.getNumPalabrasUnicas();
  std::map<std::string, double> modeloLenguajePhishing;
  modeloLenguajePhishing.insert(std::pair<std::string, double>("tokenUnknow", (1 / (numPalabrasTotalesCorpus + numPalabrasVocabulario))));
  for (const auto& elemento : vocavulario) {
    auto iterador = vocavularioPhishing.find(elemento);
    if (iterador != vocavularioPhishing.end()) {
      double aux = iterador->second + 1;
      aux = aux / (numPalabrasTotalesCorpus + numPalabrasVocabulario);
      aux = std::log(aux);
      modeloLenguajePhishing.insert(std::pair<std::string, double>(elemento, aux));
    } else {
      double aux = 1;
      aux = aux / (numPalabrasTotalesCorpus + numPalabrasVocabulario);
      aux = std::log(aux);
      modeloLenguajePhishing.insert(std::pair<std::string, double>(elemento, aux));
    }
  }
  return modeloLenguajePhishing;
}

/**
 * @brief Escribe el modelo de lenguaje seguro en un archivo.
 * 
 * @param diccionarioGeneral Diccionario general de palabras.
 * @param diccionarioSafe Diccionario de palabras seguras.
 * @param modeloLenguajeSafe Modelo de lenguaje seguro a escribir.
 */
void 
procesador::escribirModeloLenguajeSafe (vocavulario& diccionarioGeneral, safe& diccionarioSafe, std::map<std::string, double>& modeloLenguajeSafe) {
  std::ofstream archivo(ficheroModeloLenguajeSafe_);
  int numCorreos = diccionarioSafe.getNumCorreos();
  int numPalabrasCorpus = diccionarioSafe.getNumPalabras();
  std::map<std::string, int> vocavularioSafe = diccionarioSafe.obtenerDiccionario();
	if (archivo.is_open()) {
		archivo << "Numero de documentos (noticias) del corpus: " << numCorreos << std::endl;
    archivo << "Número de palabras del corpus: " << numPalabrasCorpus << std::endl;
		for (const auto& par : modeloLenguajeSafe) {
      auto iterador = vocavularioSafe.find(par.first);
      if (iterador == vocavularioSafe.end()) {
        archivo << "Palabra: " << par.first << "  Frec: 0 LogProb: " << par.second << std::endl;
      } else {
        archivo << "Palabra: " << par.first << "  Frec: " << iterador->second << " LogProb: " << par.second << std::endl;
      }
    }
  	archivo.close();
	} else {
		std::cerr << "Error al abrir el archivo." << std::endl;
	}
}

/**
 * @brief Escribe el modelo de lenguaje para phishing en un archivo.
 * 
 * @param diccionarioGeneral Diccionario general de palabras.
 * @param diccionarioPhishing Diccionario de palabras de phishing.
 * @param modeloLenguajePhishing Modelo de lenguaje para phishing a escribir.
 */
void 
procesador::escribirModeloLenguajePhishing (vocavulario& diccionarioGeneral, phishing& diccionarioPhishing, std::map<std::string, double>& modeloLenguajePhishing) {
  std::ofstream archivo(ficheroModeloLenguajePhishing_);
  int numCorreos = diccionarioPhishing.getNumCorreos();
  int numPalabrasCorpus = diccionarioPhishing.getNumPalabras();
  std::map<std::string, int> vocavularioPhishing = diccionarioPhishing.obtenerDiccionario();
	if (archivo.is_open()) {
		archivo << "Numero de documentos (noticias) del corpus: " << numCorreos << std::endl;
    archivo << "Número de palabras del corpus: " << numPalabrasCorpus << std::endl;
		for (const auto& par : modeloLenguajePhishing) {
      auto iterador = vocavularioPhishing.find(par.first);
      if (iterador == vocavularioPhishing.end()) {
        archivo << "Palabra: " << par.first << "  Frec: 0 LogProb: " << par.second << std::endl;
      } else {
        archivo << "Palabra: " << par.first << "  Frec: " << iterador->second << " LogProb: " << par.second << std::endl;
      }
    }
		archivo.close();
	} else {
		std::cerr << "Error al abrir el archivo." << std::endl;
	}
}