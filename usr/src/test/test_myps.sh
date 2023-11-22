#!/bin/bash

output_file="./output/myps_test.txt"

echo "--------------------------------------------------------------------------" > "$output_file"
echo "Test 1: only command" >> "$output_file"
echo "--------------------------------------------------------------------------" >> "$output_file"
../../bin/myps >> "$output_file"

echo "--------------------------------------------------------------------------" >> "$output_file"
echo "Test 2: command with option <-p pid> (exit)" >> "$output_file"
echo "--------------------------------------------------------------------------" >> "$output_file"
../../bin/myps | sed -n '3 s/^\([^[:space:]]*\)[[:space:]].*/\1/p' | xargs -r ../../bin/myps -p >> "$output_file"

echo "--------------------------------------------------------------------------" >> "$output_file"
echo "Test 3: command with option <-p pid> (random)" >> "$output_file"
echo "--------------------------------------------------------------------------" >> "$output_file"
../../bin/myps -p 26 >> "$output_file"

echo "--------------------------------------------------------------------------" >> "$output_file"
echo "All tests finish" >> "$output_file"
echo "--------------------------------------------------------------------------" >> "$output_file"