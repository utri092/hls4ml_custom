# Keras to HLS 
# HLS version

Reads Keras model json for architecture and hdf5 for weights and biases.
Alternatively, specify whole model in hdf5. Json file is not needed
The interface needs to be changed in the generated folder to match Zynq Processing System

# Configuration

Configuration options for the HLS translation of Keras models in *keras_configs/keras-config-x.yml* files.

*KerasJson, KerasH5*: For Keras translation, you are required to provide `json` and `h5` model files.  
Examples are in the directory: `example-keras-model-files`

*OutputDir*: Directory where your HLS project will go

*IOType*: We provide 2 options for the way inputs are input to the architecture, serially or in parallel.  The keywords are `io_serial` or `io_parallel`

*ReuseFactor*: For the running mode `io_parallel`, the calculations do not have to be fully parallelized but resources can be reused at the cost of higher latency.  A `ReuseFactor: 1` means fully parallelized and no resources are reused

*DefaultPrecision*: This is the default type of the weights, biases, accumulators, input and output vectors.  This can then be further modified by the `firmware/parameters.h` file generated in your HLS project.


# Instructions to run. 

## Generates the HLS project
## HLS4ML generates the project in a directory called 
## A seperate directory called Firmware is generated. This does not ...., this does .... 
## performs a C-Simulation in terminal (to see program behavior before synthesis)
```
chmod +x createHLSProject.sh
./createHLSProject.sh
```

## Runs HLS CLI. This does pre-synthesis-simulation, synthesis, post-synthesis simulation and exports an IP Block
## ! Setting synth=0 will disable cosim and export as well
```
cd my-hls-test/
vivado_hls -f build_prj.tcl "csim=1 synth=1 cosim=1 export=1"
```

## Running HLS GUI for HLS project. 


```

cd my-hls-test/
vivado_hls -f build_prj.tcl "csim=1"
vivado_hls -p <project_dir>
```
### If customising HLS Project in GUI
```
chmod +x launchGeneratedProject.sh
./launchGeneratedProject.sh
```
