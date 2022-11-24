
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
    this->estadisticas.flagCongelado = false;
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
    int opcion;
    this->estadisticas.turnos++;
    do {
        cout<<"Si desea realizar una carga manual de celulas vivas ingrese 1, si prefiere aleatorio ingrese 0: "<<endl;
        cin.clear();
        cin.ignore(100, '\n');
        cin>>opcion;
    } while(opcion != 1 && opcion != 0);
    if(opcion == 0) { 
        this->inicializarCelulasConfiguracion();
        return;
    }
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
        this->estadisticas.celulasVivas++;
        cout<<"Si no quiere agregar otra presione cualquier letra y Enter"<<endl;
    }
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
    this->configuracion.cantidadCelulasVivas = confElegida.cantidadCelulasVivas;
    delete listaDeConfigs;
}

void JuegoDeLaVida::interaccionesUsuario() {
    int numeroIngresado;
    cin.clear();
    cin.ignore(100, '\n');
    this->tablero->mostrarTablero();
    this->imprimirEstadisticas();
    this->dibujarJuegoDeLaVida();
    cout<<"Presione 1 para avanzar turnos, 2 para reiniciar el juego, 3 o cualquier otro digito para cerrarlo"<<endl;
    while(cin>>numeroIngresado) {
        if(numeroIngresado == 1) {
            int cantidadDeTurnos = 1;
            cout<<"¿Cuantos turnos desea ejecutar? (minimo 1, maximo 5): ";
            cin>>cantidadDeTurnos;
            while(cantidadDeTurnos > 5 || cantidadDeTurnos < 1) {
                cin.clear();
                cin.ignore(100, '\n');
                cout<<"Ingreso incorrecto, indique un numero entero (minimo 1, maximo 5): ";
                cin>>cantidadDeTurnos;
            }
            for (int turnosEjecutados = 0; turnosEjecutados < cantidadDeTurnos; turnosEjecutados++)
            {
                this->pasarTurno();
                this->estadisticas.turnos++;
            }
        }
        if(numeroIngresado == 2) {
            this->inicializarJuegoDeLaVida();
        }
        if(numeroIngresado == 3) {
            break;
        }
        this->tablero->mostrarTablero();
        this->imprimirEstadisticas();
        this->dibujarJuegoDeLaVida();
        this->estadisticas.muertesDelTurno = 0;
        this->estadisticas.nacimientosDelTurno = 0;
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
        this->estadisticas.flagCongelado = true;
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
            this->estadisticas.celulasVivas--;
            this->estadisticas.muertesDelTurno++;
            this->estadisticas.muertesTotales++;
        }
        if(comportamiento == Envenenada) {
            celula->setGen(generarNumeroRandom(3), 0);
        }
        if(comportamiento == Procreadora) {
            if(this->configuracion.x1 > 3) {
                this->configuracion.x1--;
            }
            if(this->configuracion.x2 > 2) {
                this->configuracion.x2--;
            }
            if(this->configuracion.x3 > 4) {
                this->configuracion.x3--; 
            }
        } 
    }
}

void JuegoDeLaVida::imprimirEstadisticas() {
    cout<<"ESTADISTICAS"<<endl;
    cout<<"CV: "<<this->estadisticas.celulasVivas<<" CQN: "<<this->estadisticas.nacimientosDelTurno<<" CQM: "<<this->estadisticas.muertesDelTurno<<endl;
    float promedioDeNacimientos = (float)this->estadisticas.nacimientosTotales / (float)this->estadisticas.turnos;
    float promedioDeMuertes = (float)this->estadisticas.muertesTotales /  (float)this->estadisticas.turnos;
    cout<<"%N: "<<promedioDeNacimientos<<" %M: "<<promedioDeMuertes<<endl;
    cout<<"Muertes Totales: "<< this->estadisticas.muertesTotales<<endl;
    cout<<"Nacimiento Totales "<< this->estadisticas.nacimientosTotales<<endl;
    if(this->estadisticas.flagCongelado) {
    cout<<"El juego esta congelado"<<endl;
    }
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
    char encabezado[200] = "ESTADISTICAS     ", turnos[40] = "  Turnos: ", nTurnos[40];
    sprintf(nTurnos, "%i", this->estadisticas.turnos);
    strcat(encabezado, turnos);
    strcat(encabezado, nTurnos);
    PrintString(imagenPortada, encabezado, 30, 30, 14, blanco);

    char linea1[200] = "Celulas Vivas: ", nVivas[40], nacimientos[40] = "  Nacimientos del turno: ", nNacimientos[40], muertes[40] =  "  Muertes del turno: ", nMuertes[40];
    sprintf(nVivas, "%i", this->estadisticas.celulasVivas);
    sprintf(nNacimientos, "%i", this->estadisticas.nacimientosDelTurno);
    sprintf(nMuertes, "%i", this->estadisticas.muertesDelTurno);
    strcat(linea1, nVivas);
    strcat(linea1, nacimientos);
    strcat(linea1, nNacimientos);
    strcat(linea1, muertes);
    strcat(linea1, nMuertes);
    PrintString(imagenPortada, linea1, 30, 60, 11, blanco);

    char linea2[200] = "Nacimientos totales: ", nNacimientosTotales[40], muertesTotales[40] = "  Muertes totales: ", nMuertesTotales[40];
    sprintf(nNacimientosTotales, "%i", this->estadisticas.nacimientosTotales);
    sprintf(nMuertesTotales, "%i", this->estadisticas.muertesTotales);
    strcat(linea2, nNacimientosTotales);
    strcat(linea2, muertesTotales);
    strcat(linea2, nMuertesTotales);
    PrintString(imagenPortada, linea2, 30, 80, 11, blanco);

    char linea3[200] = "Porcentaje de nacimientos: ", nPorcNaciemientos[40], porcMuertes[40] = "  Porcentaje de muertes ", nPorcMuertes[40];
    sprintf(nPorcNaciemientos, "%f", (float)this->estadisticas.nacimientosTotales / (float)this->estadisticas.turnos);
    sprintf(nPorcMuertes, "%f", (float)this->estadisticas.muertesTotales /  (float)this->estadisticas.turnos);
    strcat(linea3, nPorcNaciemientos);
    strcat(linea3, porcMuertes);
    strcat(linea3, nPorcMuertes);
    PrintString(imagenPortada, linea3, 30, 100, 11, blanco);

    if(this->estadisticas.flagCongelado) {
        char linea5[40] = "JUEGO CONGELADO";
        PrintString(imagenPortada, linea5, 200, 125, 12, blanco);
    }

    imagenPortada.WriteToFile("imagenes/estadisticas.bmp");

    for(int capa = 1; capa <= capas; capa++) {
        BMP imagenCapa;

        imagenCapa.SetSize(columnas*TAMANIO_CELDA, (filas*TAMANIO_CELDA)+MARGEN_INFERIOR);

        for(int i=0; i<imagenCapa.TellWidth(); i++) {
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

        for(int fila = 1; fila <= filas; fila++) {
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
        char ruta[200] = "imagenes/capa", formato[5] = ".bmp", numeroImagen[40];
        sprintf(numeroImagen, "%i", capa);
        strcat(ruta, numeroImagen);
        strcat(ruta, formato);
        imagenCapa.WriteToFile(ruta);

    }
}

void JuegoDeLaVida::inicializarCelulasConfiguracion() {
    this->estadisticas.celulasVivas = this->configuracion.cantidadCelulasVivas;
    for(int i=0; i<this->configuracion.cantidadCelulasVivas; i++) {
        Celula * celulaAux = NULL;
        do {
        celulaAux = this->tablero->getCelda(generarNumeroRandom(this->configuracion.capas),
                                            generarNumeroRandom(this->configuracion.filas),
                                            generarNumeroRandom(this->configuracion.columnas))->getCelula();
        } while(celulaAux->getEstado() == Viva);
        celulaAux->revivirCelula();
    }  
}
