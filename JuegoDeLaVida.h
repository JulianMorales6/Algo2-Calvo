#include "Tablero.h"

typedef struct{
    string dificultad;
    int largo,ancho,profundidad;//valores para el tamanio del tablero
    int x1,x2,x3; //valores para nacimiento y muerte
    int cantidadCeldasTipo1;   //cantidad de celdas tipo contaminada
    int cantidadCeldasTipo2;   //cantidad de celdas tipo envenenada
    int cantidadCeldasTipo3;   //cantidad de celdas tipo procreadora
    int cantidadCeldasTipo4;   //cantidad de celdas tipo portal
    int cantidadCeldasTipo5;   //cantidad de celdas tipo radioactiva
    
}Configuracion;

typedef struct{
    int nacimientosTotales;
    int muertesTotales;
    int celulasVivas;
    int nacimientosDelTurno;
    int muertesDelTurno;
    int turnos;
    int controlMuertes;
    int controlNacimientos;
}Estadisticas;

class JuegoDeLaVida{
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
    void cambiarEstado(int i, int j, int k, EstadoDeCelula estado) {
        Celda * celda = this->tablero->getCelda(i,j,k);
        ComportamientoDeCelda comportamiento = celda->getComportamiento();
        if(estado == Viva) {
            if(comportamiento == Portal) {
                this->tablero->cambiarEstadoTablero(generarNumeroRandom(this->configuracion.ancho),generarNumeroRandom(this->configuracion.largo),generarNumeroRandom(this->configuracion.profundidad), estado);
            } if( comportamiento == Radioactiva) {
                celda->getCelula()->cambiarGen(1,1);//cambiar los 1,1 por el comportamiento que deseemos
            } if(comportamiento == Contaminada) {
                estado = Muerta;
            } if(comportamiento == Envenenada) {
                celda->getCelula()->cambiarGen(generarNumeroRandom(3),0);
            } if(comportamiento == Procreadora) {
                --this->configuracion.x1;
                --this->configuracion.x2;
                --this->configuracion.x3; 
            } 
            }
        this->tablero->cambiarEstadoTablero(i,j,k,estado);
        }
    void cambiarComportamiento(int i, int j, int k, ComportamientoDeCelda comportamiento);
    ComportamientoDeCelda obtenerComportamiento(int i, int j, int k);
    void interaccionesUsuario();
    void pasarTurno();
    void copiarTableroAuxiliar();
    void actualizarCelulasVivas();
    void actualizarControlMuertes();
    void actualizarEstadoCelula(int i, int j, int k);
    void setGenesCelula(int i, int j, int k, int gen1, int gen2, int gen3);
    void controlMuertes();
};