#ifndef ROUTER_H
#define ROUTER_H

#include <map>
#include <vector>
#include <utility>

using namespace std;

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
    void confDistancia(int distancia);
    void actualizarCosto(int destino, int costo);
    void reinicio();
};

void dijkstra(Router* fuente);
vector<int> routes(Router* destino);
void imprimirCamino(Router* destino);

#endif
