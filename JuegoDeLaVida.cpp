#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "JuegoDeLaVida.h"
#include "Configuraciones.h"
#include "Configuraciones.cpp"
#define ARCHIVO_CONFIGURACION "data.csv"

JuegoDeLaVida::JuegoDeLaVida() {
    this->tablero = NULL;
    this->tableroAux = NULL;
}

JuegoDeLaVida::~JuegoDeLaVida() {
    delete this->tablero;
    delete this->tableroAux;
}

void JuegoDeLaVida::inicializarJuegoDeLaVida() {
    this->cargarConfiguracion();
    this->tablero = new Tablero(this->configuracion.capas, this->configuracion.filas, this->configuracion.columnas);
    this->tableroAux = new Tablero(this->configuracion.capas, this->configuracion.filas, this->configuracion.columnas);
    this->cargarComportamientos();
    this->cargarCelulasVivas();
}


void JuegoDeLaVida::cargarCelulasVivas() {
    int capa, fila, columna;
    cout<<"Si desea ingresar una Celula viva introduzca el primer valor - Enter, segundo valor - Enter y tercer valor - Enter. De lo contrario presione cualquier letra"<<endl;
    while(cin >> columna >> fila >> capa) {
        if(capa <= 0 || fila <= 0 || columna <= 0 || capa > this->configuracion.capas || columna > this->configuracion.columnas || fila > this->configuracion.filas) {
            cout<<"Celula inválida, por favor ingrese otra:"<<endl;
            continue;
        }
        cambiarEstado(capa-1, fila-1, columna-1, Viva);
        ++this->estadisticas.celulasVivas;
        ++this->estadisticas.nacimientosDelTurno;
        ++this->estadisticas.nacimientosTotales;
        cout<<"Si no quiere agregar otra presione cualquier letra y Enter"<<endl;
    }
    this->estadisticas.turnos++;
}

void JuegoDeLaVida::cargarComportamientos() {
    for(int i=0; i<this->configuracion.cantidadCeldasContaminadas; i++){
        this->cambiarComportamiento(rand()%(this->configuracion.capas+ 1),rand()%(this->configuracion.filas+ 1),rand()%(this->configuracion.columnas+ 1), Contaminada);
    }
    for(int i=0; i<this->configuracion.cantidadCeldasEnvenenadas; i++){
        this->cambiarComportamiento(rand()%(this->configuracion.capas+ 1),rand()%(this->configuracion.filas+ 1),rand()%(this->configuracion.columnas+ 1), Envenenada);
    }    
    for(int i=0; i<this->configuracion.cantidadCeldasProcreadoras; i++){
        this->cambiarComportamiento(rand()%(this->configuracion.capas+ 1),rand()%(this->configuracion.filas+ 1),rand()%(this->configuracion.columnas+ 1), Procreadora);
    }    
    for(int i=0; i<this->configuracion.cantidadCeldasPortales; i++){
        this->cambiarComportamiento(rand()%(this->configuracion.capas+ 1),rand()%(this->configuracion.filas+ 1),rand()%(this->configuracion.columnas+ 1), Portal);
    }    
    for(int i=0; i<this->configuracion.cantidadCeldasRadioactivas; i++){
        this->cambiarComportamiento(rand()%(this->configuracion.capas+ 1),rand()%(this->configuracion.filas+ 1),rand()%(this->configuracion.columnas+ 1), Radioactiva);
    }    
}

void JuegoDeLaVida::cambiarComportamiento(int capa, int fila, int columna, ComportamientoDeCelda comportamiento) {
    this->tablero->getCelda(capa, fila, columna)->setComportamiento(comportamiento);
}

ComportamientoDeCelda JuegoDeLaVida::obtenerComportamiento(int capa, int fila, int columna) {
    return((this->tablero)->getCelda(capa, fila, columna)->getComportamiento());
}

void JuegoDeLaVida::cargarConfiguracion() {
    Configuraciones * listaDeConfigs = new Configuraciones;
    listaDeConfigs->mostrarConfiguraciones();
    Configuracion confElegida = listaDeConfigs->seleccionarUnaConfiguracion();
    
    this->configuracion.dificultad = confElegida.dificultad;
    this->configuracion.capas = confElegida.capas;
    this->configuracion.filas = confElegida.filas;
    this->configuracion.columnas = confElegida.columnas;
    this->configuracion.x1 = confElegida.x1;
    this->configuracion.x2 = confElegida.x2;
    this->configuracion.x3 = confElegida.x3;
    this->configuracion.cantidadCeldasContaminadas = confElegida.cantidadCeldasContaminadas;
    this->configuracion.cantidadCeldasEnvenenadas = confElegida.cantidadCeldasEnvenenadas;
    this->configuracion.cantidadCeldasProcreadoras = confElegida.cantidadCeldasProcreadoras;
    this->configuracion.cantidadCeldasPortales = confElegida.cantidadCeldasPortales;
    this->configuracion.cantidadCeldasRadioactivas = confElegida.cantidadCeldasRadioactivas;
    delete listaDeConfigs;
}

void JuegoDeLaVida::interaccionesUsuario() {
    int numeroIngresado;
    cin.clear();
    cin.ignore(100, '\n');
    cout<<"Presione 1 para avanzar un turno, 2 para reiniciar el juego, 3 o cualquier otro digito para cerrarlo"<<endl;
    while(cin>>numeroIngresado) {
        this->tablero->mostrarTablero();
        this->imprimirEstadisticas();
        if(numeroIngresado == 1) {
            this->pasarTurno();
            
        }
        if(numeroIngresado == 2) {
            this->inicializarJuegoDeLaVida();
        }
        if(numeroIngresado == 3) {
            break;
        }
        cout<<"Presione 1 para avanzar un turno, 2 para reiniciar el juego, 3 o cualquier otro digito para cerrarlo"<<endl;
        cin.clear();
        cin.ignore(100, '\n');
    }
}

void JuegoDeLaVida::pasarTurno() {
    this->copiarTableroAuxiliar();
    this->actualizarCelulasVivas();
    this->controlMuertes();
    this->actualizarControlMuertes();
    ++this->estadisticas.turnos;
    this->estadisticas.muertesDelTurno = 0;
    this->estadisticas.nacimientosDelTurno = 0;
}

void JuegoDeLaVida::copiarTableroAuxiliar() {
    for(int capa = 0; capa < this->configuracion.capas; capa++) {
        for(int fila = 0; fila < this->configuracion.filas; fila++) {
            for(int columna = 0; columna < this->configuracion.columnas; columna++) {
                this->tableroAux->getCelda(capa,fila,columna)->getCelula()->setEstadoDeCelula(this->tablero->getCelda(capa,fila,columna)->getCelula()->getEstado());
            }
        }
    }
} 

void JuegoDeLaVida::actualizarCelulasVivas() {
    for(int capa = 0; capa < this->configuracion.capas; capa++) {
        for(int fila = 0; fila < this->configuracion.filas; fila++) {
            for(int columna = 0; columna < this->configuracion.columnas; columna++) {
                actualizarEstadoCelula(capa,fila,columna);
            }
        }
    }
}

void JuegoDeLaVida::actualizarEstadoCelula(int capa, int fila, int columna) {
    int celulasVivasAlrededor = 0;
    int gen1 = 0;
    int gen2 = 0;
    int gen3 = 0;//primera promedio, segundo maximo, tercera while hasta < 255
    int maxi = capa+1;
    int mini = capa-1;
    int maxj = fila+1;
    int minj = fila-1;
    int maxk = columna+1;
    int mink = columna-1;
    Celda * celda = this->tableroAux->getCelda(capa,fila,columna);
    for(int a = mini; a<= maxi; a++) {
        for(int b = minj; b<= maxj; b++) {
            for(int c = mink; c<= maxk; c++) {
                Celda * celdaAux = this->tableroAux->getCelda(a,b,c);
                if(celdaAux->getCelula()->getEstado() == Viva) {
                    celulasVivasAlrededor++;
                    gen1 += celdaAux->getCelula()->getGen(1);
                    gen3 += celdaAux->getCelula()->getGen(3);
                    if(celdaAux->getCelula()->getGen(2) > gen2) {
                        gen2 = celdaAux->getCelula()->getGen(2);
                    }
                    if(celda->getCelula()->getEstado() == Viva) {
                        celulasVivasAlrededor--;
                    }
                }
            }
        }
    }
    if(celda->getCelula()->getEstado() == Muerta) {
        if(celulasVivasAlrededor == this->configuracion.x1) {
            this->cambiarEstado(capa, fila, columna, Viva);
            while(gen3>255) {
                gen3 = gen3 - 255;
            }
            this->setGenesCelula(capa, fila, columna,gen1/celulasVivasAlrededor,gen2,gen3);
            this->estadisticas.celulasVivas++;
            this->estadisticas.nacimientosDelTurno++;
            this->estadisticas.nacimientosTotales++;
        }  
    } else {
        if(celulasVivasAlrededor < this->configuracion.x2 || celulasVivasAlrededor > this->configuracion.x3) {
            this->cambiarEstado(capa, fila, columna, Muerta);
            this->setGenesCelula(capa, fila, columna, 0,0,0);
            this->estadisticas.celulasVivas--;
            this->estadisticas.muertesDelTurno++;
            this->estadisticas.muertesTotales++;        
        }
    }
}

void JuegoDeLaVida::setGenesCelula(int capa, int fila, int columna, int gen1, int gen2, int gen3) {
    Celula * celula = this->tablero->getCelda(capa, fila, columna)->getCelula();
    celula->cambiarGen(1,gen1);
    celula->cambiarGen(2,gen2);
    celula->cambiarGen(3,gen3);
}
    

void JuegoDeLaVida::actualizarControlMuertes() {
    this->estadisticas.controlMuertes == this->estadisticas.muertesTotales;// no hay un = demas?
    this->estadisticas.controlNacimientos == this->estadisticas.nacimientosTotales;
}

void JuegoDeLaVida::controlMuertes() {
    if(this->estadisticas.muertesDelTurno == 0 &&
       this->estadisticas.nacimientosDelTurno == 0) {
            cout<<"El juego esta congelado, presione 2 para reiniciar o 3 para cerrar"<<endl;
       }
}

void JuegoDeLaVida::cambiarEstado(int capa, int fila, int columna, EstadoDeCelula estado) {
    Celda * celda = this->tablero->getCelda(capa,fila,columna);
    ComportamientoDeCelda comportamiento = celda->getComportamiento();
    if(estado == Viva) {
        if(comportamiento == Portal) {
            this->tablero->getCelda(generarNumeroRandom(this->configuracion.capas),generarNumeroRandom(this->configuracion.filas),generarNumeroRandom(this->configuracion.columnas))->getCelula()->setEstadoDeCelula(estado);
        } if( comportamiento == Radioactiva) {
            celda->getCelula()->cambiarGen(1,1);//tiene 50% de afectar a cada gen y si lo afecta lo hace la mitad
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
    this->tablero->getCelda(capa,fila,columna)->getCelula()->setEstadoDeCelula(estado);
}

//carga una configuracion default. lo cree para hacer pruebas de la logica del juego
void JuegoDeLaVida::setConfiguracion() {
    this->configuracion.capas = 4;
    this->configuracion.filas = 6;
    this->configuracion.columnas = 10;
    
    this->configuracion.cantidadCeldasContaminadas = 2;
    this->configuracion.cantidadCeldasEnvenenadas = 2;
    this->configuracion.cantidadCeldasProcreadoras = 2;
    this->configuracion.cantidadCeldasPortales = 2;
    this->configuracion.cantidadCeldasRadioactivas = 2;
    this->configuracion.dificultad = "Default";
    this->configuracion.x1 = 3;
    this->configuracion.x2 = 2;
    this->configuracion.x3 = 4; 
}

void JuegoDeLaVida::imprimirEstadisticas() {
    cout<<"ESTADISTICAS"<<endl;
    cout<<"CV: "<<this->estadisticas.celulasVivas<<" CQN: "<<this->estadisticas.nacimientosDelTurno<<" CQM: "<<this->estadisticas.muertesDelTurno<<endl;
    float promedioDeNacimientos = (float)this->estadisticas.nacimientosTotales / (float)this->estadisticas.turnos;
    float promedioDeMuertes = (float)this->estadisticas.muertesTotales /  (float)this->estadisticas.turnos;
    cout<<"PN: "<<promedioDeNacimientos<<" PM: "<<promedioDeMuertes<<endl;
    cout<<"Muertes del turno: "<< this->estadisticas.muertesDelTurno<<endl;
    cout<<"Nacimiento del turno "<< this->estadisticas.nacimientosDelTurno<<endl;
}