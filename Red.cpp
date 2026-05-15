#include "Red.h"

#include <fstream>
#include <iostream>
#include <sstream>

void Red::agregarRouter(int id) {
    if (routers.find(id) == routers.end()) {
        routers.emplace(id, Router(id));
    }
}

void Red::conectarRouters(int origen, int destino, int costo) {
    if (origen == destino || costo <= 0) {
        return;
    }

    agregarRouter(origen);
    agregarRouter(destino);

    Router* routerOrigen = &routers.at(origen);
    Router* routerDestino = &routers.at(destino);

    routerOrigen->nuevoVecino(routerDestino, costo);
    routerDestino->nuevoVecino(routerOrigen, costo);
}

bool Red::eliminarRouter(int id) {
    auto router = routers.find(id);
    if (router == routers.end()) {
        return false;
    }

    for (auto& par : routers) {
        vector<pair<Router*, int>>& vecinos = par.second.vecinos;

        for (size_t i = 0; i < vecinos.size();) {
            if (vecinos[i].first->idRouter == id) {
                vecinos.erase(vecinos.begin() + i);
            } else {
                ++i;
            }
        }
    }

    routers.erase(router);
    actualizarTablas();
    return true;
}

bool Red::eliminarEnlace(int origen, int destino) {
    auto routerOrigen = routers.find(origen);
    auto routerDestino = routers.find(destino);

    if (routerOrigen == routers.end() || routerDestino == routers.end()) {
        return false;
    }

    bool eliminado = false;
    vector<pair<Router*, int>>& vecinosOrigen = routerOrigen->second.vecinos;
    vector<pair<Router*, int>>& vecinosDestino = routerDestino->second.vecinos;

    for (size_t i = 0; i < vecinosOrigen.size();) {
        if (vecinosOrigen[i].first->idRouter == destino) {
            vecinosOrigen.erase(vecinosOrigen.begin() + i);
            eliminado = true;
        } else {
            ++i;
        }
    }

    for (size_t i = 0; i < vecinosDestino.size();) {
        if (vecinosDestino[i].first->idRouter == origen) {
            vecinosDestino.erase(vecinosDestino.begin() + i);
            eliminado = true;
        } else {
            ++i;
        }
    }

    if (eliminado) {
        actualizarTablas();
    }

    return eliminado;
}

void Red::actualizarTablas() {
    for (auto& parOrigen : routers) {
        reiniciarRouters();
        Router* origen = &parOrigen.second;
        calcularRutas(origen);

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
    calcularRutas(&routers.at(origen));

    if (routers.at(destino).distancia == INFINITO) {
        return camino;
    }

    return obtenerRuta(&routers.at(destino));
}

int Red::costoCamino(const vector<int>& camino) const {
    if (camino.empty()) {
        return INFINITO;
    }

    int costoTotal = 0;

    for (size_t i = 0; i + 1 < camino.size(); ++i) {
        int actual = camino[i];
        int siguiente = camino[i + 1];

        auto router = routers.find(actual);
        if (router == routers.end()) {
            return INFINITO;
        }

        bool encontrado = false;
        for (const auto& vecino : router->second.vecinos) {
            if (vecino.first->idRouter == siguiente) {
                costoTotal += vecino.second;
                encontrado = true;
            }
        }

        if (!encontrado) {
            return INFINITO;
        }
    }

    return costoTotal;
}

bool Red::cargarDesdeArchivo(const string& rutaArchivo) {
    ifstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        return false;
    }

    routers.clear();
    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty() || linea[0] == '#') {
            continue;
        }

        istringstream datos(linea);
        int origen = 0;
        int destino = 0;
        int costo = 0;

        if (datos >> origen >> destino >> costo) {
            conectarRouters(origen, destino, costo);
        }
    }

    actualizarTablas();
    return true;
}

void Red::coutTopologia() const {
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

void Red::coutTablas() const {
    cout << "Tablas de costos:" << endl;

    for (const auto& par : routers) {
        cout << char('A' + par.first) << ": ";

        for (const auto& costo : par.second.tablaCostos) {
            cout << char('A' + costo.first) << "=";

            if (costo.second >= INFINITO) {
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
