
enum EstadoDeCelula {
    Viva,
    Muerta
};

enum ComportamientoDeCelula {
    Contaminada,
    Envenenada,
    Procreadora,
    Portal,
    Radioactiva,
    Normal
};

class Celula {

private:

EstadoDeCelula Estado;
ComportamientoDeCelula Comportamiento;
int Gen[];

public:

Celula();
Celula(int gen1, int gen2, int gen3);
void inicializarCelula(Celula *celula, ComportamientoDeCelula comportamiento);
void matarCelula(Celula *celula);
void revivirCelula(Celula *celula, int gen1, int gen2, int gen3);
EstadoDeCelula obtenerEstado(Celula *celula);
void cambiarGen(Celula *celula, int numeroDeGen, int cambio);
int ObtenerGen(Celula *celula, int numeroDeGen);

};