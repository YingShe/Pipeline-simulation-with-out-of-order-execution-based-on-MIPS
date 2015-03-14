#include "init.h"
#include "global.h"
#include "disassemble.h"
#include <string.h>

void Init(char *filepath)
{
	memset(reg, 0, sizeof(reg));
	PC = 0;
	wInstrunction = -1;
	eInstrunction = -1;

	postALUQueue = -1;
	preMemQueue = -1;
	postMemQueue = -1;
	preIssueQueueEntry = 0;
	preALUQueueEntry = 0;

	
	programContinue = true;
	cycle = 0;
	Disassemble(filepath);
}
