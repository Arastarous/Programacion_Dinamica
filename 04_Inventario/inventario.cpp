#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm> // Para sort (opcional, pero haremos burbuja manual para cumplir temario)

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
void ordenar_por_precio(); // Nueva funcion

int main() {
    int opcion = 0;
    cout << "--- SISTEMA DE GESTION DE INVENTARIO FINAL ---" << endl;

    do {
        mostrar_menu();
        cin >> opcion;

        switch(opcion) {
            case 1: agregar_producto(); break;
            case 2: mostrar_inventario(); break;
            case 3: buscar_producto(); break;
            case 4: ordenar_por_precio(); break; // Nueva opcion
            case 5: cout << "Guardando y saliendo..." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while(opcion != 5);

    return 0;
}

void mostrar_menu() {
    cout << "\n1. Agregar Producto" << endl;
    cout << "2. Mostrar Inventario" << endl;
    cout << "3. Buscar por ID" << endl;
    cout << "4. Ordenar por Precio (Menor a Mayor)" << endl;
    cout << "5. Salir" << endl;
    cout << "Opcion: ";
}

void agregar_producto() {
    Producto nuevo;
    cout << "\n--- Nuevo Producto ---" << endl;
    cout << "ID: "; cin >> nuevo.id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cout << "Nombre: "; getline(cin, nuevo.nombre);
    cout << "Cantidad: "; cin >> nuevo.cantidad;
    cout << "Precio: $"; cin >> nuevo.precio;
    
    inventario.push_back(nuevo);
    cout << "Producto guardado." << endl;
}

void mostrar_inventario() {
    if (inventario.empty()) {
        cout << "\n[!] Inventario vacio." << endl;
    } else {
        cout << "\n--- Lista de Productos ---" << endl;
        for (const auto& p : inventario) {
            cout << "ID: " << p.id 
                 << " | " << p.nombre 
                 << " | Stock: " << p.cantidad 
                 << " | $" << p.precio << endl;
        }
    }
}

// Implementacion de Busqueda Lineal
void buscar_producto() {
    int id_buscado;
    bool encontrado = false;
    cout << "Ingrese ID a buscar: ";
    cin >> id_buscado;

    for (const auto& p : inventario) {
        if (p.id == id_buscado) {
            cout << "\n[ENCONTRADO] " << p.nombre << " - $" << p.precio << endl;
            encontrado = true;
            break;
        }
    }
    if (!encontrado) cout << "\n[!] Producto no encontrado." << endl;
}

// Implementacion de Ordenamiento (Metodo Burbuja simple)
void ordenar_por_precio() {
    if (inventario.size() < 2) {
        cout << "No hay suficientes productos para ordenar." << endl;
        return;
    }
    
    for (size_t i = 0; i < inventario.size() - 1; ++i) {
        for (size_t j = 0; j < inventario.size() - i - 1; ++j) {
            if (inventario[j].precio > inventario[j+1].precio) {
                // Intercambio manual
                Producto temp = inventario[j];
                inventario[j] = inventario[j+1];
                inventario[j+1] = temp;
            }
        }
    }
    cout << "Inventario ordenado por precio. Seleccione opcion 2 para ver." << endl;
}