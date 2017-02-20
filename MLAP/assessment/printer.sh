#!/bin/bash
matlab -nodisplay -nojvm -nosplash -nodesktop -r "try, assessment('$1', '$2'), catch, exit(1), end, exit(0);"
