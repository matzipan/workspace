function [U,E]=seig(A)
% Compute the eigenvectors and eigenvalues of symmetric matrix A
% Returns the results in sorted order with largest first
% Eigenvectors are normalised
% If A is not symmetric, it will be symmetrised by 0.5*(A+A')

sz=size(A,1);
A=0.5*(A+A');
[U,E]=eig(A);
E=diag(E);
E=diag(E(sz:-1:1));
U=U(:,sz:-1:1);


