#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float r1[2] = {0};
float r2[2] = {0};
float p_best;
float *p_best_coordinates;

struct Particle {
    float v_max;
    float c1;
    float c2;
    float weight;
    int number_of_population;
    float array_of_speed[10];
    float p;
    float *p_coordinates;
    float *p_coordinates_best_for_obj;
};

float f(float x[2]) {
    int A = 10;
    float result = 0;
    for (int i = 0; i < 2; i++) {
        result = result + x[i] * x[i] - A * cos(2 * M_PI * x[i]);
    }
    return A * 2 + result;
}

struct Particle init(struct Particle particle,
                     float v_max, float weight,
                     int number_of_population, float coordinates[],
                     float c1, float c2) {
    particle.v_max = v_max;
    particle.weight = weight;
    particle.number_of_population = number_of_population;
    particle.p_coordinates = coordinates;
    particle.c1 = c1;
    particle.c2 = c2;
    particle.p = f(particle.p_coordinates);
    return particle;
}

float new_matrix[2] = {0, 0};

float* difference(float matrix1[], float matrix2[]) {
    for (int i = 0; i < 2; i++) {
        new_matrix[i] = matrix1[i] - matrix2[i];
    }
    return new_matrix;
}

float dot(float matrix1[], float matrix2[]) {
    float result = 0;
    for (int i = 0; i < 2; i++) {
        result += matrix1[i] * matrix2[i];
    }
    return result;
}

struct Particle particle_movement(struct Particle particle) {
    particle.array_of_speed[0] = particle.v_max;
    printf("\nflag1");
    for (int i = 1; i < 10; i++) {
        particle.array_of_speed[i] = particle.array_of_speed[i - 1] * particle.weight;
        particle.array_of_speed[i] +=
                particle.c1 * dot(r1, difference(p_best_coordinates, particle.p_coordinates)) +
                particle.c2 * dot(r2, difference(p_best_coordinates, particle.p_coordinates));

        if(particle.array_of_speed[i] > particle.v_max || particle.array_of_speed[i] * -1 > particle.v_max) {
            particle.array_of_speed[i] = particle.v_max;
        }
        particle.p_coordinates[0] = particle.p_coordinates[0] + particle.array_of_speed[i];
        particle.p_coordinates[1] = particle.p_coordinates[1] + particle.array_of_speed[i];

        if(particle.p > f(particle.p_coordinates)) {
            particle.p = f(particle.p_coordinates);
            particle.p_coordinates_best_for_obj = particle.p_coordinates;
            printf("\nflag");
        }
    }

    if(p_best > particle.p) {
        p_best = particle.p;
        p_best_coordinates = particle.p_coordinates_best_for_obj;
    }

    return particle;

}

void print_particle(struct Particle particle) {
    printf("%f %f %i\n", particle.v_max, particle.weight, particle.number_of_population);

    for (int i = 0; i < 2; i++) {
        printf("%f", particle.p_coordinates[i]);
    }

    printf("\nc1: %f; c2: %f; p: %f", particle.c1, particle.c2, particle.p);
}

float random(float min, float max) {
    return min + (max - min) / RAND_MAX * rand();
}

int test() {
    float coordinates[2] = {0, 0};
    struct Particle particle = init(particle, 10.9, 3.4, 0, coordinates, random(-5.12f, 5.12f), random(-5.12f, 5.12f));

    if (particle.c1 == 0 || particle.c2 == 0 || particle.p != 0) {
        return 1;
    }

    print_particle(particle);

    printf("\nmatrix");
    float matrix1[2] = {3.5f, 4};
    float matrix2[2] = {10, 1.2f};

    float *dif = difference(matrix1, matrix2);
    for(int i=0;i<2;i++){
        printf("\n%f", dif[i]);
    }

    float multiplication = dot(matrix1, matrix2);
    printf("\nmultiplication is %f", multiplication);

    return 0;
}

int main() {
    srand(time(NULL));

    for (int i = 0; i < 2; i++) {
        r1[i] = random(0, 1);
        r2[i] = random(0, 1);
    }
    printf("r1[0]: %f, r1[1]: %f", r1[0], r1[1]);
    printf("\nr2[0]: %f, r2[1]: %f", r2[0], r2[1]);
    printf("\n--------------------------------\n");

    float coordinates[2] = {0, 0};
    for (int i = 0; i < 20; i++) {
        coordinates[0] = random(-5.12f, 5.12f);
        coordinates[1] = random(-5.12f, 5.12f);
        struct Particle particle;
        if (i < 10) {
            particle = init(particle, 10.9f, 3.4f, 0, coordinates, random(0, 1), random(0, 1));
//            particle = particle_movement(particle);
        } else {
            particle = init(particle, 10.9f, 3.4f, i / 10, coordinates, random(0, 1), random(0, 1));
//            particle = particle_movement(particle);
        }
        print_particle(particle);
    }

//    printf("\np_best: %f", p_best);
//    printf("\ncoordinates: %f, %f", p_best_coordinates[0], p_best_coordinates[1]);

    return 0;
}
