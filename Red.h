#ifndef RED_H
#define RED_H

#include "Router.h"

#include <map>
#include <vector>

using namespace std;

class Red {
public:
    void agregarRouter(int id);
    void conectarRouters(int origen, int destino, int costo);
    void actualizarTablas();
    vector<int> calcularCamino(int origen, int destino);
    void imprimirTopologia() const;
    void imprimirTablas() const;

private:
    map<int, Router> routers; // conjunto de routers de la red

    void reiniciarRouters();
};

#endif // RED_H
