function art1plot(x)
%   This code is an annotated version of code 
%   downloaded from http://www.imse.cnm.es/%7Ebernabe/matlabform.htm
%   The code was written by Bernabé Linares-Barranco to accompany the book
%   "Adaptive Resonance Theory Microchips", published by Kluwer
    % x         = vector of values corresponding to an ART unit
[n,m]=size(x);
x=(1-x)*100;
image(x)
axis('off')
axis('equal')
axis([0.5 m+0.5 0.5 n+0.5])
colormap('gray')
