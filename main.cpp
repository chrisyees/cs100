//#include "command.h"
#include "rshell.h"
#include "vectorContainer.h"
#include <iostream>
using namespace std;

int main()
{
    string input;
    bool isQuit = false;
    do{
    //while(!isQuit){
        cout << "$ ";
        getline(cin, input);
        if(input == "quit"){
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