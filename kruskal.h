#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <random>
#include "grafo.h"
#include "ruta.h"
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

void generarArchivoArbolExpansion() {
    construirGrafo(); // Este solo se usa si `rutas` depende de aristas, puedes omitirlo si ya están cargadas
    vector<Ruta> mst = aplicarKruskal(); // corregido el tipo
    ofstream archivo("arbol_expansion.txt");

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de salida.\n";
        return;
    }

    double costoTotal = 0;
    archivo << "Árbol de Expansión Mínima (Kruskal modificado):\n";
    for (const auto& r : mst) {
        archivo << r.origen << " - " << r.destino << " : " << r.costo << "\n";
        costoTotal += r.costo;
    }
    archivo << "Costo total: " << costoTotal << "\n";

    archivo.close();
    cout << "Archivo 'arbol_expansion.txt' generado correctamente.\n";
}

