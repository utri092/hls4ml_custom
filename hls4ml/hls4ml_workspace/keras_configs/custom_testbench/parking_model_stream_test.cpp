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

// No of inputs to process
#define LIMIT 10

int main(int argc, char **argv)
{
  //load input data from text file
  std::ifstream fin("tb_data/tb_input_features.dat");
  //load predictions from text file
  std::ifstream fpr("tb_data/tb_output_predictions.dat");

#ifdef RTL_SIM
  std::string RESULTS_LOG = "tb_data/rtl_cosim_results.log";
#else
  std::string RESULTS_LOG = "tb_data/csim_results.log";
#endif
  std::ofstream fout(RESULTS_LOG);

  std::string iline;
  std::string pline;
  unsigned int input_no = 0;

  std::vector<unsigned int> expected_outputs;
  stream<featuresSdCh>  inStream, outStream;

  if (fin.is_open() && fpr.is_open()) {
	while ( std::getline(fin,iline) && std::getline (fpr,pline) && input_no < LIMIT) {

	  char* cstr=const_cast<char*>(iline.c_str());
	  char* current;
	  current=strtok(cstr," ");
	  featuresSdCh valIn;
	  while(current!=NULL) {
		unsigned int feature = atoi(current);
		valIn.data = feature;
		inStream.write(valIn);
		current=strtok(NULL," ");
	  }

	  cstr=const_cast<char*>(pline.c_str());

	  current=strtok(cstr," ");
	  while(current!=NULL) {
		  unsigned int expected = atoi(current);
		  expected_outputs.push_back(expected);
		current=strtok(NULL," ");
	  }

	  input_no++;

	}

    fin.close();
    fpr.close();

	unsigned int max_size;
	// Insert interface from myproject.h
	myproject(inStream, outStream, max_size);

	featuresSdCh valOut;

	cout<< "INFO: Processing "<< LIMIT <<" inputs"<<endl;
	for(int i = 0;  i < LIMIT; i++){
	  outStream.read(valOut);

	  cout<< "HW Prediction: "<< valOut.data << " Expected Prediction: "<< expected_outputs[i] <<endl;
	}

  } else {
    std::cout << "ERROR: Unable to open input/predictions file, ending test." << std::endl;
  }

  fout.close();


  return 0;
}

