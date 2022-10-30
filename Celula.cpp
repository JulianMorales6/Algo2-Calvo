
#include "Celula.h"

Celula::Celula() {
    
    this->Estado = Muerta;
    for(int i = 0; i<CANTIDAD_GENES; i++) {
        this->Gen[i] = 0;
    };
};


Celula::Celula(int genes[]){

    this->Estado = Muerta;
    for(int i = 0; i<CANTIDAD_GENES; i++) {
        this->Gen[i] = genes[i];
    };
};

void Celula::inicializarCelula() {
    this->Estado = Muerta;
    for(int i = 0; i<CANTIDAD_GENES; i++) {
        this->Gen[i] = 0;
    }
};

void Celula::matarCelula(){
    this->Estado = Muerta;
};

void Celula::revivirCelula(int genes[]){
    
    this->Estado = Viva;
    for(int i = 0; i<CANTIDAD_GENES; i++) {
        this->Gen[i] = genes[i];
    };
};

EstadoDeCelula Celula::obtenerEstado(){
    return this->Estado;
};

void Celula::cambiarGen(int numeroDeGen, int cambio) {
    if(cambio > 255 || cambio < 0) {
        cambio = 0;
    };
    this->Gen[numeroDeGen] = cambio;
};

int Celula::ObtenerGen(int numeroDeGen){
    return this->Gen[numeroDeGen];
};