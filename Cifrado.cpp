#include "Cifrado.hpp"

#include <fstream>
#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

Cifrado::Cifrado(){
    
}

std::vector<unsigned char> Cifrado::encryptMessage(const std::string& message, const std::string& privateKeyPath) {
    // Cargar la clave pública
    FILE* privateKeyFile = fopen(privateKeyPath.c_str(), "rb");
    if (!privateKeyFile) {
        std::cerr << "Error al abrir el archivo de clave privada" << std::endl;
        return std::vector<unsigned char>(0);
    }

    RSA* rsa = PEM_read_RSAPrivateKey(privateKeyFile, NULL, NULL, NULL);
    fclose(privateKeyFile);

    if (!rsa) {
        std::cerr << "Error al leer la clave privada" << std::endl;
        return std::vector<unsigned char>(0);
    }

    // Encriptar el mensaje
    std::vector<unsigned char> result{std::vector<unsigned char>(512, 0)};
    int encryptedLength = RSA_private_encrypt(message.size(), reinterpret_cast<const unsigned char*>(message.data()),
                                             &result[0], rsa, RSA_PKCS1_PADDING);                                             

    RSA_free(rsa);
    if (encryptedLength == -1) {
        std::cerr << "Error al encriptar el mensaje" << std::endl;
    }
    
    result.resize(encryptedLength);
    return result;
    
}

int Cifrado::chunkSize(const std::string& privateKeyPath) {
    // Cargar la clave privada
    FILE* privateKeyFile = fopen(privateKeyPath.c_str(), "rb");
    if (!privateKeyFile) {
        return 0;
    }
    RSA* rsa = PEM_read_RSAPrivateKey(privateKeyFile, NULL, NULL, NULL);
    fclose(privateKeyFile);

    if (!rsa) {
        std::cerr << "Error al leer la clave privada" << std::endl;
        return 0;
    }

    int rsaSize = RSA_size(rsa) - 42;
    RSA_free(rsa);
    return rsaSize;
}

