#include <stdio.h>
#include <stdlib.h>
#include "tdas/list.h"
#include "tdas/extra.h"
#include "tdas/map.h"
#include "tdas/stack.h"
#include "tdas/queue.h"
#include "tdas/heap.h"
#include "tdas/set.h"
#include <string.h>
#include <stdbool.h>
#define MAX_DEPTH 11

// Definición de la estructura para el estado del puzzle
typedef struct {
    int square[3][3]; // Matriz 3x3 que representa el tablero
    int x;    // Posición x del espacio vacío
    int y;    // Posición y del espacio vacío
    List* actions;
    int depth;
} State;

// Función para copiar una lista
List* copy_list(List* list) {
    List* new_list = list_create();
    Node* current = list->head;
    while (current != NULL) {
        list_pushBack(new_list, current->data);
        current = current->next;
    }
    return new_list;
}

// Función para obtener los nodos adyacentes
List* get_adj_nodes(State *state) {
    List* adj_nodes = list_create();
    int x = state->x;
    int y = state->y;

    // Movimiento hacia arriba
    if (x > 0) {
        State* new_state = (State*) malloc(sizeof(State));
        memcpy(new_state, state, sizeof(State));
        new_state->x = x - 1;
        new_state->y = y;
        new_state->square[x][y] = new_state->square[x - 1][y];
        new_state->square[x - 1][y] = 0;
        new_state->actions = copy_list(state->actions);
        list_pushBack(new_state->actions, "Up");
        list_pushBack(adj_nodes, new_state);
    }

    // Movimiento hacia abajo
    if (x < 2) {
        State* new_state = (State*) malloc(sizeof(State));
        memcpy(new_state, state, sizeof(State));
        new_state->x = x + 1;
        new_state->y = y;
        new_state->square[x][y] = new_state->square[x + 1][y];
        new_state->square[x + 1][y] = 0;
        new_state->actions = copy_list(state->actions);
        list_pushBack(new_state->actions, "Down");
        list_pushBack(adj_nodes, new_state);
    }

    // Movimiento hacia la izquierda
    if (y > 0) {
        State* new_state = (State*) malloc(sizeof(State));
        memcpy(new_state, state, sizeof(State));
        new_state->x = x;
        new_state->y = y - 1;
        new_state->square[x][y] = new_state->square[x][y - 1];
        new_state->square[x][y - 1] = 0;
        new_state->actions = copy_list(state->actions);
        list_pushBack(new_state->actions, "Left");
        list_pushBack(adj_nodes, new_state);
    }

    // Movimiento hacia la derecha
    if (y < 2) {
        State* new_state = (State*) malloc(sizeof(State));
        memcpy(new_state, state, sizeof(State));
        new_state->x = x;
        new_state->y = y + 1;
        new_state->square[x][y] = new_state->square[x][y + 1];
        new_state->square[x][y + 1] = 0;
        new_state->actions = copy_list(state->actions);
        list_pushBack(new_state->actions, "Right");
        list_pushBack(adj_nodes, new_state);
    }

    return adj_nodes;
}

// Función para verificar si el stack está vacío
int pila_vacia(Stack* stack) {
    return stack->head == NULL;
}

// Función para verificar si la queue está vacía
int cola_vacia(Queue* queue) {
    return queue->head == NULL;
}

// Función para verificar si la lista está vacía
int lista_vacia(List* list) {
    return list->head == NULL;
}

// Función para calcular la distancia L1
int distancia_L1(State* state) {
    int ev = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int val = state->square[i][j];
            if (val == 0) continue;
            int ii = (val) / 3;
            int jj = (val) % 3;
            ev += abs(ii - i) + abs(jj - j);
        }
    }
    return ev;
}

// Función para imprimir el estado del puzzle
void imprimirEstado(const State *estado) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (estado->square[i][j] == 0)
                printf("x "); // Imprime un espacio en blanco para el espacio vacío
            else
                printf("%d ", estado->square[i][j]);
        }
        printf("\n");
    }
}

// Función para imprimir la lista de acciones
void imprimirListaDeAcciones(List* actions) {
    printf("Secuencia de acciones: ");
    Node* current = actions->head;
    while (current != NULL) {
        printf("%s ", (char*) current->data);
        current = current->next;
    }
    printf("\n");
}

// Función de búsqueda en profundidad (DFS)
void dfs(State *estado_inicial) {
    long cont = 0;
    printf("El estado inicial es:\n");
    imprimirEstado(estado_inicial);
    Stack* stack = stack_create(stack);
    stack_push(stack, estado_inicial);
    while (!pila_vacia(stack)) {
        State* estado_actual = (State*) stack_top(stack);
        stack_pop(stack);
        if (distancia_L1(estado_actual) == 0) {
            printf("Solución encontrada\n");
            printf("Iteraciones para resolver el puzzle: %ld\n", cont);
            imprimirEstado(estado_actual);
            imprimirListaDeAcciones(estado_actual->actions);

            while (!pila_vacia(stack)) {
                stack_pop(stack);
            }
            return;
        }
        if (estado_actual->depth <= MAX_DEPTH) {
            List* adj_nodes = get_adj_nodes(estado_actual);
            while (!lista_vacia(adj_nodes)) {
                State* estado_siguiente = (State*) list_first(adj_nodes);
                estado_siguiente->depth = estado_actual->depth + 1;
                list_popFront(adj_nodes);
                stack_push(stack, estado_siguiente);
                cont++;
            }
        } else {
            estado_actual->depth = 0;
        }
    }

    printf("No se encontró solución\n");
}

// Función de búsqueda en anchura (BFS)
void bfs(State *estado_inicial) {
    int cont = 0;
    printf("El estado inicial es:\n");
    imprimirEstado(estado_inicial);
    Queue* queue = queue_create(queue);
    queue_insert(queue, estado_inicial);
    while (!cola_vacia(queue)) {
        State* estado_actual = (State*) queue_front(queue);
        queue_remove(queue);
        if (distancia_L1(estado_actual) == 0) {
            printf("Solución encontrada\n");
            printf("Iteraciones para resolver el puzzle: %d\n", cont);
            imprimirEstado(estado_actual);
            imprimirListaDeAcciones(estado_actual->actions);
            return;
        }
        List* adj_nodes = get_adj_nodes(estado_actual);
        while (!lista_vacia(adj_nodes)) {
            State* estado_siguente = (State*) list_first(adj_nodes);
            estado_siguente->depth = estado_actual->depth + 1;
            queue_insert(queue, estado_siguente);
            list_popFront(adj_nodes);
            cont++;
        }
    }
    printf("No se encontró solución\n");
    printf("%d\n", cont);
}

int main() {
    // Estado inicial del puzzle
    State estado_inicial = {
        {{0, 2, 8}, // Primera fila
         {1, 3, 4}, // Segunda fila
         {6, 5, 7}, // Tercera fila
         },  
        0, 0, // Posición del espacio vacío
        list_create(),
        0 
    };

    // Imprime el estado inicial
    printf("Estado inicial del puzzle:\n");
    imprimirEstado(&estado_inicial);

    printf("Distancia L1: %d\n", distancia_L1(&estado_inicial));


    printf("\n***** EJEMPLO USO DE HEAP ******\nCreamos un Heap e insertamos 3 elementos con distinta prioridad\n");
    Heap* heap = heap_create();
    char* data = strdup("Cinco");
    printf("Insertamos el elemento %s con prioridad -5\n", data);
    heap_push(heap, data, -5 );
    data = strdup("Seis");
    printf("Insertamos el elemento %s con prioridad -6\n", data);
    heap_push(heap, data, -6 );
    data = strdup("Siete");
    printf("Insertamos el elemento %s con prioridad -7\n", data);
    heap_push(heap, data, -7 );

    printf("\nLos elementos salen del Heap ordenados de mayor a menor prioridad\n");
    while (heap_top(heap) != NULL) {
        printf("Top: %s\n", (char*) heap_top(heap));
        heap_pop(heap);
    }
    printf("No hay más elementos en el Heap\n");

    int opcion;
    do {
        printf("\n***** EJEMPLO MENU ******\n");
        puts("========================================");
        puts("     Escoge método de búsqueda");
        puts("========================================");

        puts("1) Búsqueda en Profundidad");
        puts("2) Buscar en Anchura");
        puts("3) Buscar Mejor Primero");
        puts("4) Salir");

        printf("Ingrese su opción: ");
        scanf(" %d", &opcion);

        switch (opcion) {
        case 1:
            printf("Has seleccionado la opción 1: Búsqueda en Profundidad\n");
            dfs(&estado_inicial);
            break;
        case 2:
            printf("Has seleccionado la opción 2: Búsqueda en Anchura\n");
            bfs(&estado_inicial);
            break;
        case 3:
            //best_first(estado_inicial);
            // al estar solo este no lo tengo que hacer
            break;
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();
    } while (opcion != 4);

    return 0;
}
