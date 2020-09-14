
/*
 Example AXI Stream top level file
*/
#include <iostream>

#include "myproject.h"
#include "parameters.h"


void myproject(stream<featuresSdCh> &inStream, stream<featuresSdCh> &outStream, unsigned short &size)

{
	/*TO_REPLACE: All #pragmas before NN functions
	 	      with below #pragmas.
	*/

	//Set the HLS stream
	#pragma HLS interface axis port=inStream
	#pragma HLS interface axis port=outStream
	#pragma HLS interface s_axilite port=size bundle=CTRL_BUS
	// Set function interface to be controlled via zynq processing system
	#pragma HLS interface s_axilite port=return bundle=CTRL_BUS
	
	// input_layer_array_size will be given in myproject.h
	const unsigned int row_length = <input_layer_size>;

	// Size of stream. Put in size according to requirements
	size = 10;


	/** A nested for loop is needed for iterating through input stream in a 2D manner.
		-> loop1: Waits on loop2 to read a row of features from input_stream for feeding into input_layer datatype of neural network,
			  Writes output (prediction) from last layer to outputStream,
 			  Assigns TLAST(End of transaction) control signal to output stream
				  
		-> loop2: Reads value from input_Stream, assigns control signals to output variable and assigns data
			  to hls4ml generated input array. (Check myproject.h for datatype name)	
	**/

    	int i;
	loop1: for(i = 0; i <= (size - row_length); i+=row_length)
	{	
		
		#pragma HLS pipeline
		
		<hls4ml_generated_dataType> <input_layer_name>[row_length];
		<hls4ml_generated_dataType> <output_layer_name>[N_LAYER_10];

		// Axi stream data type in myproject.h for reading/writing to input/output streams respectively
		featuresSdCh valIn, valOut;

		int j;
		//Read inputs from input stream and puts in hls4ml generated input array
		loop2: for(j = 0 ; j <  row_length; j++){
			#pragma HLS pipeline
			
			
			inStream.read(valIn);
			
			valOut.keep = valIn.keep;
			valOut.strb = valIn.strb;
			valOut.user = valIn.user;
			valOut.id = valIn.id;
			valOut.dest = valIn.dest;

			<input_layer_name>[j] = valIn.data;
		}



		/******************  NN functions reside here **************************/

		
		// Write to output Stream after NN functions
		// Output layer returns an array of size 1 in this example
		valOut.data = <output_layer_name>[0];

		valOut.last = valIn.last;

		outStream.write(valOut);

	}

}

