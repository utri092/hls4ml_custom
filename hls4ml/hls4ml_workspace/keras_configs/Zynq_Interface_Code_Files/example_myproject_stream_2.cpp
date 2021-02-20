
/*
 Example AXI Stream top level file
*/

#include <iostream>
#include "example_myproject_stream_2.h"
#include "parameters.h"


/** ###################  COPY ########################### **/

void myproject(stream<featuresSdCh> &inStream, stream<featuresSdCh> &outStream)
{

	//Set the HLS stream
	#pragma HLS interface axis port=inStream
	#pragma HLS interface axis port=outStream
	// Set function interface to be controlled via zynq processing system
	#pragma HLS interface s_axilite port=return bundle=CTRL_BUS


	// input_layer_array_size will be given in myproject.h
	const unsigned int row_length = N_INPUT_1_1;

/** ###################  STOP COPY ########################### **/

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

/** ###################  COPY ########################### **/
    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

	/*Replace <dataType> <layer_name> with generated names in header file, e.g.  
	=> input_t input1   --> for input
	=> result_t layer11_out [N_LAYER_10]  --> for output
	*/
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
				
				<input_layer_name>[j] = valIn.data; //remember to change <input_layer_name> too
			}

/** ###################  STOP COPY ########################### **/

	/******************  NN functions reside here **************************/
	 
	/** ###################  DO NOT COPY ########################### 

		layer2_t layer2_out[N_LAYER_2];
	    #pragma HLS ARRAY_PARTITION variable=layer2_out complete dim=0
	    nnet::dense_latency<input_t, layer2_t, config2>(input1, layer2_out, w2, b2);

	    layer3_t layer3_out[N_LAYER_2];
	    #pragma HLS ARRAY_PARTITION variable=layer3_out complete dim=0
	    nnet::relu<layer2_t, layer3_t, relu_config3>(layer2_out, layer3_out);

	    layer4_t layer4_out[N_LAYER_4];
	    #pragma HLS ARRAY_PARTITION variable=layer4_out complete dim=0
	    nnet::dense_latency<layer3_t, layer4_t, config4>(layer3_out, layer4_out, w4, b4);

	    layer5_t layer5_out[N_LAYER_4];
	    #pragma HLS ARRAY_PARTITION variable=layer5_out complete dim=0
	    nnet::relu<layer4_t, layer5_t, relu_config5>(layer4_out, layer5_out);

	    layer6_t layer6_out[N_LAYER_6];
	    #pragma HLS ARRAY_PARTITION variable=layer6_out complete dim=0
	    nnet::dense_latency<layer5_t, layer6_t, config6>(layer5_out, layer6_out, w6, b6);

	    layer7_t layer7_out[N_LAYER_6];
	    #pragma HLS ARRAY_PARTITION variable=layer7_out complete dim=0
	    nnet::relu<layer6_t, layer7_t, relu_config7>(layer6_out, layer7_out);

	    layer8_t layer8_out[N_LAYER_8];
	    #pragma HLS ARRAY_PARTITION variable=layer8_out complete dim=0
	    nnet::dense_latency<layer7_t, layer8_t, config8>(layer7_out, layer8_out, w8, b8);

	    layer9_t layer9_out[N_LAYER_8];
	    #pragma HLS ARRAY_PARTITION variable=layer9_out complete dim=0
	    nnet::relu<layer8_t, layer9_t, relu_config9>(layer8_out, layer9_out);

	    layer10_t layer10_out[N_LAYER_10];
	    #pragma HLS ARRAY_PARTITION variable=layer10_out complete dim=0
	    nnet::dense_latency<layer9_t, layer10_t, config10>(layer9_out, layer10_out, w10, b10);

	    nnet::linear<layer10_t, result_t, linear_config11>(layer10_out, layer11_out);

		 ###################  DO NOT COPY ########################### **/


/** ###################  COPY ########################### **/
	/******************  NN functions reside here **************************/

	// Write to output Stream after NN functions
	// Output layer returns an array of size 1 in this example
	valOut.data = <output_layer_name>[0];  //remember to change <output_layer_name> too

	valOut.keep = valIn.keep;
	valOut.strb = valIn.strb;
	valOut.user = valIn.user;
	valOut.id = valIn.id;
	valOut.dest = valIn.dest;

	valOut.last = valIn.last;

	outStream.write(valOut);

	}

}

/** ###################  STOP COPY ########################### **/

