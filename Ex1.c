#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct Node {
    int x, y;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

Node* createNode(int x, int y) {
    Node* newNode = malloc(sizeof(Node));
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node*));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest, int x, int y) {
    Node* newNode = createNode(x, y);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(graph->adjLists[dest]->x, graph->adjLists[dest]->y);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void drawGraph(SDL_Renderer* renderer, Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* node = graph->adjLists[i];
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        while (node != NULL) {
            if (node->next != NULL) {
                SDL_RenderDrawLine(renderer, node->x, node->y, node->next->x, node->next->y);
            }
            node = node->next;
        }
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Graph Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int vertices = 5;
    Graph* graph = createGraph(vertices);

    // Set vertex positions
    graph->adjLists[0] = createNode(100, 100);
    graph->adjLists[1] = createNode(200, 50);
    graph->adjLists[2] = createNode(300, 150);
    graph->adjLists[3] = createNode(400, 100);
    graph->adjLists[4] = createNode(250, 300);

    // Create edges
    addEdge(graph, 0, 1, 200, 50);
    addEdge(graph, 1, 2, 300, 150);
    addEdge(graph, 2, 3, 400, 100);
    addEdge(graph, 3, 4, 250, 300);
    addEdge(graph, 4, 0, 100, 100);

    int quit = 0;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawGraph(renderer, graph);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

