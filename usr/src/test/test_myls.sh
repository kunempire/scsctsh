#!/bin/bash

output_file="./output/myls_test.txt"

echo "--------------------------------------------" > "$output_file"
echo "Test 1: only command" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../bin/myls >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 2: command with option <-l>" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../bin/myls -l >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 3: command with argument [PATH]" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../bin/myls / >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 4: command with option <-l> and argument [PATH]" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../bin/myls -l /home >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "All tests finish" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"