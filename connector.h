#ifndef __CONNECTOR_H_
#define __CONNECTOR_H_
#include "rshell.h"
#include <string>

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
private:
	string myCon;
	bool isExecuted;
	int index;
};
#endif


