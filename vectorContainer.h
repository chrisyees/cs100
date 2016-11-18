#ifndef _VECTORCONTAINER_H_
#define _VECTORCONTAINER_H_
#include "rshell.h"
#include <boost/tokenizer.hpp>
#include <string>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <typeinfo>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "argument.h"
#include "connector.h"
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;
using namespace boost;
class vectorContainer {
    private:
        string input;
        //the users input
        
        vector<rshell*> argumentList; 
        //holds all parsed commands/arguments
        
        vector<rshell*> connectorList;
        //holds all parsed connectors
    public:
        vectorContainer() : input(NULL){};
        vectorContainer(string in) : input(in){}; //passes in a string to parse into the vector

        //void add_element(rshell* element); 
        //used in parse() to add to the vector
        
        void print(); 
        //prints all commands in the vector
        
        int size(); 
        //returns both vectors' sizes sum
        
        void parse();
        //breaks string into it's separate commands and places them into the vector container
        
        rshell* argAt(int i); 
        //returns the argument at a location
        
        rshell* conAt(int i);
        //return the connector at a location
        
        void execute();
        //uses all functions above to both create the vector of commands and execute it
};
#endif