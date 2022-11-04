
#include "Tablero.cpp"

int main() {

    Tablero tablero(5, 10, 10); //creo un tablero de (3x3x3) 3 capas, 3 filas y 3 columnas 
    
    Celda celda = *(*(*(*tablero.getTablero())[0])[1])[2]; //accedo a un casillero y lo modifico
    
    celda.getCelula()->setEstadoDeCelula(Viva);

                                   //capa,fila,columna 
    cout<<((*(*(*tablero.getTablero())[0])[1])[2])->getCelula()->getEstado()<<endl;

    tablero.mostrarTablero();


    //falta hacer el destructor del tablero!




    return 0;
}