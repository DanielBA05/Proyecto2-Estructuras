#pragma once
#include <iostream>
#include <string>
#include <vector>

struct Galaxia {
    std::string nombre;
    std::string codigo;
    double x, y, z;
};

static std::vector<Galaxia> galaxias;

inline void cargarGalaxias() {
    galaxias.push_back({"Andromeda", "G001", 0.1, 0.2, 0.3});
    galaxias.push_back({"Orion", "G002", 1.1, 2.2, 3.3});
    galaxias.push_back({"Pegaso", "G003", 2.0, 3.1, 4.2});
    galaxias.push_back({"Fenix", "G004", 4.2, 5.3, 6.4});
    galaxias.push_back({"Centauro", "G005", 6.0, 7.1, 8.2});
    galaxias.push_back({"Cisne", "G006", 1.3, 2.4, 3.5});
    galaxias.push_back({"Sagitario", "G007", 7.7, 8.8, 9.9});
    galaxias.push_back({"Leo", "G008", 2.5, 3.6, 4.7});
    galaxias.push_back({"Draco", "G009", 5.0, 6.0, 7.0});
    galaxias.push_back({"Hercules", "G010", 8.1, 9.2, 1.3});
}

inline void mostrarGalaxias() {
    for (const auto& g : galaxias) {
        std::cout << "Nombre: " << g.nombre << ", Codigo: " << g.codigo
                  << ", Coordenadas: (" << g.x << ", " << g.y << ", " << g.z << ")\n";
    }
}

inline bool galaxiaExiste(const std::string& codigo) {
    for (const auto& g : galaxias) {
        if (g.codigo == codigo) return true;
    }
    return false;
}

inline void agregarGalaxia() {
    Galaxia g;
    std::cout << "Ingrese nombre: "; std::cin >> g.nombre;
    std::cout << "Ingrese codigo: "; std::cin >> g.codigo;
    if (galaxiaExiste(g.codigo)) {
        std::cout << "Galaxia ya registrada.\n";
        return;
    }
    std::cout << "Ingrese coordenadas X Y Z: ";
    std::cin >> g.x >> g.y >> g.z;
    galaxias.push_back(g);
    std::cout << "Galaxia agregada exitosamente.\n";
}

inline const std::vector<Galaxia>& obtenerGalaxias() {
    return galaxias;
}
