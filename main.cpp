#include "galaxia.h"
#include "ruta.h"
#include "grafo.h"
#include "kruskal.h"
#include "nave.h"
#include <iostream>

using namespace std;
   
inline void mostrarEstadisticas() {
    if (naves.empty()) {
        cout << "No hay datos estadísticos disponibles.\n";
        return;
    }

    // Estadísticas básicas
    int totalViajes = 0;
    unordered_map<string, bool> galaxiasUnicas;
    unordered_map<string, int> conectividadGalaxias;

    for (const auto& nave : naves) {
        totalViajes += nave.historial.size();
        for (const auto& viaje : nave.historial) {
            galaxiasUnicas[viaje.origen] = true;
            galaxiasUnicas[viaje.destino] = true;
            conectividadGalaxias[viaje.origen]++;
            conectividadGalaxias[viaje.destino]++;
        }
    }

    // Top 3 galaxias más conectadas
    vector<pair<string, int>> topGalaxias(conectividadGalaxias.begin(), conectividadGalaxias.end());
    sort(topGalaxias.begin(), topGalaxias.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    
    cout << "\n--- ESTADÍSTICAS ---\n";
    cout << "• Galaxias únicas visitadas: " << galaxiasUnicas.size() << "\n";
    cout << "• Naves registradas: " << naves.size() << "\n";
    cout << "• Total de viajes: " << totalViajes << "\n";
    cout << "• Promedio de viajes/nave: " << (float)totalViajes / naves.size() << "\n";

    if (!topGalaxias.empty()) {
        cout << "\n• Top 3 galaxias más conectadas:\n";
        for (int i = 0; i < min(3, (int)topGalaxias.size()); i++) {
            cout << "  " << i + 1 << ". " << topGalaxias[i].first 
                      << " (" << topGalaxias[i].second << " conexiones)\n";
        }
    }
}


void menuGalaxias() {
    int opcion;
    do {
        cout << "\n--- GALAXIAS ---\n";
        cout << "1. Agregar galaxia\n";
        cout << "2. Modificar galaxia\n";
        cout << "3. Eliminar galaxia\n";
        cout << "4. Mostrar galaxias\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarGalaxia(); break;
            case 2: modificarGalaxia(); break;
            case 3: eliminarGalaxia(); break;
            case 4: mostrarGalaxias(); break;
            case 0: break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}

void menuRutas() {
    int opcion;
    do {
        cout << "\n--- RUTAS ---\n";
        cout << "1. Agregar ruta\n";
        cout << "2. Eliminar ruta\n";
        cout << "3. Mostrar todas las rutas\n";
        cout << "0. Volver\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string origen, destino;
                float costo;
                cout << "Origen: "; cin >> origen;
                cout << "Destino: "; cin >> destino;
                cout << "Costo: "; cin >> costo;
                agregarRuta(origen, destino, costo);
                break;
            }
            case 2: {
                string origen, destino;
                cout << "Ingrese galaxia de origen: ";
                cin >> origen;
                cout << "Ingrese galaxia de destino: ";
                cin >> destino;
                eliminarRuta(origen, destino);
                break;
            }
            case 3:
                mostrarTodasLasRutas();
                break;
            case 0:
                cout << "Volviendo al menú principal...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}


void menuNaves() {
    int opcion;
    do {
        cout << "\n--- NAVES ---\n";
        cout << "1. Agregar nave\n";
        cout << "2. Eliminar nave\n";
        cout << "3. Mostrar naves\n";
        cout << "4. Registrar viaje\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarNave(); break;
            case 2: eliminarNave(); break;
            case 3: mostrarNaves(); break;
            case 4: registrarViaje(); break;
            case 0: break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}

void menuConsultas() {
    int opcion;
    do {
        cout << "\n--- CONSULTAS ---\n";
        cout << "1. Rutas desde una galaxia\n";
        cout << "2. Ruta de menor costo entre galaxias\n";
        cout << "3. Historial de viajes por nave\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string inicio;
                cout << "Codigo de galaxia: ";
                cin >> inicio;
                mostrarRutasDesde(inicio);
                break;
            }
            case 2: {
                string origen, destino;
                cout << "Origen: "; cin >> origen;
                cout << "Destino: "; cin >> destino;
                rutaMenorCosto(origen, destino);
                break;
            }
            case 3: mostrarHistorialPorNave(); break;
            case 0: break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}

void menuReportes() {
    int opcion;
    do {
        cout << "\n--- REPORTES ---\n";
        cout << "1. Mostrar conexiones del grafo\n";
        cout << "2. Árbol generado por Kruskal\n";
        cout << "3. Generar archivo de rutas más cortas\n";
        cout << "4. Generar archivo de árbol de expansión\n";
        cout << "5. Mostrar estadísticas de conectividad\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: construirGrafo(); mostrarConexiones(); break;
            case 2: construirGrafo(); aplicarKruskal(); break;
            case 3: generarArchivoRutasCortas(); break;
            case 4: generarArchivoArbolExpansion(); break;
            case 5: mostrarEstadisticas(); break;
            case 0: break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}

int main() {
    cargarGalaxias();
    cargarNaves();
    cargarRutas();

    int opcion;
    do {
        cout << "\n=== MENU PRINCIPAL ===\n";
        cout << "1. Gestionar Galaxias\n";
        cout << "2. Gestionar Rutas\n";
        cout << "3. Gestionar Naves\n";
        cout << "4. Consultas\n";
        cout << "5. Reportes\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuGalaxias(); break;
            case 2: menuRutas(); break;
            case 3: menuNaves(); break;
            case 4: menuConsultas(); break;
            case 5: menuReportes(); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    guardarGalaxias();
    guardarRutas();
    guardarNaves();

    return 0;
}
