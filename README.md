# Red-Black-Tree

C implementation of Red Black Tree and "Green Tree" data structures. Green Tree structure was created by course instructor and simply counts the frequency of a given data value (in my test cases, words).

Implemented by essentially turning C into an object oriented language using void pointers to "manually" create objects.

All necessary files are included in the directory. After downloading/cloning the repository, utilize the makefile in order to run the main "trees" file.

Command Line examples:</br>
~$ make</br>
~$ ./trees -g assign2Tests/trees.0 assign2Tests/trees.1 outputs/1</br>
 </t> (the above will throw items in trees.0 found in trees.1 into a Green Tree Structure, writing the GT into outputs/1)</br>
~$ ./trees -r assign2Tests/trees.0 assign2Tests/trees.1 outputs/1</br>
 </t> (will do the same as the first command, but will use throw items into Red-Black Tree instead)</br>
~$ make test</br>
 </t> (runs program on plethora of tests and uses diff command w/ previously known correct outputs to check correctness)</br>
~$ make clean</br>
  </t>(cleans directory of executables for full recompilation)
