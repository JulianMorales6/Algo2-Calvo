#include "JuegoDeLaVida.h"

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

