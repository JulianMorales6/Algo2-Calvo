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
    
}Configuracion;

typedef Lista<Configuracion *> *ListaConfiguraciones;

class Configuraciones {
private:
    Configuracion * configAux;
    ListaConfiguraciones lista;
    Configuracion * primero;
    int cantidadDeConfiguraciones;
public:

    // pre: El archivo "config.csv" no debe estar vacío.
    // post: crea una lista de configuraciones a partir de "config.csv".
    Configuraciones();


    ~Configuraciones();
    void obtenerConfiguraciones();
    void mostrarConfiguraciones();
};
