#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /usr/userfs/a/az579/bla/solution1/.autopilot/db/a.g.bc ${1+"$@"}
