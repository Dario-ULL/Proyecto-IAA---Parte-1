/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial Avanzada
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    19/04/2024
 * @brief   Implementacion de las funciones de la clase vocavulario.
*/

#include "vocavulario.h"

/**
 * @brief Constructor de la clase vocavulario.
 * 
 * Inicializa el número de palabras del diccionario en 0.
 */
vocavulario::vocavulario() {
    numeroPalabras_ = 0;
}

/**
 * @brief Añade una palabra al diccionario.
 * 
 * @param palabra La palabra que se añadirá al diccionario.
 */
void vocavulario::añadirPalabra(std::string palabra) {
    if (diccionario_.insert(palabra).second) {
        numeroPalabras_++;
    }
}

/**
 * @brief Obtiene el diccionario de palabras.
 * 
 * @return Un conjunto de cadenas que representa el diccionario de palabras.
 */
std::set<std::string> vocavulario::obtenerDiccionario() {
    return diccionario_;
}

/**
 * @brief Escribe el diccionario en un archivo.
 * 
 * @param fichero El nombre del archivo donde se escribirá el diccionario.
 */
void vocavulario::escribirDiccionario(std::string fichero) {
    std::ofstream archivo(fichero);
    if (archivo.is_open()) {
        archivo << "Numero de palabras: " << numeroPalabras_ << std::endl;
        for (const std::string& palabra : diccionario_) {
            archivo << palabra << std::endl;
        }
        archivo.close();
    } else {
        std::cerr << "Error al abrir el archivo." << std::endl;
    }
}

/**
 * @brief Limpia el diccionario.
 * 
 * Elimina todas las palabras del diccionario y establece el número de palabras a 0.
 */
void vocavulario::limiarDiccionario() {
    diccionario_.clear();
    numeroPalabras_ = 0;
}
