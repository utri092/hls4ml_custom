
/*
 Example AXI Stream top level file
*/

#include <iostream>
#include "example_myproject_stream_2.h"
#include "parameters.h"

void myproject(stream<featuresSdCh> &inStream, stream<featuresSdCh> &outStream)
{

	//Set the HLS stream
	#pragma HLS interface axis port=inStream
	#pragma HLS interface axis port=outStream
	// Set function interface to be controlled via zynq processing system
	#pragma HLS interface s_axilite port=return bundle=CTRL_BUS


	// input_layer_array_size will be given in myproject.h
	const unsigned int row_length = N_INPUT_1_1;


/** DO NOT COPY. Only to show where to place code in actual main file
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
**/


	<hls4ml_generated_dataType> <input_layer_name>[row_length];
	<hls4ml_generated_dataType> <output_layer_name>[N_LAYER_10];

	// Axi stream data type in myproject.h for reading/writing to input/output streams respectively
	featuresSdCh valIn, valOut;


	while(!inStream.empty())
	{
			// For concurrent execution and sharing HW resources
			#pragma HLS pipeline

			unsigned int j;
			//Read inputs from input stream and puts in hls4ml generated input array
			for(j = 0 ; j <  row_length; j++){
				// Parallelise assignments
				#pragma HLS unroll
				
				inStream.read(valIn);
				
				<input_layer_name>[j] = valIn.data;
			}

			/******************  NN functions reside here **************************/

			// Write to output Stream after NN functions
			// Output layer returns an array of size 1 in this example
			valOut.data = <output_layer_name>[0];

			valOut.keep = valIn.keep;
			valOut.strb = valIn.strb;
			valOut.user = valIn.user;
			valOut.id = valIn.id;
			valOut.dest = valIn.dest;

			valOut.last = valIn.last;

			outStream.write(valOut);

	}

}



