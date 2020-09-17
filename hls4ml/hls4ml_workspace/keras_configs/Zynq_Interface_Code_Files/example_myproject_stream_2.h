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

#ifndef MYPROJECT_H_
#define MYPROJECT_H_

#include "ap_int.h"
#include "ap_fixed.h"
#include <iostream>
#include <hls_stream.h>
#include <ap_axi_sdata.h>


using namespace hls;

typedef ap_axiu<32, 2, 5, 6> featuresSdCh;

#include "defines.h"


// Prototype of top level function for C-synthesis
// AXI Stream prototype
// Instream and outstream
// -> Instream (1st value is time, 2nd id)
// <- outstream (occupancy)
// !Unlimited size of stream
void myproject(stream<featuresSdCh> &inStream, stream<featuresSdCh> &outStream);

#endif





