

#include "Tablero.h"

Tablero::Tablero(int capas, int filas, int columnas){//tablero de enteros para probar
   
    this->tablero = new Lista<Lista<Lista<Celda *> *> *>;
    this->tablero->inicializarCursor();
    for(int i=0; i<capas; i++){
        Lista<Lista<Celda *> *> *capa = new Lista<Lista<Celda *> *>;
        this->tablero->add(capa);

        for(int j=0; j<filas; j++){
            Lista<Celda *> *fila = new Lista<Celda *>;
            this->tablero->getCursor()->add(fila);

            for(int k=0; k<columnas; k++){
                Celda *p = new Celda;
                p->getCelula()->inicializarCelula();
                this->tablero->getCursor()->getCursor()->add(p); //en lugar de p iria el casillero
                
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
    int largoi = getTablero()->getLargo();
    int largoj = getTablero()->getCursor()->getLargo();
    int largok = getTablero()->getCursor()->getCursor()->getLargo();
    for(int i = 0; i<largoi; i++) {
        cout<<"Capa:"<<i+1<<endl;
        for(int j = 0; j<largoj; j++) {
            for(int k = 0; k<largok; k++) {
                cout<<this->getCelda(k,j,i)->getCelula()->getEstado();
            }
            cout<<endl;
        }
    }
}

void Tablero::cambiarEstadoTablero(int i, int j, int k, EstadoDeCelula estado) {
    this->getCelda(i,j,k)->getCelula()->setEstadoDeCelula(estado);
}

void Tablero::cambiarComportamientoTablero(int i, int j, int k, ComportamientoDeCelda comportamiento) {
    this->getCelda(i,j,k)->setComportamiento(comportamiento);
}

ComportamientoDeCelda Tablero::getComportamientoTablero(int i, int j, int k) {
    return(this->getCelda(i,j,k)->getComportamiento());
}

Celda * Tablero::getCelda(int i, int j, int k) {
    return((*(*(*this->tablero)[i])[j])[k]);
}