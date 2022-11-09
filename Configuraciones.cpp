#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Configuraciones.h"
#define ARCHIVO_CONFIGURACIONES "data.csv"

using namespace std;



Configuraciones::Configuraciones() {
    this->lista = new Lista<Configuracion *>;
    this->obtenerConfiguraciones();
}

void Configuraciones::obtenerConfiguraciones() {
    ifstream archivo(ARCHIVO_CONFIGURACIONES);
    string linea, dato;

    char separador = ',';
    getline(archivo,linea);
    while(getline(archivo,linea)) {
        stringstream stream(linea);
        getline(stream, configAux.dificultad, separador);

        getline(stream, dato, separador);
        configAux.largo = stoi(dato);

        getline(stream, dato, separador);
        configAux.ancho = stoi(dato);

        getline(stream, dato, separador);
        configAux.profundidad = stoi(dato);

        getline(stream, dato, separador);
        configAux.x1 = stoi(dato);

        getline(stream, dato, separador);
        configAux.x2 = stoi(dato);

        getline(stream, dato, separador);
        configAux.x3 = stoi(dato);

        getline(stream, dato, separador);
        configAux.cantidadCeldasTipo1 = stoi(dato);

        getline(stream, dato, separador);
        configAux.cantidadCeldasTipo2 = stoi(dato);

        getline(stream, dato, separador);
        configAux.cantidadCeldasTipo3 = stoi(dato);

        getline(stream, dato, separador);
        configAux.cantidadCeldasTipo4 = stoi(dato);

        getline(stream, dato, separador);
        configAux.cantidadCeldasTipo5 = stoi(dato);

        Configuracion * punteroAuxiliar = &configAux;
        this->lista->add(punteroAuxiliar);
    }
    archivo.close();
}