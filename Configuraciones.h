#ifndef CONFIGURACIONES_H_
#define CONFIGURACIONES_H_

#include "ListaDobleCircular.h"

struct Configuracion{
    string dificultad;
    int id;
    int capas,filas,columnas;//valores para el tamanio del tablero
    int x1,x2,x3; //valores para nacimiento y muerte
    int cantidadCeldasContaminadas;   //cantidad de celdas tipo contaminada
    int cantidadCeldasEnvenenadas;   //cantidad de celdas tipo envenenada
    int cantidadCeldasProcreadoras;   //cantidad de celdas tipo procreadora
    int cantidadCeldasPortales;   //cantidad de celdas tipo portal
    int cantidadCeldasRadioactivas;   //cantidad de celdas tipo radioactiva
    
};

typedef Lista<Configuracion *> *ListaConfiguraciones;

class Configuraciones {
private:
    Configuracion * configAux;
    ListaConfiguraciones lista;
    Configuracion * primeraConf;
    int cantidadDeConfiguraciones;
public:

    // pre: El archivo "Configuracion.txt" no debe estar vacío.
    // post: crea una instancia "Configuraciones".
    Configuraciones();

    //Post: Elimina la configuracion
    ~Configuraciones();

    //Pre: El archivo "config.csv" debe existir y no debe estar vacío.
    //Post: Lee el archivo y almacena las configuraciones en una lista
    void obtenerConfiguraciones();

    //Post: Lista las dificultades en consola.
    void mostrarConfiguraciones();

    //Post: Mediante ingreso de usuario, se establece la configuracion del juego.
    Configuracion seleccionarUnaConfiguracion();

    Configuracion cargarManualConfig(Configuracion confElegida);
};

#endif /* CONFIGURACIONES_H_ */
