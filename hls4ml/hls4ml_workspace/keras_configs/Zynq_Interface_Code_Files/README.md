The Zynq Processing System uses AXILITE and AXISTREAM protocols to communicate with IP blocks

# AXILITE Protocol

### Source File Code Replacement:
In myproject.cpp, right after the top level definition void myproject()

Replace the line:-
` #pragma HLS INTERFACE ap_vld port=input_layer_array, output_last_layer `

with:- 

```
 #pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
 #pragma HLS INTERFACE s_axilite port=<name of input layer> bundle=CTRL_BUS
 #pragma HLS INTERFACE s_axilite port=<name of output layer> bundle=CTRL_BUS
 #pragma HLS INTERFACE s_axilite port=<const size variable> bundle=CTRL_BUS
```

# AXI_STREAM Protocol

Got to myproject.h and take a note of the input/output dataType and array size of generated protoype function

### Header File Code Replacement:

Size of input layer is equal to N_INPUT_1_1 and output_layer is N_LAYER_10.  
In myproject.h, replace the below code:-  
```
void myproject(
    input_t input1[N_LAYER_1_1],
    result_t layer11_out[N_LAYER_10],
    unsigned short &const_size_in_1,
    unsigned short &const_size_out_1
);
```

with:-  
```
void myproject(stream<featuresSdCh> &inStream, stream<featuresSdCh> &outStream, unsigned short &size);
```

### Source File Code Replacement:
Check example_myproject_stream.cpp for instructions on changing myproject.cpp

### Test Bench Code Replacement
Replace code in *myproject_test.cpp* with code in *keras_configs/custom_testbench/parking_model_stream_test.cpp*.  
Alternatively, add the test bench file and make it the target testbench.  
	   
	

