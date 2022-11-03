#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#define ARCHIVO_DIFICULTADES "data.csv"

using namespace std;

struct dificultad
{
    string dificultad,
        alturaTablero,
        anchoTablero,
        profundidadTablero,
        vecinasParaNacer,
        minParaSeguirViva,
        maxParaSeguirViva;
};


int main()
{
    dificultad lista_dificultades[2];
    ifstream archivo(ARCHIVO_DIFICULTADES);
    string linea;
    char separador = ',';
    int i = 0;
    getline(archivo,linea);
    while(getline(archivo,linea)) {
        dificultad nuevaDificultad;
        stringstream stream(linea);
        getline(stream, nuevaDificultad.dificultad, separador);
        getline(stream, nuevaDificultad.alturaTablero, separador);
        getline(stream, nuevaDificultad.anchoTablero, separador);
        getline(stream, nuevaDificultad.profundidadTablero, separador);
        getline(stream, nuevaDificultad.vecinasParaNacer, separador);
        getline(stream, nuevaDificultad.minParaSeguirViva, separador);
        getline(stream, nuevaDificultad.maxParaSeguirViva, separador);

        lista_dificultades[i] = nuevaDificultad;

        cout<<"Dificultad: "<<nuevaDificultad.dificultad<<endl<<"Altura del tablero: "<<nuevaDificultad.alturaTablero<<endl<<"Ancho del tablero: "<<nuevaDificultad.anchoTablero<<endl<<"Profundidad del tablero: "<<nuevaDificultad.profundidadTablero<<endl<<"Vecinas vivas para que nazca una celula: "<<nuevaDificultad.vecinasParaNacer<<endl<<"Limite inferior de vecinas vivas para que siga viva una celula: "<<nuevaDificultad.minParaSeguirViva<<endl<<"Limite superior de vecinas vivas para que siga viva una celula: "<<nuevaDificultad.maxParaSeguirViva<<endl<<endl;
        i++;
    }
    
    for (int i = 0; i <= 1; i++)
    {
        cout<<"Dificultad: "<<lista_dificultades[i].dificultad<<endl<<"Altura del tablero: "<<lista_dificultades[i].alturaTablero<<endl<<"Ancho del tablero: "<<lista_dificultades[i].anchoTablero<<endl<<"Profundidad del tablero: "<<lista_dificultades[i].profundidadTablero<<endl<<"Vecinas vivas para que nazca una celula: "<<lista_dificultades[i].vecinasParaNacer<<endl<<"Limite inferior de vecinas vivas para que siga viva una celula: "<<lista_dificultades[i].minParaSeguirViva<<endl<<"Limite superior de vecinas vivas para que siga viva una celula: "<<lista_dificultades[i].maxParaSeguirViva<<endl<<endl;
    }
    
    archivo.close();
}