#ifndef RED_H
#define RED_H

#include "Router.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

class Red {
public:
    void agregarRouter(int id);
    bool eliminarRouter(int id);
    void conectarRouters(int origen, int destino, int costo);
    bool eliminarEnlace(int origen, int destino);
    void actualizarTablas();
    vector<int> calcularCamino(int origen, int destino);
    int costoCamino(const vector<int>& camino) const;
    bool cargarDesdeArchivo(const string& rutaArchivo);
    void coutTopologia() const;
    void coutTablas() const;

private:
    map<int, Router> routers;

    void reiniciarRouters();
};

#endif
