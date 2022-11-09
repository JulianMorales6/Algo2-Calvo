#include "ListaDobleCircular.h"

typedef struct{
    string dificultad;
    int id;
    int largo,ancho,profundidad;//valores para el tamanio del tablero
    int x1,x2,x3; //valores para nacimiento y muerte
    int cantidadCeldasTipo1;   //cantidad de celdas tipo contaminada
    int cantidadCeldasTipo2;   //cantidad de celdas tipo envenenada
    int cantidadCeldasTipo3;   //cantidad de celdas tipo procreadora
    int cantidadCeldasTipo4;   //cantidad de celdas tipo portal
    int cantidadCeldasTipo5;   //cantidad de celdas tipo radioactiva
    
} Configuracion;

typedef Lista<Configuracion *> *ListaConfiguraciones;

class Configuraciones {
private:
    Configuracion * configAux;
    ListaConfiguraciones lista;
    Configuracion * primero;
    int cantidadDeConfiguraciones;
public:

    // pre: El archivo "config.csv" no debe estar vacío.
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
    Configuracion * seleccionarUnaConfiguracion();
};
