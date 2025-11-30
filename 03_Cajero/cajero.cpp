#include <iostream>
#include <cstdlib> // Para system("cls")
using namespace std;

// Variables Globales
double saldo_actual = 1000.00;
const int PIN_CORRECTO = 1234;

// Prototipos
void limpiar_pantalla();
void pausar();
void mostrar_menu();
void consultar_saldo();
void retirar_efectivo();
void depositar_fondos();
void transferir_fondos();

int main() {
    int pin_ingresado;
    
    // Configuracion regional basica
    setlocale(LC_ALL, ""); 

    cout << "=== CAJERO AUTOMATICO ===" << endl;
    cout << "Ingrese su PIN: ";
    cin >> pin_ingresado;

    if (pin_ingresado == PIN_CORRECTO) {
        int opcion = 0;
        do {
            limpiar_pantalla();
            mostrar_menu();
            cin >> opcion;

            limpiar_pantalla(); // Limpiar antes de mostrar la accion
            switch(opcion) {
                case 1: consultar_saldo(); break;
                case 2: retirar_efectivo(); break;
                case 3: depositar_fondos(); break;
                case 4: transferir_fondos(); break;
                case 5: cout << "Gracias por usar nuestro banco." << endl; break;
                default: cout << "Opcion no valida." << endl;
            }
            if (opcion != 5) pausar();

        } while (opcion != 5);
    } else {
        cout << "PIN incorrecto. Acceso denegado." << endl;
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
    cin.ignore();
    cin.get();
}

void mostrar_menu() {
    cout << "--- MENU PRINCIPAL ---" << endl;
    cout << "1. Consultar Saldo" << endl;
    cout << "2. Retirar Efectivo" << endl;
    cout << "3. Depositar Fondos" << endl;
    cout << "4. Transferir Fondos" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

void consultar_saldo() {
    cout << ">> Su saldo actual es: $" << saldo_actual << endl;
}

void retirar_efectivo() {
    double monto;
    cout << "Saldo disponible: $" << saldo_actual << endl;
    cout << "Ingrese cantidad a retirar: $";
    cin >> monto;

    if (monto > saldo_actual) {
        cout << "[!] Fondos insuficientes." << endl;
    } else if (monto <= 0) {
        cout << "[!] Cantidad no valida." << endl;
    } else {
        saldo_actual -= monto;
        cout << ">> Retiro exitoso. Nuevo saldo: $" << saldo_actual << endl;
    }
}

void depositar_fondos() {
    double monto;
    cout << "Ingrese cantidad a depositar: $";
    cin >> monto;

    if (monto > 0) {
        saldo_actual += monto;
        cout << ">> Deposito exitoso. Nuevo saldo: $" << saldo_actual << endl;
    } else {
        cout << "[!] Cantidad no valida." << endl;
    }
}

void transferir_fondos() {
    int cuenta_destino;
    double monto;
    
    cout << "Ingrese cuenta destino (5 digitos): ";
    cin >> cuenta_destino;
    cout << "Ingrese monto a transferir: $";
    cin >> monto;

    if (monto > saldo_actual) {
        cout << "[!] Fondos insuficientes para la transferencia." << endl;
    } else if (monto <= 0) {
        cout << "[!] Monto invalido." << endl;
    } else {
        saldo_actual -= monto;
        cout << ">> Transferencia de $" << monto << " a la cuenta " << cuenta_destino << " exitosa." << endl;
        cout << ">> Saldo restante: $" << saldo_actual << endl;
    }
}