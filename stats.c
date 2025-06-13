#include "stats.h"
#include <stdio.h>
#include <string.h>

/**
 * Initializes the statistics structure by resetting all counters.
 *
 * @param stats Pointer to the Stats structure to initialize.
 */
void stats_init(Stats* stats) {
    if (!stats) return;

    // Set all ladder and snake hit counters to zero
    memset(stats->snake_hits, 0, sizeof(stats->snake_hits));
    memset(stats->ladder_hits, 0, sizeof(stats->ladder_hits));
    stats->total_games = 0;
}

/**
 * Updates the statistics based on a completed (won) game.
 * This function counts how many times each snake or ladder was used.
 *
 * @param board Pointer to the game board.
 * @param result Pointer to the result of a single game.
 * @param stats Pointer to the Stats structure to update.
 */
void stats_update(const Board* board, const GameResult* result, Stats* stats) {
    if (!board || !result || !stats || !result->won) return;

    int position = 1;

    for (int i = 0; i < result->move_count; i++) {
        int roll = result->moves[i];
        int next = position + roll;

        // If the move overshoots the board, ignore it
        if (next > board->size) {
            next = position;
        }

        // Check if there's a jump (snake or ladder)
        int jumped = board_apply_jump(board, next);

        if (jumped != next) {
            // Determine if it was a snake
            for (int j = 0; j < board->num_snakes; j++) {
                if (board->snakes[j].start == next && board->snakes[j].end == jumped) {
                    stats->snake_hits[j]++;
                    break;
                }
            }

            // Determine if it was a ladder
            for (int j = 0; j < board->num_ladders; j++) {
                if (board->ladders[j].start == next && board->ladders[j].end == jumped) {
                    stats->ladder_hits[j]++;
                    break;
                }
            }

            position = jumped;
        } else {
            position = next;
        }
    }

    stats->total_games++;
}

/**
 * Prints out statistics about how often each snake and ladder was used.
 *
 * @param board Pointer to the game board.
 * @param stats Pointer to the Stats structure containing usage data.
 */
void stats_print(const Board* board, const Stats* stats) {
    if (!board || !stats) return;

    printf("\n📊 Snake and Ladder Usage Statistics (across %d games):\n", stats->total_games);

    printf("\n🐍 Snakes:\n");
    for (int i = 0; i < board->num_snakes; i++) {
        int count = stats->snake_hits[i];
        double freq = (stats->total_games > 0) ? ((double)count / stats->total_games) : 0.0;
        printf("  Snake %2d: from %3d to %3d — used %4d times (%.2f per game)\n",
               i + 1, board->snakes[i].start, board->snakes[i].end, count, freq);
    }

    printf("\n🪜 Ladders:\n");
    for (int i = 0; i < board->num_ladders; i++) {
        int count = stats->ladder_hits[i];
        double freq = (stats->total_games > 0) ? ((double)count / stats->total_games) : 0.0;
        printf("  Ladder %2d: from %3d to %3d — used %4d times (%.2f per game)\n",
               i + 1, board->ladders[i].start, board->ladders[i].end, count, freq);
    }
}
