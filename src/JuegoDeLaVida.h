#ifndef JUEGODELAVIDA_H_
#define JUEGODELAVIDA_H_
#include "Tablero.h"
#include "Configuraciones.h"
#include "Estadisticas.h"
#include "Configuracion.h"
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

/*
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
*/

class JuegoDeLaVida {
    private:
    Tablero * tablero;
    Tablero * tableroAux;
    Estadisticas estadisticas;
    Configuracion configuracion;
    
    public:
    /* PRE:
       POST: Crea un juego de la vida inicialmente con datos en NULL*/
    JuegoDeLaVida();
    /* PRE:
       POST: Destruye la instancia de JuegoDeLaVida y sus datos*/    
    ~JuegoDeLaVida();
    /* PRE:
       POST: Carga e inicializa los datos privados de la instancia de JuegoDeLaVida*/    
    void inicializarJuegoDeLaVida();
    /* PRE:
       POST: Imprime por terminal las capas del tablero de la instancia de JuegoDeLaVida*/
    void mostrarJuegoDeLaVida();
    /* PRE: Las celulas que se pasan estan dentro de los parametros del tablero
       POST: Carga las celulas vivas al tablero de JuegoDeLaVida*/    
    void cargarCelulasVivas();
    /* PRE:
       POST: Pide al usuario una accion a realizar con el juego y muestra el tablero en cada accion */    
    void interaccionesUsuario();
    /* PRE:
       POST: Carga segun la configuracion elegida los parametros correspondientes a traves de un archivo*/    
    void cargarConfiguracion();
    /* PRE:
       POST: Carga los comportamientos de las celdas, especificados en la configuracion*/    
    void cargarComportamientos();
    /* PRE:
       POST: Cambia el estado de la celula correspondiente a las coordenadas pasadas por parametro
             a el estado pasado por parametro*/    
    void cambiarEstado(int capa, int fila, int columna, EstadoDeCelula estado);
    /* PRE:
       POST: Cambia el comportamiento de la celda correspondiente a las coordenadas pasadas por parametro
             a el comportameinto pasado por parametro*/    
    void cambiarComportamiento(int capa, int fila, int columna, ComportamientoDeCelda comportamiento);
    /* PRE:
       POST: Devuelve el comportamiento de la celda correspondiente a las coordenadas pasadas por parametro*/    
    ComportamientoDeCelda obtenerComportamiento(int capa, int fila, int columna);
    /* PRE:
       POST: Pasa un turno del juego, aumentando el numero de turnos y llama a funciones auxiliares de 
            logica del juego*/    
    void pasarTurno();
    /* PRE:
       POST: Copia el tablero principal del juego a TableroAux*/    
    void copiarTableroAuxiliar();
    /* PRE:
       POST: Recorre el tablero y llama a actualizarEstadoCelula para cada celula*/    
    void actualizarCelulasVivas();
    /* PRE:
       POST: Actualiza la cantidad de muertes y nacimientos totales en el turno*/    
    void actualizarControlMuertes();
    /* PRE:
       POST: Determina  y actualiza el estado de una celula dependiendo de sus vecinas,
        de ser necesario calcula los genes*/    
    void actualizarEstadoCelula(int capa, int fila, int columna);
    /* PRE:
       POST: Carga los genes pasados por parametro a la celula correspondiente a las coordenadas
       pasadas por parametro*/    
    void setGenesCelula(int capa, int fila, int columna, int gen1, int gen2, int gen3);
    /* PRE:
       POST: Determina si el juego esta congelado imprimiendolo por pantalla*/    
    void controlMuertes();
    /* PRE:
       POST: Carga una configuracion default para hacer pruebas del tablero*/    
    void setConfiguracion();
   /* PRE:
      POST: Imprime las estadisticas del JuegoDeLaVida*/
   void imprimirEstadisticas();
};
#endif /* JUEGODELAVIDA_H_ */
