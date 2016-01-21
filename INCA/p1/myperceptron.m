% THIS IS WRITTEN AS A FUNCTION
% REMOVE THE DECLARATION LINE BELOW TO USE IT AS A SCRIPT

% [loop, w] = myperceptron(data2d(1:2,:), data2d(3,:), 300);

function [loop, w] = myperceptron(dataM,classN,maxL)

% dataM - matrix containing data, with variables as rows and observations as columns
% classN - vector (1 x n matrix) of class labels {-1,+1}
% maxL - maximum number of iterations you set for the algorithm
% loop - returns number of iterations
% w - return the weight vector, including bias weight

% You could set a learning rate
eta = 0.1;

% get the number of data points and number of variables
N = size(dataM,2); % number of data points
v = size(dataM,1); % number of input variables

% the Perceptron needs a bias input as well
% Add a row of 1's to the data matrix for bias inputs
dataM = [ ones(1,N) ; dataM ];

% initialise the weight vector to random values()
w = rand(v+1,1); % there are v+1 weights including the weight on the bias

% set a flag for whether data is correctly classified 
correct = -1; % initialise it to 'fail'

% we will calculate the output from the neuron as the weighted sum of its
% inputs, and threshold it to give a class label of {-1,+1}.
% initialise the vector to record the calculated class
class = zeros(1,N);

% initialise a loop counter
loop = 0;

% repeat the following until it converges on a correct classifier
% or we reach the maximum number of iterations
while (correct == -1) && (loop < maxL)
    
    loop = loop + 1;
    
    % check whether patterns are all classified correctly
    correct = 1; % assume they are to start with...
    
    %% INSERT YOUR CODE HERE TO CALCULATE THE CLASS FOR ALL OBSERVATIONS 
    for point = 1:N
        if w(1) * dataM(1, point) + w(2) * dataM(2, point) + w(3)* dataM(3, point) > 0
            class(point) = 1;
        else
            class(point) = -1;
        end
    end
    
    % compare calculated class and desired class    
    if any(class ~= classN)
        correct = -1; % set the flag to fail if any don't match
    end

    % if any observation is classified incorrectly, adjust the weights
    if correct == -1
        for point = 1:N
            if class(point) ~= classN(point)
                for weight = 1:v+1
                    if (classN(point) < 0 && class(point) > 0)
                        w(weight) = w(weight) - eta * dataM(weight, point);
                    end
                    if (classN(point) > 0 && class(point) < 0)
                        w(weight) = w(weight) + eta * dataM(weight, point);
                    end
                end
            end
        end
    end
end
