import random

from deap import base
from deap import creator
from deap import tools

import numpy

import matplotlib.pyplot as plt

import csv

trainingData = numpy.genfromtxt('training.csv', delimiter=',')
testingData = numpy.genfromtxt('testing.csv', delimiter=',')

creator.create("FitnessMin", base.Fitness, weights=(-1.0,))
creator.create("Individual", list, fitness=creator.FitnessMin)

toolbox = base.Toolbox()
# Attribute generator
toolbox.register("attr_real", random.random)
# Structure initializers
toolbox.register("individual", tools.initRepeat, creator.Individual, toolbox.attr_real, 4)
toolbox.register("population", tools.initRepeat, list, toolbox.individual)

def	prediction(coeffs,	row):
    dotproduct = sum(c * r for c,r in zip(coeffs, row))

    return (dotproduct/sum(coeffs))

def evalPrediction(data, individual):
    results = []

    for row in data:
            results = pow(row[4] - prediction(individual, row[0:3]), 2)

    return numpy.sum (results),

toolbox.register("evaluate", evalPrediction, trainingData)

toolbox.register("mate", tools.cxTwoPoint)

def	mutUniformReal(individual,	indpb=0.2):
    size = len(individual)
    for i in range(size):
        if random.random() < indpb:
            individual[i] = random.uniform(0.0,1.0)
	return	individual,
toolbox.register("mutate",	mutUniformReal,	indpb=0.2)
toolbox.register("select", tools.selTournament, tournsize=3)

def checkBounds(min, max):
    def decorator(func):
        def wrapper(*args, **kargs):
            offspring = func(*args, **kargs)
            for child in offspring:
                for i in xrange(len(child)):
                    if child[i] > max:
                        child[i] = max
                    elif child[i] < min:
                        child[i] = min
            return offspring
        return wrapper
    return decorator


toolbox.decorate("mate", checkBounds(0, 1))
toolbox.decorate("mutate", checkBounds(0, 1))


def main():
    CXPB, MUTPB, NGEN, NRUNS = 0.5, 0.2, 15, 15

    final_fitnesses = []

    for bla in range(NRUNS):
        # Begin the evolution
        pop = toolbox.population(n=300)

        # Evaluate the entire population
        fitnesses = list(map(toolbox.evaluate, pop))
        for ind, fit in zip(pop, fitnesses):
            ind.fitness.values = fit

        for g in range(NGEN):
            print("-- Generation %i --" % g)

            # Select the next generation individuals
            offspring = toolbox.select(pop, len(pop))
            # Clone the selected individuals
            offspring = list(map(toolbox.clone, offspring))


            # Apply crossover and mutation on the offspring
            for child1, child2 in zip(offspring[::2], offspring[1::2]):
                if random.random() < CXPB:
                    toolbox.mate(child1, child2)
                    del child1.fitness.values
                    del child2.fitness.values

            for mutant in offspring:
                if random.random() < MUTPB:
                    toolbox.mutate(mutant)
                    del mutant.fitness.values

             # Evaluate the individuals with an invalid fitness
            invalid_ind = [ind for ind in offspring if not ind.fitness.valid]
            fitnesses = map(toolbox.evaluate, invalid_ind)
            for ind, fit in zip(invalid_ind, fitnesses):
                ind.fitness.values = fit

            pop[:] = offspring

        final_fitnesses.append (evalPrediction(testingData, tools.selBest(pop, 1)[0]))

    plt.boxplot(final_fitnesses)
    plt.show ()

main()
