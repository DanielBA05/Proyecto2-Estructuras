#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "ruta.h"
#include "galaxia.h"
using namespace std;
struct Arista {
    string origen;
    string destino;
    double costo;
};

static vector<Arista> aristas;

inline void construirGrafo() {
    aristas.clear();
    const auto& galaxias = obtenerGalaxias();
    const auto& rutas = obtenerRutas();

    for (const auto& g1 : galaxias) {
        for (const auto& g2 : galaxias) {
            if (g1.codigo != g2.codigo && rutaExiste(g1.codigo, g2.codigo)) {
                for (const auto& r : rutas) {
                    if (r.origen == g1.codigo && r.destino == g2.codigo) {
                        aristas.push_back({g1.codigo, g2.codigo, r.costo});
                    }
                }
            }
        }
    }
}

inline void mostrarConexiones() {
    cout << "Conexiones en el grafo:\n";
    for (const auto& a : aristas) {
        cout << a.origen << " -> " << a.destino << " : " << a.costo << "\n";
    }
}

inline const vector<Arista>& obtenerAristas() {
    return aristas;
}
