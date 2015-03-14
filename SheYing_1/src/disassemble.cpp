#include "disassemble.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
using namespace std;

void Disassemble(char *filepath)
{
	FILE *fp = fopen(filepath, "r");
	
	char binary[33];
	int i = 0;
	//at beginning, the cmd is instruction, so we initialize it to be 0
	int instructionOrData = 0;
	while(fscanf(fp, "%s", binary) != -1)
	{
		string tmp(binary);
		binarycmd.push_back(tmp);
		cmd tmp2;
		DisassembleOne(binary, instructionOrData, tmp2, startAddress+i);
		assemble.push_back(tmp2);
		i += 4;
	}
	fclose(fp);
}

//this function disassemble one binary string which stores in binary,
//when binary is "BREAK", then, function will set instructionOrCode to 1, 
//the same time it will set the value of "memoryStartAddress".
//tmp2 will store the information disassemble from binary.
//the "address" will told us which address does this binary belong to
void DisassembleOne(char binary[], int &instructionOrData, cmd &tmp2, int address)
{
	//int first, second, third;s
	if(instructionOrData == 0)
   	 {
        	int fthree=((binary[0]-'0')<<2)+((binary[1]-'0')<<1)+(binary[2]-'0');
        switch(fthree)
		{
			case(0)://category-1
            {
                int mthree=((binary[3]-'0')<<2)+((binary[4]-'0')<<1)+(binary[5]-'0');
                switch(mthree)
				{
                    case(0)://J
                    {
						int first = 0;
						for(int i = 6; i <32; i++)
						{
							first <<= 1;
							first += (binary[i]-'0');
						}
                        first <<= 2;
						first += (address+4)&(1<<28+1<<29+1<<30+1<<31);
						tmp2.address = address;
						tmp2.instructionOrData = 0;
						tmp2.kind = 0;
						tmp2.first = first;

                        break;
                    }
                    case(2)://BEQ
                    {
                        int first = ((binary[6]-'0')<<4)+((binary[7]-'0')<<3)+((binary[8]-'0')<<2)+((binary[9]-'0')<<1)+(binary[10]-'0');
                        int second = ((binary[11]-'0')<<4)+((binary[12]-'0')<<3)+((binary[13]-'0')<<2)+((binary[14]-'0')<<1)+(binary[15]-'0');
						int third = 0;
						for(int i = 16; i < 32; ++i)
						{
							third <<= 1;
							third += (binary[i]-'0');
						}
						third <<= 2;
						//store the value
						tmp2.address = address;
						tmp2.instructionOrData = 0;
						tmp2.kind = 1;
						tmp2.first = first;
						tmp2.second = second;
						tmp2.third = third;
						
						tmp2.selfReadReg[0] = first;
						tmp2.selfReadReg[1] = second;
                        break;
                    }
                    case(4)://BGTZ
                    {
                        int first = ((binary[6]-'0')<<4)+((binary[7]-'0')<<3)+((binary[8]-'0')<<2)+((binary[9]-'0')<<1)+(binary[10]-'0');
                        int second = 0;
						for(int i = 16; i < 32; ++i)
						{
							second <<= 1;
							second += (binary[i]-'0');
						}
                        second <<= 2;
						
						tmp2.address = address;
						tmp2.instructionOrData = 0;
						tmp2.kind = 2;
						tmp2.first = first;
						tmp2.second = second;

						tmp2.selfReadReg[0] = first;
                        break;
                    }
                    case(5)://BREAK
                    {
                        int lastsix=((binary[26]-'0')<<5)+((binary[27]-'0')<<4)+((binary[28]-'0')<<3)+((binary[29]-'0')<<2)+((binary[30]-'0')<<1)+(binary[31]-'0');
                        if (lastsix == 13)
						{
							tmp2.address = address;
							tmp2.kind = 3;
							tmp2.instructionOrData = 0;
							//set instructionOrData to 1
							instructionOrData = 1;
							//now remember to set the value of memory data
							memoryStartAddress = address + 4;
						}
                        else
						{
							cout << "Error in disassembleOne(...), unknow code\n";
                            exit(1);
                        }
                        break;
                    }
                    case(6)://SW
                    {
                        int first = ((binary[11]-'0')<<4)+((binary[12]-'0')<<3)+((binary[13]-'0')<<2)+((binary[14]-'0')<<1)+(binary[15]-'0');
                        int second = 0;
						for(int i = 16; i < 32; ++i)
						{
							second <<= 1;
							second += (binary[i] - '0');
						}
						int third = ((binary[6]-'0')<<4)+((binary[7]-'0')<<3)+((binary[8]-'0')<<2)+((binary[9]-'0')<<1)+(binary[10]-'0');
						tmp2.address = address;
						tmp2.instructionOrData = 0;
						tmp2.kind = 4;
						tmp2.first = first;
						tmp2.second = second;
						tmp2.third = third;

						tmp2.selfReadReg[0] = first;
						tmp2.selfReadReg[1] = third;
                        break;
                    }
                    case(7)://LW
                    {
						int first = ((binary[11]-'0')<<4)+((binary[12]-'0')<<3)+((binary[13]-'0')<<2)+((binary[14]-'0')<<1)+(binary[15]-'0');
                        int second = 0;
						for(int i = 16; i < 32; ++i)
						{
							second <<= 1;
							second += (binary[i] - '0');
						}
						int third = ((binary[6]-'0')<<4)+((binary[7]-'0')<<3)+((binary[8]-'0')<<2)+((binary[9]-'0')<<1)+(binary[10]-'0');
                        tmp2.address = address;
						tmp2.instructionOrData = 0;
						tmp2.kind = 5;
						tmp2.first = first;
						tmp2.second = second;
						tmp2.third = third;

						tmp2.selfReadReg[0] = third;
						tmp2.selfWriteReg = first;
						break;
                    }
                }
                break;
            }
			case(6)://category 2
            {
                //char Middlethreebinarys[4]={binary[13],binary[14],binary[15],'\0'};
                int mthree=((binary[13]-'0')<<2)+((binary[14]-'0')<<1)+(binary[15]-'0');
				int first = ((binary[16]-'0')<<4)+((binary[17]-'0')<<3)+((binary[18]-'0')<<2)+((binary[19]-'0')<<1)+(binary[20]-'0');
				int second = ((binary[3]-'0')<<4)+((binary[4]-'0')<<3)+((binary[5]-'0')<<2)+((binary[6]-'0')<<1)+(binary[7]-'0');
				int third = ((binary[8]-'0')<<4)+((binary[9]-'0')<<3)+((binary[10]-'0')<<2)+((binary[11]-'0')<<1)+(binary[12]-'0');
				tmp2.address = address;
				tmp2.instructionOrData = 0;
				tmp2.first = first;
				tmp2.second = second;
				tmp2.third = third;

				tmp2.selfReadReg[0] = second;
				tmp2.selfReadReg[1] = third;
				tmp2.selfWriteReg = first;
                switch(mthree)
				{
                    case(0)://ADD
						tmp2.kind = 6; break;
                    case(1)://SUB
						tmp2.kind = 7; break;
                    case(2)://MUL
						tmp2.kind = 8; break;
                    case(3)://AND
						tmp2.kind = 9; break;
                    case(4)://OR
						tmp2.kind = 10; break;
                    case(5)://XOR
						tmp2.kind = 11; break;
                    case(6)://NOR
						tmp2.kind = 12; break;
                }
                break;
            }
            case(7)://category-3
            {
				
                //char Middlethreebinarys[4]={binary[13],binary[14],binary[15],'\0'};
                int mthree=((binary[13]-'0')<<2)+((binary[14]-'0')<<1)+(binary[15]-'0');
				int first = ((binary[8]-'0')<<4)+((binary[9]-'0')<<3)+((binary[10]-'0')<<2)+((binary[11]-'0')<<1)+(binary[12]-'0');
				int second = ((binary[3]-'0')<<4)+((binary[4]-'0')<<3)+((binary[5]-'0')<<2)+((binary[6]-'0')<<1)+(binary[7]-'0');
				int third = 0;
				for(int i = 16; i < 32; ++i)
				{
					third <<= 1;
					third += (binary[i] - '0');
				}
				tmp2.address = address;
				tmp2.instructionOrData = 0;
				tmp2.first = first;
				tmp2.second = second;
				tmp2.third = third;

				tmp2.selfReadReg[0] = second;
				tmp2.selfWriteReg = first;
                switch(mthree)
				{
                    case(0)://ADDI
						tmp2.kind = 13; break;
                    case(1)://ANDI
						tmp2.kind = 14; break;
                    case(2)://ORI
						tmp2.kind = 15; break;
                    case(3)://XORI
						tmp2.kind = 16; break;
                }
                break;
            }
        } //end of switch
    }// end of if
	else
	{
		if (binary[0] == '1')
        {   
			int data = 0;
			for(int i = 1; i < 32; ++i)
			{
				data <<= 1;
				data += (binary[i] -'0');
			}
			//=(1<<31)+((binary[1]-'0')<<30)+((binary[2]-'0')<<29)+((binary[3]-'0')<<28)+((binary[4]-'0')<<27)+((binary[5]-'0')<<26)+((binary[6]-'0')<<25)+((binary[7]-'0')<<24)+((binary[8]-'0')<<23)+((binary[9]-'0')<<22)+((binary[10]-'0')<<21)+((binary[11]-'0')<<20)+((binary[12]-'0')<<19)+((binary[13]-'0')<<18)+((binary[14]-'0')<<17)+((binary[15]-'0')<<16)+((binary[16]-'0')<<15)+((binary[17]-'0')<<14)+((binary[18]-'0')<<13)+((binary[19]-'0')<<12)+((binary[20]-'0')<<11)+((binary[21]-'0')<<10)+((binary[22]-'0')<<9)+((binary[23]-'0')<<8)+  ((binary[24]-'0')<<7)+((binary[25]-'0')<<6)+((binary[26]-'0')<<5)+((binary[27]-'0')<<4)+((binary[28]-'0')<<3)+((binary[29]-'0')<<2)+((binary[30]-'0')<<1)+(binary[31]-'0');
			data += (1<<31);
			data=data^(-1);
			data=data+1;
			tmp2.address = address;
			tmp2.instructionOrData = 1;
			tmp2.first = -data;
            //memorydata[leftline]=-data;
			mem.push_back(-data);
        } 
        else if (binary[0] == '0')
        {   
			int data = 0;
			for(int i = 1; i < 32; ++i)
			{
				data <<= 1;
				data += (binary[i] -'0');
			}
			//=((binary[1]-'0')<<30)+((binary[2]-'0')<<29)+((binary[3]-'0')<<28)+((binary[4]-'0')<<27)+((binary[5]-'0')<<26)+((binary[6]-'0')<<25)+((binary[7]-'0')<<24)+((binary[8]-'0')<<23)+((binary[9]-'0')<<22)+((binary[10]-'0')<<21)+((binary[11]-'0')<<20)+((binary[12]-'0')<<19)+((binary[13]-'0')<<18)+((binary[14]-'0')<<17)+((binary[15]-'0')<<16)+((binary[16]-'0')<<15)+((binary[17]-'0')<<14)+((binary[18]-'0')<<13)+((binary[19]-'0')<<12)+((binary[20]-'0')<<11)+((binary[21]-'0')<<10)+((binary[22]-'0')<<9)+((binary[23]-'0')<<8)+  ((binary[24]-'0')<<7)+((binary[25]-'0')<<6)+((binary[26]-'0')<<5)+((binary[27]-'0')<<4)+((binary[28]-'0')<<3)+((binary[29]-'0')<<2)+((binary[30]-'0')<<1)+(binary[31]-'0');
			tmp2.address = address;
			tmp2.instructionOrData = 1;
			tmp2.first = data;
			//memorydata[leftline]=data;
			mem.push_back(data);
        }
	}//end of else
	return;
}
