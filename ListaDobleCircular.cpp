#include <iostream>
using namespace std;


template <class T> class Lista; //para usar el friend


template <class T> class Nodo {
    friend class Lista<T>;
    private:
    T _dato;
    Nodo<T> *_siguiente;
    Nodo<T> *_anterior;
    public:
    Nodo(T dato);
};

template <class T> Nodo<T>::Nodo(T dato) {
    _dato = dato;
    _siguiente = NULL;
    _anterior = NULL;

}



template <class T> class Lista {
    private:
    Nodo<T> *primero;
    Nodo<T> *cursor;
    int largo;
    public:
    //constructor
    Lista();
    //destructor
    ~Lista();
    //agrega el elemento pasado al final
    void add(T elemento);
    //inserta el elemento pasado en una posicion especifica
	void add(T elemento, int posicion);
    //saca el primero elemento que sea igual al pasado? falta implementar
    void remove(T elemento);
    //devuelve el largo de la lista
    int getLargo();
    //verifica si la lista esta vacia
    bool estaVacia();
    //muestra la lista
    void emitir();
    //mueve el cursor a la primera posicion
    void inicializarCursor();
    //avanza el cursor un lugar
    void avanzarCursor();
    //retrocede el cursor un lugar
    void retrocederCursor();
    //devuelve el elemento almacenado en el nodo
    T getCursor();
};


template <class T> Lista <T>::Lista() {
    primero=NULL;
    cursor=NULL;
    largo=0;
}


template <class T> Lista<T>::~Lista() {
    if(primero) {
        if (primero->_siguiente == primero) {
            delete primero;
        }
        else {   
            Nodo <T> *nodoActual, *nodoAux;
            nodoActual=primero->_siguiente;
            primero->_siguiente =0;
            while(nodoActual!=0) {
                nodoAux=nodoActual;
                nodoActual=nodoActual->_siguiente;
                delete nodoAux;
            }
        }
    }
}


template <class T> void Lista<T>::add(T elemento) {
	add(elemento, largo);
}


template <class T> void Lista<T>::add(T elemento, int posicion) {
    if(posicion < 0 || posicion > largo) {//validar la posicion ingresda
        throw invalid_argument("posicion fuera de rango");
    }  
    Nodo<T> *nuevoNodo=new Nodo<T>(elemento);
    if(estaVacia()) {
        nuevoNodo->_siguiente=nuevoNodo;
        nuevoNodo->_anterior=nuevoNodo;
        primero = nuevoNodo;
    }
    else {
        Nodo<T> *nodoActual;
        nodoActual = primero;
        int cont = 0;
        while(cont < posicion) {         
            nodoActual = nodoActual->_siguiente;
            cont++;
        }
        nuevoNodo->_siguiente=nodoActual;
        nuevoNodo->_anterior=nodoActual->_anterior;
        nodoActual->_anterior->_siguiente=nuevoNodo;
        nodoActual->_anterior=nuevoNodo;

        if(posicion==0) {
            primero = nuevoNodo;
        }
    }
    largo++;
    inicializarCursor();
}


template <class T> void Lista<T>::inicializarCursor(){
    cursor=primero;
}


template <class T> void Lista<T>::avanzarCursor() {
    if(!estaVacia()) {
        cursor=cursor->_siguiente;
    }
}


template <class T> void Lista<T>::retrocederCursor() {
    if(!estaVacia()) {
        cursor=cursor->_anterior;
    }
}


template <class T> T Lista<T>::getCursor() {
    if(cursor==NULL) {
        throw invalid_argument("cursor invalido para una lista vacia");
    }  
    return cursor->_dato;
}


template <class T> void Lista<T>::emitir() {  
    Nodo<T> *aux=primero;
    cout<<"[";
    if(!estaVacia()) {
        do {
            cout<<aux->_dato;
            if (aux!=primero->_anterior) {
                cout<<',';
            }   
            aux=aux->_siguiente;
        } while(aux!=primero);
    }
    cout<<"]"<<endl;
}


template <class T> bool Lista <T>::estaVacia() {
    return(primero==NULL);
}


template <class T> int Lista<T>::getLargo() {
    return largo;
}


int main() {

    Lista <char> c1;

    c1.add('a');
    c1.add('b');
    c1.add('u', 0);
    c1.add('c');
    c1.emitir();
    

    for (int i=1; i<=2; i++) {
        c1.avanzarCursor();
    }
    for (int i=1; i<=0; i++) {
        c1.retrocederCursor();
    }

    cout<<(c1.getCursor())<<endl;

    return 0;
}

