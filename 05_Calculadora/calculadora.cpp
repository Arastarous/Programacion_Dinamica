#include <iostream>
#include <cmath> // Necesaria para pow() y sqrt()
using namespace std;

// Prototipos
void sumar();
void restar();
void multiplicar();
void dividir();
void calcular_factorial();
void potencia(); 
void raiz_cuadrada();

int main() {
    int opcion;
    do {
        // Menu simple
        cout << "\n--- CALCULADORA CIENTIFICA v2.0 ---" << endl;
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
            case 8: cout << "Cerrando aplicacion..." << endl; break;
            default: cout << "Opcion no reconocida." << endl;
        }
    } while (opcion != 8);

    return 0;
}

void sumar() {
    double a, b;
    cout << "Ingrese primer numero: "; cin >> a;
    cout << "Ingrese segundo numero: "; cin >> b;
    cout << "Resultado: " << (a + b) << endl;
}

void restar() {
    double a, b;
    cout << "Ingrese primer numero: "; cin >> a;
    cout << "Ingrese segundo numero: "; cin >> b;
    cout << "Resultado: " << (a - b) << endl;
}

void multiplicar() {
    double a, b;
    cout << "Ingrese primer numero: "; cin >> a;
    cout << "Ingrese segundo numero: "; cin >> b;
    cout << "Resultado: " << (a * b) << endl;
}

void dividir() {
    double a, b;
    cout << "Ingrese dividendo: "; cin >> a;
    cout << "Ingrese divisor: "; cin >> b;
    if (b != 0)
        cout << "Resultado: " << (a / b) << endl;
    else
        cout << "Error: Division por cero indefinida." << endl;
}

void calcular_factorial() {
    int n;
    long long factorial = 1; 
    cout << "Ingrese un numero entero positivo: "; 
    cin >> n;

    if (n < 0) {
        cout << "Error: No existe factorial de negativos." << endl;
    } else {
        for(int i = 1; i <= n; ++i) {
            factorial *= i;
        }
        cout << "El factorial de " << n << " es: " << factorial << endl;
    }
}

// Funciones Avanzadas (Implementadas hoy Sabado)
void potencia() {
    double base, exp;
    cout << "Ingrese base: "; cin >> base;
    cout << "Ingrese exponente: "; cin >> exp;
    cout << "Resultado: " << pow(base, exp) << endl;
}

void raiz_cuadrada() {
    double n;
    cout << "Ingrese numero: "; cin >> n;
    if (n >= 0) {
        cout << "Raiz cuadrada: " << sqrt(n) << endl;
    } else {
        cout << "Error: No se puede calcular raiz de negativo en reales." << endl;
    }
}