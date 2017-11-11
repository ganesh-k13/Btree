# B Tree

B trees implementation written in C based on Introduction to Algorithms, CLRS.

### Prerequisites

* gcc (Ubuntu 5.4.1-8ubuntu1) or higher
* clang version 4.0.0-1ubuntu1 or higher

### Installing

First compile the project on your local system by:

```
make clean
make
```
For testing if it works, see Running tests below

## Running Tests

For manual tests, run:

``` 
./test [OPTIONS]... [PARAMETERS]...

OPTIONS:
	
    -b [LENGTH]
        Build B tree and flush to file bearing [LENGTH] records from dataset.csv
    -d [KEY]
        Delete record bearing the given [KEY].
    -s [KEY]
        Print record details bearing the given [KEY] by reading existing file.
    -sb [LENGTH] [KEY]
        Build B tree and flush to file bearing [LENGTH] records from dataset.csv and print record details bearing the given [KEY]
    -t [LENGTH] 
        Testing option.
    
EXAMPLE:
    ./test -t 100000 75643
```

To clear existing .dat file:

```
make remdat

```

## Deployment

For using the B Tree:

* Copy BTree.h and Node.h header files to the location of your source file.
* Include BTree.h and Node.h to your source file.
* Use BTree.o and Node.o object files and compile your program:

## Built With

* C - The main backend used

## Authors

* **Ganesh K.** - [DarkFate13](https://github.com/DarkFate13)

## Acknowledgments

* This is developed as an assignment for Advanced Algorithms Course.
* I would like to thank my professors, Prof. NS Kumar and Prof. Channa Bankapur for their valuable advice. 
* I would like to give credit to Prof. NS Kumar for providing necessary code for file handling.
* The delete functions are based on GeeksforGeeks implementation in C++.

## Important Note
* The code tends to give a segmentation fault in Ubuntu. 
* Highly recommended to use Windows Bash shell till issue is resolved.
