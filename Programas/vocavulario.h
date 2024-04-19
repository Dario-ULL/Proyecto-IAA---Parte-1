/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial Avanzada
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    19/04/2024
 * @brief   Definicion de la clase vocavulario.
*/

#ifndef VOCAVULARIO_H_
#define VOCAVULARIO_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <set>
#include <map>

/**
 * @brief Clase lectorArchivo que estara a cargo de la lectura y filtracion de los correos leidos.
 * 
 * @param numeroPalabras_  -  Atributo privado que guarda el numero de palabras totales.
 * @param diccionario_     -  Atributo privado que guarda todas las palabras seleccionadas.
*/
class vocavulario {
 private:
  int numeroPalabras_;
  std::set<std::string> diccionario_;
 public:
  vocavulario ();
  void añadirPalabra (std::string);
  std::set<std::string> obtenerDiccionario ();
  void escribirDiccionario (std::string);
  void limiarDiccionario ();
};

#endif