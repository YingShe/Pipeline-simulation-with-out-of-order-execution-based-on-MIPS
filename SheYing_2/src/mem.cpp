#include "mem.h"
#include <iostream>
using namespace std;

void MEM(vector<int> &a)
{
	if( preMemQueue != -1)
	{
		if(assemble[preMemQueue].kind == 5)
		{
			assemble[preMemQueue].result = mem[(assemble[preMemQueue].result-memoryStartAddress)/4];	
			postMemQueue = preMemQueue;
			preMemQueue = -1;
		}
		else
		{
			mem[(assemble[preMemQueue].result-memoryStartAddress)/4] = reg[assemble[preMemQueue].first];
			a.push_back(preMemQueue);
			preMemQueue = -1;
		}
	}
}
