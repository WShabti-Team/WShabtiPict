# WShabtiPict

A simple tool for combinatorial test cases and **JUnit5** code generation. 


## Building with clang++ on Linux, OS/X, *BSD, etc.
Install clang through your package manager (most systems), Xcode (OS/X), or from the [LLVM website](http://llvm.org/releases/).
On Linux, you also need to install recent libstdc++ offered by gcc 5 and c++2a offered by g++-9.

Run `make` to build the `WShabtiPict` binary.

## Building on Windows
Install [cygwin](http://www.cygwin.com/) and clone this repo into your home folder. Run `make` to build the `WShabtiPict` binary.

OR

Use WSL (Windows Subsystem for Linux) (link [here](https://www.microsoft.com/en-us/p/ubuntu-2004-lts/9n6svws3rx71?activetab=pivot:overviewtab)) to execute in linux environment without installing cygwin.
To compile you need to install build-essential and make

```raw
sudo apt update
sudo apt install build-essential
sudo apt install make
sudo apt upgrade
```

If you are using **Ubuntu 18.4 or older** you need to install **g++-9**


## Usage Sample (Interactive)

```raw
./WShabtiPict
SourceCode Path: ClassExample/Calcolatrice.java

-----METHOD: public int somma(int a, int b)-----
#Do you want skip this method? (y/n)
Please specify your choice: n

#Do you want specify input file source? (y/n)
Please specify your choice: n

Please specify, separated by a comma, all possible values of "a"
For a range of numbers you can use the syntax "start:stop:step": 1:5:1,7

Please specify, separated by a comma, all possible values of "b"
For a range of numbers you can use the syntax "start:stop:step": 3,4

#Do you want specify Exclusive Constraints? (y/n)
Please specify your choice: y

To specify a combination to exclude, use the syntax "value1,value2,...".
Use "*" if you don't care about a parameter.

Please specify a combination to exclude or "stop" to terminate: 1,3

Please specify a combination to exclude or "stop" to terminate: *,4

Please specify a combination to exclude or "stop" to terminate: stop

Please specify the order of combinations for "somma": 2

-----ORACLE: public int somma(int a, int b)-----
Please specify the oracle for the following possible combinations
For a range of numbers you can use the syntax "expected_value:delta"
somma(2,3): 5
somma(4,3): 7
somma(3,3): 6
somma(5,3): 8
somma(7,3): 10

-----METHOD: public float divisione (int a, int b)-----
#Do you want skip this method? (y/n)
Please specify your choice: n

#Do you want specify input file source? (y/n)
Please specify your choice: y
Please specify the parameter file path: divisione_input.txt

Please specify the order of combinations for "divisione": 2

-----ORACLE: public float divisione (int a, int b)-----
Please specify the oracle for the following possible combinations
For a range of numbers you can use the syntax "expected_value:delta"
divisione(10,1): 10
divisione(20,3): 6:1
divisione(10,3): 3.3:0.2
divisione(5,2): 2.5
divisione(5,3): 1:1
divisione(5,1): 5
divisione(20,1): 20

Your tests have been generated, please check JUnitTests/Calcolatrice/
WARNING: Default constructor is used for class Calcolatrice. If needed, complete it in the code.
```

## Usage Sample (Automatic)
![User usage diagram](https://user-images.githubusercontent.com/58850712/110207546-780f8d00-7e84-11eb-9fd6-87648ed6994f.jpg)


**Mode: TestGenerator [-t]**
```raw
./WShabtiPict -t <INPUT_JAVA_CLASS> <INDEX_OF_METHOD_TO_TEST> <INPUT_VALUES_FILE> <K_DEGREE> 
./WShabtiPict -t ClassExample/Calcolatrice.java 2 divisione_input.txt 2
```
INPUT_VALUES_FILE 
```raw
parameter_name1:value_p1_1,value_p1_2,value_p1_3,...
parameter_name2:value_p2_start:value_p2_end:step...
...
#CONSTRAINTS
value_p1_x,value_p2_x,value_p3_x,...
value_p1_y,value_p2_y,value_p3_y,...
...
```
Example
```raw
a:10,5
b:2:3:1
#CONSTRAINTS
10,2
```

**Mode: OracleGenerator [-o]**

This mode can be skipped writing the oracle manually in the **csv file** generated by **TestGeneration** mode.
```raw
./WShabtiPict -o <INPUT_JAVA_CLASS> <INDEX_OF_METHOD_TESTED> <TEST_INPUT_FILE> 
./WShabtiPict -o ClassExample/Calcolatrice.java 2 ./tmp/test_case.csv
```
TEST_INPUT_FILE
```raw
value_p1,value_p2
...
```
Example
```raw
10,3
5,2
5,3
```

**Mode: JUnitTestCaseGenerator [-j]**
```raw
./WShabtiPict -j <INPUT_JAVA_CLASS> <INDEX_OF_METHOD_TESTED> <TEST_WITH_ORACLES_INPUT_FILE> 
./WShabtiPict -j ClassExample/Calcolatrice.java 2 JUnitTests/Calcolatrice/divisione_test.csv 
```
TEST_WITH_ORACLES_INPUT_FILE
```raw
value_p1,value_p2,expected_value
...
```
Example
```raw
10,3,3.3
5,2,2.5
5,3,1.6
```
TEST_WITH_ORACLES_INPUT_FILE (if at least one oracle needs delta)
```raw
value_p1,value_p2,expected_value,delta
...
```
Example
```raw
10,3,3.3,0.1
5,2,2.5,0
5,3,1.6,0.1
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[MIT](https://choosealicense.com/licenses/mit/)
