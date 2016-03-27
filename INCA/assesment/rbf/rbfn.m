load('workspace.mat');

[W, dmax, c, neuron_count] = rbfn_train(input_train, x_train, 350);

mse = rbfn_test(input_eval, x_eval, W, dmax, c, neuron_count)

