#ifndef RUTA_H
#define RUTA_H
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
using namespace std;

struct Ruta {
    string origen;
    string destino;
    float costo;
};

static vector<Ruta> rutas;

void agregarRuta(const string& origen, const string& destino, float costo) {
    rutas.push_back({origen, destino, costo});
    rutas.push_back({destino, origen, costo});
}

void cargarRutas() {
    agregarRuta("G001", "G002", 4.5);
    agregarRuta("G001", "G003", 2.0);
    agregarRuta("G002", "G004", 3.0);
    agregarRuta("G003", "G004", 1.5);
    agregarRuta("G004", "G005", 2.5);
    agregarRuta("G002", "G005", 5.0);
    agregarRuta("G003", "G006", 4.0);
    agregarRuta("G006", "G005", 1.0);
    agregarRuta("G005", "G007", 3.2);
    agregarRuta("G007", "G008", 2.3);
}

bool rutaExiste(const string& origen, const string& destino) {
    for (const auto& r : rutas) {
        if (r.origen == origen && r.destino == destino) {
            return true;
        }
    }
    return false;
}


// Función para obtener ruta de menor costo usando Dijkstra
void rutaMenorCosto(const string& inicio, const string& destino) {
    unordered_map<string, vector<pair<string, float>>> grafo;

    for (const auto& r : rutas) {
        grafo[r.origen].push_back({r.destino, r.costo});
    }

    unordered_map<string, float> dist;
    unordered_map<string, string> anterior;
    priority_queue<pair<float, string>, vector<pair<float, string>>, greater<>> pq;

    for (const auto& nodo : grafo) {
        dist[nodo.first] = INT_MAX;
    }

    dist[inicio] = 0;
    pq.push({0, inicio});

    while (!pq.empty()) {
        auto [d, actual] = pq.top(); pq.pop();

        for (const auto& [vecino, peso] : grafo[actual]) {
            float nuevo = dist[actual] + peso;
            if (nuevo < dist[vecino]) {
                dist[vecino] = nuevo;
                anterior[vecino] = actual;
                pq.push({nuevo, vecino});
            }
        }
    }

    if (dist[destino] == INT_MAX) {
        cout << "No hay ruta entre " << inicio << " y " << destino << ".\n";
        return;
    }

    vector<string> camino;
    string actual = destino;
    while (actual != inicio) {
        camino.push_back(actual);
        actual = anterior[actual];
    }
    camino.push_back(inicio);
    reverse(camino.begin(), camino.end());

    cout << "Ruta de menor costo: ";
    for (const auto& nodo : camino) {
        cout << nodo;
        if (nodo != destino) cout << " -> ";
    }
    cout << "\nCosto total: " << dist[destino] << "\n";
}

void mostrarRutasDesde(const string& inicio) {
    unordered_map<string, vector<string>> grafo;

    for (const auto& r : rutas) {
        grafo[r.origen].push_back(r.destino);
    }

    if (grafo.find(inicio) == grafo.end()) {
        cout << "La galaxia " << inicio << " no existe o no tiene rutas.\n";
        return;
    }

    unordered_map<string, bool> visitado;
    queue<string> q;
    q.push(inicio);
    visitado[inicio] = true;

    cout << "Rutas posibles desde " << inicio << ":\n";

    while (!q.empty()) {
        string actual = q.front(); q.pop();
        cout << actual << " -> ";

        for (const string& vecino : grafo[actual]) {
            cout << vecino << " ";
            if (!visitado[vecino]) {
                q.push(vecino);
                visitado[vecino] = true;
            }
        }
        cout << endl;
    }
}

inline const vector<Ruta>& obtenerRutas() {
    return rutas;
}

#endif
