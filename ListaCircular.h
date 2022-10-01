#include "Nodo.h"

template <class T> class ListaC{
    
    public:
    ListaC(); //constructor
    ~ListaC(); //destructor
    void AltaPrin(const T &); //alta al principio
    void AltaFin(const T &); //alta al final

    private:
    Nodo <T> * principio;
    int cantidadDeNodos;
};

template <class T> ListaC <T>::ListaC() {
    this->principio = NULL
};

template <class T> ListaC <T>::~ListaC() {

    if(principio) {
        if(principio->siguiente == principio) delete principio;
        else {
            Nodo <T> *
            //falta terminar este metodo y el resto 
        }
    }
}