set lang "C++"
set moduleName "toplevel"
set moduleIsExternC "0"
set rawDecl ""
set globalVariable ""
set PortName2 "matrix"
set BitWidth2 "800"
set ArrayOpt2 ""
set Const2 "0"
set Volatile2 "0"
set Pointer2 "0"
set Reference2 "0"
set Initializer2 ""
set External2 0
set Dims2 [list  10 10]
set Interface2 "wire"
set NameSpace2 [list ]
set DataType2 "[list ap_int 1 ]"
set Port2 [list $PortName2 $Interface2 $DataType2 $Pointer2 $Dims2 $Const2 $Volatile2 $ArrayOpt2 $Initializer2 $External2 $NameSpace2]
lappend globalVariable $Port2
set PortList ""
set PortName0 "input"
set BitWidth0 "32"
set ArrayOpt0 ""
set Const0 "0"
set Volatile0 "0"
set Pointer0 "2"
set Reference0 "1"
set Dims0 [list 0]
set Interface0 [list AP_STREAM 0] 
set DataType0 "[list ap_uint 32 ]"
set Port0 [list $PortName0 $Interface0 $DataType0 $Pointer0 $Dims0 $Const0 $Volatile0 $ArrayOpt0]
lappend PortList $Port0
set PortName1 "output"
set BitWidth1 "32"
set ArrayOpt1 ""
set Const1 "0"
set Volatile1 "0"
set Pointer1 "2"
set Reference1 "1"
set Dims1 [list 0]
set Interface1 [list AP_STREAM 0] 
set DataType1 "[list ap_uint 32 ]"
set Port1 [list $PortName1 $Interface1 $DataType1 $Pointer1 $Dims1 $Const1 $Volatile1 $ArrayOpt1]
lappend PortList $Port1
set globalAPint "" 
set returnAPInt "" 
set hasCPPAPInt 1 
set argAPInt "" 
set hasCPPAPFix 0 
set hasSCFix 0 
set hasCBool 0 
set hasCPPComplex 0 
set isTemplateTop 0
set hasHalf 0 
set dataPackList ""
set module [list $moduleName $PortList $rawDecl $argAPInt $returnAPInt $dataPackList]
