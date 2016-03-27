%% Manifold learning practical

% Load and display the data
load 'digits';
%digits_image=Devectorise(digits,40);
%imagesc(digits_image);
%colormap(gray);

%% Complete the function PCA
XPCA=PCA(digits,3);

figure;
hold on;
scatter3(XPCA(1:500,1),XPCA(1:500,2),XPCA(1:500,3),20,'red','o');
scatter3(XPCA(501:1000,1),XPCA(501:1000,2),XPCA(501:1000,3),20,'blue','*');
set(gca,'DataAspectRatio',[1 1 1])

%% Complete the function LDA
% Uncomment this section when you are ready to implement this part:
% select the section and from the top menu use Uncomment
% Create the classes; first 500 are class 1, second 500 are class 2

% classes=[ones(1,500) 2*ones(1,500)];
%
% XLDA=LDA(digits,3,classes);
% 
% % LDA only produces one useful dimension in this case (why?)
% % We get the other two from PCA, so this uses the result of the previous
% % calculation
% figure;
% hold on;
% scatter3(XLDA(1:500,1),XPCA(1:500,1),XPCA(1:500,2),20,'red','o');
% scatter3(XLDA(501:1000,1),XPCA(501:1000,1),XPCA(501:1000,2),20,'blue','*');

%% Complete the function MDS

% Create a distance matrix
% ours is based on the sum of absolute differences

% samples=size(digits,1);
% % D is the distance matrix
% D=zeros(samples,samples);
% for i=1:samples
%     % Our distance is symmetric, so to save time we only need
%     % to compute half of the distances
%     for j=i+1:samples
%         D(i,j)=sum(abs(digits(i,:)-digits(j,:)));
%         D(j,i)=D(i,j);
%     end
% end
% 
% % The input to MDS is the squared distances
% D=D.^2;
% 
% XMDS=MDS(D,3);
% 
% figure;
% hold on;
% scatter3(XMDS(1:500,1),XMDS(1:500,2),XMDS(1:500,3),20,'red','o');
% scatter3(XMDS(501:1000,1),XMDS(501:1000,2),XMDS(501:1000,3),20,'blue','*');

%% Complete the function ISOMAP

% XISO=ISOMAP(digits,3);
% 
% figure;
% hold on;
% scatter3(XISO(1:500,1),XISO(1:500,2),XISO(1:500,3),20,'red','o');
% scatter3(XISO(501:1000,1),XISO(501:1000,2),XISO(501:1000,3),20,'blue','*');

%% Complete the function LLE

% XLLE=LLE(digits,3);
% 
% figure;
% hold on;
% scatter3(XLLE(1:500,1),XLLE(1:500,2),XLLE(1:500,3),20,'red','o');
% scatter3(XLLE(501:1000,1),XLLE(501:1000,2),XLLE(501:1000,3),20,'blue','*');
