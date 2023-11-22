#!/bin/bash

output_file="../output/mycp_test.txt"

mkdir temp_dir
cd temp_dir
echo "This is file1" > file1.txt
echo "This is file4" > file4.txt
mkdir subdir1
echo "This is file2" > subdir1/file2.txt
mkdir subdir2
echo "This is file3" > subdir2/file3.txt
echo "Create test files and directory for testing" > "$output_file"

echo "--------------" >> "$output_file"
echo "tree for now:" >> "$output_file"
echo "--------------" >> "$output_file"
tree >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 1: only command" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../../bin/mycp >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 2: cp one file to one file" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../../bin/mycp file4.txt file1.txt >> "$output_file"
echo "file4.txt:" >> "$output_file"
cat file4.txt >> "$output_file"
echo "--------------" >> "$output_file"
echo "tree for now:" >> "$output_file"
echo "--------------" >> "$output_file"
tree >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 3: cp one directory to one directory" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../../bin/mycp subdir1 subdir2 >> "$output_file"
echo "--------------" >> "$output_file"
echo "tree for now:" >> "$output_file"
echo "--------------" >> "$output_file"
tree >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 4: cp multiple files to one directory" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../../bin/mycp subdir2 file1.txt subdir2/file3.txt subdir1/file2.txt >> "$output_file"
echo "--------------" >> "$output_file"
echo "tree for now:" >> "$output_file"
echo "--------------" >> "$output_file"
tree >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 5: cp mixed files and directory to one directory" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../../bin/mycp subdir1 file1.txt subdir2 subdir2/file3.txt >> "$output_file"
echo "--------------" >> "$output_file"
echo "tree for now:" >> "$output_file"
echo "--------------" >> "$output_file"
tree >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "Test 6: cp directory2 to one directory1 (directory2 contians directory1)" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"
../../../bin/mycp subdir1/subdir2 subdir1 >> "$output_file"

echo "--------------------------------------------" >> "$output_file"
echo "All tests finish" >> "$output_file"
echo "--------------------------------------------" >> "$output_file"

cd ..
rm -r temp_dir