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
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "firmware/myproject.h"


using namespace hls;
using namespace std;

namespace nnet {
    bool trace_enabled = true;
    std::map<std::string, void *> *trace_outputs = NULL;
    size_t trace_type_size = sizeof(double);
}

int main(int argc, char **argv)
{

	  stream<featuresSdCh>  inStream, outStream;

	  const unsigned int row_length = 2;
	  unsigned short size = 10;
	  unsigned int time = 1586381880;
	  unsigned int id = 1;

	  for(int i = 0;  i <= (size-row_length); i+=row_length){

		  	  for(int j = 0; j < row_length; j++){
		  		  featuresSdCh valIn;


		  		  valIn.data = time;
		  		  inStream.write(valIn);
		  		  valIn.data = id;
		  		  inStream.write(valIn);


		  	  }
	  }

	  myproject(inStream, outStream, size);

	  for(int i = 0; i < size/row_length; i++){
		  featuresSdCh valOut;
		  outStream.read(valOut);

		  cout<< "HW Prediction: "<< valOut.data << " Input: "<< time << " "<< id<<endl;

	  }

	  return 0;
}

