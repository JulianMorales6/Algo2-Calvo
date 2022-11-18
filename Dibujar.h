#include <iostream>
using namespace std;
#include "JuegoDeLaVida.cpp"
#include "bmp/EasyBMP.h"
#include "bmp/EasyBMP_Geometry.h"
#include "bmp/EasyBMP_Font.h"
#include <string>

static const int MARGEN_INFERIOR = 20;
static const int TAMANIO_CELDA = 20;
static const int RADIO_CELULA = 8;
static const int CERO_ASCII = 48;


class Dibujar {
    private:
    Tablero *tablero;
    Estadisticas estadisticas;
    int capas;
    int filas;
    int columnas;
    RGBApixel grisClaro;
    RGBApixel grisOscuro;
    RGBApixel blanco;
    
    public:
    Dibujar(Tablero *tableroPasado, Estadisticas estadisticasPasadas);
    void dibujarJuego();
    void dibujarEstadisticas();
    void dibujarCeldas(BMP &imagenCapa);
    void dibujarComportamientoCelda(BMP &imagenCapa, Celda *celda, int columna, int fila);
    void dibujarInfoCapa(BMP &imagenCapa, int capa);
    void dibujarCelula(BMP &imagenCapa, Celula *celula, int columna, int fila);
    void guardarImagen(BMP &imagenCapa, int capa);
};

/*
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
*/