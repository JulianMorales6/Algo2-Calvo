
#include "JuegoDeLaVida.cpp"
#include <string>
#include <dirent.h>
#include <iostream>

void vaciarCarpetaImagenes() {

    DIR *directorio = opendir("imagenes/");
    struct dirent *archivo;
    char rutaCompleta[64] = "imagenes/";

    if(directorio != NULL) {
        while((archivo = readdir(directorio)) != NULL) {
            char ruta[64] = "imagenes/";
            strcat(ruta, archivo->d_name);
            cout<<ruta<<endl;
            remove(ruta);
        }
    }
}

int main() {
    vaciarCarpetaImagenes();
    JuegoDeLaVida * juego = new JuegoDeLaVida;
    juego->inicializarJuegoDeLaVida();
    juego->interaccionesUsuario();
    delete juego;
    return 0;
}