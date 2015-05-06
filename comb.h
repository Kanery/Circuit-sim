#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct inputblock{
	
	char* name;
	int state;
	int type; /* 0 - Input, 1 - Output, (-1) = Temporary */
	
}block;

typedef struct instructionblock{
	
	char* gate;
	char* vari;
	
}instruct;

void printer(block* var, block* tvar, instruct* instructions);
void readInputs(char* name, int numInput, instruct* instructions, block* var, block* tvar);
void readStates(char* name, block* var);