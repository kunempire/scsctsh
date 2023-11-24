**scstsh** is a project of simple shell developed in c(Linux). 

Here is version 2.0.

- `./src` is the scstsh resources.
- `./usr` is the external commands similar to Linux implemented by me. There is also a ReadMe in `./usr`.

## Origin

First of all, it's a comprehensive work assigned in *Operation System*. It is named after School of Cyber Science and Technology, Shenzhen Campus of Sun Yat-sen University.

## Function

1. **Builtin command:** Support `myhelp`, `mycd`, `mypwd`, `myhistory`, `mykill`, and `exit` to exit (<ctrl+c> is capturued). All these commands are similar to builtin commands in bash. You can run `myhelp <cmd_name>` in scstsh for usage help.
2. **External command:** Support almost all the commands in the $PATH.
3. **Backgroud run:** Support `&` function with space separated in the last of a command line.
4. **Pipe:** Support `|` function with space separated.
5. **Redirection:** Support all the redirection symbol with space separated.
6. **Up and down change:** Support change command in history with up and down key, but you cannot use this function without any char input.
7. **Script file support(new):** You can write a script with '#' as annotion and `scstsh` will perform the script line by line but ignore lines beginning with '#'.

## Quick Start

There is a **scsth** compiled here, which you can run directly by `./scstsh`.

If you want to compile the project locally, you can use */src/Makefile* to make project, just keeping the directory structure.

Here is a command demo: `cat main.c | grep -n "int" | wc -l > out.txt`.

If you want to test the `Script file support`, there is a *demo.sh* in *./src/test*.

## Attention

### myhelp

The scstsh has builtin help text about `scstsh`. However, for 'loading when using', other builtin commands' help texts are stored in `./src/help`. There are 4 ways to solve the problem of path relation between `scstsh` and `help`:

1. Just keep the project structure and run `scstsh` directly.
2. Only need to keep `scstsh` and `./src` in the same directory like now.
3. Modify the relative `help` path `RELATIVE_PATH_TO_HELP` in *excute.c* to the `scstsh`.
4. Add the help texts to become a part of source code like scstsh's help text.

### error

`scstsh` now has no perfect error-handling system, that is only to capture error with limited handling like printing error information. 

When using it directly, it can nearly stasify basic need without error to crash, just avoid to input ctrl char like left and right. However, using `scstsh` to perform a script is more restricted. You cannot perform wrong command and annotion must be in a single line beginning with '#'.

### interupt and exit

<ctrl+c> to kill current command but not to exit. Use `exit` to exit `scstsh`.

### others

1. Builtin command cannot be redirected.

## Improvement

Here are also the problems and shorts exiting ~~but author doesn't want to solve~~:

1. **Keyboard monitor.** No specific process to monitor (kind of lightweight) and the monitoring logic is simple.
2. **Error handle.** Mentioned below.
3. **"Small" bugs.** Just experience it.

## Reference

[unzeY/Shell-in-linux](https://github.com/SunzeY/Shell-in-linux)

[Operation system in 2022 of Nanjing Universiry, jyy](http://jyywiki.cn/OS/2022/)

