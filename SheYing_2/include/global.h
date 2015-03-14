#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include <vector>
#include <queue>
#include <string>

struct cmd{
	//the address of the cmd;
	int address;
	//indicate whether this is an instruction or data
	//0->instruction, 1->data
	//if is instruction, "first", "second" and "third" will be used to indicate the value of oprands
	//if is data, then "first" will be used to store the value
	bool instructionOrData;
	int kind;
	int first;
	int second;
	int third;
	int result;
	int selfReadReg[2];
	int selfWriteReg;
	cmd()
	{kind = first = second = third = selfReadReg[0] = selfReadReg[1] = selfWriteReg = -1;}
};

struct indicate{
	int preReadReg[32];
	int preWriteReg[32];
	indicate()
	{
		for(int i = 0; i < 32; i++)
			 preReadReg[i] = preWriteReg[i] = 0;
	}
};


extern std::vector<cmd> assemble;
extern std::vector<std::string> binarycmd;
extern std::vector<indicate> indicator;
extern int startAddress;
extern int memoryStartAddress;

//register and memory
extern int reg[32];
extern std::vector<int> mem;


extern int PC;
extern int wInstrunction;
extern int eInstrunction;
extern std::vector<int> preIssueQueue;
extern std::vector<int> preALUQueue;
extern int postALUQueue;
extern int preMemQueue;
extern int postMemQueue;

extern int preIssueQueueEntry;
extern int preALUQueueEntry;

extern indicate registerBeingWritten;
extern bool programContinue;

extern int cycle;

#endif
