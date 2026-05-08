#include <iostream>
#include "Router.h"
#include <queue>
#include <climits>
#include <algorithm>

Router::Router(int id) : idRouter(id), previo(nullptr), distancia(INT_MAX), visitado(false) {}

void Router::nuevoVecino(Router* vecino, int costo) {
    vecinos.emplace_back(vecino, costo);
}

void Router::cambiarDistancia(int dist) {
    distancia = dist;
}

void Router::actualizarCosto(int destino, int costo) {
    tablaCostos[destino] = costo;
}

void Router::reinicio() {
    distancia = INT_MAX;
    visitado = false;
    previo = nullptr;
}

void calcularRutas(Router* fuente) {
    fuente->cambiarDistancia(0);

    priority_queue<pair<int, Router*>> cola;
    cola.push({0, fuente});

    while (!cola.empty()) {
        Router* actual = cola.top().second;
        cola.pop();

        if (actual->visitado) continue;

        actual->visitado = true;

        for (auto& vec : actual->vecinos) {
            Router* routerVecino = vec.first;
            int costoEnlace = vec.second;

            int nuevaDistancia = actual->distancia + costoEnlace;
            if (nuevaDistancia < routerVecino->distancia) {
                routerVecino->cambiarDistancia(nuevaDistancia);
                routerVecino->previo = actual;
                cola.push({-nuevaDistancia, routerVecino});
            }
        }
    }
}

vector<int> obtenerRuta(Router* destino) {
    vector<Router*> camino;
    for (Router* r = destino; r != nullptr; r = r->previo) {
        camino.push_back(r);
    }
    reverse(camino.begin(), camino.end());

    vector<int> ruta;
    for (Router* router : camino) {
        ruta.push_back(router->idRouter);
    }

    return ruta;
}

void imprimirCamino(Router* destino) {
    vector<int> camino = obtenerRuta(destino);

    cout << "Camino mas corto: ";
    for (size_t i = 0; i < camino.size(); ++i) {
        cout << char('A' + camino[i]);
        if (i != camino.size() - 1)
            cout << " -> ";
    }
    cout << endl;
}
