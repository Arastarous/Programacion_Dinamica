#include <iostream>
#include <string>
#include <stdexcept> // Para manejo de excepciones
#include <limits>

using namespace std;

// REQUISITO: Estructura
struct Producto {
    int id;
    string nombre;
    int cantidad;
    float precio;
};

// REQUISITO: Arreglos (Tamaño fijo para cumplir con "Arreglos" en lugar de vector)
const int MAX_PRODUCTOS = 20; 
Producto inventario[MAX_PRODUCTOS];
int contador_productos = 0;

// Prototipos
void mostrar_menu();
void agregar_producto();
void mostrar_inventario();

// REQUISITO: Punteros (La funcion retorna un puntero al producto encontrado)
Producto* buscar_por_id(int id);
Producto* buscar_por_nombre(string nombre);

// REQUISITO: Uso de punteros para modificar inventario
void modificar_stock(Producto* prod);

void ordenar_por_precio();
void ordenar_por_cantidad();

// --- MAIN ---
int main() {
    int opcion = 0;
    
    // Datos precargados de prueba (Opcional, ayuda a tener los "10 productos" rapido)
    // Puedes borrarlos si prefieres ingresarlos manual.
    /* inventario[contador_productos++] = {1, "Teclado", 15, 500.0};
    inventario[contador_productos++] = {2, "Mouse", 20, 250.0};
    inventario[contador_productos++] = {3, "Monitor", 5, 3500.0};
    */

    do {
        mostrar_menu();
        if (!(cin >> opcion)) {
            cin.clear(); cin.ignore(1000, '\n');
            continue;
        }

        try { // REQUISITO: Manejo de Excepciones (Bloque try-catch principal)
            switch(opcion) {
                case 1: 
                    agregar_producto(); 
                    break;
                case 2: 
                    mostrar_inventario(); 
                    break;
                case 3: {
                    // Busqueda con excepcion y modificacion con punteros
                    int id_temp;
                    cout << "Ingrese ID a buscar: "; cin >> id_temp;
                    
                    // buscar_por_id lanza excepcion si falla
                    Producto* encontrado = buscar_por_id(id_temp); 
                    
                    cout << "\n[ENCONTRADO]: " << encontrado->nombre << endl;
                    cout << "¿Desea modificar el stock? (1: Si / 0: No): ";
                    int resp; cin >> resp;
                    if (resp == 1) {
                        modificar_stock(encontrado); // Pasamos el puntero
                    }
                    break;
                }
                case 4: {
                    string nombre_temp;
                    cout << "Ingrese Nombre a buscar: "; 
                    cin.ignore(); getline(cin, nombre_temp);
                    
                    Producto* encontrado = buscar_por_nombre(nombre_temp);
                    cout << "\n[ENCONTRADO]: ID " << encontrado->id << " - $" << encontrado->precio << endl;
                    break;
                }
                case 5: 
                    ordenar_por_precio(); 
                    cout << "Ordenado por precio exitosamente." << endl;
                    mostrar_inventario();
                    break;
                case 6: 
                    ordenar_por_cantidad(); 
                    cout << "Ordenado por cantidad exitosamente." << endl;
                    mostrar_inventario();
                    break;
                case 7: 
                    cout << "Saliendo..." << endl; 
                    break;
                default: 
                    cout << "Opcion invalida." << endl;
            }
        }
        catch (const exception& e) {
            // Aqui caen los errores de busqueda ("Producto no encontrado")
            cout << "\n[ERROR EXCEPCION]: " << e.what() << endl;
        }

    } while(opcion != 7);

    return 0;
}

void mostrar_menu() {
    cout << "\n--- GESTION DE INVENTARIO (CON PUNTEROS) ---" << endl;
    cout << "1. Agregar Producto" << endl;
    cout << "2. Mostrar Inventario" << endl;
    cout << "3. Buscar por ID y Modificar (Usa Punteros)" << endl;
    cout << "4. Buscar por Nombre" << endl;
    cout << "5. Ordenar por Precio" << endl;
    cout << "6. Ordenar por Cantidad" << endl;
    cout << "7. Salir" << endl;
    cout << "Opcion: ";
}

void agregar_producto() {
    if (contador_productos >= MAX_PRODUCTOS) {
        cout << "Error: Inventario lleno." << endl;
        return;
    }

    Producto nuevo;
    cout << "\n--- Nuevo Producto ---" << endl;
    cout << "ID: "; cin >> nuevo.id;
    cin.ignore(); 
    cout << "Nombre: "; getline(cin, nuevo.nombre);
    cout << "Cantidad: "; cin >> nuevo.cantidad;
    cout << "Precio: $"; cin >> nuevo.precio;
    
    inventario[contador_productos] = nuevo; // Guardar en arreglo
    contador_productos++;
    cout << "Producto registrado." << endl;
}

void mostrar_inventario() {
    if (contador_productos == 0) {
        cout << "\nInventario vacio." << endl;
        return;
    }
    cout << "\n--- Listado ---" << endl;
    // Uso de punteros para recorrer el arreglo (Opcional pero se ve bien)
    for (int i = 0; i < contador_productos; i++) {
        Producto* p = &inventario[i]; // Puntero al elemento actual
        cout << "ID: " << p->id 
             << " | " << p->nombre 
             << " | Stock: " << p->cantidad 
             << " | Precio: $" << p->precio << endl;
    }
}

// REQUISITO: Excepciones en busquedas
Producto* buscar_por_id(int id) {
    for (int i = 0; i < contador_productos; i++) {
        if (inventario[i].id == id) {
            return &inventario[i]; // Retorna la DIRECCION DE MEMORIA (Puntero)
        }
    }
    // Si termina el ciclo y no encontro nada:
    throw runtime_error("Producto con ese ID no existe.");
}

Producto* buscar_por_nombre(string nombre) {
    for (int i = 0; i < contador_productos; i++) {
        if (inventario[i].nombre == nombre) {
            return &inventario[i];
        }
    }
    throw runtime_error("Producto con ese nombre no existe.");
}

// REQUISITO: Modificar inventario usando punteros
void modificar_stock(Producto* prod) {
    // Recibe un puntero, asi que usamos flecha (->) para acceder a miembros
    int nueva_cant;
    cout << "Stock actual: " << prod->cantidad << endl;
    cout << "Ingrese nueva cantidad: "; cin >> nueva_cant;
    
    prod->cantidad = nueva_cant; // Modifica directamente el original en memoria
    cout << "Stock actualizado correctamente." << endl;
}

// REQUISITO: Ordenamiento (Burbuja)
void ordenar_por_precio() {
    for (int i = 0; i < contador_productos - 1; i++) {
        for (int j = 0; j < contador_productos - i - 1; j++) {
            if (inventario[j].precio > inventario[j+1].precio) {
                // Intercambio
                Producto temp = inventario[j];
                inventario[j] = inventario[j+1];
                inventario[j+1] = temp;
            }
        }
    }
}

void ordenar_por_cantidad() {
    for (int i = 0; i < contador_productos - 1; i++) {
        for (int j = 0; j < contador_productos - i - 1; j++) {
            if (inventario[j].cantidad > inventario[j+1].cantidad) { // Criterio: Cantidad
                Producto temp = inventario[j];
                inventario[j] = inventario[j+1];
                inventario[j+1] = temp;
            }
        }
    }
}