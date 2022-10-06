#include "Celula.h"

Celula::Celula() {
    
    this->Estado = Muerta;
    this->Comportamiento = Normal;
    CantidadGenes = CANTIDAD_GENES;
    for(int i = 0; i<CantidadGenes; i++) {
        this->Gen[i] = 0;
    };
};


Celula::Celula(int genes[]){

    this->Estado = Muerta;
    this->Comportamiento = Normal;
    for(int i = 0; i<CantidadGenes; i++) {
        this->Gen[i] = genes[i];
    };
};

void Celula::inicializarCelula(Celula *celula, ComportamientoDeCelula comportamiento){

};

void Celula::matarCelula(Celula *celula){
    
    celula->Estado = Muerta;
};

void Celula::revivirCelula(Celula *celula, int genes[]){
    
    celula->Estado = Viva;
    for(int i = 0; i<CantidadGenes; i++) {
        this->Gen[i] = genes[i];
    };
};

EstadoDeCelula Celula::obtenerEstado(Celula *celula){
    return celula->Estado;
};

void Celula::cambiarGen(Celula *celula, int numeroDeGen, int cambio) {
    if(cambio > 255 || cambio < 0) {
        cambio = 0;
    };
    celula->Gen[numeroDeGen] = cambio;
};

int Celula::ObtenerGen(Celula *celula, int numeroDeGen){
    return celula->Gen[numeroDeGen];
};
