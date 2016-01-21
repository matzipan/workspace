function [newW, newV, E] = backprop2(X,W,V,D,eta,epochs)
% [newW, newV, E] = backprop2(X,W,V,D,eta,epochs)
%   X is n x N, where each column is a data point.
%   W is h x (n+1), giving the weights to the hidden units and their biases.
%   V is m x (h+1), giving the weights and biases to output nodes
%   D is m x N, giving the desired ouput values for each sample.
%   eta is the learning rate.
%   epochs is the number of weight updates.
%
%   newW and newV are the network weights after learning.
%   E is a vector of mean error values, one for each epoch.

% from the data, find the number of datapoints (N) and the number of input
% values for each datapoint (h)
N = size(X,2); h = size(W,1);

% add a row of 1s to the data as the bias inputs
Xp = [ ones(1,N); X];

% the vector E is going to record the error after each epoch (pass through
% the training data.)
E = zeros(epochs);

for j=1:epochs
    for i=1:N
        % forward pass
        for hidden = 1:size(W,1)
            Z(hidden) =  sigmf(dot(W(hidden, :),Xp(:,i).'), [-1, 0]) % outputs from hidden nodes
        end
        
        Zp  =   [1 Z] % ...include bias
        
        for output = 1:size(V,1)
            Y(output)   =  sigmf(dot(V(output,:),Zp), [-1,0]) % outputs from output nodes
        end
        
        % accumulate total error for epoch j, for plotting
        E(j) = E(j) + sum(sum(Y-D(:,i).').^2/(2 * N)); 
        
        e = D(:,i).'-Y
        
        % backward pass
        for output = 1:size(V,1)
            Ylg(output) =  e(output)*Y(output)*(1-Y(output)) % local gradient at output nodes
        end
        
        for hidden = 1:size(W,1)
            Zlg(hidden) = Z(hidden)*(1-Z(hidden))*sum(dot(V(:,hidden), Ylg))  % local gradient at hidden nodes
        end
        
        for output = 1:size(V,2)
           V(:,output) = eta*times(Ylg,Y) % calculate weight change at output layer
        end
        
        for hidden = 1:size(W,2)
            W(:,hidden) = eta*times(Zlg,Z) % calculate weight change at hidden layer
        end
    end
end
newW = W; newV = V;

%backprop2(X1, 2*rand(size(D1,1),size(X1,1)+1)-1,2*rand(size(D1,1), size(X1,1)+1)-1, D1, 0.1, 100)


