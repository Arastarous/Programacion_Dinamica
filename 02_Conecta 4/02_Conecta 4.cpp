#include <iostream>   // Para entradas (cin) y salidas (cout)
#include <vector>     // Para el tablero (matriz dinamica)
#include <string>     // Para los nombres de jugadores
#include <cstdlib>    // Para system("cls") y system("clear")
#include <limits>     // Para limpiar el buffer de cin (cin.ignore)
#include <clocale>    // Para acentos

// Usamos el espacio de nombres std
using namespace std;

// --- Constantes del Tablero ---
const int FILAS = 6;
const int COLUMNAS = 7;

// --- Variables Globales para Marcador y Nombres ---
// (Valores por defecto si no quieren personalizarlos)
string nombre_j1 = "Jugador 1";
string nombre_j2 = "Jugador 2";
int victorias_j1 = 0;
int victorias_j2 = 0;
int empates = 0;

// --- Prototipos de Funciones ---
void limpiar_pantalla();
void preguntar_nombres();
void inicializar_tablero(vector<vector<char>>& tablero);
void dibujar_tablero(const vector<vector<char>>& tablero);
bool es_columna_valida(int col);
bool es_columna_llena(const vector<vector<char>>& tablero, int col);
bool soltar_ficha(vector<vector<char>>& tablero, int col, char simbolo);
char verificar_ganador(const vector<vector<char>>& tablero);
bool verificar_empate(const vector<vector<char>>& tablero);
void ciclo_de_juego();

// --- Funcion Principal ---
int main() {
    setlocale(LC_ALL, "Spanish"); // Para acentos

    preguntar_nombres(); // Pregunta una vez al inicio

    bool jugar_de_nuevo = false;
    do {
        ciclo_de_juego(); // Ejecuta una partida completa

        cout << "\n¿Quieren jugar otra partida? (s/n): ";
        char respuesta;
        cin >> respuesta;
        jugar_de_nuevo = (respuesta == 's' || respuesta == 'S');

    } while (jugar_de_nuevo);

    cout << "\n¡Gracias por jugar! Puntuacion final:" << endl;
    cout << nombre_j1 << ": " << victorias_j1 << " - " << nombre_j2 << ": " << victorias_j2 << " - Empates: " << empates << endl;

    return 0;
}

// --- Definicion de Funciones ---

/**
 * @brief Limpia la pantalla de la consola.
 */
void limpiar_pantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * @brief Pregunta si desean usar nombres personalizados.
 */
void preguntar_nombres() {
    limpiar_pantalla();
    cout << "--- Bienvenida a Conecta 4 ---" << endl;
    cout << "¿Quieren usar nombres personalizados? (s/n): ";
    char respuesta;
    cin >> respuesta;

    // Limpiamos el buffer de 'cin' antes de usar 'getline'
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (respuesta == 's' || respuesta == 'S') {
        cout << "Nombre del Jugador 1 (X): ";
        getline(cin, nombre_j1);
        cout << "Nombre del Jugador 2 (O): ";
        getline(cin, nombre_j2);
    }
}

/**
 * @brief Llena el tablero con caracteres vacios ('.').
 */
void inicializar_tablero(vector<vector<char>>& tablero) {
    // Usamos el constructor de vector para inicializar
    tablero.assign(FILAS, vector<char>(COLUMNAS, '.'));
}

/**
 * @brief Dibuja el estado actual del tablero y el marcador.
 */
void dibujar_tablero(const vector<vector<char>>& tablero) {
    limpiar_pantalla();

    // Mostrar Marcador
    cout << "--- CONECTA 4 ---" << endl;
    cout << "MARCADOR: " << nombre_j1 << " (X) [" << victorias_j1 << "]  -  ";
    cout << nombre_j2 << " (O) [" << victorias_j2 << "]  -  ";
    cout << "Empates [" << empates << "]" << endl;
    cout << "------------------------------------------" << endl << endl;

    // Imprimir numeros de columnas (1-7)
    cout << "  1   2   3   4   5   6   7  " << endl;
    cout << "-----------------------------" << endl;

    // Imprimir el tablero
    for (int i = 0; i < FILAS; ++i) {
        cout << "| ";
        for (int j = 0; j < COLUMNAS; ++j) {
            cout << tablero[i][j] << " | ";
        }
        cout << endl;
    }
    cout << "-----------------------------" << endl << endl;
}

/**
 * @brief Valida si el numero de columna esta en el rango 1-7.
 */
bool es_columna_valida(int col) {
    return col >= 1 && col <= 7;
}

/**
 * @brief Revisa si la columna esta llena (mirando la celda superior).
 */
bool es_columna_llena(const vector<vector<char>>& tablero, int col) {
    // col ya esta 0-indexado (0-6)
    return tablero[0][col] != '.';
}

/**
 * @brief "Suelta" la ficha en la columna elegida.
 * @return true si la ficha se coloco, false si no.
 */
bool soltar_ficha(vector<vector<char>>& tablero, int col, char simbolo) {
    // Itera de ABAJO hacia ARRIBA
    for (int i = FILAS - 1; i >= 0; --i) {
        if (tablero[i][col] == '.') {
            tablero[i][col] = simbolo; // Coloca la ficha
            return true; // Exito
        }
    }
    return false; // Esto no deberia pasar si 'es_columna_llena' se usa bien
}

/**
 * @brief Revisa las 4 direcciones (horizontal, vertical, 2 diagonales).
 * @return 'X' o 'O' si hay ganador, '.' si no hay.
 */
char verificar_ganador(const vector<vector<char>>& tablero) {
    // Itera por cada celda como punto de inicio
    for (int r = 0; r < FILAS; ++r) {
        for (int c = 0; c < COLUMNAS; ++c) {
            char simbolo = tablero[r][c];
            if (simbolo == '.') continue; // Ignora celdas vacias

            // 1. Revision Horizontal (->)
            if (c + 3 < COLUMNAS &&
                simbolo == tablero[r][c+1] &&
                simbolo == tablero[r][c+2] &&
                simbolo == tablero[r][c+3]) {
                return simbolo;
            }

            // 2. Revision Vertical (v)
            if (r + 3 < FILAS &&
                simbolo == tablero[r+1][c] &&
                simbolo == tablero[r+2][c] &&
                simbolo == tablero[r+3][c]) {
                return simbolo;
            }

            // 3. Revision Diagonal Descendente (\)
            if (r + 3 < FILAS && c + 3 < COLUMNAS &&
                simbolo == tablero[r+1][c+1] &&
                simbolo == tablero[r+2][c+2] &&
                simbolo == tablero[r+3][c+3]) {
                return simbolo;
            }

            // 4. Revision Diagonal Ascendente (/)
            if (r - 3 >= 0 && c + 3 < COLUMNAS &&
                simbolo == tablero[r-1][c+1] &&
                simbolo == tablero[r-2][c+2] &&
                simbolo == tablero[r-3][c+3]) {
                return simbolo;
            }
        }
    }
    return '.'; // No hay ganador
}

/**
 * @brief Revisa si el tablero esta lleno (empate).
 */
bool verificar_empate(const vector<vector<char>>& tablero) {
    // Solo necesitamos revisar la fila superior (fila 0)
    for (int c = 0; c < COLUMNAS; ++c) {
        if (tablero[0][c] == '.') {
            return false; // Hay espacio, no es empate
        }
    }
    return true; // Fila superior llena, es empate
}

/**
 * @brief Contiene la logica de una partida individual.
 */
void ciclo_de_juego() {
    vector<vector<char>> tablero;
    inicializar_tablero(tablero);

    char turno_actual = 'X';
    bool juego_terminado = false;

    while (!juego_terminado) {
        dibujar_tablero(tablero);

        string nombre_jugador_actual = (turno_actual == 'X') ? nombre_j1 : nombre_j2;
        cout << "Turno de: " << nombre_jugador_actual << " (" << turno_actual << ")" << endl;
        cout << "Elige una columna (1-7): ";

        int col_elegida_raw;
        int col_elegida_idx; // 0-indexada

        // Bucle de validacion de entrada
        while (true) {
            if (!(cin >> col_elegida_raw)) {
                // No es un numero
                cout << "Entrada invalida. Ingresa un numero (1-7): ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else if (!es_columna_valida(col_elegida_raw)) {
                // Numero fuera de rango
                cout << "Columna fuera de rango. Debe ser entre 1 y 7: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                col_elegida_idx = col_elegida_raw - 1; // Convertir a 0-index
                if (es_columna_llena(tablero, col_elegida_idx)) {
                    // Columna llena
                    cout << "Esa columna esta llena. Elige otra: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else {
                    break; // ¡Entrada valida!
                }
            }
        } // Fin del bucle de validacion

        // Realizar la jugada
        soltar_ficha(tablero, col_elegida_idx, turno_actual);

        // --- Verificar estado del juego ---
        char ganador = verificar_ganador(tablero);
        bool empate = verificar_empate(tablero);

        if (ganador != '.') {
            dibujar_tablero(tablero); // Dibujar el tablero final
            if (ganador == 'X') {
                cout << "¡FELICIDADES, " << nombre_j1 << "! Has ganado." << endl;
                victorias_j1++;
            } else {
                cout << "¡FELICIDADES, " << nombre_j2 << "! Has ganado." << endl;
                victorias_j2++;
            }
            juego_terminado = true;
        } else if (empate) {
            dibujar_tablero(tablero);
            cout << "¡EMPATE! El tablero esta lleno." << endl;
            empates++;
            juego_terminado = true;
        } else {
            // Cambiar de turno
            turno_actual = (turno_actual == 'X') ? 'O' : 'X';
        }
    } // Fin del bucle de la partida
}
