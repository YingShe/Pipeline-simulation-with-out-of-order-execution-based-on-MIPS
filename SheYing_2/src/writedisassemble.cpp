#include "writedisassemble.h"
#include <stdio.h>

void WriteDisassemble()
{
	FILE *fp = fopen("disassembly.txt", "w");
	int size = binarycmd.size();
	int i = 0;
	while(i < size)
	{
		fprintf(fp, "%s\t%d\t", binarycmd[i].c_str(), assemble[i].address);
		if(assemble[i].instructionOrData == 0)
		{
			switch(assemble[i].kind)
			{
			case 0: fprintf(fp, "J #%d\n", assemble[i].first); break;
			case 1: fprintf(fp, "BEQ R%d, R%d, #%d\n", assemble[i].first, assemble[i].second, assemble[i].third); break;
			case 2: fprintf(fp, "BGTZ R%d, #%d\n", assemble[i].first, assemble[i].second); break;
			case 3: fprintf(fp, "BREAK\n"); break;
			case 4: fprintf(fp, "SW R%d, %d(R%d)\n", assemble[i].first, assemble[i].second, assemble[i].third); break;
			case 5: fprintf(fp, "LW R%d, %d(R%d)\n", assemble[i].first, assemble[i].second, assemble[i].third); break;
			case 6: fprintf(fp, "ADD R%d, R%d, R%d\n", assemble[i].first, assemble[i].second, assemble[i].third); break;
			case 7: fprintf(fp, "SUB R%d, R%d, R%d\n", assemble[i].first, assemble[i].second, assemble[i].third); break;
			case 8: fprintf(fp, "MUL R%d, R%d, R%d\n", assemble[i].first, assemble[i].second, assemble[i].third); break;
			case 9: fprintf(fp, "AND R%d, R%d, R%d\n", assemble[i].first, assemble[i].second, assemble[i].third); break;
			case 10: fprintf(fp, "OR R%d, R%d, R%d\n", assemble[i].first, assemble[i].second, assemble[i].third); break;
			case 11: fprintf(fp, "XOR R%d, R%d, R%d\n", assemble[i].first, assemble[i].second, assemble[i].third); break;
			case 12: fprintf(fp, "NOR R%d, R%d, R%d\n", assemble[i].first, assemble[i].second, assemble[i].third); break;
			case 13: fprintf(fp, "ADDI R%d, R%d, #%d\n", assemble[i].first, assemble[i].second, assemble[i].third); break;
			case 14: fprintf(fp, "ANDI R%d, R%d, #%d\n", assemble[i].first, assemble[i].second, assemble[i].third); break;
			case 15: fprintf(fp, "ORI R%d, R%d, #%d\n", assemble[i].first, assemble[i].second, assemble[i].third); break;
			case 16: fprintf(fp, "XORI R%d, R%d, #%d\n", assemble[i].first, assemble[i].second, assemble[i].third); break;
			}
		}
		else
		{
			fprintf(fp, "%d\n", assemble[i].first);
		}
		i++;
	}
	fclose(fp);
	return;
}