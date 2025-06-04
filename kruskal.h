#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <random>
#include "grafo.h"

static std::unordered_map<std::string, std::string> padre;

inline std::string encontrar(const std::string& nodo) {
    if (padre[nodo] == nodo) return nodo;
    return padre[nodo] = encontrar(padre[nodo]);
}

inline void unir(const std::string& a, const std::string& b) {
    padre[encontrar(a)] = encontrar(b);
}

inline void aplicarKruskal() {
    auto aristas = obtenerAristas();

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(aristas.begin(), aristas.end(), g);

    padre.clear();
    std::vector<Arista> mst;

    for (const auto& a : aristas) {
        padre[a.origen] = a.origen;
        padre[a.destino] = a.destino;
    }

    for (const auto& a : aristas) {
        std::string u = encontrar(a.origen);
        std::string v = encontrar(a.destino);
        if (u != v) {
            mst.push_back(a);
            unir(u, v);
        }
    }

    std::cout << "\n--- Arbol de expansion minimo (Kruskal modificado) ---\n";
    for (const auto& a : mst) {
        std::cout << a.origen << " -> " << a.destino << " : " << a.costo << "\n";
    }
}
