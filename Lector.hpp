#ifndef LECTOR_H
#define LECTOR_H

#include <string>
#define BUFFER 1024

class Lector {
  public:
    Lector();
    int open(std::string flname) ;
    int openBinari(std::string flname) ;
    int read(int chunk);
    unsigned char * getChars();
    int close();
    ~Lector();
  private:
    std::string filename;
    FILE * archivo;
    unsigned char * buffer = new unsigned char[BUFFER];
};
#endif  // LECTOR_H
