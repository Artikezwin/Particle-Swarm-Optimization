import time
from math import cos, pi
from random import uniform
from random import random
import numpy as np
from numba import njit


@njit
def f(x: np.ndarray):  # функция Растригена от -5.12 до 5.12
    a = 10
    result = 0
    n = len(x)
    for i in range(n):
        result += x[i] ** 2 - a * cos(2 * pi * x[i])

    return a * n + result


@njit
def main(v_max: float):
    r1 = np.random.rand(2)
    r2 = np.random.rand(2)
    weight: float = 3.4
    p_global_best: float = 1000
    p_best_coordinates: np.ndarray = np.zeros(2)

    for j in range(100_000):

        coordinates = np.array([uniform(-5.12, 5.12), uniform(-5.12, 5.12)])
        c1 = random()
        c2 = random()
        p_coordinates_now = coordinates
        p_coordinates = coordinates
        p = f(coordinates)
        array_of_speed = np.zeros((10, 2))

        array_of_speed[0][0] = uniform(-1 * v_max, v_max)
        array_of_speed[0][1] = uniform(-1 * v_max, v_max)

        for i in range(1, len(array_of_speed)):
            array_of_speed[i] = array_of_speed[i - 1] * weight + \
                                c1 * r1 * (p_best_coordinates - p_coordinates_now) + \
                                c2 * r2 * (p_best_coordinates - p_coordinates_now)

            if array_of_speed[i][0] > 0:
                array_of_speed[i][0] = min(array_of_speed[i][0], v_max)
            else:
                array_of_speed[i][0] = max(array_of_speed[i][0], v_max)

            if array_of_speed[i][1] > 0:
                array_of_speed[i][1] = min(array_of_speed[i][1], v_max)
            else:
                array_of_speed[i][1] = max(array_of_speed[i][1], v_max)

            p_coordinates_now = p_coordinates_now + array_of_speed[i]

            if p > f(p_coordinates_now):
                p = f(p_coordinates_now)
                p_coordinates = p_coordinates_now

        if p_global_best > p:
            p_best_coordinates = p_coordinates
            p_global_best = p

    # print("global_best:", p_global_best, "coordinates:", p_best_coordinates)


start = time.time()
main(1.9)
end = time.time() - start
print(end, "seconds")
