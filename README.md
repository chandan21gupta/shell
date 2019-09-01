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
    Shell prints wrong path provided<br/>
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
  (Any other flag provided)<br/>
  Simply prints it due to the assumption.<br/>
  
  
