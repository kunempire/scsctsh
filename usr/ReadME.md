This folder contains the external commands made only with POSIX and STD C libraries in Linux (UNIX). 

Of cause, compared to the similar Linux commands, these are too simple and ugly. Thus, for the final examination, the insight into Linux system and your reference, here the folder is.

> Code is simple and varables' names are easy to understand. Besides, annotations are noted when necessary.

## Structure

Let's have a quick view of the structure of this folder.

```bash
.
├── ReadME.md
├── bin # binary commands to execute after compiled
│   ├── mycp
│   ├── myls
│   ├── myman
│   ├── mymv
│   ├── myps
│   ├── myrm
│   └── mytree
└── src
    ├── Makefile # help to compile C files
    ├── header
    │   ├── operate_file.h
    │   ├── parameter.h
    │   └── print_setting.h
    ├── manual_page # myman's pages to get software information
    │   ├── mycp.txt
    │   ├── myls.txt
    │   ├── myman.txt
    │   ├── mymv.txt
    │   ├── myps.txt
    │   ├── myrm.txt
    │   ├── mytree.txt
    │   └── scstsh.txt
    ├── mycp.c
    ├── myls.c
    ├── myman.c
    ├── mymv.c
    ├── myps.c
    ├── myrm.c
    ├── mytree.c
    ├── operate_file.c
    └── test # test commands
        ├── Makefile # run `make test` to test all the commands
        ├── output # test output
        │   ├── mycp_test.txt
        │   ├── myls_test.txt
        │   ├── myman_test.txt
        │   ├── mymv_test.txt
        │   ├── myps_test.txt
        │   ├── myrm_test.txt
        │   └── mytree_test.txt
        ├── test_mycp.sh # test script suits
        ├── test_myls.sh
        ├── test_myman.sh
        ├── test_mymv.sh
        ├── test_myps.sh
        ├── test_myrm.sh
        └── test_mytree.sh
```

## Attention

1. If you want to have information of these commands, run `myman <name>`.
2. If you want to use these commands somewhere else (althrough impossible), remember to add `the path to/bin` to enviromental varables.
3. The manual pages are stored in `/src/manual_page`. Therefore, if you use `myman` somewhere else, you need to modify the `MANUAL_PAGE_PATH` in */src/myman.c* properly. If you arenot familar with C, you can just keep the project structure and run `myman` or run `../../bin/myman` without enviromental varable setting,in *the/path/to/usr/src/test`.
4. Try to use `Makefile` to build projects or run commands. You will find it convenient.