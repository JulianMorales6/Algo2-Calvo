#include "Celda.h"

Celda::Celda() {
    this->celula = Celula();
    this->Comportamiento = Normal;
};

Celda::Celda(ComportamientoDeCelda comportamiento) {
    this->celula = Celula();
    this->Comportamiento = comportamiento;
};

ComportamientoDeCelda Celda::getComportamiento() {
    return(this->Comportamiento);
};

Celula Celda::getCelula() {
    return(this->celula);
};