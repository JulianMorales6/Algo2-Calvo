#ifndef LISTADOBLECIRCULAR_H_
#define LISTADOBLECIRCULAR_H_

#include <iostream>
#include "Nodo.h"

template <class T> class Lista {
    private:
    Nodo<T> *primero;
    Nodo<T> *cursor;
    int posicionCursor;
    int largo;
    public:
    /*POST: Crea una instancia de lista*/
    Lista();
    /*POST: Borra los nodos creados con new*/
    ~Lista();
    /*POST: Agrega el elemento pasado al final de la lista y deja el cursor apuntando al mismo*/
    void add(T elemento);
    /*PRE: La posicion pasada esta entre 0 y el largo de la lista
      POST: Inserta el elemento en la posicion pasada y deja el cursor apuntando al mismo*/
	void add(T elemento, int posicion);
    /*POST: Devuelve el largo de la lista*/
    int getLargo();
    /*POST: Verifica si la lista esta vacia*/
    bool estaVacia();
    /*PRE: La lista no puede estar vacia y solo emite lista de una dimension
      POST: Muestra por consola la lista*/
    void emitir();
    /*PRE: La lista no puede estar vacia
      POST: Inicializa el cursor en el primer nodo*/
    void inicializarCursor();
    /*PRE: El cursor debe estar inicializado o en algun nodo, la lista no puede estar vacia
      POST: Avanza el cursor un lugar y devuelve false si al avanzar vuelve al primero*/
    bool avanzarCursor();
    /*PRE: El cursor debe estar inicializado o en algun nodo, la lista no puede estar vacia
      POST: Retrocede el cursor un lugar y devuelve false si al retroceder vuelve al ultimo*/
    bool retrocederCursor();
    /*PRE: La lista no puede estar vacia
      POST: Devuelve el dato al que apunta el cursor*/
    T getCursor();
    /*PRE: La posicion pasada debe estar entre 0 y el largo-1 
        (si se pasa uno mas o uno menos se devuelve el primero o el ultimo respectivamente) 
      POST: Devuelve una referencia al elemento de la posicion pasada*/
    T operator[](int posicion);
};


template <class T> Lista <T>::Lista() {
    this->primero = NULL;
    this->cursor = NULL;
    this->largo = 0;
    this->posicionCursor = 0;
}


template <class T> Lista<T>::~Lista() {
    if(this->primero) {
        if (this->primero->_siguiente == this->primero) {
            delete this->primero;
        }
        else {   
            Nodo <T> *nodoActual, *nodoAux;
            nodoActual = this->primero->_siguiente;
            this->primero->_siguiente = NULL;
            while(nodoActual != NULL) {
                nodoAux = nodoActual;
                nodoActual = nodoActual->_siguiente;
                delete nodoAux;
            }
        }
    }
}


template <class T> void Lista<T>::add(T elemento) {
	this->add(elemento, this->largo);
}


template <class T> void Lista<T>::add(T elemento, int posicion) {
    if(posicion < 0 || posicion > this->largo) {//validar la posicion ingresda
        throw "se intentasto agregar en una posicion invalida";
    }  
    Nodo<T> *nuevoNodo=new Nodo<T>(elemento);
    
    if(this->estaVacia()) {
        nuevoNodo->_siguiente=nuevoNodo;
        nuevoNodo->_anterior=nuevoNodo;
        this->primero = nuevoNodo;
    }
    else {
        Nodo<T> *nodoActual;
        nodoActual = this->primero;
        int cont = 0;
        while(cont < posicion) {         
            nodoActual = nodoActual->_siguiente;
            cont++;
        }
        nuevoNodo->_siguiente = nodoActual;
        nuevoNodo->_anterior = nodoActual->_anterior;
        nodoActual->_anterior->_siguiente = nuevoNodo;
        nodoActual->_anterior = nuevoNodo;

        if(posicion == 0) {
            this->primero = nuevoNodo;
        }
    }
    this->largo++;
    this->cursor = nuevoNodo;
}


template <class T> void Lista<T>::inicializarCursor() {
    this->cursor = this->primero;
    this->posicionCursor = 0;
}


template <class T> bool Lista<T>::avanzarCursor() {
    this->cursor = this->cursor->_siguiente;
    if(this->cursor == this->primero) {
        this->posicionCursor = 0;
    }
    else {
        this->posicionCursor++;
    }
    return(this->cursor != this->primero);
}


template <class T> bool Lista<T>::retrocederCursor() {
    this->cursor = this->cursor->_anterior;
    if(this->cursor == this->primero->_anterior) {
        this->posicionCursor = this->largo-1;
    }
    else {
        this->posicionCursor--;
    }
    return(this->cursor != this->primero->_anterior);
}


template <class T> T Lista<T>::getCursor() {
    if(this->cursor == NULL) {
        throw "no hay cursor para una lista vacia";
    }  
    return this->cursor->_dato;
}


template <class T> void Lista<T>::emitir() {  
 
    this->inicializarCursor();
   
    std::cout<<"[";
    if(!this->estaVacia()) {
        do {
            std::cout<<*this->getCursor();
            if(this->cursor != this->primero->_anterior) {
                std::cout<<',';
            }   
            this->avanzarCursor();
        } while(this->cursor != this->primero);
    }
    std::cout<<"]";
}


template <class T> bool Lista <T>::estaVacia() {
    return(this->primero == NULL);
}


template <class T> int Lista<T>::getLargo() {
    return this->largo;
}


template <class T> T Lista<T>::operator[](int posicion) {
    if(posicion < -1 || posicion > this->largo) {//validar la posicion ingresda
        throw "indice de acceso a la lista fuera de rango";
    }  
    if(posicion == this->largo) {
        posicion = 0;
    }
    if(posicion == -1) {
        posicion = this->largo-1;
    }
    int menorDistancia = posicion;
    int desdeCursor = posicion - this->posicionCursor; 
    int hastaFinal = (this->largo-1) - posicion; 
    int hastaCursor = this->posicionCursor - posicion; 
    
    if(desdeCursor<menorDistancia && desdeCursor>=0) {
        menorDistancia = desdeCursor;  
    }
    else if(hastaCursor<menorDistancia && hastaCursor>=0) {
        menorDistancia = hastaCursor;
    }
    else if(hastaFinal<menorDistancia) {
        menorDistancia = hastaFinal;  
        this->inicializarCursor();
        this->retrocederCursor();
    }
    else {
        this->inicializarCursor();
    }
    for(int i=1; i<=menorDistancia; i++) {
        if(menorDistancia == posicion || menorDistancia == desdeCursor) {
            this->avanzarCursor();
        }
        else {
            this->retrocederCursor();
        }
    }
    return this->cursor->_dato;
}

#endif /* LISTADOBLECIRCULAR_H_ */




