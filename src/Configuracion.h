
#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

#include <iostream>
#include <string>

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

    Configuracion();

};



#endif /* CONFIGURACION_H_ */
