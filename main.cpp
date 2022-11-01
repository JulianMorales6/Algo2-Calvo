
#include "Tablero.cpp"

int main() {

    Tablero tablero(3, 3, 3); //creo un tablero de (3x3x3) 3 capas, 3 filas y 3 columnas 
    
    Celda celda = *(*(*(*tablero.getTablero())[0])[0])[0]; //accedo a un casillero y lo modifico
    
    celda.getCelula()->setEstadoDeCelula(Viva);

                                   //capa,fila,columna 
    cout<<((*(*(*tablero.getTablero())[0])[3])[2])->getCelula()->getEstado()<<endl;

    tablero.mostrarTablero();


    //falta hacer el destructor del tablero!




    return 0;
}