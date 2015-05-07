#include "comb.h"

int main (int argc, char* argv[]){	
	
	if (argc != 3){
		printf("Incorrect arguments for comb. Please enter your circuit description file, followed by your input file.\n");
		return 0;
	}
	
	int i, j, numInput;
	block* var = malloc(26 * sizeof(block));
	block* tvar = malloc(26 * sizeof(block));
	instruct* instructions = malloc(100 * sizeof(instruct));
	
	for (i = 0; i < 26; i++)
	var[i].name = (char *) malloc (sizeof(char) * 11);
	for (i = 0; i < 26; i++)
	tvar[i].name = (char *) malloc (sizeof(char) * 11);
	for (i = 0; i < 100; i++){
		instructions[i].gate = (char *) malloc (sizeof(char) * 11);
		instructions[i].vari = malloc(100 * sizeof(char *));
		for (j = 0; j < 100; j++)
		instructions[i].vari[j] = malloc(100 * sizeof(char));
	}

	readInputs(argv[1], numInput, instructions, var, tvar);
	
	
	
	readStates(argv[2], var);

	
	
	printer(var, tvar, instructions);
	return 0;
}

void readInputs(char* name, int numInput, instruct* instructions, block* var, block* tvar){
	
	FILE *inputtext;
	char str[11];
	int i, j, varcount, tvarflag;
	int count, tvarcount = 0;
	
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
		if ((strcmp(str, "NOT")) == 0){
			strcpy(instructions[count].gate, str);
			instructions[count].numVari = 1;
			for(i = 0; i < instructions[count].numVari + 1; i++){
				tvarflag = 0;
				fscanf(inputtext, "%s", &str);
				if (islower(str[0])){
					for (j = 0; j < 26; j++){
						if(strcmp(tvar[j].name, str) == 0){
							tvarflag = 1;
							break;
						}
					}
					if(!tvarflag){
						strcpy(tvar[tvarcount].name, str);
						tvarcount++;
					}
				}
				strcpy(instructions[count].vari[i], str);
			}
			count++;
		}
		if ((strcmp(str, "AND")) == 0){
			strcpy(instructions[count].gate, str);
			instructions[count].numVari = 2;
			for(i = 0; i < instructions[count].numVari + 1; i++){
				tvarflag = 0;
				fscanf(inputtext, "%s", &str);
				if (islower(str[0])){
					for (j = 0; j < 26; j++){
						if(strcmp(tvar[j].name, str) == 0){
							tvarflag = 1;
							break;
						}
					}
					if(!tvarflag){
						strcpy(tvar[tvarcount].name, str);
						tvarcount++;
					}
				}
				strcpy(instructions[count].vari[i], str);
			}
			count++;
		}
		if ((strcmp(str, "OR")) == 0){
			strcpy(instructions[count].gate, str);
			instructions[count].numVari = 2;
			for(i = 0; i < instructions[count].numVari + 1; i++){
				tvarflag = 0;
				fscanf(inputtext, "%s", &str);
				if (islower(str[0])){
					for (j = 0; j < 26; j++){
						if(strcmp(tvar[j].name, str) == 0){
							tvarflag = 1;
							break;
						}
					}
					if(!tvarflag){
						strcpy(tvar[tvarcount].name, str);
						tvarcount++;
					}
				}
				strcpy(instructions[count].vari[i], str);
			}
			count++;
		}
		if ((strcmp(str, "DECODER")) == 0){
			strcpy(instructions[count].gate, str);
			fscanf(inputtext, "%s", &str);
			instructions[count].numVari = atoi(str);
			for(i = 0; i < (instructions[count].numVari + pow(2, instructions[count].numVari)); i++){
				tvarflag = 0;
				fscanf(inputtext, "%s", &str);
				if (islower(str[0])){
					for (j = 0; j < 26; j++){
						if(strcmp(tvar[j].name, str) == 0){
							tvarflag = 1;
							break;
						}
					}
					if(!tvarflag){
						strcpy(tvar[tvarcount].name, str);
						tvarcount++;
					}
				}
				strcpy(instructions[count].vari[i], str);
			}
			count++;
		}
		if ((strcmp(str, "MULTIPLEXER")) == 0){
			strcpy(instructions[count].gate, str);
			fscanf(inputtext, "%s", &str);
			instructions[count].numVari = atoi(str);
			for(i = 0; i < (instructions[count].numVari + (log10(instructions[count].numVari) / log10(2)) + 1); i++){
				tvarflag = 0;
				fscanf(inputtext, "%s", &str);
				if (islower(str[0])){
					for (j = 0; j < 26; j++){
						if(strcmp(tvar[j].name, str) == 0){
							tvarflag = 1;
							break;
						}
					}
					if(!tvarflag){
						strcpy(tvar[tvarcount].name, str);
						tvarcount++;
					}
				}
				strcpy(instructions[count].vari[i], str);
			}
			count++;
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
		var[count].state = state;
		count++;
	}
}

void printer(block* var, block* tvar, instruct* instructions){
	
	int i, j;
	printf("--Printing Input & Output Variables--\n");
	for (i = 0; i < 26; i++){
		if (!var[i].name || strcmp(var[i].name, "") == 0)
		break;
		printf("var[%d] is: %s: %d\n", i, var[i].name, var[i].state);
	}
	printf("--Printing Temporary Variables--\n");
	for (i = 0; i < 26; i++){
		if (!tvar[i].name || strcmp(tvar[i].name, "") == 0)
		break;
		printf("tvar[%d] is: %s: %d\n", i, tvar[i].name, tvar[i].state);
	}
	printf("--Printing Logic Operations--\n");
	for (i = 0; i < 100; i++){
		
		if (!instructions[i].gate || strcmp(instructions[i].gate, "") == 0)
		break;
		printf("%s, %d, ", instructions[i].gate, instructions[i].numVari);
		for (j = 0; j < 100; j++){
			
			printf("%s", instructions[i].vari[j]);
			
		}
	}
	
}


