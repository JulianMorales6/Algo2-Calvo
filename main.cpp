
#include "JuegoDeLaVida.cpp"

int main() {
    char ruta_carpeta[32] = "imagenes/";
    vaciarCarpetaImagenes(ruta_carpeta);
    JuegoDeLaVida * juego = new JuegoDeLaVida;
    juego->inicializarJuegoDeLaVida();
    juego->interaccionesUsuario();
    delete juego;
    return 0;
}
