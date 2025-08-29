import math
import time 

tamaño_tablero = 8

tablero = [
    [".", ".", ".", ".", ".", ".", ".","."],
    [".", "#", "#", ".", "#", ".", "#", "."],
    [".", ".", ".", ".", "#", ".", ".", "."],
    [".", ".", "#", ".", ".", "#", ".", "."],
    [".", ".", ".", ".", ".", ".", ".", "."],
    [".", "#", ".", "#", ".", "#", ".", "."],
    [".", ".", ".", ".", "#", ".", ".", "."],
    [".", ".", ".", ".", ".", ".", ".", "."]
    
]

# Guarda en una tupla las posiciones del gato, raton y queso. para usar las variables mas facilmente 
gato = (3,3)
raton = (7,0)
queso = (0,7)

# Mostrar en el tablero 
tablero[gato[0]][gato[1]] = "G"
tablero[raton[0]][raton[1]] = "R"
tablero[queso[0]][queso[1]] = "Q"

# Imprimir tablero de forma linda

def imprimir_tablero(tablero):
    print("  "+" ".join(str(i) for i in range(tamaño_tablero)))
    for i, fila in enumerate(tablero):
        print(f"{i} "+ " ".join(fila))
    print()


# Funcion para validar movimientos posibles 
def movimientos_posibles(posicion,jugador,tablero):
    fila,columna = posicion
    if jugador == "raton":
        posibles = [(fila-1,columna), #izquierda
                    (fila+1,columna), #Derecha 
                    (fila,columna-1), #Arriba
                    (fila,columna+1) #Abajo
                    ]
    else:
        posibles = [(fila-1,columna), #izquierda
                    (fila+1,columna), #Derecha 
                    (fila,columna-1), #Arriba
                    (fila,columna+1) #Abajo
                ]
        #Filtrar posiciones validas
    validos = [(fila,columna)for fila,columna in posibles if 0 <= fila < tamaño_tablero and 0 <= columna < tamaño_tablero]
    validos = [(fila,columna)for fila,columna in validos if tablero[fila][columna] != "#" and (jugador=="raton" or (fila,columna)!=queso) ]
    return validos

# Funcion para el estado final 
def estado_final(gato,raton,queso):
    if gato==raton:
        return "gato"
    if raton == queso:
        return "raton"
    return None       #Si los if no reciben "respuesta correcta" entonces retorna un None que nos indica que no esta pasando lo condicionado 

# Heuristica para el gato 
def heuristica(gato,raton): 
    return 100 -(abs(gato[0]-raton[0]) + abs(gato[1]-raton[1])) 

# Funcion minimax corregida
def minimax(gato, raton, profundidad, es_turno_gato):
    # Verificar estado final
    resultado = estado_final(gato, raton, queso)
    if resultado == "gato":
        return 1000  # Gana el gato
    elif resultado == "raton":
        return -1000  # Gana el ratón
    elif profundidad == 0:
        return heuristica(gato, raton)
        
    if es_turno_gato:
        max_eval = -math.inf
        movimientos = movimientos_posibles(gato, "gato", tablero)
        for mov in movimientos:
            eval = minimax(mov, raton, profundidad-1, False)
            max_eval = max(max_eval, eval)
        return max_eval
    else:
        min_eval = math.inf
        movimientos = movimientos_posibles(raton, "raton", tablero)
        for mov in movimientos:
            eval = minimax(gato, mov, profundidad-1, True)
            min_eval = min(min_eval, eval)
        return min_eval

# Funcion que define el mejor movimiento del gato
def mejor_movimiento_gato():
    mejor_val = -math.inf
    mejor_mov = gato
    for mov in movimientos_posibles(gato,"gato", tablero):
        val = minimax(mov, raton, 6, False)  # Después de mover el gato, es turno del ratón
        if val > mejor_val:
            mejor_val = val
            mejor_mov = mov
    return mejor_mov

# Funcion mover jugador
def mover(jugador, posicion, nuevo):
    fila,columna = posicion
    if posicion != queso:
        tablero[fila][columna] = "."
    fila2, columna2 = nuevo
    tablero[fila2][columna2] = "R" if jugador == "raton" else "G"
    return (fila2, columna2)

# bucle para el funcionamieto del programa
turno = "raton"
max_turnos = 20
turno_actual = 0

imprimir_tablero(tablero)

while True:
    turno_actual += 1 
    if turno_actual > max_turnos:
        print("Empate por limite de turnos!")
        break
    
    if turno == "raton":
        mov = input("Mover raton con w/a/s/d: ").lower()
        fila,columna = raton
        if mov == "w":
            nuevo = (fila-1,columna)
        elif mov == "s":
            nuevo = (fila+1,columna)
        elif mov == "a":
            nuevo = (fila,columna-1)
        elif mov == "d":
            nuevo = (fila,columna+1)
        else:
            print("Movimiento invalido")
            continue
        if 0 <= nuevo[0] < tamaño_tablero and 0 <= nuevo[1] < tamaño_tablero and tablero[nuevo[0]][nuevo[1]] != "#":
            raton = mover("raton",raton, nuevo)
        else:
            print("Movimiento bloqueado")
            continue

        turno = "gato"

    else: 
        print("Turno del gato (pensando. . .)")
        time.sleep(1)
        nuevo_gato = mejor_movimiento_gato()
        gato = mover("gato",gato, nuevo_gato)
        turno = "raton"

    imprimir_tablero(tablero)

    estado = estado_final(gato, raton, queso)
    if estado:
        print(f"¡Gana {estado}!")
        break

print("===================")
print("===FIN DEL JUEGO===")
print("===================")