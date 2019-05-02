#!/bin/bash
#
# run_gem5_x86_spec17_benchmark.sh
 
############ DIRECTORY VARIABLES: MODIFY ACCORDINGLY #############
GEM5_DIR='/home/rohan/gem5'        # Install location of gem5
SPEC_DIR='/home/rohan/SPEC2017'            # Install location of your SPEC2017 benchmarks
##################################################################
 
ARGC=$# # Get number of arguments excluding arg0 (the script itself). Check for help message condition.
if [[ "$ARGC" != 2 ]]; then # Bad number of arguments.
    echo "run_gem5_alpha_spec17_benchmark.sh"
    echo "USAGE: run_gem5_alpha_spec17_benchmark.sh <BENCHMARK> <OUTPUT_DIR>"
    echo "EXAMPLE: ./run_gem5_x86_spec17_benchmark.sh bzip2 /FULL/PATH/TO/output_dir"
    echo ""
    echo "A single --help help or -h argument will bring this message back."
    exit
fi
 
# Get command line input. We will need to check these.
BENCHMARK=$1                    # Benchmark name, e.g. bzip2
OUTPUT_DIR=$2                   # Directory to place run output. Make sure this exists!
 
######################### BENCHMARK CODENAMES ####################
PERLBENCH_CODE=600.perlbench_s
XZ_CODE=657.xz_s
MCF_CODE=605.mcf_s
IMAGICK_CODE=638.imagick_s
EXCHANGE2_CODE=648.exchange2_s
OMNETPP_CODE=620.omnetpp_s
POVRAY_CODE=511.povray_r
LBM_CODE=619.lbm_s
LEELA_CODE=641.leela_s

################################################################## 
# Check BENCHMARK input
#################### BENCHMARK CODE MAPPING ######################
BENCHMARK_CODE="none"
 
if [[ "$BENCHMARK" == "perlbench" ]]; then
    BENCHMARK_CODE=$PERLBENCH_CODE
fi
if [[ "$BENCHMARK" == "xz" ]]; then
    BENCHMARK_CODE=$BZIP2_CODE
fi
if [[ "$BENCHMARK" == "imagick" ]]; then
    BENCHMARK_CODE=$IMAGICK_CODE
fi
if [[ "$BENCHMARK" == "mcf" ]]; then
    BENCHMARK_CODE=$MCF_CODE
fi
if [[ "$BENCHMARK" == "exchange2" ]]; then
    BENCHMARK_CODE=$EXCHANGE2_CODE
fi
if [[ "$BENCHMARK" == "omnetpp" ]]; then
    BENCHMARK_CODE=$OMNETPP_CODE
fi
if [[ "$BENCHMARK" == "povray" ]]; then
    BENCHMARK_CODE=$POVRAY_CODE
fi
if [[ "$BENCHMARK" == "lbm" ]]; then
    BENCHMARK_CODE=$LBM_CODE
fi
if [[ "$BENCHMARK" == "leela" ]]; then
    BENCHMARK_CODE=$LEELA_CODE
fi

if [[ "$BENCHMARK_CODE" == "none" ]]; then
    echo "Input benchmark selection $BENCHMARK did not match any known SPEC CPU2017 benchmarks! Exiting."
    exit 1
fi
##################################################################
 
# Check OUTPUT_DIR existence
if [[ !(-d "$OUTPUT_DIR") ]]; then
    echo "Output directory $OUTPUT_DIR does not exist! Exiting."
    exit 1
fi
 
RUN_DIR=$SPEC_DIR/benchspec/CPU/$BENCHMARK_CODE/run/run_base_test\_mytest-m64.0000     # Run directory for the selected SPEC benchmark
SCRIPT_OUT=$OUTPUT_DIR/runscript.log                                                                    # File log for this script's stdout henceforth
 
################## REPORT SCRIPT CONFIGURATION ###################
 
echo "Command line:"                                | tee $SCRIPT_OUT
echo "$0 $*"                                        | tee -a $SCRIPT_OUT
echo "================= Hardcoded directories ==================" | tee -a $SCRIPT_OUT
echo "GEM5_DIR:                                     $GEM5_DIR" | tee -a $SCRIPT_OUT
echo "SPEC_DIR:                                     $SPEC_DIR" | tee -a $SCRIPT_OUT
echo "==================== Script inputs =======================" | tee -a $SCRIPT_OUT
echo "BENCHMARK:                                    $BENCHMARK" | tee -a $SCRIPT_OUT
echo "OUTPUT_DIR:                                   $OUTPUT_DIR" | tee -a $SCRIPT_OUT
echo "==========================================================" | tee -a $SCRIPT_OUT
##################################################################
 
 
#################### LAUNCH GEM5 SIMULATION ######################
echo ""
echo "Changing to SPEC benchmark runtime directory: $RUN_DIR" | tee -a $SCRIPT_OUT
cd $RUN_DIR
 
echo "" | tee -a $SCRIPT_OUT
echo "" | tee -a $SCRIPT_OUT
echo "------- Starting gem5! ------------" | tee -a $SCRIPT_OUT
echo "" | tee -a $SCRIPT_OUT
echo "" | tee -a $SCRIPT_OUT
 
# Actually launch gem5!
$GEM5_DIR/build/X86/gem5.opt --outdir=$OUTPUT_DIR $GEM5_DIR/configs/example/spec17_config.py --benchmark=$BENCHMARK --benchmark_stdout=$OUTPUT_DIR/$BENCHMARK.out --benchmark_stderr=$OUTPUT_DIR/$BENCHMARK.err --num-cpus=1 --ruby --l1d_size=32kB --l1i_size=32kB --l2_size=256kB --l3_size=2mB --mem-size=4GB --l1d_assoc=8 --l1i_assoc=8 --l2_assoc=8 --l3_assoc=16 --maxinsts=100000 | tee -a $SCRIPT_OUT



