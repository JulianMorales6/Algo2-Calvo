#ifndef NULL
#define NULL 0
#endif /* NULL */


template <class T> class Lista;


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