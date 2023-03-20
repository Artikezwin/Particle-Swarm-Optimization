#ifndef CPSOWITHC_PARTICLE_H
#define CPSOWITHC_PARTICLE_H

struct Particle {
    float v_max;
    float c1;
    float c2;
    float weight;
    int number_of_population;
    float array_of_speed[10];
    float p;
    float p_coordinates[2];
    float p_coordinates_best_for_obj[2];
};

#endif //CPSOWITHC_PARTICLE_H
