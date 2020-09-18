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

using namespace std;


namespace nnet {
    bool trace_enabled = true;
    std::map<std::string, void *> *trace_outputs = NULL;
    size_t trace_type_size = sizeof(double);
}

int main(int argc, char **argv)
{

	  stream<featuresSdCh>  inStream, outStream;

	  const unsigned int row_length = N_INPUT_1_1; // Insert input layer size from myproject.h

	  vector<unsigned int> features{1586381880, 1, 1586381960, 2};
	  featuresSdCh valIn;

	  for(int i = 0;  i < features.size(); i++){

		  valIn.data = features[i];
		  inStream.write(valIn);

	  }

	  unsigned int max_size;
	  myproject(inStream, outStream, max_size);

	  for(int i = 0;  i <= (features.size()-row_length); i+=row_length){
		  featuresSdCh valOut;
		  outStream.read(valOut);

		  cout<< "HW Prediction: "<< valOut.data<<" Input: ";

		  for(int j = 0; j < row_length; j++){
			  cout<<features[i+j]<<' ';
		  }
		  cout<<endl;
	  }

	  return 0;
}
