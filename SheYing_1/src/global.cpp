#include "global.h"
#include <vector>
#include <string>
#include <queue>
using namespace std;

vector<cmd> assemble;
vector<indicate> indicator;
vector<string> binarycmd;
int startAddress = 128;
int memoryStartAddress;
int reg[32];
vector<int> mem;


//PC=1 means we are executing binarycmd[PC]
int PC;
int wInstrunction;
int eInstrunction;
vector<int> preIssueQueue;
vector<int> preALUQueue;
int postALUQueue;
int preMemQueue;
int postMemQueue;

int preIssueQueueEntry;
int preALUQueueEntry;

indicate registerBeingWritten;
bool programContinue;

int cycle;
