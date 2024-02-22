```md
██████╗ ██╗██████╗ ███████╗██╗  ██╗
██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝
██████╔╝██║██████╔╝█████╗   ╚███╔╝ 
██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗ 
██║     ██║██║     ███████╗██╔╝ ██╗
╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝
```
# PIPEX
> The pipes are doors to different worlds within the code. As if it was some sort of black magic, they connect the multiple processes.
![Doraemon](https://rheyofsunshine.files.wordpress.com/2014/05/doraemon_anywhere_door_intro.jpg)
## What is pipex
This project emulates in *C* the way pipes work in *Bash*. For example, the input:
```c
./pipex in cat "wc -l" out
```
is the equivalent of:
```sh
<in cat | wc -l >out
```
The bonus version is a bit more complex; so it accepts an unlimited ammount of pipes and the use of *here_doc*.
For example:
```c
./pipex here_doc eof "cat -e" "cat -e" "cat -e" out
```
## How to use it
The program requires at least 4 inputs:

__Basic version:__
: **<input_file>** : This is where the program reads the info from. It must exist. Before executing the program.
: **<first_command>** : Any shell executable script in the path.
: **<second_command** : Any shell executable script in the path.
: **<out_file>** : If it doesn't exist, the program will crate it. If it already exists, the user must have write permissions; otherwose the program will end without writing to this file.

__Bonus version:__
: **<input file>** : If there's not such a file in the system, the user can use **here_doc** followed by the **closing command**. This will give the user the option to write on a temporary file that will become the input.
: **<unlimited_amount_of_shell_commands>** : The only condition is that they must be in the part, and they can't contain simple commas (').
: **<out_file>** : If it doesn't exist, the program will crate it. If it already exists, the user must have write permissions; otherwose the program will end without writing to this file.

## Compilation
```c
// Download the repository, then, within the folder, use:
make
// or:
make bonus
```