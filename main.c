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
#define MAX_DEPTH 50

// Definición de la estructura para el estado del puzzle
typedef struct {
    int square[3][3]; // Matriz 3x3 que representa el tablero
    int x;    // Posición x del espacio vacío
    int y;    // Posición y del espacio vacío
    List* actions;
    int depth;
} State;
List* get_adj_nodes(State *state){
    List* adj_nodes = list_create();
    int x = state->x;
    int y = state->y;
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
void imprimirListaDeAcciones(List* actions) {
    printf("Secuencia de acciones: ");
    int cont = 0;
    while (!list_is_empty(actions)) {
        char* action = (char*) list_first(actions);
        printf("%s ", action);
        list_popFront(actions);
        cont++;
        if(cont>=5){
            char* last_action = (char*) actions->tail->data;
            printf("... %s\n",last_action);
            break;
        }
    }
    printf("\n");
}

List* copy_list(List* list){
    List* new_list = list_create();
    Node* current = list->head;
    while (current != NULL){
        list_pushBack(new_list, current->data);
        current = current->next;
    }
    return new_list;
}

void dfs(State *estado_inicial){
    long cont = 0;
    List* act = list_create();
    printf("el estado inicial es:\n");
    imprimirEstado(estado_inicial);
    Stack* stack = stack_create(stack);
    stack_push(stack, estado_inicial);
    while (!stack_is_empty(stack)){
        State* estado_actual = (State*) stack_top(stack);
        stack_pop(stack);
        if(distancia_L1(estado_actual) == 0){
            printf("Solucion encontrada\n");
            printf("itraciones para resolver el puzzle: %ld\n", cont);
            imprimirEstado(estado_actual);
            imprimirListaDeAcciones(act);
            
            while (!stack_is_empty(stack)){
                stack_pop(stack);
            }
            return;
        }
        if(estado_actual->depth <= MAX_DEPTH){
            List* adj_nodes = get_adj_nodes(estado_actual);
            while (!list_is_empty(adj_nodes)){
                State* estado_siguente = (State*) list_first(adj_nodes);
                list_pushBack(act, estado_siguente->actions->head->data);
                estado_siguente->depth = estado_actual->depth + 1;
                list_popFront(adj_nodes);
                stack_push(stack, estado_siguente);
                cont++;
            }
        }
        else{
            estado_actual->depth = 0;
        }
    }

    printf("No se encontro solucion\n");
}

void bfs(State *estado_inicial){
    int cont = 0;
    List* act = list_create();
    printf("el estado inicial es:\n");
    imprimirEstado(estado_inicial);
    Queue* queue = queue_create(queue);
    queue_insert(queue, estado_inicial);
    while (!queue_is_empty(queue)){
        State* estado_actual = (State*) queue_front(queue);
        queue_remove(queue);
        if (distancia_L1(estado_actual) == 0){
            printf("Se encontro solucion\n");
            printf("iteraciones para resolver el puzzle: %d\n", cont);
            imprimirEstado(estado_actual);
            imprimirListaDeAcciones(act);
            return;
        }
        List* adj_nodes = get_adj_nodes(estado_actual);
        while (!list_is_empty(adj_nodes)){
            State* estado_adj = (State*) list_first(adj_nodes);
            list_pushBack(act, estado_adj->actions->head->data);
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
          // al estar solo este no lo tengo que hacer
          break;
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();

  } while (opcion != '4');

  return 0;
}