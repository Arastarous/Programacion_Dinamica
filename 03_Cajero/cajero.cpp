#include <iostream>
using namespace std;

// Variables Globales (Simulando base de datos del banco)
double saldo_actual = 1000.00; // Saldo inicial de prueba
const int PIN_CORRECTO = 1234;

// Prototipos de funciones
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
                case 4: transferir_fondos(); break;
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
    cout << "4. Transferir" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

// Funciones vacias por ahora (Se implementaran mañana)
void consultar_saldo() {
    cout << "Funcion consultar_saldo pendiente..." << endl;
}
void retirar_efectivo() {
    cout << "Desarrollar logica de retiro aqui..." << endl;
}
void depositar_fondos() {
    cout << "Desarrollar logica de deposito aqui..." << endl;
}
void transferir_fondos() {
    cout << "Desarrollar logica de transferencia aqui..." << endl;
}