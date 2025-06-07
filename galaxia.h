#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

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
        std::cin.clear(); // Limpiar posibles errores
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

inline const std::vector<Galaxia>& obtenerGalaxias() {
    return galaxias;
}
