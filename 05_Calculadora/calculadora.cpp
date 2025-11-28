#include <iostream>
using namespace std;

// Prototipos de operaciones
void sumar();
void restar();
void multiplicar();
void dividir();
void calcular_factorial();
void potencia(); // Avanzado
void raiz_cuadrada(); // Avanzado

int main() {
    int opcion;
    do {
        cout << "\n--- CALCULADORA CIENTIFICA BASICA ---" << endl;
        cout << "1. Suma" << endl;
        cout << "2. Resta" << endl;
        cout << "3. Multiplicacion" << endl;
        cout << "4. Division" << endl;
        cout << "5. Factorial (!)" << endl;
        cout << "6. Potencia (^)" << endl;
        cout << "7. Raiz Cuadrada" << endl;
        cout << "8. Salir" << endl;
        cout << "Elige una operacion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: sumar(); break;
            case 2: restar(); break;
            case 3: multiplicar(); break;
            case 4: dividir(); break;
            case 5: calcular_factorial(); break;
            case 6: potencia(); break;
            case 7: raiz_cuadrada(); break;
            case 8: cout << "Adios." << endl; break;
            default: cout << "Opcion no reconocida." << endl;
        }
    } while (opcion != 8);

    return 0;
}

// Implementaciones vacias (Placeholders)
void sumar() { cout << "Pendiente..." << endl; }
void restar() { cout << "Pendiente..." << endl; }
void multiplicar() { cout << "Pendiente..." << endl; }
void dividir() { cout << "Pendiente..." << endl; }
void calcular_factorial() { cout << "Pendiente logica de bucles..." << endl; }
void potencia() { cout << "Pendiente..." << endl; }
void raiz_cuadrada() { cout << "Pendiente..." << endl; }