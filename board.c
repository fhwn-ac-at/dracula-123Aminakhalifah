#include "board.h"
#include <stdio.h>

/**
 * Initializes the board with given width and height.
 * Resets snake and ladder counters to zero.
 */
void board_init(Board* board, int width, int height) {
    if (!board || width <= 0 || height <= 0 || width * height > MAX_BOARD_SIZE) {
        return; // Invalid parameters or board too large
    }

    board->width = width;
    board->height = height;
    board->size = width * height;
    board->num_snakes = 0;
    board->num_ladders = 0;
}

/**
 * Adds a snake from start to end (must be descending).
 * Validates input and checks for conflict with existing snakes/ladders.
 */
bool board_add_snake(Board* board, int start, int end) {
    if (!board || board->num_snakes >= MAX_SNAKES) return false;

    // Snake must go downward and not end on same square or outside bounds
    if (start <= end || start >= board->size || end < 1 || start == board->size) return false;

    if (board_is_conflict(board, start, end)) return false;

    board->snakes[board->num_snakes].start = start;
    board->snakes[board->num_snakes].end = end;
    board->num_snakes++;
    return true;
}

/**
 * Adds a ladder from start to end (must be ascending).
 * Validates input and checks for conflict with existing snakes/ladders.
 */
bool board_add_ladder(Board* board, int start, int end) {
    if (!board || board->num_ladders >= MAX_LADDERS) return false;

    // Ladder must go upward and not exceed board size
    if (start >= end || end > board->size || start < 1 || start == board->size) return false;

    if (board_is_conflict(board, start, end)) return false;

    board->ladders[board->num_ladders].start = start;
    board->ladders[board->num_ladders].end = end;
    board->num_ladders++;
    return true;
}

/**
 * Checks if a player landed on a ladder or snake.
 * Returns the destination square after applying the jump.
 */
int board_apply_jump(const Board* board, int position) {
    if (!board) return position;

    // Check if position is the start of a ladder
    for (int i = 0; i < board->num_ladders; i++) {
        if (board->ladders[i].start == position) {
            return board->ladders[i].end;
        }
    }

    // Check if position is the start of a snake
    for (int i = 0; i < board->num_snakes; i++) {
        if (board->snakes[i].start == position) {
            return board->snakes[i].end;
        }
    }

    return position; // No jump
}

/**
 * Checks whether a new snake/ladder conflicts with any existing ones.
 * Returns true if the start or end overlaps with any other object.
 */
bool board_is_conflict(const Board* board, int start, int end) {
    for (int i = 0; i < board->num_snakes; i++) {
        if (board->snakes[i].start == start || board->snakes[i].end == end ||
            board->snakes[i].start == end || board->snakes[i].end == start) {
            return true;
        }
    }

    for (int i = 0; i < board->num_ladders; i++) {
        if (board->ladders[i].start == start || board->ladders[i].end == end ||
            board->ladders[i].start == end || board->ladders[i].end == start) {
            return true;
        }
    }

    return false;
}

/**
 * Prints the board configuration including ladders and snakes.
 * Useful for debugging and verification.
 */
void board_print(const Board* board) {
    if (!board) return;

    printf("Board Size: %dx%d (%d squares)\n", board->width, board->height, board->size);

    printf("Ladders (%d):\n", board->num_ladders);
    for (int i = 0; i < board->num_ladders; i++) {
        printf("  Ladder from %d to %d\n", board->ladders[i].start, board->ladders[i].end);
    }

    printf("Snakes (%d):\n", board->num_snakes);
    for (int i = 0; i < board->num_snakes; i++) {
        printf("  Snake from %d to %d\n", board->snakes[i].start, board->snakes[i].end);
    }
}
