#include "dice.h"
#include <stdio.h>

/**
 * Initializes the random number generator.
 * This function should be called once before using any dice rolls.
 */
void dice_init(void) {
    // Seed the random number generator using current time
    srand((unsigned int)time(NULL));
}

/**
 * Rolls a fair (uniform) die with a specified number of faces.
 * Returns a random number between 1 and `faces` (inclusive).
 * If `faces` is invalid, returns 1 and prints a warning.
 */
int dice_roll_uniform(int faces) {
    if (faces <= 0 || faces > MAX_DIE_FACES) {
        fprintf(stderr, "Invalid number of die faces: %d\n", faces);
        return 1;
    }

    return (rand() % faces) + 1;
}

/**
 * Rolls a non-uniform die based on a given probability distribution.
 *
 * @param faces Number of die faces
 * @param probabilities Array of `faces` positive integers representing weights for each face
 * @return A random die face (1-based index) according to the weighted distribution
 */
int dice_roll_non_uniform(int faces, const int* probabilities) {
    if (!probabilities || faces <= 0 || faces > MAX_DIE_FACES) {
        return dice_roll_uniform(faces); // fallback to fair roll
    }

    // Calculate total weight from the probability array
    int total = 0;
    for (int i = 0; i < faces; i++) {
        if (probabilities[i] <= 0) return dice_roll_uniform(faces); // invalid weight
        total += probabilities[i];
    }

    // Generate random number between 1 and total weight
    int r = (rand() % total) + 1;

    // Find which face corresponds to the random weight
    int cumulative = 0;
    for (int i = 0; i < faces; i++) {
        cumulative += probabilities[i];
        if (r <= cumulative) {
            return i + 1; // faces are 1-based
        }
    }

    // Fallback (should not happen if probabilities are valid)
    return faces;
}

/**
 * Validates the given probability array for a non-uniform die.
 * Returns true if all values are positive and within bounds.
 */
bool dice_validate_probabilities(const int* probabilities, int faces) {
    if (!probabilities || faces <= 0 || faces > MAX_DIE_FACES) {
        return false;
    }

    for (int i = 0; i < faces; i++) {
        if (probabilities[i] <= 0) {
            return false; // All weights must be strictly positive
        }
    }

    return true;
}
