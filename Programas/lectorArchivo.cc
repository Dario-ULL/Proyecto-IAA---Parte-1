/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial Avanzada
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    19/04/2024
 * @brief   Implentacion de las funciones de la clase lectorArchivo
*/

#include "lectorArchivo.h"


/**
 * @brief Constructor de la clase lectorArchivo.
 * 
 * @param nombreArchivoEntrada Nombre del archivo de entrada.
 * @param nombreArchivoSalida Nombre del archivo de salida.
 */
lectorArchivo::lectorArchivo(std::string nombreArchivoEntrada, std::string nombreArchivoSalida) {
    ficheroEntrada_ = nombreArchivoEntrada;
    ficheroSalida_ = nombreArchivoSalida;
}

/**
 * @brief Procesa el texto del archivo, aplicando una serie de transformaciones y extrayendo las palabras
 * para añadirlas al diccionario.
 * 
 * @param diccionario Instancia de la clase vocavulario donde se añadirán las palabras procesadas.
 */
void 
lectorArchivo::procesarTexto (vocavulario& diccionario) {
  std::ifstream archivo(ficheroEntrada_);
  if (!archivo.is_open()) {
      std::cerr << "Error al abrir el archivo " << ficheroEntrada_ << std::endl;
      exit(1);
  }
  std::string linea;
  std::string correo;
  bool primerSegmento = true;
  bool segundoSegmento = true;
  int i = 0;
  std::getline(archivo, linea);
  while (std::getline(archivo, linea)) {
    bool procesar = false;
    int it = 0;
    if (primerSegmento == true) {
      primerSegmento = false;
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
      while (linea[it] != ';') {
        if (it == 0) {
          break;
        }
        it--;
      }
      if (it != 0) {
        linea.erase(linea.begin() + it, linea.end());
        procesar = true;
        primerSegmento = true;
      }      
    }
    if (!linea.empty()) {
      correo += linea;
    }   
    if (procesar == true) {
      convertirMinusculas(correo);
      eliminarEspaciosDobles(correo);
      elimianrEnlaces(correo);
      elimianrhashtags(correo);
      eliminarSignos(correo);
      eliminarPalabrasResevadas(correo);
      eliminarEmojisYEmoticonos(correo);
      eliminarNumeros(correo);
      eliminarCaracteresNoImprimibles(correo);
      añadirAlDiccionario(diccionario, correo);
      correo.clear();
      if (i % 1000 == 1) {
        diccionario.escribirDiccionario(ficheroSalida_);
        diccionario.limiarDiccionario();
      }
    }
    i++;
  }
  std::cout << i << std::endl;
  archivo.close();
}

/**
 * @brief Elimina los signos de puntuación de una cadena de texto.
 * 
 * @param texto La cadena de texto de la que se eliminarán los signos de puntuación.
 */
void
lectorArchivo::eliminarSignos (std::string& texto) {
  texto.erase(std::remove_if(texto.begin(), texto.end(), [](char c) { return std::ispunct(c); }), texto.end());
}

/**
 * @brief Convierte todos los caracteres de una cadena de texto a minúsculas.
 * 
 * @param texto La cadena de texto que se convertirá a minúsculas.
 */
void
lectorArchivo::convertirMinusculas (std::string& texto) {
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
lectorArchivo::eliminarEspaciosDobles (std::string& texto) {
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
lectorArchivo::eliminarPalabrasResevadas (std::string& texto) {
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
lectorArchivo::eliminarEmojisYEmoticonos (std::string& texto) {
  std::regex emojiRegex(u8"[\U0001F300-\U0001F9FF]");
  texto = std::regex_replace(texto, emojiRegex, "");
}

/**
 * @brief Elimina enlaces URL de una cadena de texto.
 * 
 * @param texto La cadena de texto de la que se eliminarán los enlaces URL.
 */
void 
lectorArchivo::elimianrEnlaces(std::string& texto) {
  std::regex urlRegex(R"(https?://\S+|www\.\S+)");
  texto = std::regex_replace(texto, urlRegex, "");
}

/**
 * @brief Elimina hashtags de una cadena de texto.
 * 
 * @param texto La cadena de texto de la que se eliminarán los hashtags.
 */
void 
lectorArchivo::elimianrhashtags(std::string& texto) {
  std::regex hashtagRegex(R"(\#\s?\w+)");
  texto = std::regex_replace(texto, hashtagRegex, "");
}

/**
 * @brief Elimina números de una cadena de texto.
 * 
 * @param texto La cadena de texto de la que se eliminarán los números.
 */
void 
lectorArchivo::eliminarNumeros (std::string& texto) {
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
lectorArchivo::eliminarCaracteresNoImprimibles(std::string& texto) {
  std::regex regexCaracterNoDeseado("[[:cntrl:]]");
  texto = std::regex_replace(texto, regexCaracterNoDeseado, "");
}

/**
 * @brief Añade las palabras de una cadena de texto al diccionario.
 * 
 * @param diccionario Instancia de la clase vocavulario donde se añadirán las palabras.
 * @param texto La cadena de texto de la que se extraerán las palabras.
 */
void 
lectorArchivo::añadirAlDiccionario (vocavulario& diccionario, const std::string& texto) {
  std::istringstream ss(texto);
  std::string palabra;
  while (ss >> palabra) {
    diccionario.añadirPalabra(palabra);
  }
}

