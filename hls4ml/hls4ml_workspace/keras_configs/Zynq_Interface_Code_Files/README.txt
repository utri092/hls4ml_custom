The Zynq Processing System uses AXILITE and AXISTREAM protocols to communicate with IP blocks

a)For using S-AXILITE Protocol with the Zynq Processing System

1) In myproject.cpp, right after the top level definition and below the comment 
//hls-fpga-machine-learning insert IO find the line of code:-

#pragma HLS INTERFACE ap_vld port=input1,layer10_out

2) Replace with :-
#pragma HLS INTERFACE s_axilite port=return bundle=model_interface
#pragma HLS INTERFACE s_axilite port=input1 bundle=model_interface
#pragma HLS INTERFACE s_axilite port=layer10_out bundle=model_interface
#pragma HLS INTERFACE s_axilite port=const_size_in_1 bundle=model_interface
#pragma HLS INTERFACE s_axilite port=const_size_out_1 bundle=model_interface
