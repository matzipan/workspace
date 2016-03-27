#!/bin/bash -x
./cross-compile main.adb
rm /tmp/tftpboot/world/program
cp main /tmp/tftpboot/world/program
chmod a+r /tmp/tftpboot/world/program
