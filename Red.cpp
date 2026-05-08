#include "Red.h"

#include <climits>
#include <iostream>

void Red::agregarRouter(int id) {
    if (routers.find(id) == routers.end()) {
        routers.emplace(id, Router(id));
    }
}

void Red::conectarRouters(int origen, int destino, int costo) {
    agregarRouter(origen);
    agregarRouter(destino);

    Router* routerOrigen = &routers.at(origen);
    Router* routerDestino = &routers.at(destino);

    routerOrigen->nuevoVecino(routerDestino, costo);
    routerDestino->nuevoVecino(routerOrigen, costo);
}

void Red::actualizarTablas() {
    for (auto& parOrigen : routers) {
        reiniciarRouters();
        Router* origen = &parOrigen.second;
        dijkstra(origen);

        for (auto& parDestino : routers) {
            origen->actualizarCosto(parDestino.first, parDestino.second.distancia);
        }
    }
}

vector<int> Red::calcularCamino(int origen, int destino) {
    vector<int> camino;

    if (routers.find(origen) == routers.end() || routers.find(destino) == routers.end()) {
        return camino;
    }

    reiniciarRouters();
    dijkstra(&routers.at(origen));

    if (routers.at(destino).distancia == INT_MAX) {
        return camino;
    }

    return routes(&routers.at(destino));
}

void Red::imprimirTopologia() const {
    cout << "Topologia de la red:" << endl;

    for (const auto& par : routers) {
        cout << char('A' + par.first) << " -> ";

        for (const auto& vecino : par.second.vecinos) {
            cout << char('A' + vecino.first->idRouter)
                 << "(" << vecino.second << ") ";
        }

        cout << endl;
    }
}

void Red::imprimirTablas() const {
    cout << "Tablas de costos:" << endl;

    for (const auto& par : routers) {
        cout << char('A' + par.first) << ": ";

        for (const auto& costo : par.second.tablaCostos) {
            cout << char('A' + costo.first) << "=";

            if (costo.second == INT_MAX) {
                cout << "INF";
            } else {
                cout << costo.second;
            }

            cout << " ";
        }

        cout << endl;
    }
}

void Red::reiniciarRouters() {
    for (auto& par : routers) {
        par.second.reinicio();
    }
}
