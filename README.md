# B Tree

B trees implementation written in C based on Introduction to Algorithms, CLRS.

### Prerequisites

* gcc (Ubuntu 5.4.1-8ubuntu1) or higher
* clang version 4.0.0-1ubuntu1 or higher [optional] [recommended]
* CUDA Version 9.0.176 or higher [optional]
* Python 3.5.3 or higher
* matplotlib==2.0.2 or higher

### Installing

First compile the project on your local system by:

```
make clean
make T=[T_VALUE]

Example:
    make T=1024
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
    ./test -sb 100000 75643
```

For automated tests, run:

```
python3 tester.py
```

The script does the following: 

* The python script compiles the source code for t values = 2^i for i in [2, 10).
* It builds the tree for the above t values with 1,000,000 records and plots graphs for t-values vs time.
* It searches for 10 random keys for each t value (same ten keys) and plots t_values vs average of those times.

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
* Python 3 - For testing
* Matplotlib - For plotting results

## Authors

* **Ganesh K.** - [DarkFate13](https://github.com/DarkFate13)

## Acknowledgments

* This is developed as an assignment for Advanced Algorithms Course.
* I would like to thank my professors, Prof. NS Kumar and Prof. Channa Bankapur for their valuable advice. 
* I would like to give credit to Prof. NS Kumar for providing necessary code for file handling.
* The delete functions are based on GeeksforGeeks implementation in C++.

## Important Note
* The code tends to give a segmentation fault in Ubuntu. [Fixed after 'Ubuntu bug fix' commit, still need to run tests]
* Highly recommended to use Windows Bash shell till issue is resolved.
