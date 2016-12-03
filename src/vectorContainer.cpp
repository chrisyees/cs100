#include "headers/vectorContainer.h"
#include <string.h>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <typeinfo>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "headers/argument.h"
#include <iostream>
#include "headers/connector.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <unistd.h>

using namespace std;

        
void vectorContainer :: print()
{
    for(unsigned i = 0; i < argumentList.size(); i++)
    {
        cout << argumentList.at(i) -> myName() << " "; //prints out the list of commands/arguments
    }
     for(unsigned i = 0; i < connectorList.size(); i++)
    {
        cout << connectorList.at(i) -> myName() << " "; //prints out the list of commands/arguments followed by connectors
    }
    cout << endl;
} 
       
        
int vectorContainer :: size()
{
    return argumentList.size() + connectorList.size(); //returns size of both containers
} 
        
        
void vectorContainer :: parse()
{
    if (input == "")
        return;
//	if(input.begin() == '(' && input.end() == ')'){
//		input = input.substr(input.begin() + 1, input.end() - 1);
//		}
    int count = 0;
    while(input[count] == ' '){
        count++;
    }
    input = input.substr(count);
    if(input[0] == '#'){
        connectorList.push_back(new connector("#"));
        return;
    }
	int parenCounter = 0;
    for (unsigned i = 0; i < input.size(); i++ ) 
    {
        if (input[i] == ';'){
            connectorList.push_back(new connector(";"));
        }
        else if (input[i] == '#'){
            connectorList.push_back(new connector("#"));
        }
        else if (input[i] == '&' && input[i+1] == '&')
        {
            connectorList.push_back(new connector("&&"));
            i++;
        }
        else if (input[i] == '|' && input[i+1] == '|')
        {
            connectorList.push_back(new connector("||"));
            i++;
        }
	else if (input[i] == '(')
	{
		connectorList.push_back(new connector("("));
		parenCounter++;
	}
	else if (input[i] == ')')
	{
		connectorList.push_back(new connector(")"));
		parenCounter--;
	}
	else if (input[i] == '[')
	{
		for (unsigned j = i; j < input.size(); j++)
		{
			if(input[j] == ']')
			{
					input.replace(j,1,"");
					input.replace(i,1," test ");
					break;
			}
		}
		if(input[i] == '[')
		{
			cout << "Incomplete command" << endl;
			return;
		}
	}
    }
	if(parenCounter != 0 ){
		cout << "parenthesis error" << endl;
		return;
	}
    
    char* cstrInput = (char*)input.c_str(); //convert input into a cstring
    
    char* token = strtok(cstrInput, ";|&()#");
    
    while(token != NULL){
        //cout << token << endl;
        argumentList.push_back(new argument(token)); //separates just by connectors
        token = strtok(NULL, ";|&()#");
    }
    
    for(unsigned i = 0; i < argumentList.size(); i++){
        argumentList.at(i) -> secondParse();//second parse splits up each command and arguemnt group by spaces
    }
}
        
rshell* vectorContainer :: argAt(int i)
{
    return argumentList.at(i); //returns command/argument at a location
} 

rshell* vectorContainer :: conAt(int i)
{
    return connectorList.at(i); //returns connector at a location
} 
        
void vectorContainer :: execute()
{
    if(argumentList.size() == 0 && connectorList.at(0) ->myName() == "#"){
        return;
    }
    else if(argumentList.size() - 1 != connectorList.size() ){
        cout << "Command input is incorrect." << endl;
        return;
    }
    int conCounter = 0; //counter for connector vector
    bool isGood = true; //checks if connector allows a command to happen
    for(unsigned i = 0; i < argumentList.size(); i++)
    {
        if(i != 0)
        { //makes sure it's not the first command
            if(connectorList.at(conCounter) -> myName() == "#")
            {
                return;
            }
            else if(connectorList.at(conCounter) -> myName() == "||") // || connector
            {
                if((argumentList.at(i - 1) -> myExecute())){
                    isGood = false;
                }
            }
            else if(connectorList.at(conCounter) -> myName() == "&&") // && connector
            {
                if(!(argumentList.at(i - 1) -> myExecute())){
                    isGood = false;
                }
            }
            else if(connectorList.at(conCounter) -> myName() == ";") // ; connector
            {
                    isGood = true;
            }
            conCounter++;
        }
        if(isGood){	
	if(strcmp(argumentList.at(i) -> myArgs()[0], "cd") == 0){
			//cout << getenv("PWD") << " ";
			//cout << getenv("OLDPWD") << " ";
			//cout << getenv("HOME") << endl;
			//cout << argumentList.at(i) -> myCounter() << endl;
			if(argumentList.at(i) -> myCounter() == 2){ //just cd
				
				if(setenv("OLDPWD", getenv("PWD"),1) == -1){
					perror("OLDPWD error");
					return;
				}
				
				if(chdir(getenv("HOME")) == -1){
					perror("chdir error");
					return;
				}
				
				if(setenv("PWD", getenv("HOME"), 1) == -1){
					perror("setenv error");
					return;
				}
			argumentList.at(i) -> isExecute();
			return;	
			}
			else if(argumentList.at(i) -> myCounter() == 3){ //cd and something else
 				if(strcmp(argumentList.at(i) -> myArgs()[1], "-") == 0){
					char* tempEnv = getenv("PWD");
					if(setenv("PWD", getenv("OLDPWD"),1) == -1){
						perror("PWD error");
						return;
					}
					if(chdir(getenv("OLDPWD")) == -1){
						cout << "hi" << endl;
						perror("chdir error");
						return;
					}
					if(setenv("OLDPWD",tempEnv,1) == -1){
						perror("setenv error");
						return;
					}
				}
				else{
					if(setenv("OLDPWD", getenv("PWD"),1) == -1){
						perror("setenv error");
						return;
					}
					if(chdir(argumentList.at(i) -> myArgs()[1]) == -1 || strcmp(argumentList.at(i) -> myArgs()[1],".") == 0 || strcmp(argumentList.at(i) -> myArgs()[1], "..") == 0){
						perror("chdir error");
						return;
					}
					char buffer[257];
					if(setenv("PWD", getcwd(buffer,256),1) == -1){
						perror("setenv error");
						return;
					}
				}
			argumentList.at(i) -> isExecute();
			return;
			}
			else{
				cout << "Too many arguments" << endl;
				return;
			}
		return;
		}	  
		  pid_t pid = fork();

            if (pid == -1) //forking has an issue
            {
                cout << "Forking error" << endl;
            } 
            else if (pid > 0)
            {
                if(wait(0) == -1){
                    perror("waiting");
                } //waiting for child
                argumentList.at(i) -> isExecute(); //successful command, change isExectued boolean value of initial command
            }
            else 
            {
		if(strcmp(argumentList.at(i) -> myArgs()[0], "test")== 0){
			struct stat s;
			if(strcmp(argumentList.at(i) -> myArgs()[1], "-e") == 0){
				if(stat(argumentList.at(i) -> myArgs()[2],&s) == 0){
					cout << "(True)" <<endl;
					argumentList.at(i) -> isExecute();
				}
				else
				{
					cout << "(False)" << endl;
				}
				_exit(0);
			}
			else if(strcmp(argumentList.at(i) -> myArgs()[1], "-f") == 0)
			{
				if(stat(argumentList.at(i) -> myArgs()[2],&s)==0 && S_ISREG(s.st_mode) != 0){
					cout << "(True)" << endl;
					argumentList.at(i) -> isExecute();
				}
				else
				{
					cout << "(False)" << endl;
				}
				_exit(0);
			}
			else if(strcmp(argumentList.at(i) -> myArgs()[1], "-d") == 0)
			{
				if(stat(argumentList.at(i) -> myArgs()[2],&s)==0 && S_ISDIR(s.st_mode) != 0){
                                        cout << "(True)" << endl;
                                        argumentList.at(i) -> isExecute();
                                }
                                else
                                {
                                        cout << "(False)" << endl;
                                }
                                _exit(0);

			}
			else{
				if(stat(argumentList.at(i) -> myArgs()[1],&s) == 0){
                                        cout << "(True)" <<endl;
                                        argumentList.at(i) -> isExecute();
                                }
                                else
                                {
                                        cout << "(False)" << endl;
                                }
                                _exit(0);

			}
		}
		else if(execvp((argumentList.at(i) -> myArgs())[0],argumentList.at(i) -> myArgs()) == -1)
                {
                	perror("command execution failed"); //error with command
                        _exit(0);
                }
              
            }
        }
    }
}
