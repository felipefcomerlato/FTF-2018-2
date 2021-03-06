# FTF 2018/2 - Projeto de injeção de falhas com Carol-FI

### Autores

Execute todas as injeções com:
```{r, engine='bash', code_block_name} 
$ sh ./run.sh
```

* **Felipe Comerlato** - [felipefcomerlato](https://github.com/felipefcomerlato)
* **Gabriel Allegretti** - [gallegretti](https://github.com/gallegretti)
* **Gustavo Rosa** - [ciques](https://github.com/ciques)
* **Rafael Allegretti** - [Allegretti2](https://github.com/Allegretti2)


# CAROL-FI (https://github.com/UFRGS-CAROL/carol-fi) - Repositório no Github


CAROL-FI GDB Fault Injector should work on any recent machine with gdb that supports python.

The fault injector requires two command line arguments as input:
* Configuration file specifying the tests to be done
* How many times to repeat the tests specified in the configuration file

The command line to run the CAROL-FI is as follow:

Then, to run the fault injector use the following command:
```{r, engine='bash', code_block_name} 
$ ./fault_injector.py -c <conf file> -i <# tests>
```

For each fault injected, CAROL-FI will compare the output produced with a _**gold**_ output. If the outputs differ, CAROL-FI will save the output with the log files in the **logs** folder. If the program crashes, hangs, or the output and gold match, the output will not be saved.


## How to run a simple test

To test quicksort, run the make into the quicksort folder '/sample-code/quicksort'. A folder into /tmp directory will be created with the binaries and files needed.

Supposing you cloned the repository into your home directory, you should be able to run the simple test with the following commands:
```{r, engine='bash', code_block_name} 
$ cd ~/carol-fi/sample-code/quicksort
$ make
```

Then, to run the fault injector use the following command:
```{r, engine='bash', code_block_name} 
$ cd ~/carol-fi
$ ./fault_injector.py -c ./sample-code/quicksort/quicksort.conf -i 10
```

The fault injector will run quicksort 10 times and, the logs will be stored in the *logs* folder.

The file 'summary-carolfi.log' will be generated, and you can run the script 'stats.sh' to have an overview of corruptions (SDCs), Hangs, Crashes, and masked faults.

Sometimes the fault injector cannot access the program data, and the fault injection will fail. 

## Configuration files

A configuration file can have several sections, each section (except the DEFAULT section) will specify one fault injection to be performed by CAROL-FI. The DEFAULT section contains information that will be used by every other section.

### DEFAULT section

The DEFAULT section contains the following keys:

* debug - Print additional information in the log files generated by CAROL-FI

* gdbExecName - How to run gdb, you can use the absolute path or execute a specific version of gdb. Usually, you can set the value to 'gdb'

* posExecScript (optional) - Specify a script or command line to execute after the program execution and before the output corruption check (SDC check); This script will be executed in the same shell you are executing the fault injector

* preExecScript (optional) - Specify a script or command line to execute before the program execution; This script will be executed in the same shell you are executing the fault injector

* goldFile - The file with the error-free output; This file will be used to check the correctness of each execution; A simple diff is used to check for errors

* outputFile - The file containing the program output; This file will be used to check the correctness of each execution; A simple diff is used to check for errors

* maxWaitTime - How long can CAROL-FI wait for the program completion, usually the program's average execution time

* gdbInitStrings - The strings used to initialize gdb, which is the program executable path and the arguments

* signalCmd - Shell command to send SIGINT to the application being tested

* killStrs - Kill commands to exit all applications (GDB and the application tested), this will be used to ensure a safe termination after each test

You can see an example of a DEFAULT section below:

```
[DEFAULT]

debug = False
gdbExecName = gdb
goldFile = /tmp/quicksort/gold_5000000
outputFile = /tmp/quicksort/output_5000000
maxWaitTime = 10
gdbInitStrings = file /tmp/quicksort/quicksort;set args 5000000 4 /tmp/quicksort/inputsort_134217728 /tmp/quicksort/output_5000000
signalCmd = killall -2 quicksort
killStrs = killall -9 gdb;killall -9 quicksort
```

### Other Sections

The other sections define when the fault will be injected and how. Thus, each section defines an initial and end time so that CAROL-FI will try to inject faults during this time, and which fault model to use.

The sections contain the following keys:
* initSignal - In seconds after the program starts running

* endSignal - In seconds after the program starts running

* faultModel - Which fault model to use: 0 -> Single; 1 -> Double; 2 -> Random; 3 -> Zero; 4 -> Least Significant Bits (LSB)

The name of each section will be used to create a folder in the *logs* directory containing all the logs and outputs.

Bellow you can find two sample sections defined:

```
[quicksort-lsb]
initSignal = 0
endSignal = 10
faultModel = 4

[quicksort-double]
initSignal = 0
endSignal = 10
faultModel = 1
```

The section named *quicksort-lsb* will choose randomly a time between 0 and 10 seconds to inject a fault, the fault model will be  *Least Significant Bits (LSB)*. The section *quicksort-double* will also choose a time between 0 and 10 seconds, but it will perform a double bit-flip as fault model.

If you need to create several sections with the same fault model, or the same fault injection time, you can define the keys you want in the DEFAULT section. For example, the configuration file below defines one section for each fault model, but all the sections use the same fault injection time.

```
[DEFAULT]

debug = False
gdbExecName = gdb
seqSignals = 1
numThreadsFI = 1
goldFile = /tmp/quicksort/gold_5000000
outputFile = /tmp/quicksort/output_5000000
maxWaitTime = 10
gdbInitStrings = file /tmp/quicksort/quicksort;set args 5000000 4 /tmp/quicksort/inputsort_134217728 /tmp/quicksort/output_5000000
signalCmd = killall -2 quicksort
killStrs = killall -9 gdb;killall -9 quicksort

initSignal = 0
endSignal = 10

[quicksort-single]
faultModel = 0

[quicksort-double]
faultModel = 1

[quicksort-random]
faultModel = 2

[quicksort-zero]
faultModel = 3

[quicksort-lsb]
faultModel = 4
```
## Fault Models
Currently, we have 5 fault models implemented:

* (0) Single - flips only one bit from all the bits that compose the data
* (1) Double - flips two bits from all the bits that compose the data
* (2) Random - replaces all the bits from the data by a random bit
* (3) Zero - replaces all the bits by zero
* (4) Least Significant Bits (LSB) - flips one bit from the first byte of the data
