#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <random>
#include "grafo.h"
using namespace std;

inline vector<Ruta> aplicarKruskal() {
    vector<Ruta> resultado;
    unordered_map<string, string> padre;

    auto encontrar = [&](string nodo) -> string {
        if (padre.find(nodo) == padre.end()) {
            padre[nodo] = nodo;
        }
        while (padre[nodo] != nodo) {
            padre[nodo] = padre[padre[nodo]]; // Compresión de ruta
            nodo = padre[nodo]; // Corrección: asignación correcta del string
        }
        return nodo;
    };

    // Procesar solo aristas únicas (omitir duplicados)
    vector<Ruta> aristasUnicas;
    for (size_t i = 0; i < rutas.size(); i += 2) {
        aristasUnicas.push_back(rutas[i]);
    }

    // Ordenar las rutas por costo
    sort(aristasUnicas.begin(), aristasUnicas.end(), 
        [](const Ruta& a, const Ruta& b) { return a.costo < b.costo; });

    for (const auto& r : aristasUnicas) {
        string raizOrigen = encontrar(r.origen);
        string raizDestino = encontrar(r.destino);
        
        if (raizOrigen != raizDestino) {
            resultado.push_back(r);
            padre[raizDestino] = raizOrigen; // Unir conjuntos
        }
    }

    return resultado;
}
