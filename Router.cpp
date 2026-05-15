#include <iostream>
#include "Router.h"

Router::Router(int id) : idRouter(id), previo(nullptr), distancia(INFINITO), visitado(false) {}

void Router::nuevoVecino(Router* vecino, int costo) {
    for (auto& parVecino : vecinos) {
        if (parVecino.first == vecino) {
            parVecino.second = costo;
            return;
        }
    }

    vecinos.emplace_back(vecino, costo);
}

void Router::cambiarDistancia(int dist) {
    distancia = dist;
}

void Router::actualizarCosto(int destino, int costo) {
    tablaCostos[destino] = costo;
}

void Router::reinicio() {
    distancia = INFINITO;
    visitado = false;
    previo = nullptr;
}

void calcularRutas(Router* fuente) {
    fuente->cambiarDistancia(0);

    bool quedanRouters = true;

    while (quedanRouters) {
        Router* actual = nullptr;
        quedanRouters = false;

        vector<Router*> pendientes;
        pendientes.push_back(fuente);

        for (size_t i = 0; i < pendientes.size(); ++i) {
            Router* routerActual = pendientes[i];

            if (!routerActual->visitado && routerActual->distancia < INFINITO) {
                if (actual == nullptr || routerActual->distancia < actual->distancia) {
                    actual = routerActual;
                }
                quedanRouters = true;
            }

            for (auto& vecino : routerActual->vecinos) {
                Router* routerVecino = vecino.first;
                bool yaEsta = false;

                for (Router* routerPendiente : pendientes) {
                    if (routerPendiente == routerVecino) {
                        yaEsta = true;
                    }
                }

                if (!yaEsta) {
                    pendientes.push_back(routerVecino);
                }
            }
        }

        if (actual == nullptr) {
            return;
        }

        for (auto& vec : actual->vecinos) {
            Router* routerVecino = vec.first;
            int costoEnlace = vec.second;

            int nuevaDistancia = actual->distancia + costoEnlace;
            if (nuevaDistancia < routerVecino->distancia) {
                routerVecino->cambiarDistancia(nuevaDistancia);
                routerVecino->previo = actual;
            }
        }

        actual->visitado = true;
    }
}

vector<int> obtenerRuta(Router* destino) {
    vector<int> ruta;

    for (Router* r = destino; r != nullptr; r = r->previo) {
        ruta.insert(ruta.begin(), r->idRouter);
    }

    return ruta;
}

void coutCamino(Router* destino) {
    vector<int> camino = obtenerRuta(destino);

    cout << "Camino mas corto: ";
    for (size_t i = 0; i < camino.size(); ++i) {
        cout << char('A' + camino[i]);
        if (i != camino.size() - 1)
            cout << " -> ";
    }
    cout << endl;
}
