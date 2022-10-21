#include <iostream>
using namespace std;

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
    /*POST: Agrega el elemento pasado al final de la lista*/
    void add(T elemento);
    /*PRE: La posicion pasada esta entre 0 y el largo de la lista
      POST: Inserta el elemento en la posicion pasada*/
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
    /*PRE: La lista no puede estar vacia
      POST: Avanza el cursor un lugar*/
    void avanzarCursor();
    /*PRE: La lista no puede estar vacia
      POST: Retrocede el cursor un lugar*/
    void retrocederCursor();
    /*PRE: La lista no puede estar vacia
      POST: Devuelve el dato al que apunta el cursor*/
    T getCursor();
    /*PRE: La posicion pasada debe estar entre -1 y largo
      POST: Devuelve una referencia al elemento de la posicion pasada*/
    T operator[](int posicion);

    //T operator[] (int j);
 
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
        throw invalid_argument("posicion fuera de rango");
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
    this->cursor = nuevoNodo;
    this->largo++;
}


template <class T> void Lista<T>::inicializarCursor(){
    this->cursor = this->primero;
    this->posicionCursor = 0;
}


template <class T> void Lista<T>::avanzarCursor() {
    if(!this->estaVacia()) {
        this->cursor = this->cursor->_siguiente;
        if(this->cursor == this->primero){
            this->posicionCursor = 0;
        }
        else{
            this->posicionCursor++;
        }
    }
}


template <class T> void Lista<T>::retrocederCursor() {
    if(!this->estaVacia()) {
        this->cursor = this->cursor->_anterior;
        if(this->cursor == this->primero->_anterior){
            this->posicionCursor = this->largo-1;
        }
        else{
            this->posicionCursor--;
        }
    }
}


template <class T> T Lista<T>::getCursor() {
    if(this->cursor == NULL) {
        throw invalid_argument("no hay cursor para una lista vacia");
    }  
    return this->cursor->_dato;
}



template <class T> void Lista<T>::emitir() {  
 
    this->inicializarCursor();
   
    cout<<"[";
    if(!this->estaVacia()) {
        do {
            cout<<*this->getCursor();
            if(this->cursor != this->primero->_anterior) {
                cout<<',';
            }   
            this->avanzarCursor();
        } while(this->cursor != this->primero);
    }
    cout<<"]";
}




template <class T> bool Lista <T>::estaVacia() {
    return(this->primero == NULL);
}


template <class T> int Lista<T>::getLargo() {
    return this->largo;
}



template <class T> T Lista<T>::operator[](int posicion){
    if(posicion < -1 || posicion > this->largo) {//validar la posicion ingresda
        throw invalid_argument("posicion fuera de rango");
    }  
    if(posicion == this->largo){
        posicion = 0;
    }
    if(posicion == -1){
        posicion = this->largo-1;
    }
    int desdePrincipio = posicion; 
    int desdeCursor = posicion - this->posicionCursor; 
    int hastaFinal = this->largo - posicion-1; 
    int hastaCursor = this->posicionCursor - posicion; 
    int menorDistancia = desdePrincipio;

    if(desdeCursor<menorDistancia && desdeCursor>=0){
        menorDistancia = desdeCursor;  
    }
    else if(hastaCursor<menorDistancia && hastaCursor>=0){
        menorDistancia = hastaCursor;
    }
    else if(hastaFinal<menorDistancia && hastaFinal>=0){
        menorDistancia = hastaFinal;  
        this->inicializarCursor();
        this->retrocederCursor();
    }
    else{
        this->inicializarCursor();
    }
    for(int i=1; i<=menorDistancia; i++){
        if(menorDistancia == desdePrincipio || menorDistancia == desdeCursor){
            this->avanzarCursor();
        }
        else{
            this->retrocederCursor();
        }
    }
    return this->cursor->_dato;
}


/*
template <class T> T Lista<T>::operator[] (int j) {
    j--;
    while(j> this->largo-1) {
        j = j-this->largo;
    };
    while(j< 0) {
        j = j+this->largo;
    }; 
    
    int dif;
    Nodo<T> * nodoAux;
    T dato;
    if(j>this->posicionCursor) {
        dif = j-this->posicionCursor;
        if(dif<=this->largo-j) {
            nodoAux = this->cursor;
            for(int i = 0; i <= j-this->posicionCursor; i++) {
                nodoAux = nodoAux->_siguiente;
                this->avanzarCursor();
            }
        } else {
            nodoAux = this->primero;
            for(int i = 0; i <= this->largo-j; i++) {
                nodoAux = nodoAux->_anterior;
                this->retrocederCursor();
            }
        }
    } else {
        dif = this->posicionCursor-j;
        if(dif<j) {
            nodoAux = this->cursor;
            for(int i = 0; i <= this->posicionCursor-j; i++) {
                nodoAux = nodoAux->_anterior;
                this->retrocederCursor();
            }
        } else {
            nodoAux = this->primero;
            for(int i = 0; i <= j; i++) {
                nodoAux = nodoAux->_siguiente;
                this->avanzarCursor();
            }
        }
    }
    dato = nodoAux->_dato;
    return dato;
};

*/







