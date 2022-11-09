

#include "Tablero.h"

Tablero::Tablero(int capas, int filas, int columnas){//-> profundidad, alto, ancho -> k,i,j
   
    this->tablero = new Lista<Lista<Lista<Celda *> *> *>;
    this->tablero->inicializarCursor();
    for(int capa = 0; capa < capas; capa++){
        Lista<Lista<Celda *> *> *listaDeCapas = new Lista<Lista<Celda *> *>;
        this->tablero->add(listaDeCapas);

        for(int fila = 0; fila < filas; fila++){
            Lista<Celda *> *listaDeFilas = new Lista<Celda *>;
            this->tablero->getCursor()->add(listaDeFilas);

            for(int columna = 0; columna < columnas; columna++){
                Celda *celda = new Celda;
                this->tablero->getCursor()->getCursor()->add(celda);
                
            }
        }
    }
}


Tablero::~Tablero(){
    delete this->tablero;
}


cubo Tablero::getTablero(){
    return this->tablero;
}


/*void Tablero::mostrarTablero(){
    int cont=1;
    for(int i=0; i<this->getTablero()->getCursor()->getCursor()->getLargo(); i++) {
        cout<<"capa "<<cont<<endl;cont++;
    for(int i=1; i<=this->getTablero()->getLargo(); i++){

        for(int i=1; i<=this->getTablero()->getCursor()->getLargo(); i++){
            cout<<this->getTablero()->getCursor()->getCursor()->getCursor()->getCelula()->getEstado();
            this->getTablero()->getCursor()->getCursor()->avanzarCursor();
            this->getTablero()->getCursor()->avanzarCursor();
            this->getTablero()->avanzarCursor();
        }
        this->getTablero()->inicializarCursor();
        cout<<endl;
        
    } 
}
}
*/

void Tablero::mostrarTablero() {
    int capas = getTablero()->getLargo();
    int filas = getTablero()->getCursor()->getLargo();
    int columnas = getTablero()->getCursor()->getCursor()->getLargo();
    for(int capa = 0; capa < capas; capa++) {
        cout<<"Capa:"<<capa+1<<endl;
        for(int fila = 0; fila < filas; fila++) {
            for(int columna = 0; columna < columnas; columna++) {
                if (this->getCelda(capa, fila, columna)->getCelula()->getEstado() == Muerta) {
                    cout<<"□ ";
                }     
                else {
                    cout<<"■ ";
                }   
            }
            cout<<endl;
        }
    }
}

void Tablero::cambiarEstadoTablero(int capa, int fila, int columna, EstadoDeCelula estado) {
    this->getCelda(capa,fila,columna)->getCelula()->setEstadoDeCelula(estado);
}

void Tablero::cambiarComportamientoTablero(int capa, int fila, int columna, ComportamientoDeCelda comportamiento) {
    this->getCelda(capa,fila,columna)->setComportamiento(comportamiento);
}

ComportamientoDeCelda Tablero::getComportamientoTablero(int capa, int fila, int columna) {
    return(this->getCelda(capa,fila,columna)->getComportamiento());
}

Celda * Tablero::getCelda(int capa, int fila, int columna) {
    return((*(*(*this->tablero)[capa])[fila])[columna]);
}