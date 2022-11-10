#ifndef NODO_H_
#define NODO_H_



template <class T> class Lista;


template <class T> class Nodo {
    friend class Lista<T>;
    private:
    T _dato;
    Nodo<T> *_siguiente;
    Nodo<T> *_anterior;
    public:
    Nodo(T dato);
    ~Nodo();
};

template <class T> Nodo<T>::Nodo(T dato) {
    _dato = dato;
    _siguiente = NULL;
    _anterior = NULL;

}

template <class T> Nodo<T>::~Nodo() {
    delete this->_dato;
}


#endif /* NODO_H_ */
