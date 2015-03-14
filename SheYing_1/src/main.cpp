#include <iostream>
#include <vector>
#include <stdio.h>
#include "global.h"
#include "disassemble.h"
#include "writedisassemble.h"
#include "init.h"
using namespace std;

void Usage()
{
	cout << "========================================\n";
	cout << "Please input command in console like:\n";
	cout << "\tMIPSsim inputfilename.txt\n";
	cout << "========================================\n";
	return;
}

int main(int args, char *argv[])
{
	if(args != 2)
	{
		Usage();
		return 0;
	}
	Init(argv[1]);
	WriteDisassemble();
	return 0;
}
