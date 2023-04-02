#include "Particle.h"
#include "Result.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const double PI = 3.14;

float *r1;
float *r2;
float global_best = (float) INT_MAX;
float *p_best_coordinates;
const int kol_in_population = 400;

float rastrigin(float x[], int dimension) {
    int A = 10;
    float result = 0;
    for (int i = 0; i < dimension - 1; i++) {
        result = result + x[i] * x[i] - A * cos(2 * PI * x[i]);
    }
    return A * (dimension-1) + result;
}

float random(float min, float max) {
    return min + (max - min) / RAND_MAX * rand();
}

float *addition(float matrix1[], float matrix2[], int dimension) {
    float *vrem = malloc((dimension-1) * sizeof(float));
    for (int i = 0; i < dimension - 1; i++) {
        vrem[i] = matrix1[i] + matrix2[i];
    }
    return vrem;
}

float *subtraction(float matrix1[], float matrix2[], int dimension) {
    float *vrem = malloc((dimension-1) * sizeof(float));
    for (int i = 0; i < dimension - 1; i++) {
        vrem[i] = matrix1[i] - matrix2[i];
    }
    return vrem;
}

float *mul_on_number(float matrix1[], float number, int dimension) {
    float *vrem = malloc((dimension-1) * sizeof(float));
    for (int i = 0; i < dimension - 1; i++) {
        vrem[i] = matrix1[i] * number;
    }
    return vrem;
}

float *mul(float matrix1[], float matrix2[], int dimension) {
    float *vrem = malloc((dimension - 1) * sizeof(float));
    for (int i = 0; i < dimension - 1; i++) {
        vrem[i] = matrix1[i] * matrix2[i];
    }
    return vrem;
}

void print_particle(Particle particle, int dimension) {
    printf("\nv_max: %f; weight: %f", particle.v_max, particle.weight);

    printf("\np_coordinates: ");
    for (int i = 0; i < dimension - 1; i++) {
        printf("%f ", particle.p_coordinates[i]);
    }

    printf("\nc1: ");
    for (int i = 0; i < dimension - 1; i++) {
        printf("%f ", r1[i]);
    }

    printf("\nc2: ");
    for (int i = 0; i < dimension - 1; i++) {
        printf("%f ", r2[i]);
    }

}

void particle_movement(Particle particle, float (*f)(float *, int), int dimension) {

    if (global_best > particle.p) {
        global_best = particle.p;
        p_best_coordinates = particle.p_coordinates_best_for_obj;
    }

    for (int k = 0; k < dimension - 1; k++) {
        particle.array_of_speed[0][k] = random(-1 * particle.v_max, particle.v_max);
    }

    for (int i = 1; i < kol_in_population; i++) {
        particle.array_of_speed[i] = mul_on_number(particle.array_of_speed[i - 1], particle.weight, dimension);
        particle.array_of_speed[i] = addition(
                particle.array_of_speed[i],
                mul(
                        mul_on_number(r1, particle.c1, dimension),
                        subtraction(p_best_coordinates, particle.p_coordinates, dimension), dimension),
                dimension);
        particle.array_of_speed[i] = addition(
                particle.array_of_speed[i],
                mul(
                        mul_on_number(r2, particle.c2, dimension),
                        subtraction(p_best_coordinates, particle.p_coordinates, dimension), dimension),
                dimension);

        for (int j = 0; j < dimension - 1; j++) {
            if (particle.array_of_speed[i][j] > particle.v_max && particle.array_of_speed[i][j] > 0) {
                particle.array_of_speed[i][j] = particle.v_max;
            } else if (particle.array_of_speed[i][j] < particle.v_max && particle.array_of_speed[i][j] < 0) {
                particle.array_of_speed[i][j] = -1 * particle.v_max;
            }
        }

        particle.p_coordinates = addition(particle.p_coordinates, particle.array_of_speed[i], dimension);

        if (particle.p > f(particle.p_coordinates, dimension)) {
            particle.p = f(particle.p_coordinates, dimension);
            particle.p_coordinates_best_for_obj = particle.p_coordinates;
        }
    }


    if (global_best > particle.p) {
        global_best = particle.p;
        p_best_coordinates = particle.p_coordinates_best_for_obj;
    }

    //return particle;
}

void generate_agents(int dimension, float (*f)(float *, int)) {
    r1 = malloc((dimension - 1) * sizeof(float));
    r2 = malloc((dimension - 1) * sizeof(float));
    p_best_coordinates = malloc((dimension - 1) * sizeof(float));

    for (int i = 0; i < dimension - 1; i++) {
        r1[i] = random(0, 1);
        r2[i] = random(0, 1);
    }

    /** Output r1, r2
     * printf("r1: ");
    for (int i = 0; i < dimension - 1; i++) {
        printf("%f ", r1[i]);
    }

    printf("\nr2: ");
    for (int i = 0; i < dimension - 1; i++) {
        printf("%f ", r2[i]);
    }

    printf("\n----------------------------------");*/

    Particle particle;
    for (int i = 0; i < 50; i++) {
        particle.array_of_speed = (float **) malloc(kol_in_population * sizeof(float *));
        for (int j = 0; j < kol_in_population; j++) {
            particle.array_of_speed[j] = (float *) malloc((dimension - 1) * sizeof(int));
        }

        particle.v_max = 1.354f;
        particle.c1 = random(0, 1);
        particle.c2 = random(0, 1);

        particle.weight = 4.5f;
        particle.p_coordinates = malloc((dimension-1) * sizeof(float));

        for (int j = 0; j < dimension - 1; j++) {
            particle.p_coordinates[j] = random(-5.12f, 5.12f);
        }

        particle.p_coordinates_best_for_obj = malloc((dimension-1) * sizeof(float));
        particle.p = f(particle.p_coordinates, dimension);

        for(int j = 0; j < dimension - 1; j++) {
            particle.p_coordinates_best_for_obj[j] = particle.p_coordinates[j];
        }

        //print_particle(particle, dimension);

        particle_movement(particle, f, dimension);

        free(particle.array_of_speed);
        free(particle.p_coordinates);
        free(particle.p_coordinates_best_for_obj);
    }
}


Result test_rastrigin(int dimension) {
    Result result;
    double time_spent = 0.0;

    clock_t begin = clock();

    srand(time(NULL));

    generate_agents(dimension, rastrigin);

    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    result.time_spent = time_spent;

    result.best_y = global_best;

    result.best_solution = p_best_coordinates;

    return result;
}