
#include "Tablero.h"

int main() {

    Tablero tablero(3, 3, 3); //creo un tablero de (3x3x3) 3 capas, 3 filas y 3 columnas 
    
    *(*(*(*tablero.getTablero())[0])[2])[2] = 5;//accedo a un casillero y lo modifico

                                   //capa,fila,columna 
    cout<<*(*(*(*tablero.getTablero())[0])[3])[2]<<endl;

    tablero.mostrarTablero();


    //falta hacer el destructor del tablero!




    return 0;
}