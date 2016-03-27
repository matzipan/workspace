function XMDS=MDS(D,dim)
% Compute the Multidimensional scaling from the squared distance matrix D
% dim is the number of dimensions to return

% Get the number of samples from D and create matrices I and J.


% Form the centred kernel matrix from matrices D, I and J.


% Compute eigenvalues and eigenvectors of the kernel matrix using seig().


% Set all negative eigenvalues to 0. A  simple way to do that is using max(0,X)


% Compute the MDS transformation using the eigenvectors and square roots of eigenvalues.
% The function sqrt(X) returns the square root of each element of X.


% Keep the first dim dimensions.
