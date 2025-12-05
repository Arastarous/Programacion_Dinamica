# 🐍 Programación Dinámica (UAS)

![Lenguaje: C++](https://img.shields.io/badge/Language-C%2B%2B-blue) ![Status: Finalizado](https://img.shields.io/badge/Status-Finalizado-green) ![Clase: Programación Dinámica](https://img.shields.io/badge/UAS-Software-red)

> Repositorio de proyectos prácticos para la materia de **Programación Dinámica**.
>
> **Enfoque:** Código en C++ moderno, utilizando punteros, manejo de excepciones (`try-catch`), estructuras dinámicas y recursividad.

---

## 📂 Catálogo de Proyectos

### 1. [01_TicTacToe](./01_TicTacToe/) (Gato)
Juego clásico de Tic-Tac-Toe para dos jugadores.
* **Características:** Menú interactivo, marcador persistente por sesión y opción de revancha.
* **Uso:** Ingrese números del `1` al `9` para seleccionar la casilla.

### 2. [02_Conecta4](./02_Conecta4/)
Implementación del juego de estrategia Conecta 4.
* **Características:** Validación de columnas llenas, detección de victoria (horizontal, vertical, diagonal) y limpieza de pantalla.
* **Uso:** Seleccione la columna (`1` - `7`) para soltar la ficha.

### 3. [03_Cajero](./03_Cajero/) (ATM Simulator) 🏧
Sistema de simulación bancaria multi-usuario con manejo de sesiones.
* **Tecnologías:** Arreglo de estructuras, **Punteros** para control de sesión y modificación de saldo, **Excepciones** para validación de fondos.
* **Funciones:** Consulta, Retiro, Depósito y Transferencias entre cuentas.

#### 🔐 Credenciales de Prueba (Login)
Utilice estos datos para iniciar sesión en el sistema:

| Usuario | No. Cuenta | NIP (PIN) | Saldo Inicial |
| :--- | :--- | :--- | :--- |
| **Juan Perez** | `11111` | `1234` | $5,000.00 |
| **Maria Lopez** | `22222` | `4321` | $12,500.50 |
| **Carlos Ruiz** | `33333` | `1111` | $300.00 |

### 4. [04_Inventario](./04_Inventario/)
Sistema CRUD (Crear, Leer, Actualizar) para gestión de productos.
* **Tecnologías:** **Punteros** para edición de memoria, ordenamiento (Burbuja) y búsqueda lineal con excepciones.
* **Funciones:**
    * **Búsqueda:** Por ID o por Nombre.
    * **Ordenamiento:** Por Precio o por Cantidad de stock.
* **Nota:** El inventario inicia vacío. Seleccione la opción `1` para agregar productos antes de intentar ordenar o buscar.

### 5. [05_Calculadora](./05_Calculadora/)
Calculadora científica con validaciones avanzadas.
* **Tecnologías:** **Recursividad** (Factorial), **Sobrecarga de funciones** (Potencia/Cuadrado), Parámetros por omisión y librería `cmath`.
* **Manejo de Errores:** Detecta división por cero y raíces negativas mediante `try-catch`.

---

## 🛠️ Stack Tecnológico

* **Lenguaje:** C++ (Standard 11+)
* **Herramientas:** Git, GitHub
* **Alumno:** [Tu Nombre / Arastarous]