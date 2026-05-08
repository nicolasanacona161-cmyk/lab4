#include "Red.h"

#include <iostream>
#include <vector>

using namespace std;

void imprimirRuta(const vector<int>& ruta) {
    for (size_t i = 0; i < ruta.size(); ++i) {
        cout << char('A' + ruta[i]);

        if (i + 1 < ruta.size()) {
            cout << " -> ";
        }
    }

    cout << endl;
}

int main() {
    Red red;

    red.conectarRouters(0, 1, 4);   // A-B
    red.conectarRouters(0, 2, 10);  // A-C
    red.conectarRouters(0, 3, 5);   // A-D
    red.conectarRouters(1, 2, 3);   // B-C
    red.conectarRouters(1, 3, 1);   // B-D
    red.conectarRouters(2, 3, 2);   // C-D

    red.actualizarTablas();

    red.imprimirTopologia();
    cout << endl;
    red.imprimirTablas();

    cout << endl << "Ruta calculada de A hasta C: ";
    imprimirRuta(red.calcularCamino(0, 2));

    return 0;
}
