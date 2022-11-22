
#include "JuegoDeLaVida.h"

#define ARCHIVO_CONFIGURACION "data.csv"

JuegoDeLaVida::JuegoDeLaVida() {
    this->tablero = NULL;
    this->tableroAux = NULL;
    this->estadisticas.nacimientosTotales = 0;
    this->estadisticas.muertesTotales = 0;
    this->estadisticas.celulasVivas = 0;
    this->estadisticas.nacimientosDelTurno = 0;
    this->estadisticas.muertesDelTurno = 0;
    this->estadisticas.turnos = 0;
    this->estadisticas.controlMuertes = 0;
    this->estadisticas.controlNacimientos = 0;
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
    cout<<"Si desea ingresar una Celula viva introduzca";
    cout<<" un valor para x - Enter, un valor para y - Enter y un valor para z - Enter. De lo contrario presione cualquier letra"<<endl;
    while(cin >> columna >> fila >> capa) {
        if(capa <= 0 || fila <= 0 || columna <= 0 || capa > this->configuracion.capas || columna > this->configuracion.columnas || fila > this->configuracion.filas) {
            cout<<"Celula inválida, por favor ingrese otra:"<<endl;
            continue;
        }
        this->tablero->getCelda(capa-1, fila-1, columna-1)->getCelula()->revivirCelula();
        ejecutarComportamiento(capa-1, fila-1, columna-1);
        ++this->estadisticas.celulasVivas;
        cout<<"Si no quiere agregar otra presione cualquier letra y Enter"<<endl;
    }
    this->estadisticas.turnos++;
}

void JuegoDeLaVida::cargarComportamientos() {
    for(int i=0; i<this->configuracion.cantidadCeldasContaminadas; i++){
        this->cambiarComportamiento(generarNumeroRandom(this->configuracion.capas),
                                    generarNumeroRandom(this->configuracion.filas),
                                    generarNumeroRandom(this->configuracion.columnas), Contaminada);
    }
    for(int i=0; i<this->configuracion.cantidadCeldasEnvenenadas; i++){
        this->cambiarComportamiento(generarNumeroRandom(this->configuracion.capas),
                                    generarNumeroRandom(this->configuracion.filas),
                                    generarNumeroRandom(this->configuracion.columnas), Envenenada);
    }    
    for(int i=0; i<this->configuracion.cantidadCeldasProcreadoras; i++){
        this->cambiarComportamiento(generarNumeroRandom(this->configuracion.capas),
                                    generarNumeroRandom(this->configuracion.filas),
                                    generarNumeroRandom(this->configuracion.columnas), Procreadora);
    }    
    for(int i=0; i<this->configuracion.cantidadCeldasPortales; i++){
        this->cambiarComportamiento(generarNumeroRandom(this->configuracion.capas),
                                    generarNumeroRandom(this->configuracion.filas),
                                    generarNumeroRandom(this->configuracion.columnas), Portal);
    }    
    for(int i=0; i<this->configuracion.cantidadCeldasRadioactivas; i++){
        this->cambiarComportamiento(generarNumeroRandom(this->configuracion.capas),
                                    generarNumeroRandom(this->configuracion.filas),
                                    generarNumeroRandom(this->configuracion.columnas), Radioactiva);
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
    this->tablero->mostrarTablero();
    this->imprimirEstadisticas();
    this->dibujarJuegoDeLaVida();
    cout<<"Presione 1 para avanzar un turno, 2 para reiniciar el juego, 3 o cualquier otro digito para cerrarlo"<<endl;
    while(cin>>numeroIngresado) {
        if(numeroIngresado == 1) {
            this->pasarTurno();
            this->tablero->mostrarTablero();
            this->imprimirEstadisticas();
            this->dibujarJuegoDeLaVida();
            ++this->estadisticas.turnos;
            this->estadisticas.muertesDelTurno = 0;
            this->estadisticas.nacimientosDelTurno = 0;
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
}

void JuegoDeLaVida::copiarTableroAuxiliar() {
    for(int capa = 0; capa < this->configuracion.capas; capa++) {
        for(int fila = 0; fila < this->configuracion.filas; fila++) {
            for(int columna = 0; columna < this->configuracion.columnas; columna++) {
                this->tableroAux->getCelda(capa,fila,columna)->getCelula()->setEstado(this->tablero->getCelda(capa,fila,columna)->getCelula()->getEstado());
                for(int i=0; i<3; i++) {
                    this->tableroAux->getCelda(capa,fila,columna)->getCelula()->setGen(i, this->tablero->getCelda(capa,fila,columna)->getCelula()->getGen(i));
                }
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
    Celda * celda = this->tablero->getCelda(capa,fila,columna);
    Celda * celdaAux = this->tableroAux->getCelda(capa,fila,columna);
    int celulasVivasAlrededor = 0;
    int genesHeredados[3];//primera promedio, segundo maximo, tercera while hasta < 255
    genesHeredados[0] = 0;
    genesHeredados[1] = 0;
    genesHeredados[2] = 0;
    int capaMax = capa+1;
    int capaMin = capa-1;
    int filaMax = fila+1;
    int filaMin = fila-1;
    int columnaMax = columna+1;
    int columnaMin = columna-1;

    for(int k = capaMin; k<= capaMax; k++) {
        for(int i = filaMin; i<= filaMax; i++) {
            for(int j = columnaMin; j<= columnaMax; j++) {
                Celda * celdaVecina = this->tableroAux->getCelda(k, i, j);
                if(celdaVecina->getCelula()->getEstado() == Viva) {
                    celulasVivasAlrededor++;
                    genesHeredados[0] += celdaVecina->getCelula()->getGen(0);
                    genesHeredados[2] += celdaVecina->getCelula()->getGen(2);
                    if(celdaVecina->getCelula()->getGen(2) > genesHeredados[1]) {
                        genesHeredados[1] = celdaVecina->getCelula()->getGen(1);
                    }
                    if(celdaAux->getCelula()->getEstado() == Viva) {
                        celulasVivasAlrededor--;
                    }
                }
            }
        }
    }
    if(celda->getCelula()->getEstado() == Muerta) {
        if(celulasVivasAlrededor == this->configuracion.x1) {
            genesHeredados[0] = genesHeredados[0]/celulasVivasAlrededor;
            while(genesHeredados[2]>255) {
                genesHeredados[2] = genesHeredados[2] - 255;
            }
            celda->getCelula()->revivirCelula(genesHeredados);
            ejecutarComportamiento(capa, fila, columna);
            this->estadisticas.celulasVivas++;
            this->estadisticas.nacimientosDelTurno++;
            this->estadisticas.nacimientosTotales++;
        }  
    } else {
        if(celulasVivasAlrededor < this->configuracion.x2 || celulasVivasAlrededor > this->configuracion.x3) {
            celda->getCelula()->matarCelula();
            this->estadisticas.celulasVivas--;
            this->estadisticas.muertesDelTurno++;
            this->estadisticas.muertesTotales++;        
        }
    }
}

void JuegoDeLaVida::actualizarControlMuertes() {
    this->estadisticas.controlMuertes = this->estadisticas.muertesTotales;
    this->estadisticas.controlNacimientos = this->estadisticas.nacimientosTotales;
}

void JuegoDeLaVida::controlMuertes() {
    if(this->estadisticas.muertesDelTurno == 0 && this->estadisticas.nacimientosDelTurno == 0) {
            cout<<"El juego esta congelado, presione 2 para reiniciar o 3 para cerrar"<<endl;
       }
}

void JuegoDeLaVida::ejecutarComportamiento(int capa, int fila, int columna) {
    Celula * celula = this->tablero->getCelda(capa,fila,columna)->getCelula();
    ComportamientoDeCelda comportamiento = this->tablero->getCelda(capa,fila,columna)->getComportamiento();
    if(celula->getEstado() == Viva) {
        if(comportamiento == Portal) {
            this->tablero->getCelda(generarNumeroRandom(this->configuracion.capas),
                                    generarNumeroRandom(this->configuracion.filas),
                                    generarNumeroRandom(this->configuracion.columnas))->getCelula()->revivirCelula();
        }
        if( comportamiento == Radioactiva) {
            for(int i = 0; i<3; i++) {
                if(generarNumeroRandom(10) > 5) {
                    celula->setGen(i, celula->getGen(i)/2);//tiene 50% de afectar a cada gen y si lo afecta lo hace la mitad
                }
            }
        }
        if(comportamiento == Contaminada) {
            celula->matarCelula();
        }
        if(comportamiento == Envenenada) {
            celula->setGen(generarNumeroRandom(3), 0);
        }
        if(comportamiento == Procreadora) {
            /*
            if(this->configuracion.x1 > 2) {
                --this->configuracion.x1;
            }
            if(this->configuracion.x2 > 3) {
                --this->configuracion.x2;
            }
            if(this->configuracion.x3 > 4) {
                --this->configuracion.x3; 
            }
            */
        } 
    }
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
    cout<<"%N: "<<promedioDeNacimientos<<" %M: "<<promedioDeMuertes<<endl;
    cout<<"Muertes Totales: "<< this->estadisticas.muertesTotales<<endl;
    cout<<"Nacimiento Totales "<< this->estadisticas.nacimientosTotales<<endl;
}

void JuegoDeLaVida::dibujarJuegoDeLaVida() {
    int capas = this->tablero->getTablero()->getLargo();
    int filas = this->tablero->getTablero()->getCursor()->getLargo();
    int columnas = this->tablero->getTablero()->getCursor()->getCursor()->getLargo();


    //colores para el tablero
    RGBApixel grisClaro;
    grisClaro.Red = 40;
    grisClaro.Green = 40;
    grisClaro.Blue = 40;

    RGBApixel grisOscuro;
    grisOscuro.Red = 20;
    grisOscuro.Green = 20;
    grisOscuro.Blue = 20;

    RGBApixel blanco;
    blanco.Red = 255;
    blanco.Green = 255;
    blanco.Blue = 255;

    BMP imagenPortada;
    imagenPortada.SetSize(650, 150);
    for(int i=0; i<imagenPortada.TellWidth(); i++) {//color del fondo
        for(int j=0; j<imagenPortada.TellHeight(); j++) {
            *imagenPortada(i,j) = grisClaro;
        }
    }
    char encabezado[1024] = "ESTADISTICAS     ", cadena0[1024] = "  Turnos: ", nTurnos[22];
    sprintf(nTurnos, "%i", this->estadisticas.turnos);
    strcat(encabezado, cadena0);
    strcat(encabezado, nTurnos);
    PrintString(imagenPortada, encabezado, 30, 30, 14, blanco);

    char cadena1[1024] = "Celulas Vivas: ", vivas[22], cadena2[1024] = "  Nacimientos del turno: ", nacimientos[22], cadena3[1024] =  "  Muertes del turno: ", muertes[22];
    sprintf(vivas, "%i", this->estadisticas.celulasVivas);
    sprintf(nacimientos, "%i", this->estadisticas.nacimientosDelTurno);
    sprintf(muertes, "%i", this->estadisticas.muertesDelTurno);
    strcat(cadena1, vivas);
    strcat(cadena1, cadena2);
    strcat(cadena1, nacimientos);
    strcat(cadena1, cadena3);
    strcat(cadena1, muertes);
    PrintString(imagenPortada, cadena1, 30, 60, 12, blanco);

    char cadena4[1024] = "Nacimientos totales: ", nacimientosTotales[22], cadena5[1024] = "  Muertes totales: ", MuertesTotales[22];
    sprintf(nacimientosTotales, "%i", this->estadisticas.nacimientosTotales);
    sprintf(MuertesTotales, "%i", this->estadisticas.muertesTotales);
    strcat(cadena4, nacimientosTotales);
    strcat(cadena4, cadena5);
    strcat(cadena4, MuertesTotales);
    PrintString(imagenPortada, cadena4, 30, 80, 12, blanco);

    char cadena6[1024] = "Porcentaje de nacimientos: ", porcNaciemientos[22], cadena7[1024] = "  Porcentaje de muertes ", porcMuertes[22];
    sprintf(porcNaciemientos, "%f", (float)this->estadisticas.nacimientosTotales / (float)this->estadisticas.turnos);
    sprintf(porcMuertes, "%f", (float)this->estadisticas.muertesTotales /  (float)this->estadisticas.turnos);
    strcat(cadena6, porcNaciemientos);
    strcat(cadena6, cadena7);
    strcat(cadena6, porcMuertes);
    PrintString(imagenPortada, cadena6, 30, 100, 12, blanco);

    imagenPortada.WriteToFile("imagenes/estadisticas.bmp");

    for(int capa = 1; capa <= capas; capa++) {
        BMP imagenCapa; //crear nueva imagen para cada capa

        imagenCapa.SetSize(columnas*TAMANIO_CELDA, (filas*TAMANIO_CELDA)+MARGEN_INFERIOR);

        for(int i=0; i<imagenCapa.TellWidth(); i++) {//color del fondo
            for(int j=0; j<imagenCapa.TellHeight(); j++) {
                *imagenCapa(i,j) = grisOscuro;
            }
        }

        for(int y=0; y<=imagenCapa.TellHeight()-MARGEN_INFERIOR; y=y+TAMANIO_CELDA) {
            DrawLine(imagenCapa, 0, y, imagenCapa.TellWidth(), y, grisClaro);
        }
        for(int x=0; x<=imagenCapa.TellWidth(); x=x+TAMANIO_CELDA) {
            DrawLine(imagenCapa, x, 0, x, imagenCapa.TellHeight()-MARGEN_INFERIOR, grisClaro);
        }

        char cadena[1024] = "Capa ";
        char numeroCapa[22];
        sprintf(numeroCapa, "%d", capa);
        strcat(cadena, numeroCapa);
        PrintString(imagenCapa, cadena, imagenCapa.TellWidth()-80, imagenCapa.TellHeight()-15, 10, blanco);

        for(int fila = 1; fila <= filas; fila++) {//dibujo las celdas y las celulas
            for(int columna = 1; columna <= columnas; columna++) {
                Celda *celda = this->tablero->getCelda(capa-1, fila-1, columna-1);
                if(celda->getComportamiento() != Normal) {
                    char comportamiento[4] = " ";
                    switch(celda->getComportamiento()) {
                        case Envenenada: comportamiento[0] = 'E'; break;
                        case Portal: comportamiento[0] = 'P'; break;
                        case Contaminada: comportamiento[0] = 'C'; break;
                        case Radioactiva: comportamiento[0] = 'R'; break;
                        case Procreadora: comportamiento[0] = 'A'; break;
                    }
                    PrintString(imagenCapa, comportamiento, (columna*TAMANIO_CELDA)-12, (fila*TAMANIO_CELDA)-12, 6, grisClaro);
                }
                Celula *celula = this->tablero->getCelda(capa-1, fila-1, columna-1)->getCelula();
                RGBApixel colorCelula;
                colorCelula.Red = celula->getGen(0);
                colorCelula.Green = celula->getGen(1);
                colorCelula.Blue = celula->getGen(2);
                if(celula->getEstado() == Viva) {
                    DrawArc(imagenCapa, (columna*TAMANIO_CELDA)-10, (fila*TAMANIO_CELDA)-10, RADIO_CELULA, 0, 7, colorCelula);
                }
            }
        }
        char ruta[1024] = "imagenes/capa", formato[5] = ".bmp", numeroImagen[22];
        sprintf(numeroImagen, "%i", capa);
        strcat(ruta, numeroImagen);
        strcat(ruta, formato);
        imagenCapa.WriteToFile(ruta);

    }
}
