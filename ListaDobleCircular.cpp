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
    void borrar();
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

    T &operator[](int);

    void reiniciarCursor();
};


template <class T> Lista <T>::Lista() {
    primero=NULL;
    cursor=NULL;
    largo=0;
}


template <class T> void Lista<T>::borrar() {
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
        cout<<"borra"<<endl;  
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
        throw invalid_argument("no hay cursor para una lista vacia");
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
    cout<<"]";
}


template <class T> bool Lista <T>::estaVacia() {
    return(primero==NULL);
}


template <class T> int Lista<T>::getLargo() {
    return largo;
}


template <class T> T &Lista<T>::operator[](int posicion){
    if(posicion < 0 || posicion >= largo) {//validar la posicion ingresda
        throw invalid_argument("posicion fuera de rango");
    }  
    if(estaVacia()){
        throw invalid_argument("lista vacia");
    }




    inicializarCursor();
    int cont = 0;
    while(cont < posicion){
        avanzarCursor();
        cont++;
    }
    return cursor->_dato;
}





int main() {
    typedef Lista<Lista<int>> listaDeListas;
   
    Lista<int> lis1, lis2, lis3;

    for (int i=1; i<=3; i++) {
        lis1.add(i);
    }
    for (int i=4; i<=6; i++) {
        lis2.add(i);
    }
     for (int i=7; i<=9; i++) {
        lis3.add(i);
    }   
    
	listaDeListas col1;
	col1.add(lis1);
    col1.add(lis2);
    col1.add(lis3);

 
    
    cout<<"[";
    for(int i=1; i<=col1.getLargo(); i++){
        col1.getCursor().emitir();
        col1.avanzarCursor();
    }
    cout<<"]"<<endl;

    lis1.borrar();
    col1.borrar();

    
    return 0;
}

/*error con el destructor: en add despues de crear el nuevo nodo que tiene como elemento otra lista, 
como ya no se va a usar esa lista en ningun otro lugar se ejecuta el destructor y 
esto porvoca que mute la guardada en el nodo nuevo*/


