#ifndef NAVE_H
#define NAVE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>

struct Viaje {
    std::string origen;
    std::string destino;
    float costo;
};

struct Nave {
    std::string codigo;
    std::string nombre;
    std::vector<Viaje> historial;
};

static std::vector<Nave> naves;

inline bool naveExiste(const std::string& codigo) {
    return std::any_of(naves.begin(), naves.end(), 
        [&codigo](const Nave& n) { return n.codigo == codigo; });
}

inline void cargarNaves() {
    std::ifstream archivo("naves.txt");
    if (!archivo) {
        std::cerr << "Advertencia: No se pudo abrir el archivo naves.txt\n";
        return;
    }

    std::string codigo, nombre;
    while (archivo >> codigo >> std::ws && std::getline(archivo, nombre)) {
        if (!naveExiste(codigo)) {
            naves.push_back({codigo, nombre});
        }
    }
}

inline void cargarViajes() {
    std::ifstream archivo("viajes.txt");
    if (!archivo) {
        std::cerr << "Advertencia: No se pudo abrir el archivo viajes.txt\n";
        return;
    }

    std::string codigo, origen, destino;
    float costo;
    while (archivo >> codigo >> origen >> destino >> costo) {
        auto it = std::find_if(naves.begin(), naves.end(), 
            [&codigo](const Nave& n) { return n.codigo == codigo; });
        
        if (it != naves.end()) {
            it->historial.push_back({origen, destino, costo});
        }
    }
}

inline void guardarNaves() {
    std::ofstream archivo("naves.txt");
    if (!archivo) {
        std::cerr << "Error: No se pudo guardar las naves\n";
        return;
    }

    for (const auto& n : naves) {
        archivo << n.codigo << " " << n.nombre << "\n";
    }
}

inline void guardarViaje(const std::string& codigo, const Viaje& v) {
    std::ofstream archivo("viajes.txt", std::ios::app);
    if (!archivo) {
        std::cerr << "Error: No se pudo registrar el viaje\n";
        return;
    }
    archivo << codigo << " " << v.origen << " " << v.destino << " " << v.costo << "\n";
}

inline void agregarNave() {
    Nave n;
    
    std::cout << "Ingrese nombre de la nave: ";
    std::getline(std::cin >> std::ws, n.nombre);
    
    std::cout << "Ingrese codigo de la nave: ";
    std::cin >> n.codigo;

    if (naveExiste(n.codigo)) {
        std::cerr << "Error: Nave ya registrada\n";
        return;
    }

    naves.push_back(n);
    guardarNaves();
    std::cout << "Nave agregada exitosamente.\n";
}

inline void registrarViaje() {
    std::string codigo;
    std::cout << "Ingrese codigo de la nave: ";
    std::cin >> codigo;

    auto it = std::find_if(naves.begin(), naves.end(), 
        [&codigo](const Nave& n) { return n.codigo == codigo; });

    if (it == naves.end()) {
        std::cerr << "Error: Nave no encontrada\n";
        return;
    }

    Viaje v;
    std::cout << "Ingrese galaxia origen: ";
    std::cin >> v.origen;
    
    std::cout << "Ingrese galaxia destino: ";
    std::cin >> v.destino;
    
    std::cout << "Ingrese costo del viaje: ";
    while (!(std::cin >> v.costo) || v.costo <= 0) {
        std::cerr << "Error: Ingrese un costo válido (número positivo): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    it->historial.push_back(v);
    guardarViaje(it->codigo, v);
    std::cout << "Viaje registrado exitosamente.\n";
}

inline void mostrarHistorialPorNave() {
    std::string codigo;
    std::cout << "Ingrese codigo de la nave: ";
    std::cin >> codigo;

    auto it = std::find_if(naves.begin(), naves.end(), 
        [&codigo](const Nave& n) { return n.codigo == codigo; });

    if (it == naves.end()) {
        std::cerr << "Error: Nave no encontrada\n";
        return;
    }

    std::cout << "\nHistorial de viajes para " << it->nombre << " (" << it->codigo << "):\n";
    if (it->historial.empty()) {
        std::cout << "No hay viajes registrados\n";
        return;
    }

    for (const auto& v : it->historial) {
        std::cout << " - Origen: " << v.origen 
                  << ", Destino: " << v.destino 
                  << ", Costo: " << v.costo << "\n";
    }
}

#endif