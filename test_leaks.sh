#!/bin/bash
# test_leaks.sh
# This script runs your so_long executable with Valgrind to check for memory leaks
# and possible double free errors.
#
# Usage: ./test_leaks.sh <path_to_map_file>
#
# Make sure that your executable is compiled with the -g flag for debugging symbols.
# Example:
#     gcc -g -Wall -Wextra -Werror -o so_long *.c -lmlx -lXext -lX11 -lm

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <path_to_map_file>"
    exit 1
fi

# Set Valgrind options
VALGRIND_OPTIONS="--leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind.log"

echo "Running Valgrind on so_long with map file: $1"
valgrind $VALGRIND_OPTIONS ./so_long "$1"

echo "Valgrind analysis complete. Please check 'valgrind.log' for details."
