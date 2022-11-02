#include "Celda.h"

Celda::Celda() {
    this->celula = new Celula();
    this->Comportamiento = Normal;
};

Celda::Celda(ComportamientoDeCelda comportamiento) {
    this->celula = new Celula();
    this->Comportamiento = comportamiento;
};

ComportamientoDeCelda Celda::getComportamiento() {
    return(this->Comportamiento);
};

Celula * Celda::getCelula() {
    return(this->celula);
};

void Celda::setComportamiento(ComportamientoDeCelda comportamiento) {
    this->Comportamiento = comportamiento; 
}