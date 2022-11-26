#ifndef NODO_H_
#define NODO_H_

template <class T> class Nodo {
    private:
    T dato;
    Nodo<T> *siguiente;
    Nodo<T> *anterior;
    public:
    /*PRE:
      POST: se inicializa en nodo con el dato pasado y el siguiente y anterior en null*/
    Nodo(T dato);
    /*PRE:
      POST:cambia el valor del dato*/
    void setDato(T nuevoDato);
    /*PRE:
      POST:devuelve el dato que contiene el nodo*/
    T getDato();
    /*PRE:
      POST:cambia el siguiente nodo por el nuevo*/
    void setSiguiente(Nodo<T> *nuevoSiguiente);
    /*PRE:
      POST:devuelve el siguiente nodo*/
    Nodo<T>* getSiguiente();
    /*PRE:
      POST:cambia el anterior nodo por el nuevo*/
    void setAnterior(Nodo<T> *nuevoAnterior);
    /*PRE:
      POST:devuelve el nodo anterior*/
    Nodo<T>* getAnterior();
};

template <class T> Nodo<T>::Nodo(T nuevoDato) {
    dato = nuevoDato;
    siguiente = NULL;
    anterior = NULL;
}

template <class T> void Nodo<T>::setDato(T nuevoDato) {
    this->dato = nuevoDato;
}

template <class T> T Nodo<T>::getDato() {
    return this->dato;
}

template <class T> void Nodo<T>::setSiguiente(Nodo<T> *nuevoSiguiente) {
    this->siguiente = nuevoSiguiente;
}

template <class T> Nodo<T>* Nodo<T>::getSiguiente() {
    return this->siguiente;
}

template <class T> void Nodo<T>::setAnterior(Nodo<T> *nuevoAnterior) {
    this->anterior = nuevoAnterior;
}

template <class T> Nodo<T>* Nodo<T>::getAnterior() {
    return this->anterior;
}

#endif /* NODO_H_ */