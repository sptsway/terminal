# terminal
an in-memory filesystem implm via c++ <br>
my terminal seemed slow, so i created my own :))

#### how to start?
1. `g++ terminal.cpp -o terminal.out`
2. `./terminal.out`


#### how to interact?
```
################### how to use terminal❓ ###################

1. help : to output documentation
2. mkdir <param path of folder> : make a directory
3. rm <param path of folder> : remove a directory recursively
4. cd <param path of folder> : change path to the specified directory
5. ls : list directory
6. pwd - print current working directory
7. printdir : print all folders with in the current directory
8. printdisk : print all folders from root directory

################### ----------------- ###################
```

### show me an example usage
```


☺☺☺☺☺☺☺☺[WTF]☺☺☺☺☺☺☺☺
welcome to funny-terminal

################### how to use terminal❓ ###################

1. help : to output documentation
2. mkdir <param path of folder> : make a directory
3. rm <param path of folder> : remove a directory recursively
4. cd <param path of folder> : change path to the specified directory
5. ls : list directory
6. pwd - print current working directory
7. printdir : print all folders with in the current directory
8. printdisk : print all folders from root directory

################### ----------------- ###################
wtf1.1$ / > mkdir hello
✅ created directory
wtf1.1$ / > mkdir hello/some
✅ created directory
wtf1.1$ / > cd hello
✅ changed directory
wtf1.1$ hello > cd some
✅ changed directory
wtf1.1$ some > pwd
/hello/some/
wtf1.1$ some > printdisk
- /
|	- hello
|	|	- some
wtf1.1$ some > cd ..
✅ changed directory
wtf1.1$ hello > rm some
✅ removed directory
wtf1.1$ hello > printdisk
- /
|	- hello
wtf1.1$ hello > cd ..
✅ changed directory
wtf1.1$ / > exit
```
