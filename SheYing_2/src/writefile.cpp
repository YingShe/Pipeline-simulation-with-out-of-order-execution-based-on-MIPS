#include "writefile.h"
#include "global.h"

void WriteFile()
{
	if (cycle == 0)
		return;
	FILE *fp = fopen("simulation.txt", "a");
	fprintf(fp, "--------------------\n");
	fprintf(fp, "Cycle:%d\n\n",cycle);
	fprintf(fp, "IF Unit:\n");
	fprintf(fp, "\tWaiting Instruction:");
	if( wInstrunction != -1)
	{
		switch(assemble[wInstrunction].kind)
		{
		case 0:fprintf(fp, "[J #%d]\n", assemble[wInstrunction].first); break;
		case 1:fprintf(fp, "[BEQ R%d, R%d, #%d]\n", assemble[wInstrunction].first,assemble[wInstrunction].second,assemble[wInstrunction].third); break;
		case 2:fprintf(fp, "[BGTZ R%d, #%d]\n", assemble[wInstrunction].first,assemble[wInstrunction].second); break;
		}
	}
	else
		fprintf(fp,"\n");

	fprintf(fp, "\tExecuted Instruction:");
	if( eInstrunction != -1)
	{
		switch(assemble[eInstrunction].kind)
		{
		case 0:fprintf(fp, "[J #%d]\n", assemble[eInstrunction].first); break;
		case 1:fprintf(fp, "[BEQ R%d, R%d, #%d]\n", assemble[eInstrunction].first,assemble[eInstrunction].second,assemble[eInstrunction].third); break;
		case 2:fprintf(fp, "[BGTZ R%d, #%d]\n", assemble[eInstrunction].first,assemble[eInstrunction].second); break;
		case 3:fprintf(fp, "[BREAK]\n"); break;
		}
	}
	else
		fprintf(fp,"\n");

	fprintf(fp, "Pre-Issue Queue:\n");
	int i = 0;
	int size = preIssueQueue.size();
	while( i < size)
	{
		fprintf(fp, "\tEntry %d:", i);
		if( preIssueQueue[i] != -1)
		{
			switch(assemble[preIssueQueue[i]].kind)
			{
			case 4: fprintf(fp, "[SW R%d, %d(R%d)]\n", assemble[preIssueQueue[i]].first, assemble[preIssueQueue[i]].second, assemble[preIssueQueue[i]].third); break;
			case 5: fprintf(fp, "[LW R%d, %d(R%d)]\n", assemble[preIssueQueue[i]].first, assemble[preIssueQueue[i]].second, assemble[preIssueQueue[i]].third); break;
			case 6: fprintf(fp, "[ADD R%d, R%d, R%d]\n", assemble[preIssueQueue[i]].first, assemble[preIssueQueue[i]].second, assemble[preIssueQueue[i]].third); break;
			case 7: fprintf(fp, "[SUB R%d, R%d, R%d]\n", assemble[preIssueQueue[i]].first, assemble[preIssueQueue[i]].second, assemble[preIssueQueue[i]].third); break;
			case 8: fprintf(fp, "[MUL R%d, R%d, R%d]\n", assemble[preIssueQueue[i]].first, assemble[preIssueQueue[i]].second, assemble[preIssueQueue[i]].third); break;
			case 9: fprintf(fp, "[AND R%d, R%d, R%d]\n", assemble[preIssueQueue[i]].first, assemble[preIssueQueue[i]].second, assemble[preIssueQueue[i]].third); break;
			case 10: fprintf(fp, "[OR R%d, R%d, R%d]\n", assemble[preIssueQueue[i]].first, assemble[preIssueQueue[i]].second, assemble[preIssueQueue[i]].third); break;
			case 11: fprintf(fp, "[XOR R%d, R%d, R%d]\n", assemble[preIssueQueue[i]].first, assemble[preIssueQueue[i]].second, assemble[preIssueQueue[i]].third); break;
			case 12: fprintf(fp, "[NOR R%d, R%d, R%d]\n", assemble[preIssueQueue[i]].first, assemble[preIssueQueue[i]].second, assemble[preIssueQueue[i]].third); break;
			case 13: fprintf(fp, "[ADDI R%d, R%d, #%d]\n", assemble[preIssueQueue[i]].first, assemble[preIssueQueue[i]].second, assemble[preIssueQueue[i]].third); break;
			case 14: fprintf(fp, "[ANDI R%d, R%d, #%d]\n", assemble[preIssueQueue[i]].first, assemble[preIssueQueue[i]].second, assemble[preIssueQueue[i]].third); break;
			case 15: fprintf(fp, "[ORI R%d, R%d, #%d]\n", assemble[preIssueQueue[i]].first, assemble[preIssueQueue[i]].second, assemble[preIssueQueue[i]].third); break;
			case 16: fprintf(fp, "[XORI R%d, R%d, #%d]\n", assemble[preIssueQueue[i]].first, assemble[preIssueQueue[i]].second, assemble[preIssueQueue[i]].third); break;
			}
			/*
			for(int k = 0; k < 32; ++k)
				fprintf(fp, "%d ", indicator[i].preReadReg[k]);
			fprintf(fp, "\n");
			for(int k = 0; k < 32;++k)
				fprintf(fp, "%d ", indicator[i].preWriteReg[k]);
			fprintf(fp, "\n");
			fprintf(fp, "selfreadreg: %d, %d\n", assemble[preIssueQueue[i]].selfReadReg[0],assemble[preIssueQueue[i]].selfReadReg[1]);
			fprintf(fp, "selfwritereg: %d\n", assemble[preIssueQueue[i]].selfWriteReg);
			*/
		}
		else
			fprintf(fp,"\n");
		i++;
	}
	
	while(i<4)
	{
		fprintf(fp, "\tEntry %d:\n", i);
		i++;
	}





	fprintf(fp, "Pre-ALU Queue:\n");
	i = 0;
	size = preALUQueue.size();
	while( i < size)
	{
		fprintf(fp, "\tEntry %d:", i);
		if( preALUQueue[i] != -1)
		{
			switch(assemble[preALUQueue[i]].kind)
			{
			case 4: fprintf(fp, "[SW R%d, %d(R%d)]\n", assemble[preALUQueue[i]].first, assemble[preALUQueue[i]].second, assemble[preALUQueue[i]].third); break;
			case 5: fprintf(fp, "[LW R%d, %d(R%d)]\n", assemble[preALUQueue[i]].first, assemble[preALUQueue[i]].second, assemble[preALUQueue[i]].third); break;
			case 6: fprintf(fp, "[ADD R%d, R%d, R%d]\n", assemble[preALUQueue[i]].first, assemble[preALUQueue[i]].second, assemble[preALUQueue[i]].third); break;
			case 7: fprintf(fp, "[SUB R%d, R%d, R%d]\n", assemble[preALUQueue[i]].first, assemble[preALUQueue[i]].second, assemble[preALUQueue[i]].third); break;
			case 8: fprintf(fp, "[MUL R%d, R%d, R%d]\n", assemble[preALUQueue[i]].first, assemble[preALUQueue[i]].second, assemble[preALUQueue[i]].third); break;
			case 9: fprintf(fp, "[AND R%d, R%d, R%d]\n", assemble[preALUQueue[i]].first, assemble[preALUQueue[i]].second, assemble[preALUQueue[i]].third); break;
			case 10: fprintf(fp, "[OR R%d, R%d, R%d]\n", assemble[preALUQueue[i]].first, assemble[preALUQueue[i]].second, assemble[preALUQueue[i]].third); break;
			case 11: fprintf(fp, "[XOR R%d, R%d, R%d]\n", assemble[preALUQueue[i]].first, assemble[preALUQueue[i]].second, assemble[preALUQueue[i]].third); break;
			case 12: fprintf(fp, "[NOR R%d, R%d, R%d]\n", assemble[preALUQueue[i]].first, assemble[preALUQueue[i]].second, assemble[preALUQueue[i]].third); break;
			case 13: fprintf(fp, "[ADDI R%d, R%d, #%d]\n", assemble[preALUQueue[i]].first, assemble[preALUQueue[i]].second, assemble[preALUQueue[i]].third); break;
			case 14: fprintf(fp, "[ANDI R%d, R%d, #%d]\n", assemble[preALUQueue[i]].first, assemble[preALUQueue[i]].second, assemble[preALUQueue[i]].third); break;
			case 15: fprintf(fp, "[ORI R%d, R%d, #%d]\n", assemble[preALUQueue[i]].first, assemble[preALUQueue[i]].second, assemble[preALUQueue[i]].third); break;
			case 16: fprintf(fp, "[XORI R%d, R%d, #%d]\n", assemble[preALUQueue[i]].first, assemble[preALUQueue[i]].second, assemble[preALUQueue[i]].third); break;
			}
		}
		else
			fprintf(fp,"\n");
		i++;
	}

	while(i<2)
	{
		fprintf(fp, "\tEntry %d:\n", i);
		i++;
	}


	fprintf(fp, "Pre-MEM Queue:");
	if (preMemQueue != -1)
	{
		switch(assemble[preMemQueue].kind)
		{
			case 4: fprintf(fp, "[SW R%d, %d(R%d)]\n", assemble[preMemQueue].first, assemble[preMemQueue].second, assemble[preMemQueue].third); break;
			case 5: fprintf(fp, "[LW R%d, %d(R%d)]\n", assemble[preMemQueue].first,assemble[preMemQueue].second, assemble[preMemQueue].third); break;
		}
	}
	else
		fprintf(fp,"\n");

	fprintf(fp, "Post-MEM Queue:");
	if (postMemQueue != -1)
	{
		switch(assemble[postMemQueue].kind)
		{
			case 4: fprintf(fp, "[SW R%d, %d(R%d)]\n", assemble[postMemQueue].first, assemble[postMemQueue].second, assemble[postMemQueue].third); break;
			case 5: fprintf(fp, "[LW R%d, %d(R%d)]\n", assemble[postMemQueue].first,assemble[postMemQueue].second, assemble[postMemQueue].third); break;
		}
	}
	else
		fprintf(fp,"\n");

	fprintf(fp, "Post-ALU Queue:");
	if (postALUQueue != -1)
	{
		switch(assemble[postALUQueue].kind)
		{
			case 6: fprintf(fp, "[ADD R%d, R%d, R%d]\n", assemble[postALUQueue].first, assemble[postALUQueue].second, assemble[postALUQueue].third); break;
			case 7: fprintf(fp, "[SUB R%d, R%d, R%d]\n", assemble[postALUQueue].first, assemble[postALUQueue].second, assemble[postALUQueue].third); break;
			case 8: fprintf(fp, "[MUL R%d, R%d, R%d]\n", assemble[postALUQueue].first, assemble[postALUQueue].second, assemble[postALUQueue].third); break;
			case 9: fprintf(fp, "[AND R%d, R%d, R%d]\n", assemble[postALUQueue].first, assemble[postALUQueue].second, assemble[postALUQueue].third); break;
			case 10: fprintf(fp, "[OR R%d, R%d, R%d]\n", assemble[postALUQueue].first, assemble[postALUQueue].second, assemble[postALUQueue].third); break;
			case 11: fprintf(fp, "[XOR R%d, R%d, R%d]\n", assemble[postALUQueue].first, assemble[postALUQueue].second, assemble[postALUQueue].third); break;
			case 12: fprintf(fp, "[NOR R%d, R%d, R%d]\n", assemble[postALUQueue].first, assemble[postALUQueue].second, assemble[postALUQueue].third); break;
			case 13: fprintf(fp, "[ADDI R%d, R%d, #%d]\n", assemble[postALUQueue].first, assemble[postALUQueue].second, assemble[postALUQueue].third); break;
			case 14: fprintf(fp, "[ANDI R%d, R%d, #%d]\n", assemble[postALUQueue].first, assemble[postALUQueue].second, assemble[postALUQueue].third); break;
			case 15: fprintf(fp, "[ORI R%d, R%d, #%d]\n", assemble[postALUQueue].first, assemble[postALUQueue].second, assemble[postALUQueue].third); break;
			case 16: fprintf(fp, "[XORI R%d, R%d, #%d]\n", assemble[postALUQueue].first, assemble[postALUQueue].second, assemble[postALUQueue].third); break;
		}
	}
	else
		fprintf(fp,"\n");

	fprintf(fp,"\n");
	fprintf(fp,"Registers\n");
	fprintf(fp,"R00:\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",reg[0],reg[1],reg[2],reg[3],reg[4],reg[5],reg[6],reg[7]);
	fprintf(fp,"R08:\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",reg[8],reg[9],reg[10],reg[11],reg[12],reg[13],reg[14],reg[15]);
	fprintf(fp,"R16:\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",reg[16],reg[17],reg[18],reg[19],reg[20],reg[21],reg[22],reg[23]);
	fprintf(fp,"R24:\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",reg[24],reg[25],reg[26],reg[27],reg[28],reg[29],reg[30],reg[31]);
	fprintf(fp, "\n");
	fprintf(fp,"Data");
	int temp = memoryStartAddress;
    for(int m = 0; m < mem.size(); m++)
    {
        if(m%8==0)
        {
            fprintf(fp,"\n");
            fprintf(fp,"%d:",temp);
            fprintf(fp,"\t%d",mem[m]);
            temp=temp+4;
        }
        else
        {
            fprintf(fp,"\t%d",mem[m]);
            temp=temp+4;
        }
    }
	fprintf(fp, "\n");
	fclose(fp);
}
