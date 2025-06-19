#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;
struct Galaxia {
    std::string nombre;
    std::string codigo;
    double x, y, z;
};

static std::vector<Galaxia> galaxias;

inline bool galaxiaExiste(const std::string& codigo) {
    for (const auto& g : galaxias) {
        if (g.codigo == codigo) return true;
    }
    return false;
}

inline void guardarGalaxias() {
    std::ofstream out("galaxias.txt");
    if (!out) {
        std::cerr << "No se pudo abrir el archivo galaxias.txt para escritura\n";
        return;
    }

    for (const auto& g : galaxias) {
        out << g.nombre << " " << g.codigo << " " << g.x << " " << g.y << " " << g.z << "\n";
    }
}

inline void cargarGalaxias() {
    std::ifstream in("galaxias.txt");
    if (!in) {
        std::cerr << "No se pudo abrir el archivo galaxias.txt\n";
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
        std::cout << "No hay galaxias registradas.\n";
        return;
    }

    for (const auto& g : galaxias) {
        std::cout << "Nombre: " << g.nombre << ", Codigo: " << g.codigo
                  << ", Coordenadas: (" << g.x << ", " << g.y << ", " << g.z << ")\n";
    }
}

inline void agregarGalaxia() {
    Galaxia g;
    std::cout << "Ingrese nombre: ";
    std::cin >> g.nombre;
    
    std::cout << "Ingrese codigo: ";
    std::cin >> g.codigo;
    
    if (galaxiaExiste(g.codigo)) {
        std::cout << "Galaxia ya registrada.\n";
        return;
    }
    
    std::cout << "Ingrese coordenadas X Y Z: ";
    while (!(std::cin >> g.x >> g.y >> g.z)) {
        std::cout << "Entrada inválida. Por favor ingrese números para las coordenadas: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    galaxias.push_back(g);
    guardarGalaxias(); 
    std::cout << "Galaxia agregada exitosamente.\n";
}

inline void modificarGalaxia() {
    std::string codigo;
    std::cout << "Ingrese el código de la galaxia a modificar: ";
    std::cin >> codigo;

    for (auto& g : galaxias) {
        if (g.codigo == codigo) {
            std::cout << "Modificando galaxia: " << g.nombre << "\n";
            std::cout << "Nuevo nombre: ";
            std::cin >> g.nombre;
            std::cout << "Nuevas coordenadas X Y Z: ";
            while (!(std::cin >> g.x >> g.y >> g.z)) {
                std::cout << "Entrada inválida. Intente de nuevo: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            guardarGalaxias();
            std::cout << "Galaxia modificada exitosamente.\n";
            return;
        }
    }

    std::cout << "No se encontró una galaxia con ese código.\n";
}

inline void eliminarGalaxia() {
    std::string codigo;
    std::cout << "Ingrese el código de la galaxia a eliminar: ";
    std::cin >> codigo;

    for (auto it = galaxias.begin(); it != galaxias.end(); ++it) {
        if (it->codigo == codigo) {
            galaxias.erase(it);
            guardarGalaxias();
            std::cout << "Galaxia eliminada exitosamente.\n";
            return;
        }
    }

    std::cout << "No se encontró una galaxia con ese código.\n";
}

inline const vector<Galaxia>& obtenerGalaxias() {
    return galaxias;
}