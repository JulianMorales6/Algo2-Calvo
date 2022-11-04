#include <cstdlib>
#include "Celula.h"

Celula::Celula() {    
    this->Estado = Muerta;
    for(int i = 0; i<CANTIDAD_GENES; i++) {
        this->Gen[i] = 0;
    }
}


void Celula::matarCelula() {
    this->Estado = Muerta;
    for(int i = 0; i<CANTIDAD_GENES; i++) {
        this->Gen[i] = 0;
    }
}


void Celula::revivirCelula(){
    this->Estado = Viva;
    for(int i = 0; i<CANTIDAD_GENES; i++) {
        this->Gen[i] = generarNumeroRandom(255);
    }
}


void Celula::revivirCelula(int genes[]){
    this->Estado = Viva;
    for(int i = 0; i<CANTIDAD_GENES; i++) {
        this->Gen[i] = genes[i];
    }
}


EstadoDeCelula Celula::getEstado(){
    return this->Estado;
}


void Celula::cambiarGen(int numeroDeGen, int cambio) {
    if(cambio > 255 || cambio < 0) {
        cambio = 0;
    }
    this->Gen[numeroDeGen] = cambio;
}


int Celula::getGen(int numeroDeGen){
    return this->Gen[numeroDeGen];
}


void Celula::setEstadoDeCelula(EstadoDeCelula Estado) {
    this->Estado = Estado;
}


int generarNumeroRandom(int i) {
    return(rand()%(i + 1));
}