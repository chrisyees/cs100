#include "headers/argument.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
argument :: argument (char* x)
{
	myArg = x;
	isExecuted = false;
	counter = 0;
//	args = new char[256];
}
string argument :: myName()
{
    return myArg;
}
void argument :: print()
{
    cout << args<< endl;
}
void argument :: isExecute()
{
    isExecuted = true;
}
bool argument :: myExecute()
{
    return isExecuted;
}
void argument :: add_element(char * x)
{
    args[counter] = x;
    counter++;
}
void argument :: secondParse()
{
    char* token = strtok(myArg, " ");
    while(token != NULL){
        //cout << "#2 " << token << endl;
        add_element(token);
        // args[counter] = token;
        // counter++;
        // 
        token = strtok(NULL, " ");
    }
    token = '\0';
    add_element(token);
   // cout << args[0] << args[1] << "mewo" << endl;
}
char** argument :: myArgs()
{
    return args;
}
int argument :: myCounter()
{	
	return counter;
}
