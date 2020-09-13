
/*
 Example AXI Stream top level file
*/
#include <iostream>

#include "myproject.h"
#include "parameters.h"


void myproject(stream<featuresSdCh> &inStream, stream<featuresSdCh> &outStream, unsigned short &size)

{


    //hls-fpga-machine-learning insert IO
	//Set the HLS native interface types
	#pragma HLS interface axis port=inStream
	#pragma HLS interface axis port=outStream
	#pragma HLS interface s_axilite port=size bundle=CTRL_BUS
	// Set function interface to be controlled via zynq processing system
	#pragma HLS interface s_axilite port=return bundle=CTRL_BUS
    #pragma HLS pipeline


	const unsigned int row_length = N_INPUT_1_1;
	size = 10;

#ifndef __SYNTHESIS__
    static bool loaded_weights = false;
    if (!loaded_weights) {
        //hls-fpga-machine-learning insert load weights
        nnet::load_weights_from_txt<Dense_weight_t, 4>(w2, "w2.txt");
        nnet::load_weights_from_txt<Dense_bias_t, 2>(b2, "b2.txt");
        nnet::load_weights_from_txt<Dense_weight_t, 10>(w4, "w4.txt");
        nnet::load_weights_from_txt<Dense_bias_t, 5>(b4, "b4.txt");
        nnet::load_weights_from_txt<Dense_weight_t, 25>(w6, "w6.txt");
        nnet::load_weights_from_txt<Dense_bias_t, 5>(b6, "b6.txt");
        nnet::load_weights_from_txt<Dense_weight_t, 25>(w8, "w8.txt");
        nnet::load_weights_from_txt<Dense_bias_t, 5>(b8, "b8.txt");
        nnet::load_weights_from_txt<Dense_weight_t, 5>(w10, "w10.txt");
        nnet::load_weights_from_txt<Dense_bias_t, 1>(b10, "b10.txt");
        loaded_weights = true;
    }
#endif

    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    //hls-fpga-machine-learning insert layers

    int i;
	for(i = 0; i <= (size - row_length); i+=row_length)
	{	
		
		//hls4ml generated interface.
		#pragma HLS pipeline
		input_t input1[row_length];
		result_t layer11_out[N_LAYER_10];

		// Axi stream data type for reading/writing to input/output streams
		featuresSdCh valIn, valOut;

		int j;
		
		//Read inputs from input stream and put in hls4ml generated input array
		for(j = 0 ; j <  row_length; j++){
			#pragma HLS pipeline
			valOut.keep = valIn.keep;
			valOut.strb = valIn.strb;
			valOut.user = valIn.user;
			valOut.id = valIn.id;
			valOut.dest = valIn.dest;
			inStream.read(valIn);
			input1[j] = valIn.data;
		}



		// NN Layers reside here

		
		// Write to output Stream after NN layers code
		// Since output is one value only
		valOut.data = output_layer[0];

		//TLAST: End of transaction
		valOut.last = valIn.last;

		outStream.write(valOut);

	}

}

