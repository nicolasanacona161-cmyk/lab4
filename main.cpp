#include "Red.h"

#include <iostream>
#include <vector>

using namespace std;

void coutRuta(const vector<int>& ruta) {
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

    red.conectarRouters(0, 1, 4);
    red.conectarRouters(0, 2, 10);
    red.conectarRouters(0, 3, 5);
    red.conectarRouters(1, 2, 3);
    red.conectarRouters(1, 3, 1);
    red.conectarRouters(2, 3, 2);

    red.actualizarTablas();

    red.coutTopologia();
    cout << endl;
    red.coutTablas();

    cout << endl << "Ruta calculada de A hasta C: ";
    coutRuta(red.calcularCamino(0, 2));

    return 0;
}
