
#include "Dibujar.h"

Dibujar::Dibujar(Tablero *tableroPasado, Estadisticas estadisticasPasadas) {
    this->tablero = tableroPasado;
    this->estadisticas = estadisticasPasadas;
    this->capas = tableroPasado->getTablero()->getLargo();
    this->filas = tableroPasado->getTablero()->getCursor()->getLargo();
    this->columnas = tableroPasado->getTablero()->getCursor()->getCursor()->getLargo();
    
    this->grisClaro.Red = 30;
    this->grisClaro.Green = 30;
    this->grisClaro.Blue = 30;

    this->grisOscuro.Red = 20;
    this->grisOscuro.Green = 20;
    this->grisOscuro.Blue = 20;

    this->blanco.Red = 255;
    this->blanco.Green = 255;
    this->blanco.Blue = 255;
}


void Dibujar::dibujarJuego() {
    this->dibujarEstadisticas();

    for(int capa = 1; capa <= capas; capa++) {
        BMP imagenCapa;
        imagenCapa.SetSize(this->columnas*TAMANIO_CELDA, (this->filas*TAMANIO_CELDA)+MARGEN_INFERIOR);

        for(int i=0; i<imagenCapa.TellWidth(); i++) {//color del fondo
            for(int j=0; j<imagenCapa.TellHeight(); j++) {
                *imagenCapa(i,j) = this->grisOscuro;
            }
        }
        this->dibujarCeldas(imagenCapa);
        this->dibujarInfoCapa(imagenCapa, capa);

        for(int fila = 1; fila <= filas; fila++) {
            for(int columna = 1; columna <= columnas; columna++) {
                Celula *celula = this->tablero->getCelda(capa, fila, columna)->getCelula();
                this->dibujarCelula(imagenCapa, celula, columna, fila);

                Celda *celda = this->tablero->getCelda(capa, fila, columna); 
                if(celda->getComportamiento() != Normal) {
                    this->dibujarComportamientoCelda(imagenCapa, celda, columna, fila);
                }
            }
        }
        this->guardarImagen(imagenCapa, capa);
    }
}


void Dibujar::dibujarCeldas(BMP &imagenCapa) {
    for(int y=0; y<=imagenCapa.TellHeight()-MARGEN_INFERIOR; y=y+TAMANIO_CELDA) {
        DrawLine(imagenCapa, 0, y, imagenCapa.TellWidth(), y, this->grisClaro);
    }
    for(int x=0; x<=imagenCapa.TellWidth(); x=x+TAMANIO_CELDA) {
        DrawLine(imagenCapa, x, 0, x, imagenCapa.TellHeight()-MARGEN_INFERIOR, this->grisClaro);
    }
}


void Dibujar::dibujarComportamientoCelda(BMP &imagenCapa, Celda *celda, int columna, int fila) {
    char texto[1024];
    char comportamiento[5] = " ";
  
    switch(celda->getComportamiento()) {
        case Envenenada: comportamiento[0] = 'E'; break;
        case Portal: comportamiento[0] = 'P'; break;
        case Contaminada: comportamiento[0] = 'C'; break;
        case Radioactiva: comportamiento[0] = 'R'; break;
        case Procreadora: comportamiento[0] = 'A'; break;
    }
    strcpy(texto, comportamiento);
    PrintString(imagenCapa, texto, (columna*TAMANIO_CELDA)-12, (fila*TAMANIO_CELDA)-12, 5, this->blanco);
}


void Dibujar::dibujarEstadisticas() {
    BMP imagenPortada;
    imagenPortada.SetSize(this->columnas*TAMANIO_CELDA, (this->filas*TAMANIO_CELDA)+MARGEN_INFERIOR);

    //falta

    imagenPortada.WriteToFile("imagenes/estadisticas.bmp");
}


void Dibujar::dibujarInfoCapa(BMP &imagenCapa, int capa) {
    char texto[1024];
    char numeroCapa[22] = "Capa";
    numeroCapa[4] = ' ';
    int indice = 5;
    for(int i=1, resto=10000, entero=1000;  i<=4; i++, resto=resto/10, entero = entero/10){
        //if para que no muestre 0001
        numeroCapa[indice] = CERO_ASCII+(char)(capa%resto)/entero;
        indice++;
    }
    strcpy(texto, numeroCapa);
    PrintString(imagenCapa, texto, imagenCapa.TellWidth()-80, imagenCapa.TellHeight()-15, 10, this->blanco);
}


void Dibujar::dibujarCelula(BMP &imagenCapa, Celula *celula, int columna, int fila) {
    RGBApixel colorCelula;
    colorCelula.Red = celula->getGen(0);
    colorCelula.Green = celula->getGen(1);
    colorCelula.Blue = celula->getGen(2);
    
    if(celula->getEstado() == Viva) {
        DrawArc(imagenCapa, (columna*TAMANIO_CELDA)-10, (fila*TAMANIO_CELDA)-10, RADIO_CELULA, 0, 7, colorCelula);
    }
    else {//sacar el else si viva o muerta solo se va a distinguir por el color
        DrawArc(imagenCapa, (columna*TAMANIO_CELDA)-10, (fila*TAMANIO_CELDA)-10, RADIO_CELULA, 0, 5, colorCelula);
    }
    /*
    for(int i=(columna*20)-19; i<(columna*20); i++) {
        for(int j=(fila*20)-19; j<(fila*20); j++) {
            *imagenCapa(i,j) = colorCelula;
       }
    }
    */
}


void Dibujar::guardarImagen(BMP &imagenCapa, int capa){
    char ruta[22] = "imagenes/capa0000.bmp";
    ruta[13] = CERO_ASCII+(char)(capa%10000)/1000;
    ruta[14] = CERO_ASCII+(char)(capa%1000)/100;
    ruta[15] = CERO_ASCII+(char)(capa%100)/10;
    ruta[16] = CERO_ASCII+(char)capa%10;
    imagenCapa.WriteToFile(ruta);
}


/*
    imagen.ReadFromFile("bmp/sample.bmp");//leo un archivo.bmp ya existente
    cout<< "File info:" << endl;
    cout<< imagen.TellWidth() << " x " << imagen.TellHeight()//muestro los datos de la imagen
        << " at " << imagen.TellBitDepth() << " bpp" << endl;
    cout << "colors: " << imagen.TellNumberOfColors() << endl;
*/


int main() {

    Tablero *tablero;

    tablero = new Tablero(4, 5, 5);//por ahora solo funciona hasta con 9 capas
    tablero->getCelda(1, 2, 3)->getCelula()->revivirCelula();
    tablero->getCelda(2, 5, 2)->getCelula()->revivirCelula();
    tablero->getCelda(1, 4, 2)->setComportamiento(Radioactiva);
    tablero->getCelda(1, 3, 5)->setComportamiento(Portal);
    tablero->getCelda(2, 5, 2)->setComportamiento(Envenenada);

    Estadisticas estadis;
    Dibujar dibujo(tablero, estadis);
    dibujo.dibujarJuego();


    return 0;
}

//se compila en terminal ->  g++ Dibujar.cpp bmp/EasyBMP.cpp bmp/EasyBMP_Geometry.cpp bmp/EasyBMP_Font.cpp -o dibujar