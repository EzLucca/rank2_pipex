#!/bin/bash

# Check for arguments
if [ $# -lt 1 ]; then
    echo "Usage: $0 <program> [args...]"
    exit 1
fi

PROGRAM=$1
shift
ARGS="$@"

# Run valgrind and generate full output + filtered source lines
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --error-exitcode=1 \
         --verbose \
         $PROGRAM $ARGS 2>&1 | tee valgrind-report.txt | \
         grep -E "==[0-9]+==.*\([a-zA-Z0-9_./-]+:[0-9]+\)" | \
         sed -E 's/^.*==[0-9]+==\s+(by|at) 0x[0-9A-F]+: //' \
         > valgrind-lines.txt

echo "Full report: valgrind-report.txt"
echo "Filtered source locations: valgrind-lines.txt"

