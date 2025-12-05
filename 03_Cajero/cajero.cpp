#include <iostream>
#include <string>
#include <stdexcept> // Para manejo de excepciones
#include <cstdlib>   // Para system("cls")

using namespace std;

// REQUISITO: Estructuras
struct Cuenta {
    int numero_cuenta;
    int nip;
    string titular;
    double saldo;
};

// REQUISITO: Arreglo de estructuras (Minimo 3 cuentas)
const int TOTAL_CUENTAS = 3;
Cuenta banco[TOTAL_CUENTAS] = {
    {11111, 1234, "Juan Perez", 5000.00},
    {22222, 4321, "Maria Lopez", 12500.50},
    {33333, 1111, "Carlos Ruiz", 300.00}
};

// REQUISITO: Puntero global para saber quien esta logueado
Cuenta* cuenta_actual = nullptr;

// Prototipos
void limpiar_pantalla();
void pausar();
void login();
void mostrar_menu();
void consultar_saldo();
// REQUISITO: Funciones que reciben punteros o modifican estado
void retirar_efectivo();
void depositar_fondos();
void transferir_fondos();
Cuenta* buscar_cuenta(int num_cuenta); // Retorna puntero

int main() {
    bool sistema_activo = true;
    
    while (sistema_activo) {
        try { // REQUISITO: Manejo de Excepciones global
            if (cuenta_actual == nullptr) {
                login();
            } else {
                int opcion;
                limpiar_pantalla();
                cout << "Bienvenido, " << cuenta_actual->titular << endl;
                mostrar_menu();
                
                if (!(cin >> opcion)) {
                    throw runtime_error("Entrada no numerica detectada.");
                }

                limpiar_pantalla();
                switch (opcion) { // REQUISITO: Control de flujo (seleccion)
                    case 1: consultar_saldo(); break;
                    case 2: retirar_efectivo(); break;
                    case 3: depositar_fondos(); break;
                    case 4: transferir_fondos(); break;
                    case 5: 
                        cout << "Cerrando sesion..." << endl;
                        cuenta_actual = nullptr; // Desloguear (puntero a null)
                        break;
                    case 6:
                        cout << "Apagando sistema ATM." << endl;
                        sistema_activo = false;
                        break;
                    default: 
                        cout << "Opcion invalida." << endl;
                }
                if (cuenta_actual != nullptr) pausar();
            }
        }
        catch (const exception& e) {
            // REQUISITO: Manejo de errores
            cin.clear(); cin.ignore(1000, '\n'); // Limpiar buffer
            cout << "\n[ERROR DEL SISTEMA]: " << e.what() << endl;
            pausar();
        }
    }
    return 0;
}

void limpiar_pantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore(); cin.get();
}

void login() {
    limpiar_pantalla();
    int num, nip;
    cout << "=== BANCO DIGITAL ===" << endl;
    cout << "Ingrese Numero de Cuenta: "; cin >> num;
    cout << "Ingrese NIP: "; cin >> nip;

    // Buscamos en el arreglo
    for (int i = 0; i < TOTAL_CUENTAS; i++) {
        if (banco[i].numero_cuenta == num && banco[i].nip == nip) {
            cuenta_actual = &banco[i]; // REQUISITO: Asignar direccion de memoria al puntero
            return;
        }
    }
    throw runtime_error("Credenciales incorrectas.");
}

void mostrar_menu() {
    cout << "--- MENU PRINCIPAL ---" << endl;
    cout << "1. Consultar Saldo" << endl;
    cout << "2. Retirar Efectivo" << endl;
    cout << "3. Depositar Fondos" << endl;
    cout << "4. Transferir a otra cuenta" << endl;
    cout << "5. Cerrar Sesion" << endl;
    cout << "6. Apagar Cajero" << endl;
    cout << "Seleccione una opcion: ";
}

void consultar_saldo() {
    // Acceso a estructura mediante flecha -> porque es puntero
    cout << ">> Cuenta: " << cuenta_actual->numero_cuenta << endl;
    cout << ">> Saldo Disponible: $" << cuenta_actual->saldo << endl;
}

void retirar_efectivo() {
    double monto;
    cout << "Saldo actual: $" << cuenta_actual->saldo << endl;
    cout << "Cantidad a retirar: $"; cin >> monto;

    // Validaciones logicas que lanzan excepciones
    if (monto <= 0) throw runtime_error("El monto debe ser positivo.");
    if (monto > cuenta_actual->saldo) throw runtime_error("Fondos insuficientes.");

    cuenta_actual->saldo -= monto; // Modificacion directa en memoria
    cout << ">> Retiro exitoso. Nuevo saldo: $" << cuenta_actual->saldo << endl;
}

void depositar_fondos() {
    double monto;
    cout << "Cantidad a depositar: $"; cin >> monto;

    if (monto <= 0) throw runtime_error("El monto debe ser positivo.");

    cuenta_actual->saldo += monto;
    cout << ">> Deposito exitoso. Nuevo saldo: $" << cuenta_actual->saldo << endl;
}

// REQUISITO: Funcion auxiliar que retorna puntero
Cuenta* buscar_cuenta(int num_cuenta) {
    for (int i = 0; i < TOTAL_CUENTAS; i++) {
        if (banco[i].numero_cuenta == num_cuenta) {
            return &banco[i]; // Retorna la direccion de la cuenta encontrada
        }
    }
    return nullptr; // Retorna nulo si no existe
}

void transferir_fondos() {
    int num_destino;
    double monto;

    cout << "Ingrese numero de cuenta destino: "; cin >> num_destino;
    
    // Validar que no se transfiera a si mismo
    if (num_destino == cuenta_actual->numero_cuenta) {
        throw runtime_error("No puede transferirse a su propia cuenta.");
    }

    Cuenta* cuenta_destino = buscar_cuenta(num_destino); // Uso de puntero auxiliar

    if (cuenta_destino == nullptr) {
        throw runtime_error("Cuenta destino no existe.");
    }

    cout << "Cuenta detectada: " << cuenta_destino->titular << endl;
    cout << "Ingrese monto a transferir: $"; cin >> monto;

    if (monto <= 0) throw runtime_error("Monto invalido.");
    if (monto > cuenta_actual->saldo) throw runtime_error("Fondos insuficientes.");

    // Operacion de transferencia entre punteros
    cuenta_actual->saldo -= monto;
    cuenta_destino->saldo += monto;

    cout << ">> Transferencia exitosa." << endl;
    cout << ">> Su nuevo saldo: $" << cuenta_actual->saldo << endl;
}