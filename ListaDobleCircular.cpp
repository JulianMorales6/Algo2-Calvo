#include <iostream>
using namespace std;


template <class T> class Lista; //para usar el friend

template <class T>
class Nodo {
    friend class Lista<T>;
    private:
    T _dato;
    Nodo<T> *_sig;
    Nodo<T> *_ant;
    public:
    Nodo(T dato, Nodo<T> *sig=0, Nodo<T> *ant=0) {
        _dato = dato;
        _sig = sig;
        _ant = ant;
    };
};




template <class T>
class Lista {
    private:
    Nodo<T> *primero;
    Nodo<T> *ultimo;
    Nodo<T> *cursor;
    int largo;
    public:
    Lista();
    ~Lista();
    //agrega el elemento pasado al final de la lista
    void add(T elemento);
    //inerta el elemento pasado en una posicion especifica
	void add(T elemento, int posicion);
    //saca el primero elemento que sea igual al pasado?
    void remove();
    //devuelve el largo de la lista
    int getLargo();
    //borra al elemento en la posicion pasada

    bool vacia();
    //muestra la lista
    void emitir();
    //avanza el cursor un lugar
    void avanzarCursor();
    //retrocede el cursor un lugar
    void retrocederCursor();
    //devuelve el elemento almacenado en el nodo
    T getCursor();
};


template <class T>
Lista <T>::Lista() {
    primero=0;
    ultimo=0;
    cursor=0;
    largo=0;

}


template <class T>
Lista<T>::~Lista() {
    if(primero) {
        if (primero->_sig == primero) {
            delete primero;
        }
        else {   
            Nodo <T> *aux1, *aux2;
            aux1=primero->_sig;
            primero->_sig =0;
            while(aux1!=0) {
                aux2=aux1;
                aux1=aux1->_sig;
                delete aux2;
            }
        }
    }
}


template<class T> 
void Lista<T>::add(T elemento) {
	add(elemento, largo);
}


template <class T>
void Lista<T>::add(T elemento, int posicion) {
    
    if(posicion < 0 || posicion > largo) {
        return;
    }  
    Nodo<T> *nuevo=new Nodo<T>(elemento);
    if(vacia()) {
        primero = nuevo;
        ultimo = nuevo;
        nuevo->_sig=nuevo;
        nuevo->_ant=nuevo;
    }
    else {
        Nodo<T> *aux1, *aux2;
        aux1 = primero;
        aux2 = ultimo;
        int cont = 0;
        while(cont < posicion) {
            aux2 = aux1;
            aux1 = aux1->_sig;
            cont++;
        }
        nuevo->_sig=aux1;
        nuevo->_ant=aux2;
        aux2->_sig=nuevo;
        aux1->_ant=nuevo;

        if(posicion==0) {
            primero = nuevo;
        }
        if(posicion==largo) {
            ultimo = nuevo;
        }
    }
    largo++;
}


template <class T>
void Lista<T>::avanzarCursor() {
    if(cursor==0) {
        cursor=primero;
    }
    else {
        cursor=cursor->_sig;
    }
}


template <class T>
void Lista<T>::retrocederCursor() {
    if(cursor==0) {
        cursor=ultimo;
    }
    else {
        cursor=cursor->_ant;
    }
}


template <class T>
T Lista<T>::getCursor() {
    return cursor->_dato;
}


template <class T>
void Lista<T>::emitir() {  
    Nodo<T> *aux=primero;
    cout<<"[";
    do {
        cout<<aux->_dato;
        if (aux!=ultimo) {
            cout<<',';
        }   
        aux=aux->_sig;
    } while(aux!=primero);
    cout<<"]"<<endl;
}


template <class T>
bool Lista <T>::vacia() {
    return(primero==0);
}


template <class T>
int Lista<T>::getLargo() {
    return largo;
}


int main() {

    Lista <char> c1;

    c1.add('a');
    c1.add('b');
    c1.add('c');
    c1.add('0');
    c1.emitir();

    for (int i=1; i<=1; i++) {
        c1.avanzarCursor();
    }

    for (int i=1; i<=0; i++) {
        c1.retrocederCursor();
    }

    cout<<(c1.getCursor())<<endl;

    return 0;
}

