function [y] = bam_process_x(x, w)
    y = 0; %TODO init;
    while 1
        y_new = w * x;
        %@TODO apply update rule +1 if >0, -1 if <0 and init value 
        x_new = w' * y_new;
        %@TODO apply update rule +1 if >0, -1 if <0 and init value 
        if(x_new == x)
            break;
        else
            x = x_new;
        end
    end
end

