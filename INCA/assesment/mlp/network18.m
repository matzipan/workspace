mlp = fitnet(18);
configure(mlp, input', output');

mlp.trainParam.showWindow = false;
net.performParam.normalization = 'standard';

[mlp, record] = train(mlp,input',output');
      
plotperform(record);
