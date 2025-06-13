#pragma once

#include "board.h"
#include "graph.h"
#include "dice.h"
#include <stdbool.h>

#define MAX_MOVES_TRACKED (MAX_BOARD_SIZE * 2)  // Safety margin for maximum moves per game

/**
 * Represents the result of a single game simulation.
 */
typedef struct {
    int move_count;                    // Total number of die rolls during this game
    int moves[MAX_MOVES_TRACKED];     // Sequence of die rolls
    bool won;                          // Set to true if the player reached the final square
} GameResult;

/**
 * Simulates one complete game of Snakes and Ladders.
 *
 * The game starts at position 1 and continues until the player either:
 * - Wins (reaches final square), or
 * - Exceeds MAX_MOVES_TRACKED (to avoid infinite loops).
 *
 * @param board Pointer to the game board.
 * @param die_faces Number of die faces (e.g. 6).
 * @param result Output structure to store the game's result.
 * @param use_non_uniform Set to true to use a weighted die.
 * @param probabilities Pointer to array of probabilities for each die face (used only if non-uniform).
 */
void simulate_game(
    const Board* board,
    int die_faces,
    GameResult* result,
    bool use_non_uniform,
    const int* probabilities
);

/**
 * Runs multiple game simulations and calculates the average number of rolls
 * required to win.
 *
 * Only successful games (i.e., games where the player reached the goal) are
 * counted towards the average.
 *
 * @param board Pointer to the board.
 * @param die_faces Number of faces on the die.
 * @param num_games Number of simulations to run.
 * @param use_non_uniform Use weighted die if true.
 * @param probabilities Optional weights for each die face (if using non-uniform).
 * @return Average number of rolls needed to win (0.0 if no games were won).
 */
double simulate_average_moves(
    const Board* board,
    int die_faces,
    int num_games,
    bool use_non_uniform,
    const int* probabilities
);

/**
 * Runs multiple simulations to find the shortest winning game.
 *
 * Tracks the game that reaches the final square using the fewest die rolls.
 *
 * @param board Pointer to the game board.
 * @param die_faces Number of die faces.
 * @param num_games Number of games to simulate.
 * @param use_non_uniform Use weighted die if true.
 * @param probabilities Weights for non-uniform die (if enabled).
 * @param out_result Output structure that will store the best result.
 * @return true if a winning game was found, false if all simulations failed.
 */
bool simulate_shortest_win(
    const Board* board,
    int die_faces,
    int num_games,
    bool use_non_uniform,
    const int* probabilities,
    GameResult* out_result
);
