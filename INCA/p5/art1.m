function art(n1,n2,rho,L,np)
%   This code is an annotated version of code 
%   downloaded from http://www.imse.cnm.es/%7Ebernabe/matlabform.htm
%   The code was written by Bernabé Linares-Barranco to accompany the book
%   "Adaptive Resonance Theory Microchips", published by Kluwer
    % n1        = number rows in an input pattern (for plotting only)
    % n2        = number columns in an input pattern (for plotting only)
    % rho       = vigilance threshold
    % L         = learning parameter
    % np        = number of random patterns to generate

clf
%% Initialisation
n=n1*n2;        % size of input (rows, columns)
z=ones(n,1);    % init all weights for first unit to 1
zold=z;         % weights from last iteration
zprev=z;        % weights from last pattern presentation
Jold=1;         % old J
Mold=1;         % old M
M=1;            % init number of units M to 1
first=1;        % first time through t loop, plot things differently
%% Pattern generation
I=[round(rand(n,1))];       % put the first random pattern in the matrix
for pattern=2:np            % add successive random patterns to the matrix
  I=[I,round(rand(n,1))];   
end
%% Main loop - continues while learning==1
iter=0;
learning=1;
while learning==1
  iter=iter+1;
  for pattern=1:np      % for each pattern defined
    ok=0;               % set OK flag, OK = 1 means we have a match
    for j=1:M           % j index, M starts == 1
                        % pattern AND z(:,j) then count bits, and divide by
                        % scale factor based on number of bits in z(:,j)
      T(j)=norm( min( I(:,pattern),z(:,j) ), 1) / (L-1+norm(z(:,j),1));
    end
    while ok==0         % repeat this until we find a match
      [maxT,J]=max(T);  % find the largest match index J
                        % pattern AND z(:,J) then count bits, 
                        % compare with fraction rho of pattern bits
      if rho*norm(I(:,pattern),1) <= norm(min(I(:,pattern),z(:,J)),1)
        ok=1;           % we have a match
      else
        T(J) = -1;      % not a match, disable this unit
      end
    end                 % guaranteed to find a match because the last column of z is ones
    % pattern AND z(:,J) assigned to z(:,J)
    z(:,J)=min(I(:,pattern),z(:,J));
    if J==M             % if we reached the end column of z, increase the size of z
      M=M+1;            % ..increase number of columns
      z=[z ones(n,1)];  % ..add a column of ones
    end
    % draw the current status
    draw_status(M,Mold,pattern,np,J,Jold,I,z,zprev,n1,n2,first,iter)
    first=0;            % this is now not the first time through the loop
    Jold=J;             % copy the index of the best match for next pattern display
    Mold=M;             % copy the number of units for next pattern display
    zprev=z;            % copy the weights for next pattern display
    pause               % pause so we can see the current status
  end                   % repeat to here for each pattern
  %% decide when to stop
  if size(z)==size(zold)
    if z==zold
      learning=0;
    end
  end
  zold=z;               % copy the weights to check after the next iteration
end
