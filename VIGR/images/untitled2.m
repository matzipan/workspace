t = [1/0.03125 1/0.0625 1/0.125 1/0.25 1/0.5 1 1/2 1/4 1/8 1/16 1/32 1/64 1/128 1/256 1/512 1/1024]';

for i=1:16
images(:,:,:,i)=imread(strcat(num2str(i),'.png'));
end

w = [0:127 127:-1:0]';

for row = 1:650
for col = 1:450
for chan = 1:3
% 1. Extract the vector of intensity values (see part 1)
vi = squeeze(images(row,col,chan,:));
% 2. Transform the intensities to log intensities using g (see part 3)
vlH = g(squeeze(images(row,col,chan,:)+1));
% 3. Compute the weights for the intensities using w (see part 2)
vwi = w(vi+1);
% 4. Compute the vector difference between the log intensities and the log of the exposure times in t
vd = vlH-log(t);
% 5. Scale the differences by the weights and take the sum
sd = sum(vd.*double(vwi));
% 6. Compute the sum of the weight
sw = sum(vwi);
% 7. Compute the final log HDR values by dividing the result of step 5 by the result of step 6:
logHDR(row,col,chan) = sd/sw;
end
end
end

HDR = exp(logHDR);