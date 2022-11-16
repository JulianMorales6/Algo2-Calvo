#ifndef JUEGODELAVIDA_H_
#define JUEGODELAVIDA_H_
#include "Tablero.cpp"
#include "Configuraciones.h"
#include "bmp/EasyBMP.h"
#include "bmp/EasyBMP_Geometry.h"
#include "bmp/EasyBMP_Font.h"
#include <string>

// typedef struct {
//     string dificultad;
//     int capas, filas, columnas;//valores para el tamanio del tablero
//     int x1,x2,x3; //valores para nacimiento y muerte
//     int cantidadCeldasTipo1;   //cantidad de celdas tipo contaminada
//     int cantidadCeldasTipo2;   //cantidad de celdas tipo envenenada
//     int cantidadCeldasTipo3;   //cantidad de celdas tipo procreadora
//     int cantidadCeldasTipo4;   //cantidad de celdas tipo portal
//     int cantidadCeldasTipo5;   //cantidad de celdas tipo radioactiva
    
// }Configuracion;

typedef struct {
    int nacimientosTotales;
    int muertesTotales;
    int celulasVivas;
    int nacimientosDelTurno;
    int muertesDelTurno;
    int turnos;
    int controlMuertes;
    int controlNacimientos;
}Estadisticas;

class JuegoDeLaVida {
    private:
    Tablero * tablero;
    Tablero * tableroAux;
    Estadisticas estadisticas;
    Configuracion configuracion;
    
    public:
    JuegoDeLaVida();
    ~JuegoDeLaVida();
    void inicializarJuegoDeLaVida();
    void mostrarJuegoDeLaVida();
    void cargarCelulasVivas();
    void interaccionesUsuario();
    void cargarConfiguracion();
    void cargarComportamientos();
    void cambiarEstado(int capa, int fila, int columna, EstadoDeCelula estado);
    void cambiarComportamiento(int capa, int fila, int columna, ComportamientoDeCelda comportamiento);
    ComportamientoDeCelda obtenerComportamiento(int capa, int fila, int columna);
    void pasarTurno();
    void copiarTableroAuxiliar();
    void actualizarCelulasVivas();
    void actualizarControlMuertes();
    void actualizarEstadoCelula(int capa, int fila, int columna);
    void setGenesCelula(int capa, int fila, int columna, int gen1, int gen2, int gen3);
    void controlMuertes();
    void setConfiguracion();
};
#endif /* JUEGODELAVIDA_H_ */
