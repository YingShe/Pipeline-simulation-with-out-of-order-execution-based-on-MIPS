#include <iostream>
#include <vector>
#include <stdio.h>
#include "global.h"
#include "disassemble.h"
#include "writedisassemble.h"
#include "init.h"
#include "writefile.h"
#include "issue.h"
#include "mem.h"
#include "alu.h"
#include "writeback.h"
#include "restore.h"
#include "fetchdecode.h"
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
	vector<int> a;
	while(true)
	//while( cycle < 42)
	{
		WriteFile();
		if(programContinue == false)
			break;
		cycle++;
		Restore(a);
		WriteBack(a);
		MEM(a);
		preALUQueueEntry = preALUQueue.size();
		ALU();
		Issue();
		FetchDecode();
	}

	return 0;
}
