# Keras to HLS 
# HLS version

Reads Keras model json for architecture and hdf5 for weights and biases.
Alternatively, specify whole model in hdf5. Json file is not needed
The interface needs to be changed in the generated folder to match Zynq Processing System

**Note:- Instructions to change interface for Zynq System is in *Zynq_Interface_Code_Files/README.md*. Hls4ml by default does not have the feature to use AXI-Lite or AXI-Stream. Manual intervention is needed.**

# Configuration

Configuration options for the HLS translation of Keras models in *keras_configs/keras-config-x.yml* files.

*KerasJson, KerasH5*: For Keras translation, you are required to provide `json` and `h5` model files.  
Examples are in the directory: `trainedKerasFormatModel`

*OutputDir*: Directory where your HLS project will go

*IOType*: We provide 2 options for the way inputs are input to the architecture, serially or in parallel.  The keywords are `io_serial` or `io_parallel`

*ReuseFactor*: For the running mode `io_parallel`, the calculations do not have to be fully parallelized but resources can be reused at the cost of higher latency.  A `ReuseFactor: 1` means fully parallelized and no resources are reused

*DefaultPrecision*: This is the default type of the weights, biases, accumulators, input and output vectors.  This can then be further modified by the `firmware/parameters.h` file generated in your HLS project.


# Instructions to run. 

## Generates the HLS project
### -> HLS4ML generates the project in a directory called my-hls-test/
### -> Performs a C-Simulation in terminal (to see program behavior before synthesis)
### -> Put desired config file name in createHLSProject.sh and run
```
chmod +x createHLSProject.sh
./createHLSProject.sh
```
### Run GUI for Vivado HLS
```
chmod +x launchHLSProject.sh
./launchHLSProject.sh
```
