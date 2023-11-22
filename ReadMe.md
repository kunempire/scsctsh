**scstsh** is a project of simple shell developed in c(Linux). This is version 1.0.

## Origin

First of all, it's a comprehensive work assigned in *Operation System*. It is named after School of Cyber Science and Technology, Shenzhen Campus of Sun Yat-sen University.

## Function

1. **Builtin command:** Support `myhelp`, `mycd`, `mypwd`, `myhistory`, `mykill`. All these commands are similar to builtin commands in bash. You can run `myhelp <cmd_name>` in scstsh for usage help.
2. **External command:** Support almost all the commands in the $PATH.
3. **Backgroud run:** Support `&` function with space separated in the last of a command line.
4. **Pipe:** Support `|` function with space separated.
5. **Redirection:** Support all the redirection symbol with space separated.
6. **Up and down change:** Support change command in history with up and down key, but you cannot use this function without any char input.

## Quick Start

There is a **scsth** compiled in */src*, which you can run directly by `make run` or `./scstsh`.

If you want to compile the project locally, you can use */src/Makefile* to make project, just keeping the directory structure.

Here is a command demo: `cat main.c | grep -n "int" | wc -l > out.txt`.

## Reference

[unzeY/Shell-in-linux](https://github.com/SunzeY/Shell-in-linux)

[Operation system in 2022 of Nanjing Universiry, jyy](http://jyywiki.cn/OS/2022/)

