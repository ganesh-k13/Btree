# B Tree

B trees implementation written in C based on Introduction to Algorithms, CLRS.

### Prerequisites

* g++ version 6.3.0 or higher
* clang++ version 4.0.0-1ubuntu1 or higher

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
    -s [LENGTH] [KEY]
        Print record details bearing the given key.
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
* I would like to give credit to Prof. NS Kumar for providing basic code for file handling.