
#include "JuegoDeLaVida.h"

int main() {
    char ruta_carpeta[32] = "src/imagenes/";
    vaciarCarpetaImagenes(ruta_carpeta);
    JuegoDeLaVida * juego = new JuegoDeLaVida;
    juego->inicializarJuegoDeLaVida();
    juego->interaccionesUsuario();
    delete juego;
    return 0;
}
