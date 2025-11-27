#include <iostream>   // Para entradas (cin) y salidas (cout)
#include <vector>     // Para usar vectores (mas facil que arreglos C)
#include <string>     // Para usar la clase string (nombres de jugadores)
#include <cstdlib>    // Para system("cls") y system("clear")
#include <limits>     // Para limpiar el buffer de cin (cin.ignore)
#include <clocale>    // Para configurar los acentos en español

// Usamos el espacio de nombres std para no escribir std::cout
using namespace std;

// --- Variables Globales para el Marcador y Nombres ---
// Las definimos aqui para que persistan entre partidas
string nombre_j1 = "";
string nombre_j2 = "";
int victorias_j1 = 0;
int victorias_j2 = 0;
int empates = 0;

// --- Prototipos de Funciones (Declaraciones) ---
// Le decimos al compilador "estas funciones existen"
void limpiar_pantalla();
void mostrar_bienvenida();
void mostrar_ayuda();
void inicializar_tablero(vector<vector<char>>& tablero);
void dibujar_tablero(const vector<vector<char>>& tablero);
bool es_casilla_valida(const vector<vector<char>>& tablero, int seleccion);
void traducir_seleccion_a_coordenadas(int seleccion, int& fila, int& col);
char verificar_ganador(const vector<vector<char>>& tablero);
bool tablero_lleno(const vector<vector<char>>& tablero);
void ciclo_de_juego();

// --- Función Principal (main) ---
// Es el punto de entrada del programa
int main() {
    // Configuramos la consola para mostrar acentos
    setlocale(LC_ALL, "Spanish");

    // Variables para el menu
    int opcion_elegida = 0;
    bool salir_del_programa = false;

    mostrar_bienvenida();

    // Bucle principal del menu
    do {
        // Mostramos el menu
        cout << "\n--- MENU PRINCIPAL ---" << endl;
        cout << "1. Iniciar Nueva Partida" << endl;
        cout << "2. Como Jugar (Ayuda)" << endl;
        cout << "3. Salir del Juego" << endl;
        cout << "Elige una opcion: ";

        // Validacion de entrada numerica simple
        while (!(cin >> opcion_elegida)) {
            cout << "Entrada invalida. Por favor, ingresa un numero (1-3): ";
            cin.clear(); // Limpia el error de cin
            // Ignora el resto de la linea incorrecta
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }

        switch (opcion_elegida) {
            case 1:
                ciclo_de_juego(); // Inicia el juego
                break;
            case 2:
                mostrar_ayuda();
                break;
            case 3:
                cout << "\n¡Gracias por jugar! Adios." << endl;
                salir_del_programa = true;
                break;
            default:
                cout << "\nOpcion no valida. Intentalo de nuevo." << endl;
        }

    } while (!salir_del_programa);

    return 0; // Termina el programa
}

// --- Definición de Funciones ---

/**
 * @brief Limpia la pantalla de la consola.
 */
void limpiar_pantalla() {
    // Comando para Windows ("cls") o Linux/Mac ("clear")
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * @brief Muestra la pantalla de bienvenida con arte ASCII.
 */
void mostrar_bienvenida() {
    limpiar_pantalla();
    cout << "========================================" << endl;
    cout << "|        ¡LA LEYENDA COMIENZA!         |" << endl;
    cout << "|    BIENVENIDO AL JUEGO DEL GATO      |" << endl;
    cout << "|         (Tic-Tac-Toe) v1.0           |" << endl;
    cout << "|                                      |" << endl;
    cout << "|           ###   ###   ###            |" << endl;
    cout << "|            #     #     #             |" << endl;
    cout << "|           ###   ###   ###            |" << endl;
    cout << "|                                      |" << endl;
    cout << "|            #     #     #             |" << endl;
    cout << "|           ###   ###   ###            |" << endl;
    cout << "|        ¡ACCIÓN  ESTRATÉGICA!         |" << endl;
    cout << "========================================" << endl;
}

/**
 * @brief Muestra las instrucciones del juego.
 */
void mostrar_ayuda() {
    limpiar_pantalla();
    cout << "--- Como Jugar ---" << endl;
    cout << "1. El objetivo es simple: consigue 3 de tus simbolos en linea." << endl;
    cout << "   (Horizontal, Vertical o Diagonal)." << endl;
    cout << "2. El Jugador 1 usara 'X' y el Jugador 2 usara 'O'." << endl;
    cout << "3. Para hacer tu movimiento, mira el tablero:" << endl;
    cout << "\n     1 | 2 | 3 " << endl;
    cout << "    ---+---+---" << endl;
    cout << "     4 | 5 | 6 " << endl;
    cout << "    ---+---+---" << endl;
    cout << "     7 | 8 | 9 " << endl;
    cout << "\n4. Cuando sea tu turno, simplemente ingresa el numero" << endl;
    cout << "   de la casilla donde quieres jugar." << endl;
    cout << "\nPresiona 'Enter' para volver al menu..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia buffer
    cin.get(); // Espera a que el usuario presione Enter
    limpiar_pantalla();
}

/**
 * @brief Prepara el tablero con casillas vacias.
 * @param tablero El tablero 2D (pasado por referencia).
 */
void inicializar_tablero(vector<vector<char>>& tablero) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            tablero[i][j] = ' '; // ' ' representa una casilla vacia
        }
    }
}

/**
 * @brief Dibuja el estado actual del tablero y el marcador.
 * @param tablero El tablero 2D (pasado por constante).
 */
void dibujar_tablero(const vector<vector<char>>& tablero) {
    limpiar_pantalla();
    
    // Mostrar Marcador
    cout << "--- JUEGO DEL GATO ---" << endl;
    cout << "MARCADOR: " << nombre_j1 << " (X) [" << victorias_j1 << "]  -  ";
    cout << nombre_j2 << " (O) [" << victorias_j2 << "]  -  ";
    cout << "Empates [" << empates << "]" << endl;
    cout << "------------------------------------------" << endl << endl;

    // Logica para mostrar numeros (1-9) en casillas vacias
    char contador_casilla_numerica = '1';
    
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            char contenido = tablero[i][j];
            if (contenido == ' ') {
                // Si esta vacia, muestra el numero guia
                cout << " " << contador_casilla_numerica << " ";
            } else {
                // Si esta ocupada ('X' u 'O'), muestra el simbolo
                cout << " " << contenido << " ";
            }

            if (j < 2) {
                cout << "|"; // Separador vertical
            }
            contador_casilla_numerica++; // Incrementa el numero guia
        }
        cout << endl; // Siguiente fila

        if (i < 2) {
            cout << "----+---+----" << endl; // Separador horizontal
        }
    }
    cout << endl; // Espacio final
}

/**
 * @brief Valida si la seleccion (1-9) es jugable.
 * @return true si la casilla esta libre y el numero es valido, false si no.
 */
bool es_casilla_valida(const vector<vector<char>>& tablero, int seleccion) {
    if (seleccion < 1 || seleccion > 9) {
        return false; // Fuera de rango
    }

    int fila, col;
    traducir_seleccion_a_coordenadas(seleccion, fila, col);

    // Revisa si la casilla esta vacia (' ')
    return tablero[fila][col] == ' ';
}

/**
 * @brief Convierte el numero 1-9 a coordenadas de matriz [fila][col].
 */
void traducir_seleccion_a_coordenadas(int seleccion, int& fila, int& col) {
    // Matematicas para la conversion (1-indexado a 0-indexado)
    fila = (seleccion - 1) / 3;
    col = (seleccion - 1) % 3;
}

/**
 * @brief Revisa las 8 posibles condiciones de victoria.
 * @return 'X' si J1 gano, 'O' si J2 gano, ' ' si nadie ha ganado.
 */
char verificar_ganador(const vector<vector<char>>& tablero) {
    // Verificar filas
    for (int i = 0; i < 3; ++i) {
        if (tablero[i][0] != ' ' && tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2]) {
            return tablero[i][0]; // Retorna 'X' o 'O'
        }
    }
    // Verificar columnas
    for (int j = 0; j < 3; ++j) {
        if (tablero[0][j] != ' ' && tablero[0][j] == tablero[1][j] && tablero[1][j] == tablero[2][j]) {
            return tablero[0][j];
        }
    }
    // Verificar diagonal principal (izquierda-arriba a derecha-abajo)
    if (tablero[0][0] != ' ' && tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]) {
        return tablero[0][0];
    }
    // Verificar diagonal secundaria (derecha-arriba a izquierda-abajo)
    if (tablero[0][2] != ' ' && tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0]) {
        return tablero[0][2];
    }

    return ' '; // No hay ganador
}

/**
 * @brief Verifica si el tablero esta lleno (para detectar empates).
 * @return true si no quedan casillas ' ', false si aun hay espacio.
 */
bool tablero_lleno(const vector<vector<char>>& tablero) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (tablero[i][j] == ' ') {
                return false; // Encontro una casilla vacia, no esta lleno
            }
        }
    }
    return true; // No encontro casillas vacias, esta lleno
}

/**
 * @brief Logica principal del juego, incluye el bucle para "jugar de nuevo".
 */
void ciclo_de_juego() {
    
    // Si es la primera vez que juegan en esta sesion, pedir nombres
    if (nombre_j1 == "") {
        limpiar_pantalla();
        cout << "¡Vamos a Jugar!" << endl;
        cout << "Ingresa el nombre del Jugador 1 (X): ";
        // cin.ignore() para limpiar el 'Enter' que quedo del menu
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        getline(cin, nombre_j1);

        cout << "Ingresa el nombre del Jugador 2 (O): ";
        getline(cin, nombre_j2);
    }

    // Bucle para "Jugar de Nuevo"
    bool jugar_de_nuevo = false;
    do {
        // --- Preparacion de la Partida ---
        vector<vector<char>> tablero(3, vector<char>(3));
        inicializar_tablero(tablero);
        
        char turno_actual = 'X'; // Jugador 1 ('X') siempre empieza
        bool juego_terminado = false;

        // --- Bucle de Turnos ---
        while (!juego_terminado) {
            dibujar_tablero(tablero);

            // Determinar nombre del jugador actual
            string nombre_jugador_actual = (turno_actual == 'X') ? nombre_j1 : nombre_j2;
            cout << "Turno de: " << nombre_jugador_actual << " (" << turno_actual << ")" << endl;
            cout << "Elige una casilla (1-9): ";

            int seleccion = 0;
            // Validacion de entrada (que sea numero Y que sea casilla valida)
            while (true) {
                if (!(cin >> seleccion) || !es_casilla_valida(tablero, seleccion)) {
                    cout << "Jugada invalida. Elige un numero (1-9) de una casilla vacia: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else {
                    break; // Entrada valida, salimos del bucle de validacion
                }
            }

            // Realizar la jugada
            int fila, col;
            traducir_seleccion_a_coordenadas(seleccion, fila, col);
            tablero[fila][col] = turno_actual;

            // --- Verificar fin del juego ---
            char ganador = verificar_ganador(tablero);
            bool lleno = tablero_lleno(tablero);

            if (ganador == 'X') {
                dibujar_tablero(tablero);
                cout << "¡FELICIDADES, " << nombre_j1 << "! Has ganado." << endl;
                victorias_j1++;
                juego_terminado = true;
            } else if (ganador == 'O') {
                dibujar_tablero(tablero);
                cout << "¡FELICIDADES, " << nombre_j2 << "! Has ganado." << endl;
                victorias_j2++;
                juego_terminado = true;
            } else if (lleno) {
                dibujar_tablero(tablero);
                cout << "¡Es un EMPATE! No hay mas movimientos." << endl;
                empates++;
                juego_terminado = true;
            } else {
                // Si el juego no ha terminado, cambiar de turno
                turno_actual = (turno_actual == 'X') ? 'O' : 'X';
            }
        } // Fin del bucle de turnos

        // --- Preguntar para Jugar de Nuevo ---
        cout << "\n¿Quieren jugar la revancha? (s/n): ";
        char respuesta_revancha;
        cin >> respuesta_revancha;
        
        jugar_de_nuevo = (respuesta_revancha == 's' || respuesta_revancha == 'S');
        limpiar_pantalla(); // Limpia antes de volver al menu o de empezar la nueva partida

    } while (jugar_de_nuevo);
}