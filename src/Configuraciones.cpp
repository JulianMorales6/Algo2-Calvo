#include <iostream>
#include <string>
#include <fstream>
#include "Configuraciones.h"

using namespace std;



Configuraciones::Configuraciones() {
    this->lista = new Lista<Configuracion *>;
    this->primeraConf = new Configuracion;
    this->obtenerConfiguraciones();
}

void Configuraciones::obtenerConfiguraciones() {
    string rutaArchivo = "src/Configuracion.txt";
    ifstream archivo;
    archivo.open(rutaArchivo.c_str());
    string linea;
    getline(archivo, linea);
    int i = 1;
    while(! archivo.eof()) {
        this->configAux = new Configuracion;

        archivo >> this->configAux->dificultad;
        archivo >> this->configAux->capas;
        archivo >> this->configAux->filas;
        archivo >> this->configAux->columnas;
        archivo >> this->configAux->x1;
        archivo >> this->configAux->x2;
        archivo >> this->configAux->x3;
        archivo >> this->configAux->cantidadCeldasContaminadas;
        archivo >> this->configAux->cantidadCeldasEnvenenadas;
        archivo >> this->configAux->cantidadCeldasProcreadoras;
        archivo >> this->configAux->cantidadCeldasPortales;
        archivo >> this->configAux->cantidadCeldasRadioactivas;
        this->configAux->id = i;
        //Configuracion *punteroAuxiliar = configAux;
        this->lista->add(this->configAux);
        if (this->primeraConf->dificultad == "")
        {
            this->primeraConf = this->configAux;
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
            cout<<this->lista->getCursor()->id<<" - "<<this->lista->getCursor()->dificultad<<endl<<
            "    Capas: "<<
            this->lista->getCursor()->capas<<endl<<
            "    Filas: "<<
            this->lista->getCursor()->filas<<endl<<
            "    Columnas: "<<
            this->lista->getCursor()->columnas<<endl<<
            "    Vecinas necesarias para nacer: "<<
            this->lista->getCursor()->x1<<endl<<
            "    Vecinas minimas para seguir viva: "<<
            this->lista->getCursor()->x2<<endl<<
            "    Vecinas maximas para seguir vivas: "<<
            this->lista->getCursor()->x3<<endl<<
            "    Cantidad de celdas contaminadas: "<<
            this->lista->getCursor()->cantidadCeldasContaminadas<<endl<<
            "    Cantidad de celdas envenenadas: "<<
            this->lista->getCursor()->cantidadCeldasEnvenenadas<<endl<<
            "    Cantidad de celdas procreadoras: "<<
            this->lista->getCursor()->cantidadCeldasProcreadoras<<endl<<
            "    Cantidad de celdas portales: "<<
            this->lista->getCursor()->cantidadCeldasPortales<<endl<<
            "    Cantidad de celdas radioactivas: "<<
            this->lista->getCursor()->cantidadCeldasRadioactivas<<endl<<endl;
            this->lista->avanzarCursor();
        } while (this->lista->getCursor()->id != this->primeraConf->id);
    }
    cout<<this->cantidadDeConfiguraciones + 1<<" - Carga manual"<<endl;
    
}

Configuracion Configuraciones::seleccionarUnaConfiguracion() {
    int idElegido;
    Configuracion confElegida;
    cout<<"Elija una dificultad o seleccione 'Carga manual' con uno de los numeros: "<<endl;
    cin>>idElegido;
    this->lista->inicializarCursor();
    if (idElegido < 1 || idElegido > (this->cantidadDeConfiguraciones + 1)) {
        throw "Esa opcion no existe.";
    }
    if (idElegido == (this->cantidadDeConfiguraciones + 1)) {
        confElegida = cargarManualConfig(confElegida);
    } else {
    do
    {
        this->lista->avanzarCursor();
        confElegida = *this->lista->getCursor();
    } while (idElegido != this->lista->getCursor()->id);
    }
    validarConfiguracion(confElegida);
    return confElegida;
}

void Configuraciones::validarConfiguracion(Configuracion conf) {
    int cantidadTotalCeldas, cantidadDeCeldasConComportamiento;
    bool error = false;
    cantidadTotalCeldas = conf.capas * conf.filas * conf.columnas;
    cantidadDeCeldasConComportamiento = conf.cantidadCeldasContaminadas + conf.cantidadCeldasEnvenenadas + conf.cantidadCeldasProcreadoras + conf.cantidadCeldasPortales + conf.cantidadCeldasRadioactivas;

    if(conf.cantidadCeldasContaminadas < 0 || conf.cantidadCeldasEnvenenadas < 0 || conf.cantidadCeldasProcreadoras < 0 || conf.cantidadCeldasPortales < 0 || conf.cantidadCeldasRadioactivas < 0 || conf.x1 < 0 || conf.x2 < 0 || conf.x3 < 0 || conf.capas < 0 || conf.filas < 0 || conf.columnas < 0) {
        error = true;
    }

    if(conf.x1 > 26 || conf.x2 > 26 || conf.x3 > 26 || conf.x2 > conf.x3) {
        error = true;
    }

    if (cantidadDeCeldasConComportamiento > cantidadTotalCeldas)
    {
        error = true;
    }
    
    if(error) {
        cout<<"Error de configuracion, tenga en cuenta que: "<<endl<<"Todos los valores que ingresa deben ser enteros positivos o 0"<<endl<<"  Los cinco comportamientos de celdas no deben ser negativos y su suma no puede ser mayor al producto de capas, filas y columnas."<<endl<<"    Tanto las vecinas necesarias para nacer, las vecinas minimas para seguir viva y las vecinas maximas para seguir viva deben tener un valor de maximo 26"<<endl<<"Vecinas minimas para no morir (x2) debe ser menor o igual a Vecinas maximas para no morir (x3)"<<endl;
        seleccionarUnaConfiguracion();
    }

}

Configuracion Configuraciones::cargarManualConfig(Configuracion confElegida) {
    cout<<"Cantidad de capas: ";
    cin>>confElegida.capas;
    cout<<"Cantidad de filas: ";
    cin>>confElegida.filas;
    cout<<"Cantidad de columnas: ";
    cin>>confElegida.columnas;
    cout<<"Vecinas vivas necesarias para nacer: ";
    cin>>confElegida.x1;
    cout<<"Minimo de vecinas vivas para no morir: ";
    cin>>confElegida.x2;
    cout<<"Maximo de vecinas vivas para no morir: ";
    cin>>confElegida.x3;
    cout<<"Cantidad de celdas contaminadas: ";
    cin>>confElegida.cantidadCeldasContaminadas;
    cout<<"Cantidad de celdas envenenadas: ";
    cin>>confElegida.cantidadCeldasEnvenenadas;
    cout<<"Cantidad de celdas procreadoras: ";
    cin>>confElegida.cantidadCeldasProcreadoras;
    cout<<"Cantidad de celdas portales: ";
    cin>>confElegida.cantidadCeldasPortales;
    cout<<"Cantidad de celdas radioactivas: ";
    cin>>confElegida.cantidadCeldasRadioactivas;
    confElegida.dificultad = "Custom";
    validarConfiguracion(confElegida);
    escribirUltimaConf(confElegida);
    return confElegida;
}

void Configuraciones::escribirUltimaConf(Configuracion conf) {
    string rutaArchivo = "Configuracion.txt", rutaTemp = "Configuracion.tmp", dato;
    ifstream archivo;
    ofstream archivoTemp;
    archivo.open(rutaArchivo.c_str());
    archivoTemp.open(rutaTemp.c_str());
    getline(archivo, dato);
    archivoTemp << dato << '\n';
    archivo >> dato;
    while(dato != "UltimaCustomIngresada" && !archivo.eof()) {
        archivoTemp << dato << ' ';
        getline(archivo, dato);
        archivoTemp << dato << '\n';
        archivo >> dato;
    }

    archivo.close();

    archivoTemp << "UltimaCustomIngresada " << conf.capas << " " << conf.filas << " " << conf.columnas << " " << conf.x1 << " " << conf.x2 << " " << conf.x3 << " " << conf.cantidadCeldasContaminadas << " " << conf.cantidadCeldasEnvenenadas << " " << conf.cantidadCeldasProcreadoras << " " << conf.cantidadCeldasPortales << " " << conf.cantidadCeldasRadioactivas;

    archivoTemp.close();
    remove("Configuracion.txt");
    rename("Configuracion.tmp", "Configuracion.txt");
}

Configuraciones::~Configuraciones() {
    delete this->lista;
    delete this->configAux;
    delete this->primeraConf;
}
