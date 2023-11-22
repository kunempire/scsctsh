#!/bin/bash

output_file="./output/myrm_test.txt"

echo "Create test files and directory for testing" > "$output_file"
echo "Test content 1" > file1.txt
echo "Another test content 2" > file2.txt
echo "Another test content 3" > file3.txt
mkdir test_directory1
cd test_directory1
mkdir test_directory2
cd ..
echo "File4 inside directory1" > test_directory1/file4.txt
echo "File5 inside directory1/directory2 " > test_directory1/test_directory2/file5.txt
echo "--------------" >> "$output_file"
echo "tree for now:" >> "$output_file"
echo "--------------" >> "$output_file"
../../bin/mytree -d 4 >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 1: only command" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../bin/myrm >> "$output_file"
echo "--------------" >> "$output_file"
echo "tree for now:" >> "$output_file"
echo "--------------" >> "$output_file"
../../bin/mytree -d 4 >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 2: rm single file" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../bin/myrm file1.txt >> "$output_file"
echo "--------------" >> "$output_file"
echo "tree for now:" >> "$output_file"
echo "--------------" >> "$output_file"
../../bin/mytree -d 4 >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 3: rm multiple files" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../bin/myrm file2.txt file3.txt >> "$output_file"
echo "--------------" >> "$output_file"
echo "tree for now:" >> "$output_file"
echo "--------------" >> "$output_file"
../../bin/mytree -d 4 >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 4: command with option <-r DIRECTORY>" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../bin/myrm -r test_directory1 >> "$output_file"
echo "--------------" >> "$output_file"
echo "tree for now:" >> "$output_file"
echo "--------------" >> "$output_file"
../../bin/mytree -d 4 >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "All tests finish" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"