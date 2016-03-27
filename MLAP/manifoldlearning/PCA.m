function XPCA=PCA(X,target_dim)
% Compute the principal components of data-matrix X
% dim is the number of dimensions to return

% Get the number of samples and dimensions from the
% shape of the data matrix X using size(). Each row
% corresponds to a different sample. This X is the transpose
% of the X matrix in the lecture slides where samples
% are put into columns.
[n, dim] = size(X)

% Centre the data matrix by subtracting the mean
% of the columns from every sample. 


% Calculate the covariance of the centred data matrix. 


% Compute eigenvalues and eigenvectors of the covariance matrix 
% using the seig() function. seig() sorts eigenvalues and
% corresponding eigenvectors in descending order.


% Compute the PCA transformation by rotating the centred data matrix
% with the computed eigenvectors.


% Keep the first dim dimensions of the transformed matrix.
