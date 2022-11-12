
#include "JuegoDeLaVida.cpp"

int main() {

    JuegoDeLaVida * juego = new JuegoDeLaVida;
    juego->setConfiguracion();
    juego->inicializarJuegoDeLaVida();
    juego->interaccionesUsuario();
    delete juego;
    return 0;
}