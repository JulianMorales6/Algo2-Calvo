const int CANTIDAD_GENES = 3;

enum EstadoDeCelula {
    Viva,
    Muerta
};

class Celula {

private:

EstadoDeCelula Estado;
int Gen[CANTIDAD_GENES];

public:

Celula();
Celula(int genes[]);
void inicializarCelula();
void matarCelula();
void revivirCelula(int genes[]);
EstadoDeCelula getEstado();
void cambiarGen(int numeroDeGen, int cambio);
int ObtenerGen(int numeroDeGen);
void setEstadoDeCelula(EstadoDeCelula Estado);

};