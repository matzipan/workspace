function []=assessment(adjacency_matrix_file, data_file)

adjacency_matrix = dlmread(adjacency_matrix_file);
data = dlmread(data_file);

probabilities = repmat(0.5, size(adjacency_matrix, 1), 1);
steps = 0;
likelihood = 0;

while 1 
    steps = steps+1;
    
    disp(['Current probabilites: ', mat2str(probabilities)]);
    
    
    sequences = itertools('01', repeat = 

    current_likelihood = 0; %% @TODO The log-likelihood of the data at each iteration of the EM algorithm. math.log
    disp(['Current log-likelihood: ', int2str(current_likelihood)]);

    if (current_likelihood - likelihood) < 0.0001
        break;
    end
    
    likelihood = current_likelihood;
   
end

    

disp(['Steps until convergence: ', int2str(steps)]);
disp(['Final probabilites: ', mat2str(probabilities)]);
disp(['Log likelihood: ', num2str(likelihood)]);


    