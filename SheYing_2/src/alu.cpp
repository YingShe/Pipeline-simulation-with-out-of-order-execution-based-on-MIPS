#include "global.h"
#include "alu.h"
#include <iostream>
using namespace std;

void ALU()
{
	if(preALUQueue.size()>0)
	{
		if(preALUQueue.front() != -1)
		{
			switch(assemble[preALUQueue.front()].kind)
			{
			case 4:assemble[preALUQueue.front()].result = assemble[preALUQueue.front()].second+reg[assemble[preALUQueue.front()].third]; break;
			case 5:assemble[preALUQueue.front()].result = assemble[preALUQueue.front()].second+reg[assemble[preALUQueue.front()].third]; break;
			case 6:assemble[preALUQueue.front()].result = reg[assemble[preALUQueue.front()].second]+reg[assemble[preALUQueue.front()].third]; break;
			case 7:assemble[preALUQueue.front()].result = reg[assemble[preALUQueue.front()].second]-reg[assemble[preALUQueue.front()].third]; break;
			case 8:assemble[preALUQueue.front()].result = reg[assemble[preALUQueue.front()].second]*reg[assemble[preALUQueue.front()].third]; break;
			case 9:assemble[preALUQueue.front()].result = reg[assemble[preALUQueue.front()].second]&reg[assemble[preALUQueue.front()].third]; break;
			case 10:assemble[preALUQueue.front()].result = reg[assemble[preALUQueue.front()].second]|reg[assemble[preALUQueue.front()].third]; break;
			case 11:assemble[preALUQueue.front()].result = reg[assemble[preALUQueue.front()].second]^reg[assemble[preALUQueue.front()].third]; break;
			case 12:assemble[preALUQueue.front()].result =~(reg[assemble[preALUQueue.front()].second]|reg[assemble[preALUQueue.front()].third]); break;
			case 13:assemble[preALUQueue.front()].result = reg[assemble[preALUQueue.front()].second]+assemble[preALUQueue.front()].third; break;
			case 14:assemble[preALUQueue.front()].result = reg[assemble[preALUQueue.front()].second]&assemble[preALUQueue.front()].third; break;
			case 15:assemble[preALUQueue.front()].result = reg[assemble[preALUQueue.front()].second]|assemble[preALUQueue.front()].third; break;
			case 16:assemble[preALUQueue.front()].result = reg[assemble[preALUQueue.front()].second]^assemble[preALUQueue.front()].third; break;
			}

			if(assemble[preALUQueue.front()].kind <= 5)
			{
				preMemQueue = preALUQueue.front();
				preALUQueue.erase(preALUQueue.begin());
			}
			else
			{
				postALUQueue = preALUQueue.front();
				preALUQueue.erase(preALUQueue.begin());
			}
			
		}
	}
}
