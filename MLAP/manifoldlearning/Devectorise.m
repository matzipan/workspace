function Y=Devectorise(X,w)
% Y=Devectorise(X,w) Converts a data-matrix into image format for the digits
% data. Y is w digit images wide.
r=size(X,1);
iy=floor((r-1)/w)+1;
Y=zeros(iy*28,w*28);
for l=0:r-1
    i=floor(l/w)*28;
    j=mod(l,w)*28;
    Y(i+1:i+28,j+1:j+28)=reshape(X(l+1,:),28,28)';
end
