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
    while(cin >> fila >> columna >> capa) {
        if(capa <= 0 || fila <= 0 || columna <= 0) {
            cout<<"Celula inválida, por favor ingrese otra:"<<endl;
            continue;
        }
        cambiarEstado(capa-1, fila-1, columna-1, Viva);
        ++this->estadisticas.celulasVivas;
        ++this->estadisticas.nacimientosDelTurno;
        ++this->estadisticas.nacimientosTotales;
        cout<<"Si no quiere agregar otra presione cualquier letra y Enter"<<endl;
    }
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
    this->tablero->cambiarComportamientoTablero(capa, fila, columna, comportamiento);
}

ComportamientoDeCelda JuegoDeLaVida::obtenerComportamiento(int capa, int fila, int columna) {
    return((this->tablero)->getComportamientoTablero(capa, fila, columna));
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
        //this->dibujarJuegoDeLaVida();
        this->tablero->mostrarTablero();
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
            this->estadisticas.muertesDelTurno--;
            this->estadisticas.muertesTotales--;        
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
    if(this->estadisticas.controlMuertes == this->estadisticas.muertesTotales &&
       this->estadisticas.controlNacimientos == this->estadisticas.nacimientosTotales) {
            cout<<"El juego esta congelado, presione 2 para reiniciar o 3 para cerrar"<<endl;
       }
}

void JuegoDeLaVida::cambiarEstado(int capa, int fila, int columna, EstadoDeCelula estado) {
    Celda * celda = this->tablero->getCelda(capa,fila,columna);
    ComportamientoDeCelda comportamiento = celda->getComportamiento();
    if(estado == Viva) {
        if(comportamiento == Portal) {
            this->tablero->cambiarEstadoTablero(generarNumeroRandom(this->configuracion.capas),generarNumeroRandom(this->configuracion.filas),generarNumeroRandom(this->configuracion.columnas), estado);
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
    this->tablero->cambiarEstadoTablero(capa, fila, columna, estado);
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


void JuegoDeLaVida::dibujarJuegoDeLaVida() {
    int capas = this->tablero->getTablero()->getLargo();
    int filas = this->tablero->getTablero()->getCursor()->getLargo();
    int columnas = this->tablero->getTablero()->getCursor()->getCursor()->getLargo();
    int margenInferior = 20;
    int tamanioCelda = 20;
    int radioCelula = 8;

    //colores para el tablero
    RGBApixel grisClaro;
    grisClaro.Red = 30;
    grisClaro.Green = 30;
    grisClaro.Blue = 30;

    RGBApixel grisOscuro;
    grisOscuro.Red = 20;
    grisOscuro.Green = 20;
    grisOscuro.Blue = 20;

    RGBApixel blanco;
    blanco.Red = 255;
    blanco.Green = 255;
    blanco.Blue = 255;

    for(int capa = 1; capa <= capas; capa++) {
        
        BMP imagen; //crear nueva imagen para cada capa

        imagen.SetSize(columnas*tamanioCelda, (filas*tamanioCelda)+margenInferior);//defino tamanio

        for(int i=0; i<imagen.TellWidth(); i++) {//fondo
            for(int j=0; j<imagen.TellHeight(); j++) {
                *imagen(i,j) = grisOscuro;
            }
        }
        
        for(int y=0; y<=imagen.TellHeight()-margenInferior; y=y+tamanioCelda) {//lineas
            DrawLine(imagen, 0, y, imagen.TellWidth(), y, grisClaro);
        }
        for(int x=0; x<=imagen.TellWidth(); x=x+tamanioCelda) {
            DrawLine(imagen, x, 0, x, imagen.TellHeight()-margenInferior, grisClaro);
        }

        char texto2[1024];//dibujo el numero de capa
        int ceroAscii = 48;
        char numeroCapa[22] = "Capa";
        numeroCapa[4] = ' ';
        int indice = 5;
        for(int i=1, resto=10000, entero=1000;  i<=4; i++, resto=resto/10, entero = entero/10){
            //if para que no muestre 0001
            numeroCapa[indice] = ceroAscii+(char)(capa%resto)/entero;
            indice++;
            
        }
        
        strcpy(texto2, numeroCapa);
        PrintString(imagen, texto2, imagen.TellWidth()-80, imagen.TellHeight()-15, 10, blanco);

        for(int fila = 1; fila <= filas; fila++) {//dibujo las celdas y las celulas
            for(int columna = 1; columna <= columnas; columna++) {
                Celda *celda = this->tablero->getCelda(capa, fila, columna); 
                if(celda->getComportamiento() != Normal) {
                    char texto[1024];
                    char comportamiento[20] = "c";
                    strcpy(texto, comportamiento);
                    PrintString(imagen, texto, (columna*tamanioCelda)-12, (fila*tamanioCelda)-18, 10, blanco);
                }
                Celula *celula = this->tablero->getCelda(capa, fila, columna)->getCelula();
                RGBApixel colorCelula;
                colorCelula.Red = celula->getGen(0);
                colorCelula.Green = celula->getGen(1);
                colorCelula.Blue = celula->getGen(2);
                if(celula->getEstado() == Viva) {
                    DrawArc(imagen, (columna*tamanioCelda)-10, (fila*tamanioCelda)-10, radioCelula, 0, 7, colorCelula);
                }
                else {//modificar el 0, 7 si se quiere diferenciar una viva de una muerta con el mismo color.
                    DrawArc(imagen, (columna*tamanioCelda)-10, (fila*tamanioCelda)-10, radioCelula, 0, 7, colorCelula);
                }
            }
        }
        char ruta[22] = "imagenes/capa0000.bmp";
        ruta[13] = ceroAscii+(char)(capa%10000)/1000;
        ruta[14] = ceroAscii+(char)(capa%1000)/100;
        ruta[15] = ceroAscii+(char)(capa%100)/10;
        ruta[16] = ceroAscii+(char)capa%10;
        imagen.WriteToFile(ruta);
    }
}