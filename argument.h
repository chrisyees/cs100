#ifndef _ARGUMENT_H_
#define _ARGUMENT_H_
#include "rshell.h"
#include <string>

class argument : public rshell
{
public: 
	argument (char* x);
	virtual void isExecute(); 
	virtual void print();  
	virtual bool myExecute(); 
	virtual string myName();
	void add_element(char* x);
	void secondParse();
	virtual char** myArgs();
private:
	char* myArg;
	bool isExecuted;
	char* args[256]; 
	int counter;
};
#endif
