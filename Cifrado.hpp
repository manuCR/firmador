#ifndef CIFRADO_H
#define CIFRADO_H

#include <string>
#include <vector>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>


class Cifrado {

public:
  Cifrado();
  std::vector<unsigned char> encryptMessage(const std::string& message, const std::string& publicKeyPath);
  int chunkSize(const std::string& privateKeyPath);
};
#endif  //CIFRADO_H
