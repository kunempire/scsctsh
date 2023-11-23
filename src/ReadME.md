Let's have a quick view of the structure of the source of `scstsh`.

```bash
.
├── ctrl.c # keyboard "monitor"
├── execute.c # execute commands
├── header
│   ├── ctrl.h
│   ├── execute.h
│   ├── main.h
│   ├── parameter.h # macro variables
│   ├── parse.h
│   └── print_setting.h # UI design to print
├── help # myhelp texts
│   ├── mycd.txt
│   ├── myhelp.txt
│   ├── myhistory.txt
│   ├── mykill.txt
│   ├── mypwd.txt
│   └── scstsh.txt
├── main.c # main function
├── Makefile # help to compile C files
├── parse.c # parse commands
├── ReadME.md
└── test # test scstsh
    ├── demo.sh
    ├── output
    └── test_scstsh.sh
```
Annotations in the code are detailed. Now, let me start your exploration: **Welcome to the undersurface of `C` and `Linux`**.