#include "Tablero.cpp"

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
    void cambiarEstado(int i, int j, int k, EstadoDeCelula estado);
    void cambiarComportamiento(int i, int j, int k, ComportamientoDeCelda comportamiento);
    ComportamientoDeCelda obtenerComportamiento(int i, int j, int k);
    void pasarTurno();
    void copiarTableroAuxiliar();
    void actualizarCelulasVivas();
    void actualizarControlMuertes();
    void actualizarEstadoCelula(int i, int j, int k);
    void setGenesCelula(int i, int j, int k, int gen1, int gen2, int gen3);
    void controlMuertes();
    void setConfiguracion();
};