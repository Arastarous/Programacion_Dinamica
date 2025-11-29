#include <iostream>
using namespace std;

// Variables Globales
double saldo_actual = 1000.00;
const int PIN_CORRECTO = 1234;

// Prototipos
void mostrar_menu();
void consultar_saldo();
void retirar_efectivo();
void depositar_fondos();
void transferir_fondos();

int main() {
    int pin_ingresado;
    cout << "Bienvenido al Cajero Automatico" << endl;
    cout << "Por favor, ingrese su PIN: ";
    cin >> pin_ingresado;

    if (pin_ingresado == PIN_CORRECTO) {
        int opcion = 0;
        do {
            mostrar_menu();
            cin >> opcion;

            switch(opcion) {
                case 1: consultar_saldo(); break;
                case 2: retirar_efectivo(); break;
                case 3: depositar_fondos(); break;
                case 4: transferir_fondos(); break; // Aún pendiente
                case 5: cout << "Saliendo... Gracias por usar nuestro banco." << endl; break;
                default: cout << "Opcion no valida." << endl;
            }
        } while (opcion != 5);
    } else {
        cout << "PIN incorrecto. Acceso denegado." << endl;
    }
    return 0;
}

void mostrar_menu() {
    cout << "\n--- MENU PRINCIPAL ---" << endl;
    cout << "1. Consultar Saldo" << endl;
    cout << "2. Retirar Efectivo" << endl;
    cout << "3. Depositar Fondos" << endl;
    cout << "4. Transferir (En mantenimiento)" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

void consultar_saldo() {
    cout << "Su saldo actual es: $" << saldo_actual << endl;
}

void retirar_efectivo() {
    double monto;
    cout << "Ingrese cantidad a retirar: $";
    cin >> monto;

    if (monto > saldo_actual) {
        cout << "Fondos insuficientes." << endl;
    } else if (monto <= 0) {
        cout << "Cantidad no valida." << endl;
    } else {
        saldo_actual -= monto;
        cout << "Retiro exitoso. Nuevo saldo: $" << saldo_actual << endl;
    }
}

void depositar_fondos() {
    double monto;
    cout << "Ingrese cantidad a depositar: $";
    cin >> monto;

    if (monto > 0) {
        saldo_actual += monto;
        cout << "Deposito exitoso. Nuevo saldo: $" << saldo_actual << endl;
    } else {
        cout << "Cantidad no valida." << endl;
    }
}

void transferir_fondos() {
    cout << "Funcion en desarrollo... intente mas tarde." << endl;
}