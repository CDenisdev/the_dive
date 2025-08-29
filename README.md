# Laberinto del Gato y el Ratón 🐭🐱

Un juego de estrategia implementado en Python donde un gato inteligente persigue a un ratón controlado por el usuario en un laberinto con obstáculos.

## Características

- Tablero de 8x8 con obstáculos (#) y objetivos (Q)
- Sistema de turnos: usuario controla al ratón, IA controla al gato
- Algoritmo Minimax para la inteligencia artificial del gato
- Heurística basada en distancia Manhattan
- Interfaz de consola con visualización del tablero
- Límite de 20 turnos 

## Cómo Ejecutar

1. Asegúrate de tener Python 3.x instalado
2. Descarga el archivo `minimax_lab.py`
3. Ejecuta en la terminal:

## Controles

- **w**: Mover el ratón hacia arriba
- **a**: Mover el ratón hacia la izquierda  
- **s**: Mover el ratón hacia abajo
- **d**: Mover el ratón hacia la derecha

## Cómo Funciona

### Algoritmo Minimax
El gato utiliza el algoritmo Minimax con una profundidad de 4 para anticipar los movimientos del ratón y tomar decisiones estratégicas. En cada turno:

1. El gato genera todos sus movimientos posibles
2. Para cada movimiento, simula los posibles contra-movimientos del ratón
3. Evalúa cada escenario usando una función heurística
4. Selecciona el movimiento que maximiza sus chances de atrapar al ratón

### Función Heurística
La función de evaluación se basa en la distancia Manhattan entre el gato y el ratón:

heurística = 100 - (|gato_x - ratón_x| + |gato_y - ratón_y|)


### Estructura del Código
- `tablero`: Matriz 8x8 que representa el laberinto
- `movimientos_posibles()`: Calcula movimientos válidos para cada jugador
- `minimax()`: Implementa el algoritmo de decisión
- `heuristica()`: Evalúa qué tan buena es una posición para el gato
- `estado_final()`: Determina si el juego ha terminado

## Que fue lo que mas me costo
Lo que mas me costo fue primero entender que era el algoritmo minimax, como funciona 
despues de eso aplicarlo al juego del gato y raton.

## Posibles Mejoras
- Implementar poda alfa-beta para optimizar el algoritmo Minimax
- Añadir múltiples niveles de dificultad
- Crear una interfaz gráfica
- Implementar diferentes estrategias para el ratón
- Permitir configuración de tableros personalizados

## Autor

Carlos Denis
