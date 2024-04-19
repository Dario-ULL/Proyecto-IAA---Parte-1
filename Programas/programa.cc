/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial Avanzada
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    19/04/2024
 * @brief   Main del programa. Iniciara el proceso de lectura de texto y calculara el tiempo total trancurrido.
*/

#include <iostream>
#include <string>
#include <chrono>

#include "vocavulario.h"
#include "lectorArchivo.h"

int main() {
  std::string nombreArchivoEntrada = "/home/usuario/IAA/Proyecto_Parte_1/Ficheros/PH_train.csv";
  std::string nombreArchivoSalida = "/home/usuario/IAA/Proyecto_Parte_1/Ficheros/vocavulario.txt";
  vocavulario vocavulario;
  lectorArchivo lector(nombreArchivoEntrada, nombreArchivoSalida);
  auto start = std::chrono::high_resolution_clock::now();
  lector.procesarTexto(vocavulario);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  double segundos = duration.count() / 1000000.0;
  std::cout << "Tiempo de ejecución: " << segundos << " segundos" << std::endl;
  return 0;
}