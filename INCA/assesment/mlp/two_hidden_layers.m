finalmse = [];

for i = 1:20
    iterationmse = [];

    for l1 = 11:11
        for l2 = 19:19
            disp(['Evaluating network with ',int2str(l1),' ', int2str(l2),' neurons']);

            mlp = fitnet([l1 l2]);
            configure(mlp, input', output');
            mlp.trainParam.showWindow = false;
            [mlp, record] = train(mlp,input',output');

            iterationmse(end+1) = record.best_tperf;
        end
        
    end
    finalmse = [finalmse;iterationmse];
end

plot(mean(finalmse));
%hold on
%plot(mean(finalrsquare));
xlabel('Number of neurons');
ylabel('Average Performance (Mean MSE)');