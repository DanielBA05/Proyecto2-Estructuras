#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;
struct Galaxia {
    string nombre;
    string codigo;
    double x, y, z;
};

static vector<Galaxia> galaxias;

inline bool galaxiaExiste(const string& codigo) {
    for (const auto& g : galaxias) {
        if (g.codigo == codigo) return true;
    }
    return false;
}

inline void guardarGalaxias() {
    ofstream out("galaxias.txt");
    if (!out) {
        cerr << "No se pudo abrir el archivo galaxias.txt para escritura\n";
        return;
    }

    for (const auto& g : galaxias) {
        out << g.nombre << " " << g.codigo << " " << g.x << " " << g.y << " " << g.z << "\n";
    }
}

inline void cargarGalaxias() {
    ifstream in("galaxias.txt");
    if (!in) {
        cerr << "No se pudo abrir el archivo galaxias.txt\n";
        return;
    }

    Galaxia g;
    while (in >> g.nombre >> g.codigo >> g.x >> g.y >> g.z) {
        if (!galaxiaExiste(g.codigo)) {
            galaxias.push_back(g);
        }
    }
}

inline void mostrarGalaxias() {
    if (galaxias.empty()) {
        cout << "No hay galaxias registradas.\n";
        return;
    }

    for (const auto& g : galaxias) {
        cout << "Nombre: " << g.nombre << ", Codigo: " << g.codigo
                  << ", Coordenadas: (" << g.x << ", " << g.y << ", " << g.z << ")\n";
    }
}

inline void agregarGalaxia() {
    Galaxia g;
    cout << "Ingrese nombre: ";
    cin >> g.nombre;
    
    cout << "Ingrese codigo: ";
    cin >> g.codigo;
    
    if (galaxiaExiste(g.codigo)) {
        cout << "Galaxia ya registrada.\n";
        return;
    }
    
    cout << "Ingrese coordenadas X Y Z: ";
    while (!(cin >> g.x >> g.y >> g.z)) {
        cout << "Entrada inválida. Por favor ingrese números para las coordenadas: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    galaxias.push_back(g);
    guardarGalaxias(); 
    cout << "Galaxia agregada exitosamente.\n";
}

inline void modificarGalaxia() {
    string codigo;
    cout << "Ingrese el código de la galaxia a modificar: ";
    cin >> codigo;

    for (auto& g : galaxias) {
        if (g.codigo == codigo) {
            cout << "Modificando galaxia: " << g.nombre << "\n";
            cout << "Nuevo nombre: ";
            cin >> g.nombre;
            cout << "Nuevas coordenadas X Y Z: ";
            while (!(cin >> g.x >> g.y >> g.z)) {
                cout << "Entrada inválida. Intente de nuevo: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            guardarGalaxias();
            cout << "Galaxia modificada exitosamente.\n";
            return;
        }
    }

    cout << "No se encontró una galaxia con ese código.\n";
}

inline void eliminarGalaxia() {
    string codigo;
    cout << "Ingrese el código de la galaxia a eliminar: ";
    cin >> codigo;

    for (auto it = galaxias.begin(); it != galaxias.end(); ++it) {
        if (it->codigo == codigo) {
            galaxias.erase(it);
            guardarGalaxias();
            cout << "Galaxia eliminada exitosamente.\n";
            return;
        }
    }

    cout << "No se encontró una galaxia con ese código.\n";
}

inline const vector<Galaxia>& obtenerGalaxias() {
    return galaxias;
}