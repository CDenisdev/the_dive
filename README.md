# 🌀 Laberinto Maestro en C++

## 📖 Descripción
Este proyecto genera y resuelve **laberintos aleatorios** en C++.  
Cada vez que se ejecuta, se crea un laberinto distinto con una **entrada** y una **salida** siempre conectadas.  
El programa también resuelve automáticamente el laberinto mostrando el **camino más corto**.

---

## ⚙️ Funcionalidades
- Generación de un **laberinto aleatorio y resoluble** usando **DFS con backtracking**.  
- Resolución automática usando **BFS**, que encuentra el **camino más corto** entre entrada y salida.  
- Tamaño configurable:  
  - Por defecto 10x10.  
  - El usuario puede ingresar el número de filas y columnas al iniciar el programa.  
- Visualización en consola con caracteres ASCII:  
  - `#` → muro  
  - `*` → camino libre  
  - `S` → entrada  
  - `E` → salida  
  - `o` → camino más corto encontrado  

---

## 🖥️ Ejemplo de ejecución

# # # # # # # # #
S o o # # # # # #
# # o # # # # # #
# # o o o # # # #
# # # # o # # # #
# # # # o # # # #
# # # # o o o o o E
# # # # # # # # #


---

## 🛠️ Tecnologías usadas
- Lenguaje: **C++**  
- Librerías estándar:  
  - `<vector>` para la matriz dinámica  
  - `<queue>` para BFS  
  - `<algorithm>` y `<random>` para aleatoriedad en DFS  

---

## 📚 Algoritmos
- **DFS (Depth First Search) con backtracking**  
  Usado para **tallar** el laberinto desde la entrada, creando caminos aleatorios.  

- **BFS (Breadth First Search)**  
  Usado para **resolver** el laberinto, encontrando siempre el camino más corto de `S` a `E`.

---

## 🚀 Cómo compilar y ejecutar
1. Compilar con g++:
   ```bash
   g++ laberinto.cpp -o laberinto

## Ejecutar 
./laberinto

