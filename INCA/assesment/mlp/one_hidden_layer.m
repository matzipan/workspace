%finalmse = [];

for i = 1:30
    disp(['Iteration number ', int2str(i)]);

   for t = 1:3
      iterationmse = [];

       for n = 13:35
            disp(['Evaluating network with ',int2str(n),' neurons with t ', int2str(t)]);

            mlp = fitnet(n);
            configure(mlp, input', output');
            
            mlp.trainParam.showWindow = false;

            [mlp, record] = train(mlp,input',output','useParallel', 'yes');

            iterationmse(end+1) = record.best_tperf;
       end
        
        finalmse = [finalmse;iterationmse];
   end
end

plot(13:35, mean(finalmse));
xlabel('Number of neurons');
ylabel('Average Performance (Mean MSE)');
