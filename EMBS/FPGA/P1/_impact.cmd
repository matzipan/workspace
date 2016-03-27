setMode -bs
setMode -bs
setMode -bs
setMode -bs
setCable -port auto
Identify -inferir 
identifyMPM 
assignFile -p 1 -file "/usr/userfs/a/az579/Workspace/EMBS/FPGA/P1/T2/implementation/system.bit"
Program -p 1 
Program -p 1 
assignFile -p 1 -file "/usr/userfs/a/az579/Workspace/EMBS/FPGA/P1/T2/exampleout.bit"
Program -p 1 
setMode -bs
setMode -bs
setMode -ss
setMode -sm
setMode -hw140
setMode -spi
setMode -acecf
setMode -acempm
setMode -pff
setMode -bs
saveProjectFile -file "/usr/userfs/a/az579/Workspace/EMBS/FPGA/P1//auto_project.ipf"
setMode -bs
setMode -bs
deleteDevice -position 1
deleteDevice -position 1
deleteDevice -position 1
setMode -bs
setMode -ss
setMode -sm
setMode -hw140
setMode -spi
setMode -acecf
setMode -acempm
setMode -pff
