set C_TypeInfoList {{ 
"toplevel" : [[], { "return": [[], "void"]} , [{"ExternC" : 0}], [ {"input": [[], {"reference": "0"}] }, {"output": [[], {"reference": "0"}] }],["1"],""],
 "1": [ "inputdata", [[], {"array": ["2", [40]]}],""], 
"2": [ "int32", {"typedef": [[[],"3"],""]}], 
"3": [ "ap_int<32>", {"hls_type": {"ap_int": [[[[], {"scalar": { "int": 32}}]],""]}}], 
"0": [ "stream<ap_uint<32> >", {"hls_type": {"stream": [[[[],"4"]],"5"]}}], 
"4": [ "ap_uint<32>", {"hls_type": {"ap_uint": [[[[], {"scalar": { "int": 32}}]],""]}}],
"5": ["hls", ""]
}}
set moduleName toplevel
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_none
set isOneStateSeq 0
set C_modelName {toplevel}
set C_modelType { void 0 }
set C_modelArgList { 
	{ input_V_V int 32 regular {fifo 0 volatile }  }
	{ output_V_V int 32 regular {fifo 1 volatile }  }
}
set C_modelArgMapList {[ 
	{ "Name" : "input_V_V", "interface" : "fifo", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "input.V.V","cData": "uint32","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "output_V_V", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "output.V.V","cData": "uint32","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} ]}
# RTL Port declarations: 
set portNum 8
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ input_V_V_dout sc_in sc_lv 32 signal 0 } 
	{ input_V_V_empty_n sc_in sc_logic 1 signal 0 } 
	{ input_V_V_read sc_out sc_logic 1 signal 0 } 
	{ output_V_V_din sc_out sc_lv 32 signal 1 } 
	{ output_V_V_full_n sc_in sc_logic 1 signal 1 } 
	{ output_V_V_write sc_out sc_logic 1 signal 1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "input_V_V_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "input_V_V", "role": "dout" }} , 
 	{ "name": "input_V_V_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_V_V", "role": "empty_n" }} , 
 	{ "name": "input_V_V_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_V_V", "role": "read" }} , 
 	{ "name": "output_V_V_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "output_V_V", "role": "din" }} , 
 	{ "name": "output_V_V_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_V_V", "role": "full_n" }} , 
 	{ "name": "output_V_V_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_V_V", "role": "write" }}  ]}
set Spec2ImplPortList { 
	input_V_V { ap_fifo {  { input_V_V_dout fifo_data 0 32 }  { input_V_V_empty_n fifo_status 0 1 }  { input_V_V_read fifo_update 1 1 } } }
	output_V_V { ap_fifo {  { output_V_V_din fifo_data 1 32 }  { output_V_V_full_n fifo_status 0 1 }  { output_V_V_write fifo_update 1 1 } } }
}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
	input_V_V { fifo_read 40 no_conditional }
	output_V_V { fifo_write 2 no_conditional }
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
