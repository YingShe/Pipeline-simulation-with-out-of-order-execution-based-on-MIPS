#include "writeback.h"
#include <iostream>
using namespace std;

void WriteBack(vector<int> &a)
{
	a.clear();
	if(postMemQueue != -1)//LW
	{
		reg[assemble[postMemQueue].first] = assemble[postMemQueue].result;
		a.push_back(postMemQueue);
		postMemQueue = -1;
	}
	if(postALUQueue != -1)
	{
		reg[assemble[postALUQueue].first] = assemble[postALUQueue].result;
		a.push_back(postALUQueue);
		postALUQueue = -1;
	}
}
