function [U,E]=nseig(A)
% Compute the eigenvectors and eigenvalues of non-symmetric matrix A
% Returns the results in sorted order with largest first
% Eigenvectors are normalised
% Assumes results are real

sz=size(A,1);
[U,E]=eig(A);
e=real(diag(E));
[e,idx]=sort(e,'descend');
U=real(U(:,idx));
l=sqrt(sum(U.*U));
U=U./repmat(l,sz,1);
E=diag(e);
