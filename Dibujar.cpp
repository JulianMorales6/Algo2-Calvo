#include <iostream>
using namespace std;
#include "JuegoDeLaVida.cpp"
#include "bmp/EasyBMP.h"
#include "bmp/EasyBMP_Geometry.h"
#include "bmp/EasyBMP_Font.h"
#include <string>

void dibujarTablero(Tablero *tablero) {
    int capas = tablero->getTablero()->getLargo();
    int filas = tablero->getTablero()->getCursor()->getLargo();
    int columnas = tablero->getTablero()->getCursor()->getCursor()->getLargo();
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
                Celda *celda = tablero->getCelda(capa, fila, columna); 
                if(celda->getComportamiento() != Normal) {
                    char texto[1024];
                    char comportamiento[20] = "c";
                    strcpy(texto, comportamiento);
                    PrintString(imagen, texto, (columna*tamanioCelda)-12, (fila*tamanioCelda)-18, 10, blanco);
                    /*
                    RGBApixel colorCelda;
                    colorCelda.Red = 48;
                    colorCelda.Green = 137;
                    colorCelda.Blue = 90;
                    colorCelda.Alpha = 240;
                    for(int i=(columna*20)-19; i<(columna*20); i++) {//fondo
                        for(int j=(fila*20)-19; j<(fila*20); j++) {
                            *imagen(i,j) = colorCelda;
                        }
                    }
                    */
                }
                Celula *celula = tablero->getCelda(capa, fila, columna)->getCelula();
                RGBApixel colorCelula;
                colorCelula.Red = celula->getGen(0);
                colorCelula.Green = celula->getGen(1);
                colorCelula.Blue = celula->getGen(2);
                if(celula->getEstado() == Viva) {
                    DrawArc(imagen, (columna*tamanioCelda)-10, (fila*tamanioCelda)-10, radioCelula, 0, 7, colorCelula);
                }
                else {//sacar el else si viva o muerta solo se va a distinguir por el color
                    DrawArc(imagen, (columna*tamanioCelda)-10, (fila*tamanioCelda)-10, radioCelula, 0, 5, colorCelula);
                }
            }
        }
        /*
        int mil, centena, decena, unidad;
        unidad = capa%10;
        decena = (capa%100)/10;
        centena = (capa%1000)/100;
        mil = (capa%10000)/1000;
        */
        char ruta[22] = "imagenes/capa0000.bmp";
        ruta[13] = ceroAscii+(char)(capa%10000)/1000;
        ruta[14] = ceroAscii+(char)(capa%1000)/100;
        ruta[15] = ceroAscii+(char)(capa%100)/10;
        ruta[16] = ceroAscii+(char)capa%10;
        imagen.WriteToFile(ruta);
    }
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

    tablero = new Tablero(4, 13, 14);//por ahora solo funciona hasta con 9 capas
    tablero->getCelda(1, 2, 3)->getCelula()->revivirCelula();
    tablero->getCelda(2, 5, 2)->getCelula()->revivirCelula();
    tablero->getCelda(1, 4, 9)->setComportamiento(Contaminada);
    tablero->getCelda(1, 3, 5)->setComportamiento(Contaminada);
    tablero->getCelda(2, 5, 2)->setComportamiento(Contaminada);
    dibujarTablero(tablero);


    return 0;
}
//se compila en terminal ->  g++ Dibujar.cpp bmp/EasyBMP.cpp bmp/EasyBMP_Geometry.cpp bmp/EasyBMP_Font.cpp -o dibujar