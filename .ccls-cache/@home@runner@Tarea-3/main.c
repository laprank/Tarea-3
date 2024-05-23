#include <stdio.h>
#include <stdlib.h>
#include "tdas/list.h"
#include "tdas/extra.h"
#include "tdas/map.h"
#include "tdas/stack.h"
#include "tdas/queue.h"
#include "tdas/heap.h"
#include <string.h>
#include <stdbool.h>

// Definición de la estructura para el estado del puzzle
typedef struct {
    int square[3][3]; // Matriz 3x3 que representa el tablero
    int x;    // Posición x del espacio vacío
    int y;    // Posición y del espacio vacío
    List* actions;
} State;
List* get_adj_nodes(State *state){
    List* adj_nodes = list_create();
    int x = state->x;
    int y = state->y;
    int i, j;
    // Movimiento hacia arriba
    if (x > 0){
        State* new_state = (State*) malloc(sizeof(State));
        memcpy(new_state, state, sizeof(State));
        new_state->x = x - 1;
        new_state->y = y;
        new_state->square[x][y] = new_state->square[x - 1][y];
        new_state->square[x - 1][y] = 0;
        new_state->actions = list_create();
        list_pushBack(new_state->actions, "Up");
        list_pushBack(adj_nodes, new_state);
    }
    // Movimiento hacia abajo
    if (x < 2){
        State* new_state = (State*) malloc(sizeof(State));
        memcpy(new_state, state, sizeof(State));
        new_state->x = x + 1;
        new_state->y = y;
        new_state->square[x][y] = new_state->square[x + 1][y];
        new_state->square[x + 1][y] = 0;
        new_state->actions = list_create();
        list_pushBack(new_state->actions, "Down");
        list_pushBack(adj_nodes, new_state);
    }
    // Movimiento hacia la izquierda
    if (y > 0){
        State* new_state = (State*) malloc(sizeof(State));
        memcpy(new_state, state, sizeof(State));
        new_state->x = x;
        new_state->y = y - 1;
        new_state->square[x][y] = new_state->square[x][y - 1];
        new_state->square[x][y - 1] = 0;
        new_state->actions = list_create();
        list_pushBack(new_state->actions, "Left");
        list_pushBack(adj_nodes, new_state);
    }
    // Movimiento hacia la derecha
    if (y < 2){
        State* new_state = (State*) malloc(sizeof(State));
        memcpy(new_state, state, sizeof(State));
        new_state->x = x;
        new_state->y = y + 1;
        new_state->square[x][y] = new_state->square[x][y + 1];
        new_state->square[x][y + 1] = 0;
        new_state->actions = list_create();
        list_pushBack(new_state->actions, "Right");
        list_pushBack(adj_nodes, new_state);
    }
    return adj_nodes;
}
int stack_is_empty(Stack* stack) {
    return stack->head == NULL;
}
int queue_is_empty(Queue* queue) {
    return queue->head == NULL;
}
int list_is_empty(List* list) {
    return list->head == NULL;
}
int distancia_L1(State* state) {
    int ev=0;
    int k=1;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            int val=state->square[i][j];
            if (val==0) continue;
            int ii=(val)/3;
            int jj=(val)%3;
            ev+= abs(ii-i) + abs(jj-j);
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
// Función para verificar si el estado es igual a otro estado


void dfs(State *estado_inicial){
    int cont = 0;
    Stack* stack = stack_create(stack);
    if (!stack) {
        printf("Error 1\n");
        return;
    }
    stack_push(stack, estado_inicial);
    while (!stack_is_empty(stack)){
        State* estado_actual = (State*) stack_top(stack);
        stack_pop(stack);
        if(distancia_L1(estado_actual) == 0){
            printf("Solucion encontrada\n");
            imprimirEstado(estado_actual);
            return;
        }
        List* adj_nodes = get_adj_nodes(estado_actual);
        if (!adj_nodes) {
            printf("Error 2\n");
            continue;
        }
        while (!list_is_empty(adj_nodes)){
            State* estado_siguiente = (State*) list_first(adj_nodes);
            if (!estado_siguiente) {
                printf("Error: 3\n");
                list_popFront(adj_nodes);
                continue;
            }
            stack_push(stack, estado_siguiente);
            list_popFront(adj_nodes);
            cont++;
        }
        // Liberar la memoria de adj_nodes si es necesario
        free(adj_nodes);
    }
    printf("Total de estados procesados: %d\n", cont);
    printf("No se encontro solucion\n");
}

void bfs(State *estado_inicial){
    int cont = 0;
    Queue* queue = queue_create(queue);
    queue_insert(queue, estado_inicial);
    while (!queue_is_empty(queue)){
        State* estado_actual = (State*) queue_front(queue);
        queue_remove(queue);
        if (distancia_L1(estado_actual) == 0){
            printf("Se encontro solucion\n");
            imprimirEstado(estado_actual);
            return;
        }
        List* adj_nodes = get_adj_nodes(estado_actual);
        while (!list_is_empty(adj_nodes)){
            State* estado_adj = (State*) list_first(adj_nodes);
            queue_insert(queue, estado_adj);
            list_popFront(adj_nodes);
            cont++;
        }
    }
    printf("No se encontro solucion\n");
    printf("%d", cont);
}
int main() {
    // Estado inicial del puzzle
    State estado_inicial = {
        {{0, 2, 8}, // Primera fila (0 representa espacio vacío)
         {1, 3, 4}, // Segunda fila
         {6, 5, 7}, // Tercera fila
         },  
        0, 0   // Posición del espacio vacío (fila 0, columna 1)
    };
    estado_inicial.actions = list_create();

    // Imprime el estado inicial
    printf("Estado inicial del puzzle:\n");
    imprimirEstado(&estado_inicial);

    printf("Distancia L1:%d\n", distancia_L1(&estado_inicial));

    //Ejemplo de heap (cola con prioridad)
    printf("\n***** EJEMPLO USO DE HEAP ******\nCreamos un Heap e insertamos 3 elementos con distinta prioridad\n");
    Heap* heap = heap_create();
    char* data = strdup("Cinco");
    printf("Insertamos el elemento %s con prioridad -5\n", data);
    heap_push(heap, data, -5 /*prioridad*/);
    data = strdup("Seis");
    printf("Insertamos el elemento %s con prioridad -6\n", data);
    heap_push(heap, data, -6 /*prioridad*/);
    data = strdup("Siete");
    printf("Insertamos el elemento %s con prioridad -7\n", data);
    heap_push(heap, data, -7 /*prioridad*/);

    printf("\nLos elementos salen del Heap ordenados de mayor a menor prioridad\n");
    while (heap_top(heap) != NULL){
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
        scanf(" %c", &opcion);

        switch (opcion) {
        case '1':
            printf("Has seleccionado la opción 1: Búsqueda en Profundidad\n");
            dfs(&estado_inicial);
            break;
        case '2':
            bfs(&estado_inicial);
          break;
        case '3':
          //best_first(estado_inicial);
          break;
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();

  } while (opcion != '4');

  return 0;
}