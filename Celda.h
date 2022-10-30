#include "Celula.h"

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
Celula celula;

public:

Celda();
Celda(ComportamientoDeCelda comportamiento);
ComportamientoDeCelda getComportamiento();
Celula getCelula();

};

