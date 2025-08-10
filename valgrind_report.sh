#!/bin/bash

# Check if executable was provided
if [ $# -lt 1 ]; then
    echo "Usage: $0 ./executable [args...]"
    exit 1
fi

program="$1"
shift

# Run valgrind with leak detection and save output to valgrind_log.txt
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-fds=yes \
         --trace-children=yes \
         --track-origins=yes \
         "$program" "$@"


