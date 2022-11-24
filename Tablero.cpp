
#include "Tablero.h"

Tablero::Tablero(int capas, int filas, int columnas) {//-> profundidad, alto, ancho -> k,i,j
   
    this->tablero = new Lista<Lista<Lista<Celda *> *> *>;
    this->tablero->inicializarCursor();
    for(int capa = 0; capa < capas; capa++) {
        Lista<Lista<Celda *> *> *listaDeCapas = new Lista<Lista<Celda *> *>;
        this->tablero->add(listaDeCapas);

        for(int fila = 0; fila < filas; fila++) {
            Lista<Celda *> *listaDeFilas = new Lista<Celda *>;
            this->tablero->getCursor()->add(listaDeFilas);

            for(int columna = 0; columna < columnas; columna++) {
                Celda *celda = new Celda;
                this->tablero->getCursor()->getCursor()->add(celda);
                
            }
        }
    }
}


Tablero::~Tablero() {
    this->tablero->inicializarCursor();
    do {
        Lista<Lista<Celda *> *> *listaDeCapas = this->tablero->getCursor();
        listaDeCapas->inicializarCursor();
        do {
            Lista<Celda *> *listaDeFilas = listaDeCapas->getCursor();
            listaDeFilas->inicializarCursor();
            do {
                delete listaDeFilas->getCursor();
            } while(listaDeFilas->avanzarCursor()); 

            delete listaDeFilas;
        }while(listaDeCapas->avanzarCursor());

        delete listaDeCapas;
    }while(this->tablero->avanzarCursor());

    delete this->tablero;
}


cubo Tablero::getTablero() {
    return this->tablero;
}


void Tablero::mostrarTablero() {
    int capas = getTablero()->getLargo();
    int filas = getTablero()->getCursor()->getLargo();
    int columnas = getTablero()->getCursor()->getCursor()->getLargo();
    for(int capa = 0; capa < capas; capa++) {
        std::cout<<"Capa:"<<capa+1<<std::endl;
        for(int fila = 0; fila < filas; fila++) {
            for(int columna = 0; columna < columnas; columna++) {
                if (this->getCelda(capa, fila, columna)->getCelula()->getEstado() == Muerta) {
                    std::cout<<"□ ";
                }     
                else {
                    std::cout<<"■ ";
                }   
            }
            std::cout<<std::endl;
        }
    }
}

Celda * Tablero::getCelda(int capa, int fila, int columna) {
    return((*(*(*this->tablero)[capa])[fila])[columna]);
}
