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
 vector<Ruta> rutas;

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
        rutas.push_back({origen, destino, costo});
        rutas.push_back({destino, origen, costo});
        cout << "Ruta agregada exitosamente.\n";
    } else {
        cout << "La ruta ya existe.\n";
    }
}
void mostrarTodasLasRutas() {
    if (rutas.empty()) {
       cout << "No hay rutas registradas.\n";
        return;
    }

   cout << "--- RUTAS DISPONIBLES ---\n";
    for (size_t i = 0; i < rutas.size(); i += 2) {
        const Ruta& r = rutas[i]; // solo tomamos una dirección
       cout << r.origen << " -> " << r.destino << " (Costo: " << r.costo << ")\n";
    }
}
inline void generarArchivoRutasCortas() {
    // Primero construimos el grafo completo
    std::unordered_map<std::string, std::vector<std::pair<std::string, float>>> grafo;
    for (const auto& r : rutas) {
        grafo[r.origen].emplace_back(r.destino, r.costo);
    }

    // Obtenemos todos los nodos únicos
    std::vector<std::string> nodos;
    for (const auto& par : grafo) {
        nodos.push_back(par.first);
    }

    // Preparamos el archivo de salida
    std::ofstream archivo("rutas_cortas.txt");
    if (!archivo) {
        std::cerr << "Error: No se pudo crear el archivo rutas_cortas.txt\n";
        return;
    }

    // Para cada par de nodos, calculamos la ruta más corta
    for (size_t i = 0; i < nodos.size(); ++i) {
        for (size_t j = i + 1; j < nodos.size(); ++j) {
            const auto& inicio = nodos[i];
            const auto& destino = nodos[j];

            // Implementación de Dijkstra (similar a rutaMenorCosto)
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

                if (actual == destino) break;

                for (const auto& [vecino, peso] : grafo[actual]) {
                    float nuevo = dist[actual] + peso;
                    if (nuevo < dist[vecino]) {
                        dist[vecino] = nuevo;
                        anterior[vecino] = actual;
                        pq.emplace(nuevo, vecino);
                    }
                }
            }

            // Si hay ruta, la escribimos en el archivo
            if (dist[destino] != std::numeric_limits<float>::max()) {
                archivo << inicio << " " << destino << " " << dist[destino] << "\n";
            }
        }
    }

    std::cout << "Archivo de rutas cortas generado exitosamente: rutas_cortas.txt\n";
}
inline void cargarRutas() {
    ifstream archivo("rutas.txt");
    if (!archivo) {
        cerr << "Advertencia: No se pudo abrir el archivo rutas.txt\n";
        return;
    }

    string origen, destino;
    float costo;
    while (archivo >> origen >> destino >> costo) {
        if (!rutaExiste(origen, destino)) {
            rutas.push_back({origen, destino, costo});
            rutas.push_back({destino, origen, costo});
        }
    }
}

inline void guardarRutas() {
    ofstream archivo("rutas.txt");
    if (!archivo) {
        cerr << "Error: No se pudo guardar las rutas.\n";
        return;
    }

    // Guardamos solo una dirección para evitar duplicados
    for (size_t i = 0; i < rutas.size(); i += 2) {
        archivo << rutas[i].origen << " " << rutas[i].destino << " " << rutas[i].costo << "\n";
    }
}
void eliminarRuta(const std::string& origen, const std::string& destino) {
    bool eliminada = false;

    for (auto it = rutas.begin(); it != rutas.end(); ) {
        if ((it->origen == origen && it->destino == destino) ||
            (it->origen == destino && it->destino == origen)) {
            it = rutas.erase(it);
            eliminada = true;
        } else {
            ++it;
        }
    }

    if (eliminada) {
        std::cout << "Ruta entre " << origen << " y " << destino << " eliminada correctamente.\n";
        guardarRutas(); // Actualiza el archivo rutas.txt
    } else {
        std::cout << "La ruta no existe.\n";
    }
}

void rutaMenorCosto(const string& inicio, const string& destino) {
    if (inicio == destino) {
        cout << "Origen y destino son el mismo.\n";
        return;
    }

    unordered_map<string, vector<pair<string, float>>> grafo;
    for (const auto& r : rutas) {
        grafo[r.origen].emplace_back(r.destino, r.costo);
    }

    if (grafo.find(inicio) == grafo.end() || grafo.find(destino) == grafo.end()) {
        cout << "Una de las galaxias no existe o no tiene rutas.\n";
        return;
    }

    unordered_map<string, float> dist;
    unordered_map<string, string> anterior;
    priority_queue<pair<float, string>, 
                       vector<pair<float, string>>, 
                       greater<>> pq;

    for (const auto& nodo : grafo) {
        dist[nodo.first] = numeric_limits<float>::max();
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

    if (dist[destino] == numeric_limits<float>::max()) {
        cout << "No hay ruta entre " << inicio << " y " << destino << ".\n";
        return;
    }
    
    vector<string> camino;
    for (string actual = destino; actual != inicio; actual = anterior[actual]) {
        camino.push_back(actual);
    }
    camino.push_back(inicio);
    reverse(camino.begin(), camino.end());

    cout << "Ruta de menor costo: ";
    for (size_t i = 0; i < camino.size(); ++i) {
        cout << camino[i];
        if (i != camino.size() - 1) cout << " -> ";
    }
    cout << "\nCosto total: " << dist[destino] << "\n";
}

void mostrarRutasDesde(const string& inicio) {
    unordered_map<string, vector<string>> grafo;
    for (const auto& r : rutas) {
        grafo[r.origen].push_back(r.destino);
    }

    auto it = grafo.find(inicio);
    if (it == grafo.end()) {
        cout << "La galaxia " << inicio << " no existe o no tiene rutas.\n";
        return;
    }

    cout << "Rutas directas desde " << inicio << ":\n";
    for (const auto& dest : it->second) {
        cout << inicio << " -> " << dest << "\n";
    }
}

inline const vector<Ruta>& obtenerRutas() {
    return rutas;
}

#endif 