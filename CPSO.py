import random
from math import cos, pi
from random import uniform
from random import random
import numpy as np


def f(x: list):  # функция Растригена от -5.12 до 5.12
    a = 10
    result = 0
    n = len(x)
    for i in range(n):
        result += x[i] ** 2 - a * cos(2 * pi * x[i])

    return a * n + result


class Particle:
    v_max = 0
    c1 = 0  # весовой коэффициент 1, для каждой частицы своё
    c2 = 0  # весовой коэффициент 2, для каждой частицы своё

    r1: np.array([])  # весовой коэффициент, вектор, един для всех частиц
    r2: np.array([])  # весовой коэффициент, вектор, един для всех частиц

    weight = 3.4  # еще один весовой коэффициент, птица в кг

    number_of_population = 0  # номер популяции, поколения

    array_of_speed = np.zeros(10)  # матрица скоростей для агента в разные момент времени

    p_best = 10000  # глобально лучшее решение для всех частиц на итерации t
    p_best_coordinates = np.array([0, 0])
    p = 10000  # лучшее решение для конкретного агента
    p_coordinates_now: np.ndarray = np.array([0, 0])  # координаты на данный момент
    p_coordinates: np.ndarray = np.array([0, 0])

    def __int__(self, coordinates, v_max, number_of_population=0):
        self.p_coordinates_now = coordinates
        self.p_coordinates = coordinates
        self.p = min(f(self.p_coordinates_now), self.p)
        self.v_max = v_max
        self.number_of_population = number_of_population
        self.array_of_speed[0] = uniform(-1 * self.v_max, self.v_max)
        self.random_generate_fields()

    def random_generate_fields(self):
        self.c1 = random()
        self.c2 = random()

        for i in range(1, len(self.array_of_speed)):
            self.array_of_speed[i] = self.array_of_speed[i - 1] * self.weight + \
                                     self.c1 * np.dot(self.r1, Particle.p_best_coordinates - self.p_coordinates_now) + \
                                     self.c2 * np.dot(self.r2, Particle.p_best_coordinates - self.p_coordinates_now)
            if abs(self.array_of_speed[i]) > self.v_max:  # ограничение скорости, пункт 13
                if self.array_of_speed[i] > 0:
                    self.array_of_speed[i] = self.v_max
                else:
                    self.array_of_speed[i] = -1 * self.v_max
            self.p_coordinates_now = self.p_coordinates_now + self.array_of_speed[i]  # пункт 14

            if self.p > f(self.p_coordinates_now):
                self.p = f(self.p_coordinates_now)
                self.p_coordinates = self.p_coordinates_now

        if self.p < Particle.p_best:  # 16 пункт
            Particle.p_best = self.p
            Particle.p_best_coordinates = self.p_coordinates

    # def __str__(self):
    #     return "-------------------\n" + \
    #         "c1: " + np.array_str(self.c1) + "\n" + \
    #         "c2: " + np.array_str(self.c2) + "\n" + \
    #         "r1: " + np.array_str(self.r1) + "\n" + \
    #         "r2: " + np.array_str(self.r2) + "\n" + \
    #         "weight: " + str(self.weight) + "\n" + \
    #         "number_of_population: " + str(self.number_of_population) + "\n" + \
    #         "p_global_best: " + str(Particle.p_best) + "\n" + \
    #         "p_global_best_coordinates: " + np.array_str(Particle.p_best_coordinates) + "\n" + \
    #         "p: " + str(self.p) + "\n" + \
    #         "p_coordinates: " + np.array_str(self.p_coordinates)


Particle.r1 = np.array([random(), random()])
Particle.r2 = np.array([random(), random()])
print(Particle.r1, Particle.r2, "\n-------------------------------------------------")

for i in range(30):
    if i < 10:
        particle = Particle()
        particle.__int__(np.array([uniform(-5.12, 5.12), uniform(-5.12, 5.12)]), 0.9)
    else:
        particle = Particle()
        particle.__int__(np.array([uniform(-5.12, 5.12), uniform(-5.12, 5.12)]), 1.5, i // 10)
    print(i + 1, "p: ", particle.p, particle.p_coordinates)
print("p_best: ", Particle.p_best, Particle.p_best_coordinates)
