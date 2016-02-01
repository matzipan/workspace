function [W, dmax, c, neuron_count] = rbfn_train(input, output, neuron_count)

%input = mapstd(input);
%output = mapstd(output);
X1 = input';
D1 = output';

N = size(X1,2); % Number of data points
sample = randsample(N,neuron_count,true);

[idx c] = kmeans(X1', neuron_count);
c = c';

points = [X1 c]; % Attach the points to the matrix
dist = squareform(pdist(points')); 
distance = dist(1:N,N+1:N+neuron_count);          
dc = dist(N+1:end,N+1:end);
dmax = max(max(dc));                      
F = exp((-neuron_count/(dmax*dmax))*(distance.*distance)); 
pF = pinv(F);
W = pF * D1';

end