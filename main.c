#include "Result.h"
#include <stdio.h>

struct Result test_rastrigin(int dimension);

int main() {
    int dimension = 2;
    Result result = test_rastrigin(dimension);
    printf("Program completed in %f seconds", result.time_spent);

    printf("\nglobal best: %f", result.best_y);

    printf("\ncoordinates: ");
    for (int i = 0; i < dimension - 1; i++) {
        printf("%f ", result.best_solution[i]);
    }
    return 0;
}