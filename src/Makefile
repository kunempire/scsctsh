scstsh: main.o parse.o execute.o ctrl.o
	gcc main.o ctrl.o parse.o execute.o -o scstsh

# gcc 
# -IPATH: search headfiles in PATH
# -c: generate the object file without linking
# -o PATH: output file PATH
main.o: main.c
	gcc -c -o main.o -I./header main.c

parse.o: parse.c
	gcc -c -o parse.o -I./header parse.c

execute.o: execute.c
	gcc -c -o execute.o -I./header execute.c

ctrl.o: ctrl.c
	gcc -c -o ctrl.o -I./header ctrl.c

# declare phony targets
.PHONY: clean clean_o test test_cd

clean:
	rm -f main.o ctrl.o parse.o execute.o scstsh

clean_o:
	rm -f main.o ctrl.o parse.o execute.o 

run:
	./scstsh

test:
	../scstsh ./test/test_scstsh.sh
