#ifndef _DISASSEMBLE_H_
#define _DISASSEMBLE_H_

#include "global.h"

void Disassemble(char *filepath);
void DisassembleOne(char binary[], int &instructionOrData, cmd &tmp2, int address);


#endif