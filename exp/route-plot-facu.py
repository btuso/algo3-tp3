import matplotlib.pyplot as plt
from sys import argv
import sys
from itertools import cycle
import numpy as np
import copy
import math
import pdb
from collections import defaultdict

class dotdict(dict):
    __getattr__ = dict.get
    __setattr__ = dict.__setitem__
    __delattr__ = dict.__delitem__

def main(solution, dataset):
    file = 'withouth-adaptative'
    routes = load_routes(solution)
    dataset = load_dataset(dataset)
    do_plot(dataset.points, dataset.warehouse, routes)
    total_distance = get_total_distance(dataset.warehouse, dataset.points, routes)

    legend(True, total_distance)

    plt.draw()
    plt.show()

    # plt.savefig(resolve_image_name(solution), dpi=320)

def resolve_image_name(solution):
    script_path = sys.path[0]
    return script_path + "/images/" + solution.split('.sol')[0] + ".png"

def legend(toggle_total_distance, total_distance):
    if(toggle_total_distance):
        total_label = r'Total$\approx%.1f$' % total_distance
        plt.plot([], [], label=total_label, color="black")

    plt.legend()

def load_dataset(file):
    f = open(file)
    dataset = dotdict()

    lines =  f.read().splitlines()
    dataset.capacity = lines[0].strip()
    dataset.warehouse = dotdict()
    dataset.warehouse.x = float(lines[1].split(',')[0])
    dataset.warehouse.y = float(lines[1].split(',')[1])

    dataset.points = []
    for line in lines[2:]:
        point = dotdict()
        point.x = float(line.split(',')[0])
        point.y = float(line.split(',')[1])
        point.demand = float(line.split(',')[2])
        dataset.points.append(point)
    f.close();
    return dataset

def load_routes(file):
    f = open(file)
    next(f)
    routes = []

    for line in f.read().splitlines():
        route = []
        route.append(0)
        for point in line.strip().split(' '):
            route.append(int(point))
        route.append(0)
        routes.append(route)
    f.close();
    return routes

def do_plot(points, warehouse, routes):
    setup(warehouse)
    plot_routes(warehouse, points, routes)

def setup(warehouse):
    plt.style.use('default')
    # plt.rcParams["figure.figsize"] = (16, 4)

    plt.plot(warehouse.x, warehouse.y, marker='*', color='black', linestyle='', markersize=10.0)

#     plt.title('Puntos y depósito')
#     plt.xlabel('x')
#     plt.ylabel('y')

    plt.grid(True)
    plt.grid(b=True, which='major', color='black', linestyle='dotted', alpha=0.1)
    plt.grid(b=True, which='minor', color='black', linestyle='dotted', alpha=0.05)
    plt.minorticks_on()

def plot_routes(warehouse, points, routes):
    colour_codes = get_cycler()

    for route in routes:
        p_x = []
        p_y = []
        p_d = []

        for point in route:
            if point == 0:
                p_x.append(warehouse.x)
                p_y.append(warehouse.y)
                p_d.append(0)
            else:
                p_x.append(points[point - 1].x)
                p_y.append(points[point - 1].y)
                p_d.append(points[point - 1].demand * 7)

        route_distance = get_route_distance(warehouse, points, route)
        route_label = r'Distancia$\approx%.1f$' % route_distance
        route_color = next(colour_codes)

        plt.plot(p_x, p_y, label=route_label, linewidth=1.0, linestyle='-', color=route_color)
        plt.scatter(p_x, p_y, marker='o', s=p_d, color=route_color, zorder=10)

def get_total_distance(warehouse, points, routes):
    total_distance = 0

    for route in routes:
        total_distance += get_route_distance(warehouse, points, route)

    return total_distance

def get_route_distance(warehouse, points, route):
    route = [0] + route + [0]
    points = [warehouse] + points

    d = 0
    for i in range(1, len(route)):
        current_index = route[i]
        prev_index = route[i - 1]
        a = points[prev_index]
        b = points[current_index]

        d += math.sqrt(math.pow(a.x - b.x, 2) + math.pow(a.y - b.y, 2))

    return d

def get_cycler():
    colour_codes = map('C{}'.format, cycle(range(10)))
    next(colour_codes)
    next(colour_codes)

    return colour_codes

# pdb.set_trace()
if(len(argv) == 3):
    solution = argv[1]
    dataset = argv[2]
    main(solution, dataset)
else:
    print("falto solution o dataset")
