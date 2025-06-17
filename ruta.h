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

struct Ruta {
    std::string origen;
    std::string destino;
    float costo;
};

static std::vector<Ruta> rutas;

inline bool rutaExiste(const std::string& origen, const std::string& destino) {
    return std::any_of(rutas.begin(), rutas.end(), 
        [&](const Ruta& r) {
            return (r.origen == origen && r.destino == destino) ||
                   (r.origen == destino && r.destino == origen);
        });
}

inline void agregarRuta(const std::string& origen, const std::string& destino, float costo) {
    if (origen == destino) {
        std::cerr << "Error: No se puede crear una ruta al mismo nodo.\n";
        return;
    }

    if (costo <= 0) {
        std::cerr << "Error: El costo debe ser un valor positivo.\n";
        return;
    }

    if (!rutaExiste(origen, destino)) {
        rutas.push_back({origen, destino, costo});
        rutas.push_back({destino, origen, costo});
        std::cout << "Ruta agregada exitosamente.\n";
    } else {
        std::cout << "La ruta ya existe.\n";
    }
}

inline void cargarRutas() {
    std::ifstream archivo("rutas.txt");
    if (!archivo) {
        std::cerr << "Advertencia: No se pudo abrir el archivo rutas.txt\n";
        return;
    }

    std::string origen, destino;
    float costo;
    while (archivo >> origen >> destino >> costo) {
        if (!rutaExiste(origen, destino)) {
            rutas.push_back({origen, destino, costo});
            rutas.push_back({destino, origen, costo});
        }
    }
}

inline void guardarRutas() {
    std::ofstream archivo("rutas.txt");
    if (!archivo) {
        std::cerr << "Error: No se pudo guardar las rutas.\n";
        return;
    }

    // Guardamos solo una dirección para evitar duplicados
    for (size_t i = 0; i < rutas.size(); i += 2) {
        archivo << rutas[i].origen << " " << rutas[i].destino << " " << rutas[i].costo << "\n";
    }
}

void rutaMenorCosto(const std::string& inicio, const std::string& destino) {
    if (inicio == destino) {
        std::cout << "Origen y destino son el mismo.\n";
        return;
    }

    std::unordered_map<std::string, std::vector<std::pair<std::string, float>>> grafo;
    for (const auto& r : rutas) {
        grafo[r.origen].emplace_back(r.destino, r.costo);
    }

    if (grafo.find(inicio) == grafo.end() || grafo.find(destino) == grafo.end()) {
        std::cout << "Una de las galaxias no existe o no tiene rutas.\n";
        return;
    }

    std::unordered_map<std::string, float> dist;
    std::unordered_map<std::string, std::string> anterior;
    std::priority_queue<std::pair<float, std::string>, 
                       std::vector<std::pair<float, std::string>>, 
                       std::greater<>> pq;

    for (const auto& nodo : grafo) {
        dist[nodo.first] = std::numeric_limits<float>::max();
    }

    dist[inicio] = 0;
    pq.emplace(0, inicio);

    while (!pq.empty()) {
        auto [d, actual] = pq.top(); 
        pq.pop();

        if (actual == destino) break; // Optimización: terminar si llegamos al destino

        for (const auto& [vecino, peso] : grafo[actual]) {
            float nuevo = dist[actual] + peso;
            if (nuevo < dist[vecino]) {
                dist[vecino] = nuevo;
                anterior[vecino] = actual;
                pq.emplace(nuevo, vecino);
            }
        }
    }

    if (dist[destino] == std::numeric_limits<float>::max()) {
        std::cout << "No hay ruta entre " << inicio << " y " << destino << ".\n";
        return;
    }

    std::vector<std::string> camino;
    for (std::string actual = destino; actual != inicio; actual = anterior[actual]) {
        camino.push_back(actual);
    }
    camino.push_back(inicio);
    std::reverse(camino.begin(), camino.end());

    std::cout << "Ruta de menor costo: ";
    for (size_t i = 0; i < camino.size(); ++i) {
        std::cout << camino[i];
        if (i != camino.size() - 1) std::cout << " -> ";
    }
    std::cout << "\nCosto total: " << dist[destino] << "\n";
}

void mostrarRutasDesde(const std::string& inicio) {
    std::unordered_map<std::string, std::vector<std::string>> grafo;
    for (const auto& r : rutas) {
        grafo[r.origen].push_back(r.destino);
    }

    auto it = grafo.find(inicio);
    if (it == grafo.end()) {
        std::cout << "La galaxia " << inicio << " no existe o no tiene rutas.\n";
        return;
    }

    std::cout << "Rutas directas desde " << inicio << ":\n";
    for (const auto& dest : it->second) {
        std::cout << inicio << " -> " << dest << "\n";
    }
}

inline const std::vector<Ruta>& obtenerRutas() {
    return rutas;
}

#endif