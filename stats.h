#pragma once

#include "board.h"
#include "simulator.h"

/**
 * Structure to track statistics of snake and ladder usage during simulations.
 */
typedef struct {
    int snake_hits[MAX_SNAKES];     // Number of times each snake was encountered
    int ladder_hits[MAX_LADDERS];   // Number of times each ladder was used
    int total_games;                // Total number of games simulated
} Stats;

/**
 * Initializes the statistics structure by resetting all counters.
 *
 * @param stats Pointer to the Stats structure to initialize.
 */
void stats_init(Stats* stats);

/**
 * Updates the statistics with the results from a completed game.
 * Only successful games (where the player reached the end) are considered.
 * It analyzes the move history and records which snakes and ladders were used.
 *
 * @param board Pointer to the board used in the game.
 * @param result Pointer to the result of the completed game.
 * @param stats Pointer to the Stats structure to update.
 */
void stats_update(const Board* board, const GameResult* result, Stats* stats);

/**
 * Prints the collected statistics for all snakes and ladders,
 * including how often each was used and their average usage per game.
 *
 * @param board Pointer to the board structure.
 * @param stats Pointer to the Stats structure containing usage statistics.
 */
void stats_print(const Board* board, const Stats* stats);
