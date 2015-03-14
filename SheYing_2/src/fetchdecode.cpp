#include "fetchdecode.h"

void FetchDecode()
{
	if( wInstrunction != -1)
	{
		if( assemble[wInstrunction].kind == 1) //BEQ
		{
			if(registerBeingWritten.preWriteReg[assemble[wInstrunction].selfReadReg[0]] <= 0 && registerBeingWritten.preWriteReg[assemble[wInstrunction].selfReadReg[1]] <= 0)
			{
				eInstrunction =  wInstrunction;
				wInstrunction = -1;
			}
		}
		else if(assemble[PC].kind == 2) //BGTZ
		{
			if(registerBeingWritten.preWriteReg[assemble[wInstrunction].selfReadReg[0]] <= 0)
			{
				eInstrunction =  wInstrunction;
				wInstrunction = -1;
			}
		}
		return;
	}

	if( eInstrunction != -1)
	{
		if( assemble[eInstrunction].kind == 0) //J
		{
			PC = (assemble[eInstrunction].first-startAddress)/4;
			eInstrunction = -1;
		}
		else if(  assemble[eInstrunction].kind == 1) //BEQ
		{
			if(reg[assemble[eInstrunction].first] == reg[assemble[eInstrunction].second])
				PC= (assemble[eInstrunction].third+assemble[eInstrunction].address+4-startAddress)/4;
			else
				PC++;
			eInstrunction = -1;
		}
		else if(  assemble[eInstrunction].kind == 2) //BGTZ
		{
			if(reg[assemble[eInstrunction].first] > 0)
				PC= (assemble[eInstrunction].second+assemble[eInstrunction].address+4-startAddress)/4;
			else
				PC++;
			eInstrunction = -1;
		}
		else
		{
			programContinue = false;
		}
		
	}

	if (wInstrunction == -1 && eInstrunction == -1 && preIssueQueueEntry < 4)
	{
		if( assemble[PC].kind >= 4)
		{
			preIssueQueue.push_back(PC);
	
			int size = preIssueQueue.size();
			if( size == 1)
			{
				indicate tmp = registerBeingWritten;
				indicator.push_back(tmp);
			}
			else
			{
				indicate tmp = indicator[size-2];
				if(assemble[preIssueQueue[size-2]].selfReadReg[0] != -1)
				{
					tmp.preReadReg[assemble[preIssueQueue[size-2]].selfReadReg[0]]++;
					if(assemble[preIssueQueue[size-2]].selfReadReg[1] != -1)
						tmp.preReadReg[assemble[preIssueQueue[size-2]].selfReadReg[1]]++;
				}
				if(assemble[preIssueQueue[size-2]].selfWriteReg != -1)
				{
					tmp.preWriteReg[assemble[preIssueQueue[size-2]].selfWriteReg]++;
				}
				indicator.push_back(tmp);
			}

			if(assemble[PC].kind == 4)
			{
				registerBeingWritten.preReadReg[assemble[PC].first]++;
				registerBeingWritten.preReadReg[assemble[PC].third]++;
			}
			else if(assemble[PC].kind == 5)
			{
				registerBeingWritten.preReadReg[assemble[PC].third]++;
				registerBeingWritten.preWriteReg[assemble[PC].first]++;
			}
			else if(assemble[PC].kind > 5 && assemble[PC].kind < 13)
			{
				registerBeingWritten.preReadReg[assemble[PC].second]++;
				registerBeingWritten.preReadReg[assemble[PC].third]++;
				registerBeingWritten.preWriteReg[assemble[PC].first]++;
			}
			else if(assemble[PC].kind >= 13)
			{
				registerBeingWritten.preReadReg[assemble[PC].second]++;
				registerBeingWritten.preWriteReg[assemble[PC].first]++;
			}

			PC++;
			preIssueQueueEntry += 1;
		}
		else if( assemble[PC].kind == 0)//J
		{
			eInstrunction = PC;
		}
		else if( assemble[PC].kind == 1)//BEQ
		{
			if(registerBeingWritten.preWriteReg[assemble[PC].first] == 0 && registerBeingWritten.preWriteReg[assemble[PC].second] == 0)
				eInstrunction = PC;
			else
				wInstrunction = PC;
		}
		else if( assemble[PC].kind == 2)//BGTZ
		{
			if(registerBeingWritten.preWriteReg[assemble[PC].first] == 0)
				eInstrunction = PC;
			else
				wInstrunction = PC;
		}
		else //BREAK
		{
			eInstrunction = PC;
			programContinue = false;
		}
	}

	if( wInstrunction == -1 && eInstrunction == -1 && preIssueQueueEntry < 4 )
	{
		if( assemble[PC].kind >= 4)
		{
			preIssueQueue.push_back(PC);

			int size = preIssueQueue.size();
			if( size == 1)
			{
				indicate tmp = registerBeingWritten;
				indicator.push_back(tmp);
			}
			else
			{
				indicate tmp = indicator[size-2];
				if(assemble[preIssueQueue[size-2]].selfReadReg[0] != -1)
				{
					tmp.preReadReg[assemble[preIssueQueue[size-2]].selfReadReg[0]]++;
					if(assemble[preIssueQueue[size-2]].selfReadReg[1] != -1)
						tmp.preReadReg[assemble[preIssueQueue[size-2]].selfReadReg[1]]++;
				}
				if(assemble[preIssueQueue[size-2]].selfWriteReg != -1)
				{
					tmp.preWriteReg[assemble[preIssueQueue[size-2]].selfWriteReg]++;
				}
				indicator.push_back(tmp);
			}

			if(assemble[PC].kind == 4)
			{
				registerBeingWritten.preReadReg[assemble[PC].first]++;
				registerBeingWritten.preReadReg[assemble[PC].third]++;
			}
			else if(assemble[PC].kind == 5)
			{
				registerBeingWritten.preReadReg[assemble[PC].third]++;
				registerBeingWritten.preWriteReg[assemble[PC].first]++;
			}
			else if(assemble[PC].kind > 5 && assemble[PC].kind < 13)
			{
				registerBeingWritten.preReadReg[assemble[PC].second]++;
				registerBeingWritten.preReadReg[assemble[PC].third]++;
				registerBeingWritten.preWriteReg[assemble[PC].first]++;
			}
			else if(assemble[PC].kind >= 13)
			{
				registerBeingWritten.preReadReg[assemble[PC].second]++;
				registerBeingWritten.preWriteReg[assemble[PC].first]++;
			}
		
			PC++;
			preIssueQueueEntry += 1;
		}
		else if( assemble[PC].kind == 0)//J
		{
			eInstrunction = PC;
		}
		else if( assemble[PC].kind == 1)//BEQ
		{
			if(registerBeingWritten.preWriteReg[assemble[PC].first] == 0 && registerBeingWritten.preWriteReg[assemble[PC].second] == 0)
				eInstrunction = PC;
			else
				wInstrunction = PC;
		}
		else if( assemble[PC].kind == 2)//BGTZ
		{
			if(registerBeingWritten.preWriteReg[assemble[PC].first] == 0)
				eInstrunction = PC;
			else
				wInstrunction = PC;
		}
		else //BREAK
		{
			eInstrunction = PC;
			programContinue = false;
		}
	}
}
