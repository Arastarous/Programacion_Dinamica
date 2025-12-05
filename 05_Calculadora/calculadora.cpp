#include <iostream>
#include <cmath>
#include <stdexcept> // Necesario para las excepciones (std::runtime_error)

using namespace std;

// --- PROTOTIPOS ---

// 1. Sobrecarga de funciones (Dos funciones con el mismo nombre pero distintos parametros)
double potencia(double base, double exponente); // Potencia normal
double potencia(double base);                   // Sobrecarga: Eleva al cuadrado (base^2)

// 2. Recursividad (Factorial se llama a si mismo)
unsigned long long factorial_recursivo(int n);

// 3. Parametros por omision (El segundo parametro es opcional, si no se pone, usa "Resultado")
void mostrar_resultado(double valor, string etiqueta = "Resultado: ");

// Funciones auxiliares
void menu_principal();
void ejecutar_operacion(int opcion);

// --- MAIN ---
int main() {
    int opcion;
    do {
        menu_principal();
        if (!(cin >> opcion)) { // Validacion basica de entrada
            cout << "Entrada invalida." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (opcion != 9) {
            ejecutar_operacion(opcion);
        } else {
            cout << "Cerrando aplicacion..." << endl;
        }

    } while (opcion != 9);

    return 0;
}

// --- IMPLEMENTACION DE FUNCIONES ---

void menu_principal() {
    cout << "\n--- CALCULADORA C++ (REQUISITOS AVANZADOS) ---" << endl;
    cout << "1. Suma" << endl;
    cout << "2. Resta" << endl;
    cout << "3. Multiplicacion" << endl;
    cout << "4. Division (Manejo de Excepciones)" << endl;
    cout << "5. Factorial (Recursivo)" << endl;
    cout << "6. Potencia General (x^y)" << endl;
    cout << "7. Cuadrado de un numero (Sobrecarga)" << endl;
    cout << "8. Raiz Cuadrada (Manejo de Excepciones)" << endl;
    cout << "9. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

// Uso de Parametros por omision
void mostrar_resultado(double valor, string etiqueta) {
    cout << ">> " << etiqueta << " " << valor << endl;
}

// Uso de Recursividad
unsigned long long factorial_recursivo(int n) {
    if (n < 0) throw runtime_error("No existe factorial de numero negativo.");
    if (n == 0 || n == 1) return 1; // Caso base
    return n * factorial_recursivo(n - 1); // Llamada recursiva
}

// Uso de Sobrecarga (Version 1: Dos argumentos)
double potencia(double base, double exponente) {
    return pow(base, exponente);
}

// Uso de Sobrecarga (Version 2: Un argumento)
double potencia(double base) {
    return pow(base, 2); // Por defecto eleva al cuadrado
}

void ejecutar_operacion(int opcion) {
    double a, b;
    
    // Bloque TRY-CATCH para Manejo de Excepciones
    try {
        switch(opcion) {
            case 1: // Suma
                cout << "Ingrese dos numeros: "; cin >> a >> b;
                mostrar_resultado(a + b); // Usa parametro por omision
                break;
            case 2: // Resta
                cout << "Ingrese dos numeros: "; cin >> a >> b;
                mostrar_resultado(a - b);
                break;
            case 3: // Multiplicacion
                cout << "Ingrese dos numeros: "; cin >> a >> b;
                mostrar_resultado(a * b);
                break;
            case 4: // Division
                cout << "Ingrese dividendo y divisor: "; cin >> a >> b;
                if (b == 0) {
                    // Lanzamos excepcion manual
                    throw runtime_error("Error matematico: Division por cero.");
                }
                mostrar_resultado(a / b);
                break;
            case 5: // Factorial
                int n;
                cout << "Ingrese un entero positivo: "; cin >> n;
                // La funcion recursiva puede lanzar excepcion si es negativo
                mostrar_resultado(factorial_recursivo(n), "Factorial:"); // Parametro explicito
                break;
            case 6: // Potencia General
                cout << "Ingrese base y exponente: "; cin >> a >> b;
                mostrar_resultado(potencia(a, b), "Potencia:"); // Llama a version 1
                break;
            case 7: // Cuadrado (Sobrecarga)
                cout << "Ingrese numero a elevar al cuadrado: "; cin >> a;
                mostrar_resultado(potencia(a), "Cuadrado:"); // Llama a version 2
                break;
            case 8: // Raiz
                cout << "Ingrese numero: "; cin >> a;
                if (a < 0) throw runtime_error("Error: Raiz cuadrada de numero negativo.");
                mostrar_resultado(sqrt(a), "Raiz:");
                break;
            default:
                cout << "Opcion no reconocida." << endl;
        }
    } 
    catch (const exception& e) {
        // Captura cualquier error lanzado dentro del bloque try
        cout << "\n[EXCEPCION DETECTADA]: " << e.what() << endl;
    }
}