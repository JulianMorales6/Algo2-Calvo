#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Configuraciones.h"
#define ARCHIVO_CONFIGURACIONES "data.csv"

using namespace std;



Configuraciones::Configuraciones() {
    this->lista = new Lista<Configuracion *>;
    this->primero = new Configuracion;
    this->obtenerConfiguraciones();
}

void Configuraciones::obtenerConfiguraciones() {
    ifstream archivo(ARCHIVO_CONFIGURACIONES);
    string linea, dato;

    char separador = ',';
    getline(archivo,linea);
    int i = 1;
    while(getline(archivo,linea)) {
        this->configAux = new Configuracion;
        stringstream stream(linea);
        getline(stream, this->configAux->dificultad, separador);

        getline(stream, dato, separador);
        this->configAux->largo = stoi(dato);

        getline(stream, dato, separador);
        this->configAux->ancho = stoi(dato);

        getline(stream, dato, separador);
        this->configAux->profundidad = stoi(dato);

        getline(stream, dato, separador);
        this->configAux->x1 = stoi(dato);

        getline(stream, dato, separador);
        this->configAux->x2 = stoi(dato);

        getline(stream, dato, separador);
        this->configAux->x3 = stoi(dato);

        getline(stream, dato, separador);
        this->configAux->cantidadCeldasTipo1 = stoi(dato);

        getline(stream, dato, separador);
        this->configAux->cantidadCeldasTipo2 = stoi(dato);

        getline(stream, dato, separador);
        this->configAux->cantidadCeldasTipo3 = stoi(dato);

        getline(stream, dato, separador);
        this->configAux->cantidadCeldasTipo4 = stoi(dato);

        getline(stream, dato, separador);
        this->configAux->cantidadCeldasTipo5 = stoi(dato);
        
        this->configAux->id = i;

        // Configuracion *punteroAuxiliar = configAux;
        this->lista->add(this->configAux);
        if (this->primero->dificultad == "")
        {
            this->primero = this->configAux;
        }
        
        i++;
    }

    this->cantidadDeConfiguraciones = this->configAux->id;

    archivo.close();
}

void Configuraciones::mostrarConfiguraciones() {
    this->lista->inicializarCursor();
    if(!this->lista->estaVacia()) {
        do
        {
            cout<<this->lista->getCursor()->id<<" - "<<this->lista->getCursor()->dificultad<<endl;
            this->lista->avanzarCursor();
        } while (this->lista->getCursor()->id != this->primero->id);
    }
    cout<<this->cantidadDeConfiguraciones + 1<<" - Carga manual"<<endl;
    
}

Configuracion * Configuraciones::seleccionarUnaConfiguracion() {
    int idElegido;
    Configuracion * confElegida;
    cout<<"Elija una dificultad o seleccione 'Carga manual' con uno de los numeros: "<<endl;
    cin>>idElegido;
    this->lista->inicializarCursor();
    if (!idElegido >= 1 && !idElegido >= (this->cantidadDeConfiguraciones + 1)) {
        throw "Esa opcion no existe.";
    }
    do
    {
        this->lista->avanzarCursor();
        confElegida = this->lista->getCursor();
    } while (idElegido != this->lista->getCursor()->id);
    return confElegida;
}

Configuraciones::~Configuraciones() {
    delete this->configAux;
    delete this->lista;
    delete this->primero;
}

int main() {
    Configuraciones * config = new Configuraciones;
    config->mostrarConfiguraciones();
    Configuracion * confElegida = config->seleccionarUnaConfiguracion();
    cout<<confElegida->dificultad;
    delete config;
}