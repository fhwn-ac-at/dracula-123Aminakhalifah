#include "graph.h"
#include <stdio.h>

/**
 * Builds a graph representation of the game board.
 * Each node represents a square on the board.
 * Each edge represents a legal move (via dice roll + jump).
 *
 * If a square contains a ladder or snake, the edge points to its end.
 *
 * @param graph Pointer to the graph structure to populate.
 * @param board The board configuration (with snakes/ladders).
 * @param die_faces Number of faces on the die (e.g., 6).
 */
void graph_build(Graph* graph, const Board* board, int die_faces) {
    if (!graph || !board || die_faces <= 0) return;

    graph->num_nodes = board->size;

    // For each square on the board, determine reachable neighbors
    for (int i = 1; i <= board->size; i++) {
        graph->nodes[i].index = i;
        graph->nodes[i].num_neighbors = 0;

        // Simulate dice rolls from this square
        for (int roll = 1; roll <= die_faces; roll++) {
            int next_pos = i + roll;

            // Skip moves that go off the board
            if (next_pos > board->size) continue;

            // Apply jump if there's a ladder or snake
            int final_pos = board_apply_jump(board, next_pos);

            // Add the final position as a neighbor if within limits
            if (graph->nodes[i].num_neighbors < MAX_NEIGHBORS) {
                graph->nodes[i].neighbors[graph->nodes[i].num_neighbors++] = final_pos;
            }
        }
    }
}

/**
 * Prints the adjacency list of the graph.
 * Each node (square) lists reachable neighbors (target squares).
 */
void graph_print(const Graph* graph) {
    if (!graph) return;

    printf("Graph representation of the board:\n");

    for (int i = 1; i <= graph->num_nodes; i++) {
        printf("Node %3d: ", i);
        for (int j = 0; j < graph->nodes[i].num_neighbors; j++) {
            printf("%3d ", graph->nodes[i].neighbors[j]);
        }
        printf("\n");
    }
}
