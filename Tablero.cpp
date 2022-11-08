

#include "Tablero.h"

Tablero::Tablero(int capas, int filas, int columnas){//-> profundidad, alto, ancho -> k,i,j
   
    this->tablero = new Lista<Lista<Lista<Celda *> *> *>;
    this->tablero->inicializarCursor();
    for(int i=0; i<capas; i++){
        Lista<Lista<Celda *> *> *capa = new Lista<Lista<Celda *> *>;
        this->tablero->add(capa);

        for(int j=0; j<filas; j++){
            Lista<Celda *> *fila = new Lista<Celda *>;
            this->tablero->getCursor()->add(fila);

            for(int k=0; k<columnas; k++){
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
    int capa = getTablero()->getLargo();
    int fila = getTablero()->getCursor()->getLargo();
    int columna = getTablero()->getCursor()->getCursor()->getLargo();
    for(int i = 0; i<capa; i++) {
        cout<<"Capa:"<<i+1<<endl;
        for(int j = 0; j<fila; j++) {
            for(int k = 0; k<columna; k++) {
                if (this->getCelda(i,j,k)->getCelula()->getEstado() == Muerta) {
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