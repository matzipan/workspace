function draw_status(M,Mold,pattern,np,J,Jold,I,z,zold,n1,n2,first,iter)
%   This code is an annotated version of code 
%   downloaded from http://www.imse.cnm.es/%7Ebernabe/matlabform.htm
%   The code was written by Bernabé Linares-Barranco to accompany the book
%   "Adaptive Resonance Theory Microchips", published by Kluwer
    % M         = number of units
    % Mold      = previous number of units
    % pattern   = current pattern index
    % np        = number of patterns
    % J         = current best unit
    % Jold      = previous best unit
    % I         = pattern matrix
    % z         = current unit matrix
    % zold      = previous unit matrix
    % n1        = number of rows in pattern
    % n2        = number of columns in pattern
    % first     = flag to control whether old stuff is plotted
    % iter      = current iteration through data

  clf                                   % clears the current figure

  subplot(2,M+2,M+2+1)                  % sets up a sub-plot 2 rows, M+2 columns, select lower left as current plot
  axis('equal')
  axis off
  %% plot the current pattern ============================
  x='';
  for(i=1:n1)                           % for the current pattern
    x=[x,I(n2*(i-1)+1:n2*i,pattern)];   % turn the column vector into a matrix
  end
  art1plot(x);                          % plot the current pattern at bottom left
  ss=sprintf('Iteration: %d,  Pattern: %d',iter,pattern);
  text(0,-0.5,ss)                       % add the annotation to the plot
  %% plot the z units ====================================
  for(j=1:M)                            % for each unit
    subplot(2,M+2,M+2+j+2)              % select that subplot position
    x='';
    for i=1:n1
      x=[x,z(n2*(i-1)+1:n2*i,j)];       % construct the pattern
    end
    art1plot(x);                        % plot the pattern
    if j==J                             % if we have just plotted the best z unit
      hold on                           % draw a square around it
      plot([0.5,0.5],[0.5,n2+0.5],'y')
      plot([0.5,n1+0.5],[n2+0.5,n2+0.5],'y')
      plot([n1+0.5,n1+0.5],[n2+0.5,0.5],'y')
      plot([n1+0.5,0.5],[0.5,0.5],'y')
      hold off
    end
  end

  %% if this is the first plot run, finish here, otherwise continue to plot
  %% previous version
  if first==1
%    break;
    return;
  end
    
  %% set the pattern indicator to the previous pattern from the set, then
  %% repeat the above plot process for the old z units
  pold=pattern-1;
  if pold==0
    pold=np;
  end
  subplot(2,M+2,1)
  axis('equal')
  axis off
  x='';
  for(i=1:n1)
    x=[x,I(n2*(i-1)+1:n2*i,pold)];
  end
  art1plot(x);
  for(j=1:Mold)
    subplot(2,M+2,j+2)
    x='';
    for i=1:n1
      x=[x,zold(n2*(i-1)+1:n2*i,j)];
    end
    art1plot(x);
    if j==Jold
      hold on
      plot([0.5,0.5],[0.5,n2+0.5],'y')
      plot([0.5,n1+0.5],[n2+0.5,n2+0.5],'y')
      plot([n1+0.5,n1+0.5],[n2+0.5,0.5],'y')
      plot([n1+0.5,0.5],[0.5,0.5],'y')
      hold off
    end
  end

