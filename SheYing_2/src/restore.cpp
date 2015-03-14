#include "restore.h"
#include <iostream>
using namespace std;

void Restore(vector<int> a)
{
	if(a.size() > 0)
	{
		int size = a.size();
		int i = 0;
		while( i < size)
		{
			if(assemble[a[i]].kind == 4)
			{
				registerBeingWritten.preReadReg[assemble[a[i]].first]--;
				registerBeingWritten.preReadReg[assemble[a[i]].third]--;
				for(int k = 0; k < preIssueQueue.size(); k ++)
				{
					indicator[k].preReadReg[assemble[a[i]].first]--;
					indicator[k].preReadReg[assemble[a[i]].third]--;
				}
			}
			else if(assemble[a[i]].kind == 5)
			{
				registerBeingWritten.preReadReg[assemble[a[i]].third]--;
				registerBeingWritten.preWriteReg[assemble[a[i]].first]--;
				for(int k = 0; k < preIssueQueue.size(); k++)
				{
					indicator[k].preReadReg[assemble[a[i]].third]--;
					indicator[k].preWriteReg[assemble[a[i]].first]--;
				}
			}
			else if(assemble[a[i]].kind >= 6 && assemble[a[i]].kind < 13)
			{
				registerBeingWritten.preReadReg[assemble[a[i]].second]--;
				registerBeingWritten.preReadReg[assemble[a[i]].third]--;
				registerBeingWritten.preWriteReg[assemble[a[i]].first]--;
				for(int k = 0; k < preIssueQueue.size(); k++)
				{
					indicator[k].preReadReg[assemble[a[i]].second]--;
					indicator[k].preReadReg[assemble[a[i]].third]--;
					indicator[k].preWriteReg[assemble[a[i]].first]--;
				}
			}
			else if(assemble[a[i]].kind >= 13)
			{
				registerBeingWritten.preReadReg[assemble[a[i]].second]--;
				registerBeingWritten.preWriteReg[assemble[a[i]].first]--;
				for(int k = 0; k < preIssueQueue.size(); k++)
				{
					indicator[k].preReadReg[assemble[a[i]].second]--;
					indicator[k].preWriteReg[assemble[a[i]].first]--;
				}
			}
			i++;
		}
	}
}
