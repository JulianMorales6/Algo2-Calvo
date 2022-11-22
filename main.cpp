
#include "JuegoDeLaVida.cpp"
#include <dirent.h>
#include <iostream>

void vaciarCarpetaImagenes(char ruta_carpeta[32]) {

    DIR *directorio = opendir(ruta_carpeta);
    struct dirent *archivo;

    if(directorio != NULL) {
        while((archivo = readdir(directorio)) != NULL) {
            char ruta[64] = "";
            strcat(ruta, ruta_carpeta);
            strcat(ruta, archivo->d_name);
            remove(ruta);
        }
    }
}

int main() {
    char ruta_carpeta[32] = "imagenes/";
    vaciarCarpetaImagenes(ruta_carpeta);
    JuegoDeLaVida * juego = new JuegoDeLaVida;
    juego->inicializarJuegoDeLaVida();
    juego->interaccionesUsuario();
    delete juego;
    return 0;
}