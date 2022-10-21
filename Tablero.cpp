

#include "Tablero.h"

Tablero::Tablero(int capas, int filas, int columnas){//tablero de enteros para probar
   
    this->tablero = new Lista<Lista<Lista<int *> *> *>;
    this->tablero->inicializarCursor();
    for(int i=0; i<capas; i++){
        Lista<Lista<int *> *> *capa = new Lista<Lista<int *> *>;
        this->tablero->add(capa);

        for(int j=0; j<filas; j++){
            Lista<int *> *fila = new Lista<int *>;
            this->tablero->getCursor()->add(fila);

            for(int k=0; k<columnas; k++){
                int *p = new int;
                *p = 0;
                this->tablero->getCursor()->getCursor()->add(p); //en lugar de p iria el casillero
                
            }
        }
    }
}


Tablero::~Tablero(){
}


cubo Tablero::getTablero(){
    return this->tablero;
}


void Tablero::mostrarTablero(){
    int cont=1;
    for(int i=1; i<=this->getTablero()->getLargo(); i++){

        for(int i=1; i<=this->getTablero()->getCursor()->getLargo(); i++){
            this->getTablero()->getCursor()->getCursor()->emitir();
            this->getTablero()->getCursor()->avanzarCursor();
        }
        cout<<"capa "<<cont<<endl;
        cont++;
        this->getTablero()->avanzarCursor();

    }
}

