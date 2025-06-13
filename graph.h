#pragma once

#include "board.h"

#define MAX_NEIGHBORS 6  

/**
 * Represents a node (square) on the game board.
 * Each node has an index and a list of reachable neighbors (after applying jump).
 */
typedef struct {
    int index;                    
    int neighbors[MAX_NEIGHBORS]; 
    int num_neighbors;           
} GraphNode;

/**
 * Represents the full graph of the board.
 */
typedef struct {
    GraphNode nodes[MAX_BOARD_SIZE + 1];  
    int num_nodes;
} Graph;

/**
 * Initializes the graph based on the board configuration and die faces.
 * Adds edges representing legal moves 
 * 
 * @param graph Pointer to the graph to initialize.
 * @param board The board structure (dimensions + snakes/ladders).
 * @param die_faces Number of faces of the die (e.g., 6).
 */
void graph_build(Graph* graph, const Board* board, int die_faces);

/**
 * Prints the graph structure (for debugging).
 * @param graph Pointer to the graph.
 */
void graph_print(const Graph* graph);
