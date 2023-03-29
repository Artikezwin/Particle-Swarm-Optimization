#ifndef CPSOWITHC_PARTICLE_H
#define CPSOWITHC_PARTICLE_H

typedef struct{
    float v_max;
    float c1;
    float c2;
    float weight;
    float **array_of_speed;
    float p;
    float *p_coordinates;
    float *p_coordinates_best_for_obj;
} Particle;

#endif //CPSOWITHC_PARTICLE_H
