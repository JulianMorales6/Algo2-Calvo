
#include "Celula.h"

Celula::Celula() {    
    this->Estado = Muerta;
    for(int i = 0; i<CANTIDAD_GENES; i++) {
        this->genes[i] = 0;
    }
}

void Celula::matarCelula() {
    this->Estado = Muerta;
    for(int i = 0; i<CANTIDAD_GENES; i++) {
        this->genes[i] = 0;
    }
}

void Celula::revivirCelula() {
    this->Estado = Viva;
    for(int i = 0; i<CANTIDAD_GENES; i++) {
        this->genes[i] = generarNumeroRandom(255);
    }
}

void Celula::revivirCelula(int genesHeredados[]) {
    this->Estado = Viva;
    for(int i = 0; i<CANTIDAD_GENES; i++) {
        this->genes[i] = genesHeredados[i];
    }
}

EstadoDeCelula Celula::getEstado() {
    return this->Estado;
}

void Celula::setGen(int numeroDeGen, int cambio) {
    if(cambio > 255 || cambio < 0) {
        cambio = 0;
    }
    this->genes[numeroDeGen] = cambio;
}

int Celula::getGen(int numeroDeGen) {
    return this->genes[numeroDeGen];
}

void Celula::setEstado(EstadoDeCelula Estado) {
    this->Estado = Estado;
}

int generarNumeroRandom(int i) {
    return(rand()%(i + 1));
}