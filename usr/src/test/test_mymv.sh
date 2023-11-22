#!/bin/bash

output_file="../output/mymv_test.txt"

mkdir temp_dir
cd temp_dir
echo "This is file1" > file1.txt
echo "This is file4" > file4.txt
mkdir subdir1
echo "This is file2" > subdir1/file2.txt
mkdir subdir2
echo "This is file3" > subdir2/file3.txt
mkdir subdir3
echo "This is file7" > subdir3/file7.txt
echo "Create test files and directory for testing" > "$output_file"

echo "--------------" >> "$output_file"
echo "tree for now:" >> "$output_file"
echo "--------------" >> "$output_file"
tree >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 1: only command" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../../bin/mymv >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 2: mv one file to one file (rename)" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../../bin/mymv file5.txt file4.txt >> "$output_file"
echo "--------------" >> "$output_file"
echo "tree for now:" >> "$output_file"
echo "--------------" >> "$output_file"
tree >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 3: mv one file to one file (mv to dest)" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../../bin/mymv subdir1/file6.txt file5.txt >> "$output_file"
echo "--------------" >> "$output_file"
echo "tree for now:" >> "$output_file"
echo "--------------" >> "$output_file"
tree >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 4: mv one directory to one directory" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../../bin/mymv subdir1 subdir3 >> "$output_file"
echo "--------------" >> "$output_file"
echo "tree for now:" >> "$output_file"
echo "--------------" >> "$output_file"
tree >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 5: cp multiple files to one directory" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../../bin/mymv subdir2 file1.txt subdir2/file3.txt subdir1/file2.txt >> "$output_file"
echo "--------------" >> "$output_file"
echo "tree for now:" >> "$output_file"
echo "--------------" >> "$output_file"
tree >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 6: mv mixed files and directory to one directory" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../../bin/mymv subdir1 subdir2/file1.txt subdir2 subdir2/file3.txt >> "$output_file"
echo "--------------" >> "$output_file"
echo "tree for now:" >> "$output_file"
echo "--------------" >> "$output_file"
tree >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 7: mv directory2 to one directory1 (directory2 contians directory1)" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../../bin/mymv subdir1/subdir3 subdir1 >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "All tests finish" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"

cd ..
rm -r temp_dir