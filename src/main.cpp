//#include "command.h"
#include "headers/rshell.h"
#include "headers/vectorContainer.h"
#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include "headers/connector.h"
#include "headers/argument.h"
using namespace std;


int main()
{
    string input;
    bool isQuit = false;
    do{
    //while(!isQuit){
    	cout << getenv("PWD") << " ";
        cout << "$ ";
        getline(cin, input);
        if(input == "exit"){
            isQuit = true;
        }
        else if(input.length() == 0){
        }
        else{
            vectorContainer* container = new vectorContainer(input);
            container -> parse();
            container -> execute();
            delete container;
        }
    } while(!isQuit);
}
