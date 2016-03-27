#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /usr/userfs/a/az579/Workspace/EMBS/FPGA/P6/T2/md5core/md5core/solution1/.autopilot/db/a.g.bc ${1+"$@"}
