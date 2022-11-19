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
    /*POST: Crea una celda que contiene una celula, con comportamiento normal*/
    Celda();
    /*POST: Crea una celda que contiene una celula, con el comportamiento pasado por parametro*/
    Celda(ComportamientoDeCelda comportamiento);
    /*POST: Elimina la instancia de celda y sus datos*/
    ~Celda();
    /*POST: Devuelve el comportamiento de la celda*/
    ComportamientoDeCelda getComportamiento();
    /*POST: Devuelve la celula que contiene la celda*/
    Celula * getCelula();
    /*POST: Cambia el comportamiento de la celda al pasado por parametro*/
    void setComportamiento(ComportamientoDeCelda comportamiento);
};

#endif /* CELDA_H_ */
