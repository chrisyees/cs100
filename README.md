Rshell
======

For License Information: Read LICENSE
Authors and contributors: .....

File list:
----------
```
argument.cpp
argument.h
connector.cpp
connector.h
LICENSE
main.cpp
makefile
README.md
rshell.h
vectorContainer.cpp
vectoContainer.h
```

Purpose:
--------
The program reads a string and interprets it as a Bash command.
It will parse the string and then execute the command. It interprets
connectors.

Design:
-------
We have an abstract base class rshell which argument and connector inherit from.
VectorContainer will separate the strings into either an argument or connector
class and store it in a vector of rshell type. Execution occurs in vectorContainer because it holds all the classes.

Bugs:
-----
