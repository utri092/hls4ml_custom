//
//    rfnoc-hls-neuralnet: Vivado HLS code for neural-net building blocks
//
//    Copyright (C) 2017 EJ Kreinar
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include <iostream>
#include "myproject.h"
#include "parameters.h"

void myproject(
    int example_in,
    int example_out
) {
        //hls-fpga-machine-learning insert IO
	S_axilite interface
	#pragma HLS INTERFACE s_axilite port=return bundle=model_interface
	#pragma HLS INTERFACE s_axilite port=example_in bundle=model_interface
	#pragma HLS INTERFACE s_axilite port=example_out bundle=model_interface
	
        Generated Interface
        #pragma HLS INTERFACE ap_vld port=example_in, example_out
}
