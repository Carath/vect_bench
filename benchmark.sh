#!/bin/sh

# This script runs several instances of a target to benchmark,
# and outputs statistics on recorded RAM usage and runtimes.
# The target may be an executable file, or a symbolic link
# to one (like most bash commands). Arguments:
# 1. The target to run. It may have args, if so said target
#    and args must be enclosed in quotes, see below.
# 2. The number of runs (optional, default: 10).
# 3. The verbosity level (optional, default: 0).
#    When > 0, the target outputs are printed.
# 4. A reference value to be compared with the average runtime (optional).
# Usage example: sh benchmark.sh "target somearg" 2 1 1.5

target=$1; runs=$2; verbosity=$3; ref=$4

isInteger() {
	if [ "$1" -eq "$1" ] 2> /dev/null; then
		return "1"
	fi
	return "0"
}

if [ -z "$target" ]; then
	echo "Please provide a target to benchmark."; exit 1
fi

targetPath=$(which $(echo $target | awk '{print $1}'))
if [ -z $targetPath ]; then
	echo "Invalid target: $target"; exit 1
fi

if [ -z $runs ]; then
	runs=10 # default
fi

isInteger $runs
if [ $? -eq 0 ] || [ $runs -le 0 ]; then
	echo "Number of runs ($runs) must be an integer > 0"; exit 1
fi

if [ -z $verbosity ]; then
	verbosity=0 # default
fi

isInteger $verbosity
if [ $? -eq 0 ]; then
	echo "Verbosity level must be an integer."; exit 1
fi

if [ ! -z $ref ] && [ $(echo "$ref <= 0" | bc -l) -eq 1 ]; then
	echo "Reference value ($ref) must be > 0"; exit 1
fi

smallhash=$(md5sum $targetPath | cut -c 1-10)
printf "Launching %d run(s) of: %s\nTarget md5sum: %s...\n\n" $runs "$target" $smallhash
maxRAM=0; totalTime=0; sumSquares=0; failures=0
for i in $(seq 1 $runs); do
	# Note: using target instead of targetPath here, in order to use its args.
	start=$(date +%s.%N)
	output=`(/bin/time -f "RAM: %M" $target) 2>&1`; exitCode=$?
	end=$(date +%s.%N)
	runtime=$(echo "$end - $start" | bc -l)
	totalTime=$(echo "$totalTime + $runtime" | bc -l)
	sumSquares=$(echo "$sumSquares + $runtime^2" | bc -l)
	RAM=$(echo "$output" | awk '/RAM/{print $NF}')
	if [ $RAM -gt $maxRAM ]; then
		maxRAM=$RAM
	fi
	if [ $exitCode -ne 0 ]; then
		failures=$((failures+1))
	fi
	if [ $verbosity -gt 0 ]; then
		echo "$output\n"
	fi
	printf "Run %d:\n Exit code: %d\n RAM peak:  %d KB\n Runtime:   %.3f s\n\n" $i $exitCode $RAM $runtime
	if [ $verbosity -gt 0 ]; then
		printf "%25s\n\n" | tr " " "-"
	fi
done
maxRAM=$(echo "$maxRAM / 1000" | bc -l)
avgtime=$(echo "$totalTime / $runs" | bc -l)

# With Bessel's correction:
stdDev=0
if [ $runs -gt 1 ]; then
	stdDev=$(echo "sqrt(($sumSquares - $runs * $avgtime^2) / ($runs-1))" | bc -l)
fi

if [ $failures -ne 0 ]; then
	printf "=> %d run(s) finished with a non-zero exit code.\n" $failures
fi

printf "=> Max RAM peak:  %.0f MB\n" $maxRAM
printf "=> Time average:  %.3f s\n" $avgtime
printf "=> Time std-dev:  %.3f s\n" $stdDev

if [ ! -z $ref ]; then
	relatDiff=$(echo "($avgtime / $ref - 1) * 100" | bc -l)
	printf "=> (avg-ref)/ref: %.3f %%\n" $relatDiff
fi
