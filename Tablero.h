

#include "Celda.cpp"
#include "ListaDobleCircular.h"

typedef Lista<Lista<Lista<Celda *> *> *> *cubo;

class Tablero{
    private:
    cubo tablero;

    public:
    /*PRE: 
      POST: Crea una instancia de tablero con las dimensiones pasadas*/
    Tablero(int capas, int filas, int columnas);
    /*PRE: 
      POST: */
    ~Tablero();
    /*PRE: 
      POST: */
    cubo getTablero();
    /*PRE: 
      POST: */
    void incializarTablero();
    /*PRE: 
      POST: */
    void mostrarTablero();

    void cambiarEstadoTablero(int capa, int fila, int columna, EstadoDeCelula estado);

    void cambiarComportamientoTablero(int capa, int fila, int columna, ComportamientoDeCelda comportamiento);

    ComportamientoDeCelda getComportamientoTablero(int capa, int fila, int columna);

    Celda * getCelda(int capa, int fila, int columna);
};


