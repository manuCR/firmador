#include "Cifrado.hpp"
#include "Escritor.hpp"
#include "Hex.h"
#include "Lector.hpp"
#include "Sha.h"
#include <iostream>

// 1:filein(string), 2:fileout(string), 3:privateKey(path)

// g++ -std=c++11 -lssl -lcrypto Cifrado.cpp Escritor.cpp Lector.cpp main.cpp Sha.cpp Hex.cpp

// ./a.out texto.txt resultado.txt key.pem
int main(int argc, char *argv[]) {
  std::string arg1 = argv[1];
  std::string arg2 = argv[2];
  std::string arg3 = argv[3];
  Lector lector;
  Cifrado cifrado;
  Sha sha;
  Hex hex;
  std::string shaCode = sha.shaFile(arg1);
  int chunk = cifrado.chunkSize(arg3);
  if (shaCode.size() > 0){
    std::cout << "el sha del mensaje es: " << shaCode << std::endl;
    std::vector<unsigned char> encryp = cifrado.encryptMessage(shaCode, arg3);
    std::string stringHex = hex.byteToHex(encryp);
    Escritor escritor;
    escritor.open(arg2, "w+");
    escritor.write(stringHex);
    escritor.close();
  }
  std::cout << "el mensaje tiene que contener al menos un caracter" << std::endl;
}
