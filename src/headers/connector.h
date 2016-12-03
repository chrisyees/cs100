#ifndef __CONNECTOR_H_
#define __CONNECTOR_H_
#include "rshell.h"
#include <string>
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
class connector : public rshell
{
public: 
	connector (string x);
	virtual void isExecute();
	virtual void print();
	virtual string myName();
	virtual bool myExecute();
	virtual void secondParse(){};
	void setIndex(int x);
	int myIndex();
	virtual char** myArgs(){return NULL;};
	virtual int myCounter(){return 0;};
private:
	string myCon;
	bool isExecuted;
	int index;
};
#endif


