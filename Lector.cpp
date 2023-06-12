#include "Lector.hpp"
#include <iostream>
#include <cstring>


// Constructor
Lector::Lector() { 
  filename = "";
}

int Lector::open(std::string flname) {
  filename = std::string(flname);
  archivo = fopen(filename.c_str(), "r"); // abre el archivo Ej: "src/archivo.txt"
  if (!archivo) { // verifica si el archivo se abrió correctamente
    std::cerr << "No se pudo abrir el archivo " << filename << std::endl;
    return 1;
  }
  return 0;
}

int Lector::openBinari(std::string flname) {
  filename = flname;
  archivo = fopen(filename.c_str(), "rb"); // abre el archivo Ej: "src/archivo.txt"
  if (!archivo) { // verifica si el archivo se abrió correctamente
    std::cerr << "No se pudo abrir el archivo " << filename << std::endl;
    return 1;
  }
  return 0;
}

int Lector::read(int chunk) {
  memset(buffer, 0, BUFFER);
  return fread(buffer, sizeof(char), chunk, archivo);
}

unsigned char * Lector::getChars() {
  return buffer;
}

int Lector::close() {
  fclose(archivo); // cierra el archivo
  return 0;
}

Lector::~Lector(){
  delete[] buffer;
}
