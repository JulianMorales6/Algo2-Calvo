
#include <iostream>
using namespace std;

#include "EasyBMP.h"
#include "EasyBMP_Geometry.h"
#include "EasyBMP_Font.h"
#include "string.h"


int main() {
    //defino los colores que voy a usar
    RGBApixel salmon;
    salmon.Red = 233;
    salmon.Green = 150;
    salmon.Blue = 122;

    RGBApixel morado;
    morado.Red = 42;
    morado.Green = 42;
    morado.Blue = 97;

    RGBApixel blanco;
    blanco.Red = 255;
    blanco.Green = 255;
    blanco.Blue = 255;

    BMP imagen; //creo una imagen
    imagen.SetSize(500, 500);//defino tamanio

    for(int i=0; i<imagen.TellHeight(); i++) {//le doy color al fondo
        for(int j=0; j<imagen.TellWidth(); j++) {
            *imagen(i,j) = morado;
        }
    }

    for(int y=10; y<imagen.TellHeight()-50; y=y+30) {
        DrawLine(imagen, 10, y, imagen.TellWidth()-10, y, salmon);
    }
    for(int x=10; x<imagen.TellWidth(); x=x+30) {
        DrawLine(imagen, x, 10, x, imagen.TellWidth()-70, salmon);
    }




    char texto1[1024];
    strcpy(texto1, "Hello world");
    PrintString(imagen, texto1, 20, 450, 20, blanco);

    char texto2[1024];
    strcpy(texto2, "Capa 1");
    PrintString(imagen, texto2, 400, 450, 20, blanco);










    imagen.WriteToFile("sample.bmp");//creo y escribo la imagen en un archivo.bmp para verla
    imagen.ReadFromFile("sample.bmp");//leo un archivo.bmp ya existente
    
    RGBApixel temp = imagen.GetPixel(14,18); //accedo a un pixel y le doy el nombre temp para operar con el
    
    cout<< "(pixel ("<<14<<", "<<18<<"): "
        << (int) temp.Red<< ","
        << (int) temp.Green<< ","//muestro los datos del pixel
        << (int) temp.Blue << ","
        << (int) temp.Alpha << ")" << endl;

    cout<< "File info:" << endl;
    cout<< imagen.TellWidth() << " x " << imagen.TellHeight()//muestro los datos de la imagen
        << " at " << imagen.TellBitDepth() << " bpp" << endl;
    cout << "colors: " << imagen.TellNumberOfColors() << endl;
    return 0;
}