#ifndef ROUTER_H
#define ROUTER_H

#include <map>
#include <vector>
#include <utility>

using namespace std;

const int INFINITO = 1000000;

class Router {
public:
    Router(int id);

    int idRouter;
    Router* previo;
    vector<pair<Router*, int>> vecinos;
    map<int, int> tablaCostos;
    int distancia;
    bool visitado;

    void nuevoVecino(Router* vecino, int costo);
    void cambiarDistancia(int distancia);
    void actualizarCosto(int destino, int costo);
    void reinicio();
};

void calcularRutas(Router* fuente);
vector<int> obtenerRuta(Router* destino);
void coutCamino(Router* destino);

#endif
