#!/bin/sh

# Name of this script.
self="$(basename "$0")"

# Default output directory.
OUTPUT_DIR="$( dirname $0 )/results"

# Default KMT executable to use.
KMT="$( dirname $0 )/objs/kmt"

# Default timeout in seconds (max CPU time) for each KMT run.
TIMEOUT=300

# Directory containing the benchmark examples.
EXAMPLE_DIR="$( dirname $0 )/examples"

# List of examples to bench on.
EXAMPLES="
FinkelCounterEx.net
FinkelKM.net
abp.net
basicME.net
ifip.net
l6000.net
pingpong.net"

# Coverability tree computation procedures.
ENGINES="km km-red mct"


# Helper functions and constants ###############################################

error ()
{
    echo "$self: error: $1" 1>&2
}


# Command-line Processing ######################################################

usage ()
{
    cat 1>&2 <<EOF
Usage: $self [options]

  -e <exe>	Use KMT executable <exe>.
  -h		Print this message and exit.
  -o <dir>	Write results in directory <dir>.
  -t <int>	Set the (CPU) timeout to <int> for each bench.
EOF
}

while getopts "e:ho:t:" option; do
    case $option in
	e)
	    KMT="$OPTARG"
	    ;;
	h)
	    usage
	    exit 0
	    ;;
	o)
	    OUTPUT_DIR="$OPTARG"
	    ;;
	t)
	    TIMEOUT="$OPTARG"
	    ;;
	*)
	    usage
	    exit 1
	    ;;
    esac
done

if [ "$#" -ge "$OPTIND" ]; then
    usage
    exit 1
fi


# Auto-configuration and checks ################################################

# Check that the KMT executable exists.
if [ ! -x "${KMT}" ]; then
    error "couldn't find KMT executable \`${KMT}'."
    exit 1
fi

# Check that the example directory exists.
if [ ! -d "${EXAMPLE_DIR}" ]; then
    error "couldn't find example directory \`${EXAMPLE_DIR}'."
    exit 1
fi


# Main #########################################################################

echo "Simple Benchmark Script for KMT (${KMT})"
echo "Timeout for each coverability tree computation run: ${TIMEOUT} (s)"
echo "Output directory: ${OUTPUT_DIR}"

mkdir -p ${OUTPUT_DIR}

for file in ${EXAMPLES}; do
    echo
    echo "==================================================================="
    echo "${file}"

    for e in ${ENGINES}; do
	for s in bfs dfs; do
	    echo "-------------------------------------------------------------------"
	    echo "With procedure \`$e' and search \`$s'"
	    outfile="${OUTPUT_DIR}/${file}.$e.$s"
	    opt="-cq -e $e -s $s -d ${outfile}.dot -t ${outfile}.txt"
	    cmdline="${KMT} ${opt} ${EXAMPLE_DIR}/${file}"
	    echo
	    echo "Command line: ${cmdline}"
	    echo
	    ulimit -t ${TIMEOUT}
	    if ! ${cmdline}; then
		echo
		echo "!!!! KMT returned an exit status of 1 (false) or was killed."
		echo "!!!! Note: CPU time was limited to ${TIMEOUT} seconds."
		echo
	    fi
	done
    done
done
