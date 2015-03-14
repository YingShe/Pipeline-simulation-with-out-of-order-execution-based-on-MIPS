#include "issue.h"
#include "global.h"
#include <vector>
using namespace std;


void Issue()
{
	int firstIssuePC;
	if( preALUQueueEntry < 2)
	{
		int i = 0;
		int hasIssued = 0;
		int size = preIssueQueue.size();
		int temp = preALUQueueEntry;
		while(i < size && hasIssued < 2 && hasIssued < 2-preALUQueueEntry)
		{
			if( preIssueQueue[i] != -1)
			{
				bool canBeIssued = true;
				//RAW hazard
				if( assemble[preIssueQueue[i]].selfReadReg[0] != -1)
				{
					if(indicator[i].preWriteReg[assemble[preIssueQueue[i]].selfReadReg[0]] > 0)
						canBeIssued = false;
					if( canBeIssued == true && assemble[preIssueQueue[i]].selfReadReg[1] != -1)
					{
						if(indicator[i].preWriteReg[assemble[preIssueQueue[i]].selfReadReg[1]] > 0)
							canBeIssued = false;
					}
				}
				// WAW hazard
				if( canBeIssued == true && assemble[preIssueQueue[i]].selfWriteReg != -1)
				{
					if(indicator[i].preWriteReg[assemble[preIssueQueue[i]].selfWriteReg] > 0)
						canBeIssued = false;
				}

				//If two instructions are issused in a cycle, you need to make sure that there are no WAW or WAR hazards between them
				if( hasIssued == 1 && canBeIssued == true)
				{
					if(assemble[preIssueQueue[i]].selfWriteReg != -1)
					{
						if(assemble[preIssueQueue[i]].selfWriteReg == assemble[firstIssuePC].selfWriteReg || assemble[preIssueQueue[i]].selfWriteReg == assemble[firstIssuePC].selfReadReg[0] || assemble[preIssueQueue[i]].selfWriteReg == assemble[firstIssuePC].selfReadReg[1])
							canBeIssued = false;
					}

				}

				//WAR hazard with earlier not-issued instructions
				if( canBeIssued == true && assemble[preIssueQueue[i]].selfWriteReg != -1)
				{
					for( int j = i-1; j >=0; j--)
					{
						if(assemble[preIssueQueue[j]].selfReadReg[0] == assemble[preIssueQueue[i]].selfWriteReg || assemble[preIssueQueue[j]].selfReadReg[1] == assemble[preIssueQueue[i]].selfWriteReg)
							canBeIssued = false;
					}
				}

				//For Mem Instruction, all the source registers are ready at the end of last cycle
				if(canBeIssued == true && assemble[preIssueQueue[i]].kind == 4) //SW
				{
					if(indicator[i].preWriteReg[assemble[preIssueQueue[i]].selfReadReg[0]] > 0 || indicator[i].preWriteReg[assemble[preIssueQueue[i]].selfReadReg[1]] > 0)
						canBeIssued = false;
				}
				if(canBeIssued == true && assemble[preIssueQueue[i]].kind == 5) //LW
				{
					if(indicator[i].preWriteReg[assemble[preIssueQueue[i]].selfReadReg[0]] > 0)
						canBeIssued = false;
				}

				//The load instruction must wait until all the previous stores are issued
				if(canBeIssued == true && assemble[preIssueQueue[i]].kind == 5)
				{
					for( int j = i-1; j >=0; j--)
					{
						if(assemble[preIssueQueue[j]].kind == 4)
							canBeIssued = false;
					}
				}

				//The store must be issued in order
				if(canBeIssued == true && assemble[preIssueQueue[i]].kind == 4)
				{
					for( int j = i-1; j >=0; j--)
					{
						if(assemble[preIssueQueue[j]].kind == 4)
							canBeIssued = false;
					}
				}

				//NOW whether one instruction can be issued
				if( canBeIssued == true)
				{
					preALUQueue.push_back(preIssueQueue[i]);
					firstIssuePC = preIssueQueue[i];
					vector<int>::iterator ite = preIssueQueue.begin();
					for(int j = 0; j < i; ++j)
						ite++;
					preIssueQueue.erase(ite);

					vector<indicate>::iterator ite2= indicator.begin();
					for(int j = 0; j < i; j++)
						ite2++;
					indicator.erase(ite2);

					size --;
					i--;
					hasIssued++;
					temp++;
					preIssueQueueEntry--;
				}

			}
			else
				break;
			i++;
		}
		preALUQueueEntry = temp;
	}
}
