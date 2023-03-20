#include "Particle.h"

float f(const float x[2]);

struct Particle init(struct Particle particle,
                     float v_max, float weight,
                     int number_of_population, float coordinates[],
                     float c1, float c2);

float *difference(float matrix1[], float matrix2[]);

float dot(float matrix1[], float matrix2[]);

struct Particle particle_movement(struct Particle particle);

void print_particle(struct Particle particle);

int test();

float random(float min, float max);

int runnable();

int run_with_time();

int main() {
    return run_with_time();
}
