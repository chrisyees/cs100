#ifndef __RSHELL_H_
#define __RSHELL_H_
#include <string>
#include <iostream>
using namespace std;

class rshell{

    public:
        rshell() {};
        virtual void print() = 0;//used for testing, implmeneted in child classes
        virtual void isExecute() = 0;
        virtual bool myExecute() = 0;
        virtual string myName() = 0;
        virtual void secondParse() = 0;
        virtual char** myArgs() = 0;
        
};
#endif