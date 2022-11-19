#ifndef JUEGODELAVIDA_H_
#define JUEGODELAVIDA_H_

#include "Tablero.cpp"
#include "Configuraciones.cpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "bmp/EasyBMP.cpp"
#include "bmp/EasyBMP_Geometry.cpp"
#include "bmp/EasyBMP_Font.cpp"


static const int MARGEN_INFERIOR = 20;
static const int TAMANIO_CELDA = 20;
static const int RADIO_CELULA = 8;
static const int CERO_ASCII = 48;


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
       POST: Corrobora si una celula que nace esta en una celda contaminada y lleva a cabo el comportamiento de la misma*/    
    void ejecutarComportamiento(int capa, int fila, int columna);
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
       POST: Determina si el juego esta congelado imprimiendolo por pantalla*/    
    void controlMuertes();
    /* PRE:
       POST: Carga una configuracion default para hacer pruebas del tablero*/    
    void setConfiguracion();
   /* PRE:
      POST: Imprime las estadisticas del JuegoDeLaVida*/
   void imprimirEstadisticas();
   /* PRE:
      POST: Crea imagenes y dibuja en formato bmp el JuegoDeLaVida*/
   void dibujarJuegoDeLaVida();
};
#endif /* JUEGODELAVIDA_H_ */
