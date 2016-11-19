#include "headers/connector.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
connector :: connector (string x)
{
	myCon = x;
	isExecuted = false;
	index = 0;
}
string connector :: myName()
{
    return myCon;
}
void connector :: print()
{
    cout << myName() << endl;
}
void connector :: isExecute()
{
    isExecuted = true;
}
bool connector :: myExecute()
{
    return isExecuted;
}
void connector :: setIndex(int x){
    index = x;
}
int connector :: myIndex(){
    return index;
}
