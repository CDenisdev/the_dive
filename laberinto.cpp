#include <iostream>      // Entrada y salida
#include <vector>        // Vectores
#include <algorithm>     // shuffle
#include <random>        // números aleatorios
#include <utility>       // pair
#include <queue>         // cola para BFS

using namespace std;

class Laberinto {
public:
    int filas, columnas;           // Filas y columnas
    int altura, ancho;             // Altura y ancho del display
    vector<vector<char>> display;  // Mapa ASCII del laberinto

    // Constructor
    Laberinto(int filas_input, int columnas_input) : filas(filas_input), columnas(columnas_input) {
        altura = 2 * filas + 1;
        ancho = 2 * columnas + 1;
        display.assign(altura, vector<char>(ancho, '#'));
    }

    // Función DFS para tallar caminos aleatorios
    void tallar_camino() {
        const int delta_fila[4] = {-1, 0, 1, 0};
        const int delta_columna[4] = {0, 1, 0, -1};

        vector<pair<int, int>> pila;
        vector<vector<bool>> visitado(filas, vector<bool>(columnas, false));

        int fila = 0, columna = 0;
        visitado[fila][columna] = true;
        display[2*fila+1][2*columna+1] = '*';
        pila.push_back({fila, columna});

        random_device rd;
        mt19937 g(rd());

        while (!pila.empty()) {
            auto [fila_actual, columna_actual] = pila.back();

            vector<int> direcciones = {0, 1, 2, 3};
            shuffle(direcciones.begin(), direcciones.end(), g);

            bool se_movio = false;
            for (int i = 0; i < 4; ++i) {
                int nueva_fila = fila_actual + delta_fila[direcciones[i]];
                int nueva_columna = columna_actual + delta_columna[direcciones[i]];

                if (nueva_fila >= 0 && nueva_fila < filas && nueva_columna >= 0 && nueva_columna < columnas && !visitado[nueva_fila][nueva_columna]) {
                    visitado[nueva_fila][nueva_columna] = true;

                    // Marcar celda vecina
                    display[2*nueva_fila+1][2*nueva_columna+1] = '*';

                    // Abrir muro entre celdas
                    int muro_fila = 2*fila_actual + 1 + delta_fila[direcciones[i]];
                    int muro_columna = 2*columna_actual + 1 + delta_columna[direcciones[i]];
                    display[muro_fila][muro_columna] = '*';

                    pila.push_back({nueva_fila, nueva_columna});
                    se_movio = true;
                    break; // Moverse a nueva celda
                }
            }

            if (!se_movio)
                pila.pop_back();
        }

        // Marcar salida
        display[2*(filas-1)+1][2*(columnas-1)+1] = '*';
    }

    // BFS para resolver el laberinto
    bool resolver() {
        vector<vector<bool>> visitado(altura, vector<bool>(ancho, false));
        vector<vector<pair<int, int>>> celda_padre(altura, vector<pair<int, int>>(ancho, {-1, -1}));

        queue<pair<int, int>> q;
        int fila_entrada = 1, columna_entrada = 1; // Entrada
        int fila_salida = altura - 2, columna_salida = ancho - 2; // Salida

        // si por alguna razón la entrada o salida no están abiertas, no resolvemos
        if (display[fila_entrada][columna_entrada] == '#' || display[fila_salida][columna_salida] == '#') {
            return false;
        }

        q.push({fila_entrada, columna_entrada});
        visitado[fila_entrada][columna_entrada] = true;
        
        const int delta_fila[4] = {-1, 0, 1, 0};
        const int delta_columna[4] = {0, 1, 0, -1};

        bool encontrado = false;
        while (!q.empty() && !encontrado) {
            auto [fila_actual, columna_actual] = q.front(); q.pop();

            for (int i = 0; i < 4; ++i) {
                int nueva_fila = fila_actual + delta_fila[i];
                int nueva_columna = columna_actual + delta_columna[i];

                if (nueva_fila >= 0 && nueva_fila < altura && nueva_columna >= 0 && nueva_columna < ancho
                && !visitado[nueva_fila][nueva_columna] && display[nueva_fila][nueva_columna] == '*') {
                    visitado[nueva_fila][nueva_columna] = true;
                    celda_padre[nueva_fila][nueva_columna] = {fila_actual, columna_actual};
                    q.push({nueva_fila, nueva_columna});
                    if (nueva_fila == fila_salida && nueva_columna == columna_salida) {
                        encontrado = true;
                        break;
                    }
                }
            }
        }

        if (!encontrado) return false;

        // Reconstruir desde fila_salida, columna_salida retrocediendo usando celda_padre
        int fila = fila_salida, columna = columna_salida;
        while (!(fila == fila_entrada && columna == columna_entrada)) {
            // evitar bucle infinito si algo sale mal
            auto p = celda_padre[fila][columna];
            if (p.first == -1 && p.second == -1) break;
            // No sobreescribir entrada/salida, marcamos solo si era camino '*'
            if (display[fila][columna] == '*') display[fila][columna] = 'o';
            fila = p.first; columna = p.second;
        }
        display[fila_entrada][columna_entrada] = 'E';
        display[fila_salida][columna_salida] = 'S';

        return true;
    }

    // Imprimir laberinto en consola
    void imprimir() const {
        for (int fila = 0; fila < altura; ++fila) {
            for (int columna = 0; columna < ancho; ++columna)
                cout << display[fila][columna] << ' ';
            cout << "\n";
        }
    }
};

int main() {
    int filas = 10, columnas = 10;  // Tamaño por defecto

    cout << "Ingrese el numero de filas del laberinto (10 por defecto): ";
    string input;
    getline(cin, input);
    if(!input.empty()) filas = stoi(input);


    cout << "Ingrese el numero de columnas del laberinto (10 por defecto): ";
    getline(cin, input);
    if(!input.empty()) columnas = stoi(input);

    Laberinto m(filas, columnas);

    m.tallar_camino(); // Generar caminos aleatorios
    cout << "Laberinto " << filas << "x" << columnas << " Generado:\n";
    m.imprimir();
    m.resolver();      // Resolver el laberinto
    
    cout << "Laberinto " << filas << "x" << columnas << " Con solucion BFS:\n";
    m.imprimir();

    return 0;
}
