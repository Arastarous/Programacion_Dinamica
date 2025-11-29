#include <iostream>
#include <vector>
#include <string>
#include <limits> // Para numeric_limits

using namespace std;

struct Producto {
    int id;
    string nombre;
    int cantidad;
    float precio;
};

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
            case 3: buscar_producto(); break; // Pendiente
            case 4: cout << "Cerrando sistema..." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while(opcion != 4);

    return 0;
}

void mostrar_menu() {
    cout << "\n1. Agregar Producto" << endl;
    cout << "2. Mostrar Todos los Productos" << endl;
    cout << "3. Buscar Producto (Pendiente)" << endl;
    cout << "4. Salir" << endl;
    cout << "Opcion: ";
}

void agregar_producto() {
    Producto nuevo;
    
    cout << "\n--- Nuevo Producto ---" << endl;
    cout << "ID: "; cin >> nuevo.id;
    
    // Limpiar buffer antes de pedir strings con espacios
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    
    cout << "Nombre: "; 
    getline(cin, nuevo.nombre);
    
    cout << "Cantidad: "; cin >> nuevo.cantidad;
    cout << "Precio: $"; cin >> nuevo.precio;
    
    inventario.push_back(nuevo);
    cout << "Producto agregado correctamente." << endl;
}

void mostrar_inventario() {
    if (inventario.empty()) {
        cout << "\nEl inventario esta vacio." << endl;
    } else {
        cout << "\n--- Lista de Productos ---" << endl;
        for (const auto& p : inventario) {
            cout << "ID: " << p.id 
                 << " | Nombre: " << p.nombre 
                 << " | Cant: " << p.cantidad 
                 << " | Precio: $" << p.precio << endl;
        }
    }
}

void buscar_producto() {
    cout << "[TODO] Implementar busqueda lineal manana" << endl;
}