# Tarea-3

# Puzzle Solver: Depth-First Search (DFS) and Breadth-First Search (BFS)

Este programa implementa dos métodos de búsqueda para resolver el clásico rompecabezas de 8 piezas (3x3): Búsqueda en Profundidad (DFS) y Búsqueda en Anchura (BFS).

## Instrucciones para Compilar y Ejecutar

Para una configuración y ejecución rápida, sigue estos pasos:

1. **Visita Repl.it:**
   Ve a [Repl.it](https://repl.it/) en tu navegador web.

2. **Inicia Sesión o Crea una Cuenta:**
   Si ya tienes una cuenta, inicia sesión. De lo contrario, crea una nueva cuenta.

3. **Importa el Repositorio:**
   En tu dashboard, selecciona "New Repl" y elige "Import from GitHub".

4. **Pega la URL del Repositorio:**
   Pega la URL del repositorio en el campo proporcionado: `https://github.com/laprank/Tarea-3.git`.

5. **Configura el Entorno:**
   Repl.it clonará el repositorio y configurará un entorno de ejecución automáticamente.

6. **Compila y Ejecuta el Programa:**
   Una vez que Repl.it haya finalizado la configuración, busca el archivo principal del programa (por ejemplo, `main.c`) y presiona el botón "Run" para compilar y ejecutar el programa.

## Funcionalidades

El programa permite resolver el rompecabezas de 8 piezas utilizando dos métodos de búsqueda diferentes:

- **Búsqueda en Profundidad (DFS):** Este método explora cada posible movimiento a fondo antes de retroceder y probar una nueva ruta. Se detiene al encontrar la solución o al alcanzar la profundidad máxima permitida.
- **Búsqueda en Anchura (BFS):** Este método explora todos los movimientos posibles en un nivel antes de pasar al siguiente. 
## Ejemplo de Uso

### Menú Principal:

Al ejecutar el programa, verás un menú con las siguientes opciones:

1. **Búsqueda en Profundidad (DFS):**
   Selecciona esta opción para usar DFS para resolver el rompecabezas. El programa imprimirá el estado inicial, el número total de iteraciones necesarias para encontrar la solución y el estado final del puzzle.
   Has seleccionado la opción 1: Búsqueda en Profundidad

2. **Buscar en Anchura (BFS):**
   Selecciona esta opción para usar BFS para resolver el rompecabezas. Similar a DFS, el programa imprimirá el estado inicial, el número total de nodos explorados y el estado final del puzzle.
   Has seleccionado la opción 2: Búsqueda en Anchura

3. **Salir:**
   Cierra el programa.

### Estado Inicial del Puzzle:

El programa imprime el estado inicial del puzzle antes de comenzar la búsqueda:

### Búsqueda en Profundidad (DFS):

El programa realiza la búsqueda en profundidad y muestra los resultados:
   Solución encontrada
   iteraciones para resolver el puzzle: [número de iteraciones]

### Búsqueda en Anchura (BFS):

El programa realiza la búsqueda en anchura y muestra los resultados:
   Se encontró solución
   iteraciones para resolver el puzzle: [número de iteraciones]

## Contribuciones

### Franco Ugarte:
- Implementó todas las funciones del sistema.
- Realizó documentación y comentarios en el código.
- Diseñó y redactó el README.

---

## Problemas Conocidos

- La funcionalidad para buscar por otros métodos (como la búsqueda heurística) está en desarrollo.
- la impresion de la secuencia mas corta en desarrollo.

## Áreas de Mejora

- Mejorar la precisión y eficiencia de las búsquedas.
- Implementar nuevas funcionalidades, como la búsqueda heurística y y la impresion de la secuencia entera.
```