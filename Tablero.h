#ifndef TABLERO_H_
#define TABLERO_H_

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
      POST: Destruye la instancia de tablero eliminando todos sus nodos */
    ~Tablero();
    /*PRE: 
      POST: Devuelve un puntero al tablero */
    cubo getTablero();
    /*PRE: 
      POST: Inicializa las celulas y celdas del tablero*/
    void incializarTablero();
    /*PRE: 
      POST: Imprime por terminal las capas del tablero */
    void mostrarTablero();
    /*PRE: 
      POST: Devuleve un puntero a celda correspondiente a las coordenadas pasadas */
    Celda * getCelda(int capa, int fila, int columna);
};

#endif /* TABLERO_H_ */
