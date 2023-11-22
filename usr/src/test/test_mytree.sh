#!/bin/bash

output_file="./output/mytree_test.txt"

echo "--------------------------------------------" > "$output_file"
echo "Test 1: only command" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../bin/mytree >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 2: command with option <-d depth>" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../bin/mytree -d 1 >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 3: command with argument [directory]" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../bin/mytree ../../ >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "All tests finish" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"