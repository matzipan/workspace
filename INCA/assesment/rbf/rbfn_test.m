function [mse] = rbfn_test(input, output, W, dmax, c, m1)
%input = mapstd(input);
%output = mapstd(output);

X2 = input';
D2 = output';

N = size(X2,2);                         

points = [X2 c];                       
dist = squareform(pdist(points'));      
dist = dist(1:N,N+1:N+m1);
F = exp((-m1/(dmax*dmax))*(dist.*dist));

%output neuron
Dcalc = F*W;

D = (Dcalc-D2').^2;
mse = sum(D)/numel(D);

end