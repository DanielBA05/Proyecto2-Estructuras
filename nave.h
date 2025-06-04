#ifndef NAVE_H
#define NAVE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

struct Viaje {
    string origen;
    string destino;
    float costo;
};

struct Nave {
    string codigo;
    string nombre;
    vector<Viaje> historial;
};

static vector<Nave> naves;

bool naveExiste(const string& codigo) {
    for (const auto& n : naves) {
        if (n.codigo == codigo) return true;
    }
    return false;
}

void agregarNave() {
    Nave n;
    cout << "Ingrese nombre de la nave: "; cin >> n.nombre;
    cout << "Ingrese codigo de la nave: "; cin >> n.codigo;
    if (naveExiste(n.codigo)) {
        cout << "Nave ya registrada.\n";
        return;
    }
    naves.push_back(n);
    cout << "Nave agregada exitosamente.\n";
}

void registrarViaje() {
    string codigo;
    cout << "Ingrese codigo de la nave: ";
    cin >> codigo;

    for (auto& n : naves) {
        if (n.codigo == codigo) {
            Viaje v;
            cout << "Ingrese galaxia origen: "; cin >> v.origen;
            cout << "Ingrese galaxia destino: "; cin >> v.destino;
            cout << "Ingrese costo del viaje: "; cin >> v.costo;
            n.historial.push_back(v);
            cout << "Viaje registrado exitosamente.\n";
            return;
        }
    }
    cout << "Nave no encontrada.\n";
}

void mostrarHistorialPorNave() {
    string codigo;
    cout << "Ingrese codigo de la nave: ";
    cin >> codigo;

    for (const auto& n : naves) {
        if (n.codigo == codigo) {
            cout << "Historial de viajes para " << n.nombre << " (" << n.codigo << "):\n";
            for (const auto& v : n.historial) {
                cout << "Origen: " << v.origen << ", Destino: " << v.destino << ", Costo: " << v.costo << "\n";
            }
            return;
        }
    }
    cout << "Nave no encontrada.\n";
}

void cargarNaves() {
    naves.push_back({"N001", "Falcon", {{"G001", "G002", 10.0}}});
    naves.push_back({"N002", "Andromeda", {{"G003", "G004", 15.0}}});
    naves.push_back({"N003", "Nebula", {{"G005", "G006", 20.0}}});
    naves.push_back({"N004", "Eclipse", {{"G007", "G008", 18.0}}});
    naves.push_back({"N005", "Lynx", {{"G009", "G010", 12.5}}});
    naves.push_back({"N006", "Orion", {{"G001", "G005", 25.0}}});
    naves.push_back({"N007", "Phoenix", {{"G002", "G003", 14.0}}});
    naves.push_back({"N008", "Voyager", {{"G004", "G006", 19.0}}});
    naves.push_back({"N009", "Nova", {{"G007", "G001", 16.0}}});
    naves.push_back({"N010", "Specter", {{"G008", "G002", 22.0}}});
}

#endif
