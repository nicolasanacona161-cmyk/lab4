#include "Red.h"

#include <algorithm>
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

bool Red::eliminarRouter(int id) {
    auto it = routers.find(id);
    if (it == routers.end()) {
        return false;
    }

    for (auto& par : routers) {
        auto& vecinos = par.second.vecinos;
        vecinos.erase(
            remove_if(vecinos.begin(), vecinos.end(),
                      [id](const pair<Router*, int>& vecino) {
                          return vecino.first->idRouter == id;
                      }),
            vecinos.end());
    }

    routers.erase(it);
    actualizarTablas();
    return true;
}

bool Red::eliminarEnlace(int origen, int destino) {
    auto itOrigen = routers.find(origen);
    auto itDestino = routers.find(destino);
    if (itOrigen == routers.end() || itDestino == routers.end()) {
        return false;
    }

    auto& vecinosOrigen = itOrigen->second.vecinos;
    auto tamAnteriorOrigen = vecinosOrigen.size();
    vecinosOrigen.erase(
        remove_if(vecinosOrigen.begin(), vecinosOrigen.end(),
                  [destino](const pair<Router*, int>& vecino) {
                      return vecino.first->idRouter == destino;
                  }),
        vecinosOrigen.end());

    auto& vecinosDestino = itDestino->second.vecinos;
    auto tamAnteriorDestino = vecinosDestino.size();
    vecinosDestino.erase(
        remove_if(vecinosDestino.begin(), vecinosDestino.end(),
                  [origen](const pair<Router*, int>& vecino) {
                      return vecino.first->idRouter == origen;
                  }),
        vecinosDestino.end());

    if (tamAnteriorOrigen == vecinosOrigen.size() && tamAnteriorDestino == vecinosDestino.size()) {
        return false;
    }

    actualizarTablas();
    return true;
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

int Red::costoCamino(const vector<int>& camino) const {
    if (camino.empty()) {
        return INT_MAX;
    }

    int costoTotal = 0;
    for (size_t i = 0; i + 1 < camino.size(); ++i) {
        int actual = camino[i];
        int siguiente = camino[i + 1];

        auto it = routers.find(actual);
        if (it == routers.end()) {
            return INT_MAX;
        }

        bool encontrado = false;
        for (const auto& vecino : it->second.vecinos) {
            if (vecino.first->idRouter == siguiente) {
                costoTotal += vecino.second;
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            return INT_MAX;
        }
    }

    return costoTotal;
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
