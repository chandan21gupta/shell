# shell
This is a custom shell I made in c for a linux based environment. Currently it handles the following 10 commands, five of which are internal and remaining external.

## internal commands

### cd [path]
  changes the shell's working directory to the input path (can be relative or absolute).<br/>
  Ex. cd Desktop (shifts from current directory to Desktop).<br/>
  Extreme cases -> (No path provided)<br/>
    Shell prints path argument missing
    <br/>
                ->(Unreachable or wrong path provided)<br/>
    Shell prints "wrong path provided".<br/>

### echo [flags] [statement]
Assumption -> Any other flag is just another statement<br/>
prints the statement input given by the user.<br/>
Ex. echo Chandan<br/>
Output - Chandan <br/>
flags -> -e, -n<br/>
-e - removes spaces from the text<br/>
-n - does not go to the next line after printing the given statement.<br/>
Extreme cases -> (No statement provided)<br/>
  simply returns to the shell.</br>
-en or ne - removes spaces and prevents newline.
(Any other flag provided)<br/>
  Simply prints it due to the assumption.<br/>

### history [flags]
Assumption -> Only storing top last 100 commands due to memory issues.<br/>
prints the list of used commands chronologically.<br/>
Ex. history<br/>
Output - list of used commands with number.<br/>
flags -> -c,-w<br/>
-c - clears the history<br/>
-w - stores the history till that point in a text file named "history.txt".<br/>
Extreme cases -> (any other flag)<br/>
prints "Invalid Command"<br/>
-cw or -wc - stores the history till now in a file and then clears it from the buffer.<br/>
(More than one arguments)<br/>
Raises warning not to give more than one arguments<br/>


### pwd 
prints the current working directory local to the shell.<br/>
Ex. pwd<br/>
Output - current working directory<br/>
Extreme cases -> same as history command<br/>
Output -> Raises a warning, telling the user not to provide arguments.<br/>

### exit 
kills the custom shell.</br>
Extreme cases -> same as history command<br/>
Output -> Raises a warning, telling the user not to provide arguments.<br/>

## external commands

### consists mainly of ls, cat, mkdir, rm and date. 
For these commands I first created a child process using fork() in c. In the child process I executed these commands using the execvp() function from the exec() family. Then I made the parent process wait for the child process to complete its execution.
<br/>
Extreme cases -> Since the execvp() system call directly executes the command binary executables, same exceptions will be shown as in the parent of shell.  
