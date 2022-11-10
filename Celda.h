#ifndef CELDA_H_
#define CELDA_H_
#include "Celula.cpp"

enum ComportamientoDeCelda {
    Contaminada,
    Envenenada,
    Procreadora,
    Portal,
    Radioactiva,
    Normal
};

class Celda {
    private:
    ComportamientoDeCelda Comportamiento;
    Celula * celula;

    public:
    Celda();
    Celda(ComportamientoDeCelda comportamiento);
    ComportamientoDeCelda getComportamiento();
    Celula * getCelula();
    void setComportamiento(ComportamientoDeCelda comportamiento);
};
#endif /* CELDA_H_ */
