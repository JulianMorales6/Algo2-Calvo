const int CANTIDAD_GENES = 3;

enum EstadoDeCelula {
    Viva,
    Muerta
};

class Celula {
    private:
    EstadoDeCelula Estado;
    int Gen[CANTIDAD_GENES];

    public:
    /*POST: Crea una celula con estado Muerta y los genes en 0*/
    Celula();

    /*POST: Cambia el estado a Muerta y los genes a 0.
    (cumpliria la funcion de un inicializarCelula)*/
    void matarCelula();

    /*POST: Cambia el estado a viva y le da a los genes valores randoms entre 0 y 255*/
    void revivirCelula();

    /*PRE: Se tienen que pasar un array con 3 genes entre 0 y 255
      POST: Cambia el estado a Viva y el valor de los genes por los pasados*/
    void revivirCelula(int genes[]);

    /*POST: Devuelve el estado de la celula*/
    EstadoDeCelula getEstado();

    /*PRE: El numero de gen debe estar entre 1 y 3
      POST: Devuelve el valor del gen*/
    int getGen(int numeroDeGen);

    /*POST: Cambia el estado de la celula*/
    void setEstadoDeCelula(EstadoDeCelula Estado);

    /*PRE: El numero de gen debe estar entre 1 y 3, y el cambio entre 0 y 255
      POST: Cambia el valor del gen seleccionado por el pasado*/
    void cambiarGen(int numeroDeGen, int cambio);
};