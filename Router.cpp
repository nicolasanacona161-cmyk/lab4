#include <iostream>
#include "Router.h"
#include <queue>
#include <climits>
#include <algorithm>

Router::Router(int id) : idRouter(id), previo(nullptr), distancia(INT_MAX), visitado(false) {} //

void Router::nuevoVecino(Router* vecino, int costo) {
    vecinos.emplace_back(vecino, costo); // en vez de push_back, porque construyo el elemento que es un par
}

void Router::confDistancia(int dist) {
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

void dijkstra(Router* fuente) {
    fuente->confDistancia(0); //(*fuente).confDistancia(0); es equivalente con dereferenciación

    priority_queue<pair<int, Router*>> pq; //es una cola que tiene un valor adicional(prioridad), el elemento con mayor prio se guarda al inicio
    pq.push({0, fuente});

    while (!pq.empty()) {
        Router* actual = pq.top().second; //Tomo el valor del router del primer elemento de la cola
        pq.pop();


        if (actual->visitado) continue;

        actual->visitado = true;

        for (auto& vec : actual->vecinos) { //leo los vecinos del router actual
            Router* sigRouter = vec.first; //vecinos es un vector de pares, el primero es un router
            int costoBorde = vec.second; //lo que cuesta el borde a ese primer vecino

            int nuevaDistancia = actual->distancia + costoBorde; //La distancia es un valor de la fuente al router
            if (nuevaDistancia < sigRouter->distancia) {
                sigRouter->confDistancia(nuevaDistancia);
                sigRouter->previo = actual;  // <- Guardar el nodo anterior
                pq.push({-nuevaDistancia, sigRouter});
            }
        }
    }
}

vector<int> routes(Router* destino) {
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
    vector<int> camino = routes(destino);

    cout << "Camino mas corto: ";
    for (size_t i = 0; i < camino.size(); ++i) {
        cout << char('A' + camino[i]);  // Asumimos que 0->A, 1->B, ...
        if (i != camino.size() - 1)
            cout << " -> ";
    }
    cout << endl;
}
