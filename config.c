#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Loads a board configuration from a file.
 * The file should contain lines in the format:
 *   BOARD <width> <height>
 *   LADDER <start> <end>
 *   SNAKE <start> <end>
 * Lines starting with '#' or empty lines are ignored.
 *
 * @param board Pointer to the board to initialize and populate.
 * @param filename Name/path of the configuration file.
 * @return true if the board was successfully initialized, false otherwise.
 */
bool load_board_from_file(Board* board, const char* filename) {
    if (!board || !filename) return false;

    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open board configuration file");
        return false;
    }

    char line[256];                   // Buffer for reading each line
    int width = 10, height = 10;      // Default board size (in case BOARD line is missing)
    bool board_initialized = false;   // Flag to prevent early use before init

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        char temp[16];

        // Skip comments and blank lines
        if (line[0] == '#' || sscanf(line, "%15s", temp) == 0)
            continue;

        int start, end;

        // Check for board size definition
        if (sscanf(line, "BOARD %d %d", &width, &height) == 2) {
            board_init(board, width, height);
            board_initialized = true;

        // Check for ladder definition
        } else if (sscanf(line, "LADDER %d %d", &start, &end) == 2) {
            if (!board_initialized) board_init(board, width, height);
            if (!board_add_ladder(board, start, end)) {
                fprintf(stderr, "⚠️ Invalid ladder from %d to %d\n", start, end);
            }

        // Check for snake definition
        } else if (sscanf(line, "SNAKE %d %d", &start, &end) == 2) {
            if (!board_initialized) board_init(board, width, height);
            if (!board_add_snake(board, start, end)) {
                fprintf(stderr, "⚠️ Invalid snake from %d to %d\n", start, end);
            }

        // Unknown line format
        } else {
            fprintf(stderr, "⚠️ Unknown line format: %s", line);
        }
    }

    fclose(file);
    return board_initialized;
}
