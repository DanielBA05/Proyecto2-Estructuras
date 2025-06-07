#include "galaxia.h"
#include "ruta.h"
#include "grafo.h"
#include "kruskal.h"
#include "nave.h"
#include <iostream>

using namespace std;

void menuRegistros() {
    int opcion;
    do {
        cout << "\n--- MENU DE REGISTROS ---\n";
        cout << "1. Agregar galaxia\n";
        cout << "2. Agregar ruta\n";
        cout << "3. Agregar nave\n";
        cout << "4. Registrar viaje\n";
        cout << "0. Volver al menu principal\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarGalaxia(); break;
            case 2: {
                string origen, destino;
                float costo;
                cout << "Ingrese galaxia origen: "; cin >> origen;
                cout << "Ingrese galaxia destino: "; cin >> destino;
                cout << "Ingrese el costo del viaje: "; cin >> costo;
                agregarRuta(origen, destino, costo);
                cout << "Ruta agregada exitosamente.\n";
                break;
            }
            case 3: agregarNave(); break;
            case 4: registrarViaje(); break;
            case 0: break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}

void menuConsultas() {
    int opcion;
    do {
        cout << "\n--- MENU DE CONSULTAS ---\n";
        cout << "1. Ver galaxias\n";
        cout << "2. Mostrar rutas desde una galaxia\n";
        cout << "3. Ruta de menor costo entre galaxias\n";
        cout << "0. Volver al menu principal\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: mostrarGalaxias(); break;
            case 2: {
                string inicio;
                cout << "Ingrese el codigo de galaxia: ";
                cin >> inicio;
                mostrarRutasDesde(inicio);
                break;
            }
            case 3: {
                string origen, destino;
                cout << "Ingrese galaxia origen: "; cin >> origen;
                cout << "Ingrese galaxia destino: "; cin >> destino;
                rutaMenorCosto(origen, destino);
                break;
            }
            case 0: break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}

void menuReportes() {
    int opcion;
    do {
        cout << "\n--- MENU DE REPORTES ---\n";
        cout << "1. Mostrar conexiones del grafo\n";
        cout << "2. Aplicar Kruskal modificado\n";
        cout << "3. Historial de viajes por nave\n";
        cout << "0. Volver al menu principal\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: construirGrafo(); mostrarConexiones(); break;
            case 2: construirGrafo(); aplicarKruskal(); break;
            case 3: mostrarHistorialPorNave(); break;
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
        cout << "1. Registros\n";
        cout << "2. Consultas\n";
        cout << "3. Reportes\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuRegistros(); break;
            case 2: menuConsultas(); break;
            case 3: menuReportes(); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
      guardarGalaxias();

    return 0;
}
