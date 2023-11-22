all : myman myls mycp mymv myrm myps mytree

# gcc 
# -IPATH: search headfiles in PATH
# -c: generate the object file without linking
# -o PATH: output file PATH
myman: myman.c
	gcc -o myman -I./header myman.c

myls: myls.c
	gcc -o myls -I./header myls.c

operate_file.o: operate_file.c
	gcc -c -o operate_file.o -I./header operate_file.c

mycp.o: mycp.c
	gcc -c -o mycp.o -I./header mycp.c

mycp: mycp.o operate_file.o
	gcc mycp.o operate_file.o -o mycp

myrm.o: myrm.c
	gcc -c -o myrm.o -I./header myrm.c

myrm: myrm.o operate_file.o
	gcc myrm.o operate_file.o -o myrm

mymv.o: mymv.c
	gcc -c -o mymv.o -I./header mymv.c

mymv: mymv.o operate_file.o
	gcc mymv.o operate_file.o -o mymv

myps: myps.c
	gcc -o myps -I./header myps.c

mytree: mytree.c
	gcc -o mytree -I./header mytree.c

# declare phony targets
.PHONY: clean test

clean:
	rm -f myman myls mycp mymv myrm myps mytree

clean_o:
	rm -f *.o







