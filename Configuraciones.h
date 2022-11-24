#ifndef CONFIGURACIONES_H_
#define CONFIGURACIONES_H_

#include "ListaDobleCircular.h"
#include <string>
#include <fstream>
#include <sstream>

struct Configuracion{
    std::string dificultad;
    int id;
    int capas,filas,columnas;//valores para el tamanio del tablero
    int x1,x2,x3; //valores para nacimiento y muerte
    int cantidadCeldasContaminadas;   //cantidad de celdas tipo contaminada
    int cantidadCeldasEnvenenadas;   //cantidad de celdas tipo envenenada
    int cantidadCeldasProcreadoras;   //cantidad de celdas tipo procreadora
    int cantidadCeldasPortales;   //cantidad de celdas tipo portal
    int cantidadCeldasRadioactivas;   //cantidad de celdas tipo radioactiva
    int cantidadCelulasVivas;   //cantidad de celulas vivas de acuerdo a la configuracion elegida
};

typedef Lista<Configuracion *> *ListaConfiguraciones;

class Configuraciones {
private:
    Configuracion * configAux;
    ListaConfiguraciones lista;
    Configuracion * primeraConf;
    int cantidadDeConfiguraciones;
public:

    //Post: crea una instancia "Configuraciones".
    Configuraciones();

    //Post: Elimina la configuracion.
    ~Configuraciones();

    //Pre: El archivo "Configuracion.txt" debe existir y no debe estar vacío.
    //Post: Almacena las configuraciones del archivo en una lista.
    void obtenerConfiguraciones();

    //Pre: La lista de configuraciones debe existir y no ser null.
    //Post: Lista las configuraciones y sus detalles en consola.
    void mostrarConfiguraciones();

    //Pre: La lista de configuraciones debe existir y no estar vacia.
    //Post: Post: Mediante ingreso de usuario, se establece la configuracion del juego.
    Configuracion seleccionarUnaConfiguracion();

    //Post: Si el jugador decidie cargar manualmente la configuracion, se le pide que ingrese cada valor por terminal.
    Configuracion cargarManualConfig(Configuracion confElegida);

    //Pre: Debe haberse ingresado la configuracion manualmente.
    //Post: Guarda la configuracion manual que ingreso el usuario, en caso de haber elegido ingreso manual, en el archivo Configuracion.txt.
    void escribirUltimaConf(Configuracion conf);

    //Pre: Se debe haber elegido una configuracion.
    //Post: Se asegura que los valores de la configuracion elegida o ingresada manualmente tengan sentido logico.
    void validarConfiguracion(Configuracion conf);
};

#endif /* CONFIGURACIONES_H_ */
