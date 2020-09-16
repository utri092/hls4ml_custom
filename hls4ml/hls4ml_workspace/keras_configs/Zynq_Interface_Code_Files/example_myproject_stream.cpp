
/*
 Example AXI Stream top level file
*/
#include <iostream>

#include "myproject.h"
#include "parameters.h"


void myproject(stream<featuresSdCh> &inStream, stream<featuresSdCh> &outStream, unsigned int &max_size)
{

	//Set the HLS stream
	#pragma HLS interface axis port=inStream
	#pragma HLS interface axis port=outStream
	#pragma HLS interface s_axilite port=max_size bundle=CTRL_BUS
	// Set function interface to be controlled via zynq processing system
	#pragma HLS interface s_axilite port=return bundle=CTRL_BUS

	// input_layer_array_size will be given in myproject.h
	const unsigned int row_length = N_INPUT_1_1;

	// MAX Size of stream. Put in size according to requirements
	max_size = 0xFFFFFFFF;


	/** A nested for loop is needed for iterating through input stream in a 2D manner.
		-> loop1: Waits on loop2 to read a row of features from input_stream for feeding into input_layer datatype of neural network,
			  Writes output (prediction) from last layer to outputStream,
 			  Assigns TLAST(End of transaction) control signal to output stream
				  
		-> loop2: Reads value from input_Stream, assigns control signals to output variable and assigns data
			  to hls4ml generated input array. (Check myproject.h for datatype name)	
	**/

    	unsigned int i;
	loop1: for(i = 0; i <= (size - row_length); i+=row_length)
	{	
		// For concurrent execution and sharing HW resources
		#pragma HLS pipeline

		if(inStream.empty()){
			break;
		}else{
			
			<hls4ml_generated_dataType> <input_layer_name>[row_length];
			<hls4ml_generated_dataType> <output_layer_name>[N_LAYER_10];

			// Axi stream data type in myproject.h for reading/writing to input/output streams respectively
			featuresSdCh valIn, valOut;

			unsigned int j;
			//Read inputs from input stream and puts in hls4ml generated input array
			loop2: for(j = 0 ; j <  row_length; j++){
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

