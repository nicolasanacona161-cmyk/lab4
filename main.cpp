#include "Red.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void coutRuta(const vector<int>& ruta) {
    if (ruta.empty()) {
        cout << "No existe ruta." << endl;
        return;
    }

    for (size_t i = 0; i < ruta.size(); ++i) {
        cout << char('A' + ruta[i]);

        if (i + 1 < ruta.size()) {
            cout << " -> ";
        }
    }

    cout << endl;
}

void coutMenu() {
    cout << endl;
    cout << "===== MENU RED DE ROUTERS =====" << endl;
    cout << "1. Mostrar topologia" << endl;
    cout << "2. Mostrar tablas de costos" << endl;
    cout << "3. Agregar router" << endl;
    cout << "4. Eliminar router" << endl;
    cout << "5. Agregar enlace" << endl;
    cout << "6. Eliminar enlace" << endl;
    cout << "7. Calcular ruta y costo entre dos routers" << endl;
    cout << "8. Cargar topologia desde archivo" << endl;
    cout << "9. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    Red red;

    if (!red.cargarDesdeArchivo("topologia.txt")) {
        cout << "No se pudo cargar topologia.txt. Se crea topologia por defecto." << endl;
        red.conectarRouters(0, 1, 4);
        red.conectarRouters(0, 2, 10);
        red.conectarRouters(0, 3, 5);
        red.conectarRouters(1, 2, 3);
        red.conectarRouters(1, 3, 1);
        red.conectarRouters(2, 3, 2);
        red.actualizarTablas();
    }

    int opcion = 0;

    while (opcion != 9) {
        coutMenu();
        cin >> opcion;

        if (!cin) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida." << endl;
            continue;
        }

        switch (opcion) {
        case 1:
            red.coutTopologia();
            break;
        case 2:
            red.coutTablas();
            break;
        case 3: {
            int id = 0;
            cout << "Ingrese id del router (0=A, 1=B, ...): ";
            cin >> id;
            red.agregarRouter(id);
            red.actualizarTablas();
            cout << "Router agregado/confirmado." << endl;
            break;
        }
        case 4: {
            int id = 0;
            cout << "Ingrese id del router a eliminar: ";
            cin >> id;

            if (red.eliminarRouter(id)) {
                cout << "Router eliminado." << endl;
            } else {
                cout << "No existe ese router." << endl;
            }
            break;
        }
        case 5: {
            int origen = 0;
            int destino = 0;
            int costo = 0;
            cout << "Ingrese origen destino costo (ej: 0 2 7): ";
            cin >> origen >> destino >> costo;
            red.conectarRouters(origen, destino, costo);
            red.actualizarTablas();
            cout << "Enlace agregado." << endl;
            break;
        }
        case 6: {
            int origen = 0;
            int destino = 0;
            cout << "Ingrese origen y destino del enlace a eliminar: ";
            cin >> origen >> destino;

            if (red.eliminarEnlace(origen, destino)) {
                cout << "Enlace eliminado." << endl;
            } else {
                cout << "No existe ese enlace." << endl;
            }
            break;
        }
        case 7: {
            int origen = 0;
            int destino = 0;
            cout << "Ingrese router origen y destino: ";
            cin >> origen >> destino;

            vector<int> ruta = red.calcularCamino(origen, destino);
            cout << "Ruta: ";
            coutRuta(ruta);

            int costo = red.costoCamino(ruta);
            cout << "Costo total: ";

            if (costo >= INFINITO) {
                cout << "INF" << endl;
            } else {
                cout << costo << endl;
            }
            break;
        }
        case 8: {
            string archivo;
            cout << "Ingrese nombre/ruta del archivo: ";
            cin >> archivo;

            if (red.cargarDesdeArchivo(archivo)) {
                cout << "Topologia cargada correctamente." << endl;
            } else {
                cout << "No se pudo cargar el archivo." << endl;
            }
            break;
        }
        case 9:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opcion invalida." << endl;
            break;
        }
    }

    return 0;
}
