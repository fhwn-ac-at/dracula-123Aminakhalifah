#pragma once

#include "board.h"

#define MAX_NEIGHBORS 6  // Maximum direct transitions (e.g., dice roll 1–6)

/**
 * Represents a node (square) on the game board.
 * Each node stores its index and a list of reachable neighbors.
 */
typedef struct {
    int index;                    // Square number (e.g., 1, 2, ..., 100)
    int neighbors[MAX_NEIGHBORS]; // Squares reachable from this node after one dice roll
    int num_neighbors;            // Actual number of neighbors
} GraphNode;

/**
 * Represents the graph corresponding to the game board.
 * Each node corresponds to one square on the board.
 */
typedef struct {
    GraphNode nodes[MAX_BOARD_SIZE + 1];  // One node per square (1-indexed)
    int num_nodes;                        // Total number of board squares
} Graph;

/**
 * Builds the graph from the board and die configuration.
 * Adds directed edges from each node to its reachable positions after dice roll,
 * considering the effect of snakes and ladders.
 *
 * @param graph Pointer to the graph structure to populate.
 * @param board Pointer to the board structure.
 * @param die_faces Number of faces on the die (e.g., 6).
 */
void graph_build(Graph* graph, const Board* board, int die_faces);

/**
 * Prints the graph structure to stdout (for debugging and visualization).
 *
 * @param graph Pointer to the graph to print.
 */
void graph_print(const Graph* graph);
