#ifndef RUTA_H
#define RUTA_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
#include <fstream>
#include <limits>
#include <string>
#include <utility>
using namespace std;
struct Ruta {
    string origen;
    string destino;
    float costo;
    
    // Constructor para facilitar la creación
    Ruta(string o, string d, float c) : origen(move(o)), destino(move(d)), costo(c) {}
};

// Variable global para almacenar las rutas (considerar usar una clase en lugar de global)
extern vector<Ruta> rutas;

// Declaraciones de funciones
bool rutaExiste(const string& origen, const string& destino);
void agregarRuta(const string& origen, const string& destino, float costo);
vector<Ruta> aplicarKruskal();
void eliminarRuta();
void mostrarTodasRutas();
void cargarRutas();
void guardarRutas();
void rutaMenorCosto(const string& inicio, const string& destino);
void mostrarRutasDesde(const string& inicio);
const vector<Ruta>& obtenerRutas();
void generarArchivoArbolExpansion();
void generarArchivoRutasCortas();

// Implementaciones inline
inline bool rutaExiste(const string& origen, const string& destino) {
    return any_of(rutas.begin(), rutas.end(), 
        [&](const Ruta& r) {
            return (r.origen == origen && r.destino == destino) ||
                   (r.origen == destino && r.destino == origen);
        });
}

inline void agregarRuta(const string& origen, const string& destino, float costo) {
    if (origen == destino) {
        cerr << "Error: No se puede crear una ruta al mismo nodo.\n";
        return;
    }

    if (costo <= 0) {
        cerr << "Error: El costo debe ser un valor positivo.\n";
        return;
    }

    if (!rutaExiste(origen, destino)) {
        rutas.emplace_back(origen, destino, costo);
        rutas.emplace_back(destino, origen, costo);
        cout << "Ruta agregada exitosamente.\n";
    } else {
        cout << "La ruta ya existe.\n";
    }
}

inline const vector<Ruta>& obtenerRutas() {
    return rutas;
}

#endif 