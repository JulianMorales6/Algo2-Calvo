#ifndef CELULA_H_
#define CELULA_H_
#include <cstdlib>
const int CANTIDAD_GENES = 3;

enum EstadoDeCelula {
    Viva,
    Muerta
};

class Celula {
    private:
    EstadoDeCelula Estado;
    int genes[CANTIDAD_GENES];

    public:
    /*PRE:
      POST: Crea una celula con estado Muerta y los genes en 0*/
    Celula();
    /*POST: Cambia el estado a Muerta y los genes a 0.
    (cumpliria tambien la funcion de un inicializarCelula)*/
    void matarCelula();
    /*PRE:
      POST: Cambia el estado a viva y le da a los genes valores randoms entre 0 y 255*/
    void revivirCelula();
    /*PRE: Se tienen que pasar un array con 3 genes entre 0 y 255
      POST: Cambia el estado a Viva y el valor de los genes por los pasados*/
    void revivirCelula(int genesHeredados[]);
    /*POST: Devuelve el estado de la celula*/
    EstadoDeCelula getEstado();
    /*PRE: El numero de gen debe estar entre 0 y 2
      POST: Devuelve el valor del gen*/
    int getGen(int numeroDeGen);
    /*PRE:
      POST: Cambia el estado de la celula*/
    void setEstado(EstadoDeCelula Estado);
    /*PRE: El numero de gen debe estar entre 0 y 3, y el cambio entre 0 y 255
      POST: Cambia el valor del gen seleccionado por el pasado*/
    void setGen(int numeroDeGen, int cambio);
};

#endif /* CELULA_H_ */
