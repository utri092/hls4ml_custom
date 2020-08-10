#Rm the current test project (if exists)
rm -rf my-hls-test/
# Activate venv environmenent (this has the hls4ml package) 
source ../../pyHLSVenv/bin/activate
# Use hls4ml to generate Vivado HLS Project (generates a directory 
hls4ml convert -c keras-config-nn1.yml 
# Go to the created directory
cd my-hls-test
# Activate Vivado HLS CLI
source ~/Xilinx/Vivado/2020.1/settings64.sh
# Pre Sythesis Simulation & Sythesis (simlulation results print on terminal)
vivado_hls -f build_prj.tcl "synth=1 csim=1 export=0 cosim=0"

