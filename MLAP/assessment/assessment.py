import argparse
from math import *
from itertools import *

def init_probabilities(adjacency_matrix):
    return list(imap(lambda incoming_count: [0.5] * int(pow(2, int(incoming_count))), imap(sum, izip(*adjacency_matrix))))

def process_data_line(line):
    return map(lambda x: float('nan') if x.startswith('nan') else float(x), line.split(','))

def process_adjacency_line(line):
    return map(int, line.split(','))

def print_probabilities(probabilities, adjacency_matrix):
    for variable_index, incoming_edges in enumerate(zip(*adjacency_matrix)):
        incoming_count = sum(incoming_edges)

        if incoming_count == 0:
            print "P(" + str(variable_index) + ") = " + str(probabilities[variable_index][0])
        else:
            conditioning_truth_val_sequences = get_sequences(incoming_count)

            conditioning_node_indices = list(compress(range(0, len(adjacency_matrix)), incoming_edges))

            print "Parents for node " + str(variable_index) + " are " + str(conditioning_node_indices)

            for incoming_truth_val_sequence in conditioning_truth_val_sequences:
                print "P(" + str(variable_index) + " = 1 | " + str(incoming_truth_val_sequence) + ") = " + str(get_probability_for_sequence(probabilities[variable_index], incoming_truth_val_sequence))

def get_sequences(repeat_count):
    return map(lambda line: map(int, line), list(product('01', repeat=repeat_count)))

def get_probability_for_sequence(probabilities, sequence):
    walking = probabilities
    for value in sequence:
        walking = probabilities[int(value)]

    return walking

def compute_likelihood(probabilities, data_matrix, adjacency_matrix):
    likelihood = 0
    for data_point in data_matrix:
        p = get_data_point_probability(data_point, probabilities, adjacency_matrix)

        if data_point == 0:
            p = 1 - p

        print p

        likelihood = likelihood + log(p)

    return likelihood

def get_data_point_probability(data_point, probabilities, adjacency_matrix):
    probability = 1

    for variable_index, incoming_edges in enumerate(izip(*adjacency_matrix)):
        incoming_count = sum(incoming_edges)

        if incoming_count == 0:
            probability = probability * probabilities[variable_index][0]
        else:
            conditioning_node_values = list(compress(data_point, incoming_edges))

            probability = probability * get_probability_for_sequence(probabilities[variable_index], conditioning_node_values)

    return probability

def get_filled_data_point(original_data_point, nan_fill):
    data_point = list(original_data_point) #make copy

    for index, value in enumerate(data_point):
        if isnan(value):
            data_point[index] = nan_fill.pop(0)

    return data_point


def e_step(probabilities, adjacency_matrix, data_matrix):
    imputed_data_matrix = []
    data_point_weights = []

    for original_data_point in data_matrix:
        nan_count = sum(imap(lambda component: 1 if isnan(component) else 0, original_data_point))

        if nan_count == 0:
            imputed_data_matrix.append(original_data_point)
            data_point_weights.append(1)
        else:
            nan_fills = get_sequences(nan_count)
            temp_data_matrix = []
            temp_weights = []

            for nan_fill in nan_fills:
                filled_data_point = get_filled_data_point(original_data_point, nan_fill)

                imputed_data_matrix.append(filled_data_point)
                temp_weights.append(get_data_point_probability(filled_data_point, probabilities, adjacency_matrix))

            imputed_data_matrix.extend(temp_data_matrix)
            data_point_weights.extend([float(i)/sum(temp_weights) for i in temp_weights])

    print "Current log-likelihood: "+ str(compute_likelihood(probabilities, imputed_data_matrix, adjacency_matrix))


    return [imputed_data_matrix, data_point_weights]

def m_step(e_step_results):
    imputed_data_matrix = e_step_results[0]
    data_point_weights = e_step_results[1]

    # @TODO for each variable, sum up over all data points and recompute

    return probabilities


parser = argparse.ArgumentParser(description='Estimating Bayesian network parameters from data with missing values')
parser.add_argument('adjacency_matrix_file', metavar='adjacency_matrix_file', type=open)
parser.add_argument('data_file', metavar='data_file', type=open)

args = parser.parse_args()

adjacency_matrix = map(process_adjacency_line, args.adjacency_matrix_file)
data_matrix = map(process_data_line, args.data_file)

probabilities = init_probabilities(adjacency_matrix)
print_probabilities(probabilities, adjacency_matrix)
steps = 0
likelihood = 0 #compute_likelihood(probabilities, data_matrix, adjacency_matrix)
#print "Current log-likelihood: " + str(likelihood)

while True:
    steps += 1

    probabilities = m_step(e_step(probabilities, adjacency_matrix, data_matrix))

    print_probabilities(probabilities, adjacency_matrix)

    current_likelihood = compute_likelihood(probabilities, data_matrix, adjacency_matrix)
    print "Current log-likelihood: "+ str(current_likelihood)

    if (current_likelihood - likelihood) < 0.0001:
        break

    likelihood = current_likelihood


print "Steps until convergence: "+ str(steps)
print "Final probabilites: "+ str(probabilities)
print "Log likelihood: "+ str(likelihood)
