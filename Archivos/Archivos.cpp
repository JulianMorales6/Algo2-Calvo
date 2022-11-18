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
        i++;
    }
    cout<<"Elejir dificultad"<<endl;
    for (int i = 0; i <= 1; i++)
    {
        int numero_opcion = i + 1;
        cout<<numero_opcion<<" - "<<lista_dificultades[i].dificultad<<endl;
    }
        cout<<"3 - Personalizada"<<endl;
    
    archivo.close();
}