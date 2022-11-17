#ifndef CONFIGURACIONES_H_
#define CONFIGURACIONES_H_

#include "ListaDobleCircular.h"
#include "Configuracion.h"

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

    void escribirUltimaConf(Configuracion conf);

    void validarConfiguracion(Configuracion conf);
};

#endif /* CONFIGURACIONES_H_ */
