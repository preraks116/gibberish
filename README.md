# gibberish
Shell implemented in C


## Running the shell
Execute the following commands
```
make
./gibberish
```
To clear the history
```
make clean
```

## Files
```
gibberish
├── Makefile
├── README.md 
├── a.out
├── gibberish
├── arrowkey.c      - has functions that are used to implement ↑ key functionality 
├── cd.c            - has functions that are used to implement cd command
├── echo.c          - has functions that are used to implement echo command
├── history.c       - has functions that are used to implement history command
├── pwd.c           - has functions that are used to implement the pwd command
├── repeat.c        - has functions that are used to implement repeat command
├── extcmd.c        - has functions that are used to handle external commands and bg processes
├── ls.c            - has functions that are used to implement ls command
├── pinfo.c         - has functions that are used to implement pinfo command
├── main.h          - has all the required header files and functions
├── prompt.c        - has functions that are used to display the prompt
├── finishbg.c      - has functions that are used to handle bg processes that have finished
├── mainbackup.c    - just in case something goes wrong
├── main.c          - contains the main function that runs the entire shell
└── history.txt     - has history saved
```
## Errors
`ls -l total is wrong`
`pinfo seg faults- path error maybe`
