#include "comb.h"

int main (int argc, char* argv[]){	
	
	if (argc != 3){
		printf("Incorrect arguments for comb. Please enter your circuit description file, followed by your input file.\n");
		return 0;
	}
	
	int i, numInput;
	block* var = malloc(26 * sizeof(block));
	block* tvar = malloc(26 * sizeof(block));
	instruct* instructions = malloc(100 * sizeof(instruct));
	
	for (i = 0; i < 26; i++)
	var[i].name = (char *) malloc (sizeof(char) * 11);
	for (i = 0; i < 26; i++)
	tvar[i].name = (char *) malloc (sizeof(char) * 11);
	for (i = 0; i < 100; i++){
		instructions[i].gate = (char *) malloc (sizeof(char) * 11);
		instructions[i].var = (char *) malloc (sizeof(char) * 50);
	}
	
	
	readInputs(argv[1], numInput, instructions, var, tvar);
	readStates(argv[2], var);
	
	
	
	
	printer(var, tvar, instructions);
	return 0;
}

void readInputs(char* name, int numInput, instruct* instructions, block* var, block* tvar){
	
	FILE *inputtext;
	char str[11];
	int i, varcount;
	int count = 0;
	
	inputtext = fopen(name, "r");
	
	if (!inputtext){
		printf("Cannot find files given.\n");
		return;
	}
	while (fscanf(inputtext, "%s", &str) != EOF){
		
		int numOutput, i;
		
		if ((strcmp(str, "INPUTVAR")) == 0){
			fscanf(inputtext, "%s", &str);
			numInput = atoi(str);
			for (i = 0; i < numInput; i++){
				fscanf(inputtext, "%s", &str);
				strcpy(var[i].name, str);
			}
		}
		if ((strcmp(str, "OUTPUTVAR")) == 0){
			fscanf(inputtext, "%s", &str);
			numOutput = atoi(str);
			for (i = numInput; i < (numInput + numOutput); i++){
				fscanf(inputtext, "%s", &str);
				strcpy(var[i].name, str);
			}
		}
		if ((strcmp(str, "AND")) == 0){
			strcpy(instructions[count].gate, str);
			count++;
			
			for(varcount = 0; varcount < 3; varcount++){
				fscanf(inputtext, "%s", &str);
				strcpy(instructions[varcount].var, str);
			}
		}
		if ((strcmp(str, "OR")) == 0){
			strcpy(instructions[count].gate, str);
			count++;
			
			for(varcount = 0; varcount < 3; varcount++){
				fscanf(inputtext, "%s", &str);
				strcpy(instructions[varcount].var, str);
			}
		}
	}
}

void readStates(char* name, block* var){
	
	FILE *statetext;
	char val[10];
	int count = 0;
	int state;
	
	statetext = fopen(name, "r");
	
	if (!statetext){
		printf("Cannot find files given.\n");
		return;
	}

	while (fscanf(statetext, "%s", &val) != EOF){
		state = atoi(val);
		/*printf("State is: %d\n", state);*/
		var[count].state = state;
		count++;
	}
}

void printer(block* var, block* tvar, instruct* instructions){
	
	int i;
	printf("--Printing Input & Output Variables--\n");
	for (i = 0; i < 26; i++){
		if (!var[i].name || strcmp(var[i].name, "") == 0)
		break;
		printf("var[%d] is: %s, %d\n", i, var[i].name, var[i].state);
	}
	printf("--Printing Temporary Variables--\n");
	for (i = 0; i < 26; i++){
		if (!tvar[i].name || strcmp(tvar[i].name, "") == 0)
		break;
		printf("tvar[%d] is: %s\n", i, tvar[i].name, tvar[i].state);
	}
	printf("--Printing Logic Operations--\n");
	for (i = 0; i < 100; i++){
		if (!instructions[i].gate || strcmp(instructions[i].gate, "") == 0)
		break;
		printf("%s\n", instructions[i].gate);
		
	}
	
}



