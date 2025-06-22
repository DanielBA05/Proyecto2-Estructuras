#ifndef NAVE_H
#define NAVE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
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

inline bool naveExiste(const string& codigo) {
    return any_of(naves.begin(), naves.end(), 
        [&codigo](const Nave& n) { return n.codigo == codigo; });
}

inline void cargarNaves() {
   ifstream archivo("naves.txt");
    if (!archivo) {
       cerr << "Advertencia: No se pudo abrir el archivo naves.txt\n";
        return;
    }

   string codigo, nombre;
    while (archivo >> codigo >>ws &&getline(archivo, nombre)) {
        if (!naveExiste(codigo)) {
            naves.push_back({codigo, nombre});
        }
    }
}

inline void cargarViajes() {
   ifstream archivo("viajes.txt");
    if (!archivo) {
       cerr << "Advertencia: No se pudo abrir el archivo viajes.txt\n";
        return;
    }

   string codigo, origen, destino;
    float costo;
    while (archivo >> codigo >> origen >> destino >> costo) {
        auto it =find_if(naves.begin(), naves.end(), 
            [&codigo](const Nave& n) { return n.codigo == codigo; });
        
        if (it != naves.end()) {
            it->historial.push_back({origen, destino, costo});
        }
    }
}

inline void guardarNaves() {
   ofstream archivo("naves.txt");
    if (!archivo) {
       cerr << "Error: No se pudo guardar las naves\n";
        return;
    }

    for (const auto& n : naves) {
        archivo << n.codigo << " " << n.nombre << "\n";
    }
}

inline void guardarViaje(const string& codigo, const Viaje& v) {
   ofstream archivo("viajes.txt",ios::app);
    if (!archivo) {
       cerr << "Error: No se pudo registrar el viaje\n";
        return;
    }
    archivo << codigo << " " << v.origen << " " << v.destino << " " << v.costo << "\n";
}

inline void agregarNave() {
    Nave n;
    
   cout << "Ingrese nombre de la nave: ";
   getline(std::cin >>ws, n.nombre);
    
   cout << "Ingrese codigo de la nave: ";
   cin >> n.codigo;

    if (naveExiste(n.codigo)) {
       cerr << "Error: Nave ya registrada\n";
        return;
    }

    naves.push_back(n);
    guardarNaves();
   cout << "Nave agregada exitosamente.\n";
}

inline void registrarViaje() {
   string codigo;
   cout << "Ingrese codigo de la nave: ";
   cin >> codigo;

    auto it =find_if(naves.begin(), naves.end(), 
        [&codigo](const Nave& n) { return n.codigo == codigo; });

    if (it == naves.end()) {
       cerr << "Error: Nave no encontrada\n";
        return;
    }

    Viaje v;
   cout << "Ingrese galaxia origen: ";
   cin >> v.origen;
    
   cout << "Ingrese galaxia destino: ";
   cin >> v.destino;
    
   cout << "Ingrese costo del viaje: ";
    while (!(std::cin >> v.costo) || v.costo <= 0) {
       cerr << "Error: Ingrese un costo válido (número positivo): ";
       cin.clear();
       cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    it->historial.push_back(v);
    guardarViaje(it->codigo, v);
   cout << "Viaje registrado exitosamente.\n";
}

inline void mostrarHistorialPorNave() {
   string codigo;
   cout << "Ingrese codigo de la nave: ";
   cin >> codigo;

    auto it =find_if(naves.begin(), naves.end(), 
        [&codigo](const Nave& n) { return n.codigo == codigo; });

    if (it == naves.end()) {
       cerr << "Error: Nave no encontrada\n";
        return;
    }

   cout << "\nHistorial de viajes para " << it->nombre << " (" << it->codigo << "):\n";
    if (it->historial.empty()) {
       cout << "No hay viajes registrados\n";
        return;
    }

    for (const auto& v : it->historial) {
       cout << " - Origen: " << v.origen 
                  << ", Destino: " << v.destino 
                  << ", Costo: " << v.costo << "\n";
    }
}

inline void mostrarNaves() {
    if (naves.empty()) {
       cout << "No hay naves registradas.\n";
        return;
    }

   cout << "\nLista de naves:\n";
    for (const auto& n : naves) {
       cout << "Codigo: " << n.codigo << " | Nombre: " << n.nombre << "\n";
    }
}

inline void eliminarNave() {
   string codigo;
   cout << "Ingrese codigo de la nave a eliminar: ";
   cin >> codigo;

    auto it =remove_if(naves.begin(), naves.end(),
        [&codigo](const Nave& n) { return n.codigo == codigo; });

    if (it != naves.end()) {
        naves.erase(it, naves.end());
        guardarNaves();
       cout << "Nave eliminada exitosamente.\n";
    } else {
       cout << "No se encontró la nave.\n";
    }
}

#endif
