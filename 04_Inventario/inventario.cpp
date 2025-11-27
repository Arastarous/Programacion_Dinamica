#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Estructura para representar un producto
struct Producto {
    int id;
    string nombre;
    int cantidad;
    float precio;
};

// Base de datos local (vector)
vector<Producto> inventario;

// Prototipos
void mostrar_menu();
void agregar_producto();
void mostrar_inventario();
void buscar_producto();

int main() {
    int opcion = 0;
    cout << "--- SISTEMA DE GESTION DE INVENTARIO V1.0 ---" << endl;

    do {
        mostrar_menu();
        cin >> opcion;

        switch(opcion) {
            case 1: agregar_producto(); break;
            case 2: mostrar_inventario(); break;
            case 3: buscar_producto(); break;
            case 4: cout << "Cerrando sistema..." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while(opcion != 4);

    return 0;
}

void mostrar_menu() {
    cout << "\n1. Agregar Producto" << endl;
    cout << "2. Mostrar Todos los Productos" << endl;
    cout << "3. Buscar Producto" << endl;
    cout << "4. Salir" << endl;
    cout << "Opcion: ";
}

// Stubs (Funciones vacias para rellenar despues)
void agregar_producto() {
    cout << "[TODO] Implementar captura de datos del producto" << endl;
}
void mostrar_inventario() {
    cout << "[TODO] Implementar recorrido del vector" << endl;
}
void buscar_producto() {
    cout << "[TODO] Implementar busqueda lineal" << endl;
}