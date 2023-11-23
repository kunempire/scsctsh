echo "Hello scstsh!" > src/test/output/demo.txt
mycd src
cat main.c | grep -n "int" | wc -l >> test/output/demo.txt
# tt
mypwd
ls -a
wc -w < test/output/demo.txt | head -n 1 >> test/output/demo.txt
echo "finish"
wrong_cmd