#include "simulator.h"
#include <stdio.h>
#include <string.h>

/**
 * Simulates a single game of Snakes and Ladders.
 * Records all die rolls and whether the game was won.
 *
 * @param board Pointer to the game board.
 * @param die_faces Number of sides on the die.
 * @param result Pointer to a GameResult struct where the output will be stored.
 * @param use_non_uniform If true, use weighted die.
 * @param probabilities Array of die weights (only used if use_non_uniform = true).
 */
void simulate_game(
    const Board* board,
    int die_faces,
    GameResult* result,
    bool use_non_uniform,
    const int* probabilities
) {
    if (!board || !result) return;

    int position = 1;       // Starting square
    int moves = 0;          // Number of rolls taken

    result->won = false;
    result->move_count = 0;
    memset(result->moves, 0, sizeof(result->moves));  // Clear move history

    // Run the simulation until win or max moves reached
    while (moves < MAX_MOVES_TRACKED) {
        // Roll the die (fair or non-uniform)
        int roll = use_non_uniform
                 ? dice_roll_non_uniform(die_faces, probabilities)
                 : dice_roll_uniform(die_faces);

        result->moves[moves++] = roll;  // Store roll
        position += roll;

        // If roll exceeds board, stay in place
        if (position > board->size) {
            position -= roll;
        } else {
            position = board_apply_jump(board, position); // Apply snake or ladder
        }

        // Check for win
        if (position == board->size) {
            result->won = true;
            break;
        }
    }

    result->move_count = moves;
}

/**
 * Simulates multiple games and computes the average number of moves for winning games.
 *
 * @param board Pointer to the board.
 * @param die_faces Number of die faces.
 * @param num_games Number of simulations to run.
 * @param use_non_uniform Use weighted die if true.
 * @param probabilities Probability weights if using non-uniform die.
 * @return Average moves to win (only from successful games).
 */
double simulate_average_moves(
    const Board* board,
    int die_faces,
    int num_games,
    bool use_non_uniform,
    const int* probabilities
) {
    if (!board || num_games <= 0) return 0.0;

    int total_moves = 0;
    int wins = 0;

    for (int i = 0; i < num_games; i++) {
        GameResult res;
        simulate_game(board, die_faces, &res, use_non_uniform, probabilities);

        if (res.won) {
            total_moves += res.move_count;
            wins++;
        }
    }

    if (wins == 0) return 0.0; // No wins occurred

    return (double)total_moves / wins;
}

/**
 * Simulates multiple games and finds the shortest sequence that results in a win.
 *
 * @param board Pointer to the board.
 * @param die_faces Number of die faces.
 * @param num_games Number of games to simulate.
 * @param use_non_uniform Use weighted die if true.
 * @param probabilities Probability weights.
 * @param out_result Pointer to the result that will hold the shortest win.
 * @return true if a win was found, false otherwise.
 */
bool simulate_shortest_win(
    const Board* board,
    int die_faces,
    int num_games,
    bool use_non_uniform,
    const int* probabilities,
    GameResult* out_result
) {
    if (!board || !out_result || num_games <= 0) return false;

    bool found = false;
    int min_moves = MAX_MOVES_TRACKED;
    GameResult temp;

    for (int i = 0; i < num_games; i++) {
        simulate_game(board, die_faces, &temp, use_non_uniform, probabilities);

        if (temp.won && temp.move_count < min_moves) {
            min_moves = temp.move_count;
            *out_result = temp; // Save shortest winning result
            found = true;
        }
    }

    return found;
}
