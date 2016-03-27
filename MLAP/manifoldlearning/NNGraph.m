function A=NNGraph(X,n)
% Compute the n-nearest-neighbour graph of X
% n is the number of neighbours
% A(i,j) contains zero if they are not neigbours, or the distance
% between them if they are

samples=size(X,1);

% kernel matrix
K=X*X';

% Euclidean distances
D=repmat(diag(K),1,samples)+repmat(diag(K)',samples,1)-2*K;
D=sqrt(D);

% Initialise A
A=zeros(samples,samples);

% nn for each vertex
for u=1:samples
    [d,idx]=sort(D(u,:));
    A(u,idx(1:n))=d(1:n);
end

% symmetrise the graph to get symmetric distances
A=max(A,A');
    