# also a test for script support and external command recall

echo "--------------------------------------------" > ./test/output/test_scstsh.txt
echo "Test 1--builtin command: mycd mypwd myhelp" >> ./test/output/test_scstsh.txt
echo "--------------------------------------------" >> ./test/output/test_scstsh.txt
# also a test for '>>'
mypwd
mycd
mypwd
myhelp
# back to the Makefile directory
mycd /home/sysu/.kun/program/scstsh/src

echo "--------------------------------------------" > ./test/output/test_scstsh.txt
echo "Test 2--pipe and redirection: >/>> < 2>/2>> $>/$>>" >> ./test/output/test_scstsh.txt
echo "--------------------------------------------" >> ./test/output/test_scstsh.txt
# also a test for '\"'
cat main.c | grep -n "int" | wc -l >> ./test/output/test_scstsh.txt
wc -w < ./test/output/test_scstsh.txt | head -n 1 >> ./test/output/test_scstsh.txt
touch "test test"
rm "test test" nofile

# tests below for presenting by hand

# Test 3--keyboard "minitor": up and down switch histroy 
# nocmd
# mytree -d 3 ./src
# remember to input a char before switching

# Test 4--myhistory
# cat lk 2> ./test/output/test_scstsh.txt
# myhelp mycd
# myhistory

# Test 5--background, interupt and mykill
# sleep 10
# ctrl+c
# sleep 70 &
# echo "fore_run" >> test/output/demo.txt
# myps -p 'sleep'
# mykill 'sleep'

# Test 6--exit
