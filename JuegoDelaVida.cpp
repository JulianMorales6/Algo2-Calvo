#include "JuegoDeLaVida.h"
#include <cstdlib>

void JuegoDeLaVida::inicializarJuegoDeLaVida() {
    this->cargarConfiguracion();
    this->tablero = new Tablero(this->configuracion.largo,this->configuracion.ancho,this->configuracion.profundidad);
    this->cargarComportamientos();
    this->cargarCelulasVivas();
}

void JuegoDeLaVida::cargarCelulasVivas() {
    int i,j,k;
    cout<<"Si desea ingresar una Celula viva introduzca el primer valor - Enter, segundo valor - Enter y tercer valor - Enter. De lo contrario presione cualquier letra"<<endl;
    while(cin >> i >> j >> k) {
        if(i <= 0 || j <= 0 || k <= 0) {
            cout<<"Celula inválida, por favor ingrese otra:"<<endl;
            continue;
        }
        cambiarEstado(i,j,k,Viva);
        ++this->estadisticas.celulasVivas;
        ++this->estadisticas.nacimientosDelTurno;
        ++this->estadisticas.nacimientosTotales;
        cout<<"Si no quiere agregar otra presione cualquier letra y Enter"<<endl;
    }
    }

void JuegoDeLaVida::cargarComportamientos() {
    for(int i=0; i<this->configuracion.cantidadCeldasTipo1; i++){
        this->cambiarComportamiento(rand()%(this->configuracion.ancho+ 1),rand()%(this->configuracion.largo+ 1),rand()%(this->configuracion.profundidad+ 1), Contaminada);
    }
    for(int i=0; i<this->configuracion.cantidadCeldasTipo2; i++){
        this->cambiarComportamiento(rand()%(this->configuracion.ancho+ 1),rand()%(this->configuracion.largo+ 1),rand()%(this->configuracion.profundidad+ 1), Envenenada);
    }    
    for(int i=0; i<this->configuracion.cantidadCeldasTipo3; i++){
        this->cambiarComportamiento(rand()%(this->configuracion.ancho+ 1),rand()%(this->configuracion.largo+ 1),rand()%(this->configuracion.profundidad+ 1), Procreadora);
    }    
    for(int i=0; i<this->configuracion.cantidadCeldasTipo4; i++){
        this->cambiarComportamiento(rand()%(this->configuracion.ancho+ 1),rand()%(this->configuracion.largo+ 1),rand()%(this->configuracion.profundidad+ 1), Portal);
    }    
    for(int i=0; i<this->configuracion.cantidadCeldasTipo5; i++){
        this->cambiarComportamiento(rand()%(this->configuracion.ancho+ 1),rand()%(this->configuracion.largo+ 1),rand()%(this->configuracion.profundidad+ 1), Radioactiva);
    }    
}

void JuegoDeLaVida::cambiarComportamiento(int i, int j, int k, ComportamientoDeCelda comportamiento) {
    this->tablero->cambiarComportamientoTablero(i,j,k,comportamiento);
}

ComportamientoDeCelda JuegoDeLaVida::obtenerComportamiento(int i, int j, int k) {
    return((this->tablero)->getComportamientoTablero(i,j,k));
}

int generarNumeroRandom(int i) {
    return(rand()%(i + 1));
}