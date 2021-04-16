#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *gets(char *);

int main() {
	
	const int NUMBER_OF_OPERANDS = 5;

	struct {
		char input[100];
		double numbers[NUMBER_OF_OPERANDS];
		char operators[NUMBER_OF_OPERANDS - 1];
	} formula;

	char delimiters[] = "+-*/";
	char numbers[] = "0123456789";
	char copy[100];

	//ACQUIRES INPUT FROM USER

	gets(formula.input);
	//strcpy(formula.input, "45+6-7*89/10"); //ONLY USED FOR DEBUGGING WITH DDD
	
	//MAKES A COPY TO ACQUIRE OPERATORS LATER
	strcpy(copy, formula.input);

	//READS NUMBERS FROM formula.input AND PUTS THEM TO formula.numbers
	char *ptr = strtok(formula.input, delimiters);
	int i = 0;
	while(ptr != NULL)
	{
		if (i >= NUMBER_OF_OPERANDS)
		{
			break;
		}
		formula.numbers[i] = atof(ptr);
		printf("%f\n", formula.numbers[i]);
		ptr = strtok(NULL, delimiters);
		i++;
	}

	//READS OPERATOR SYMBOLS FROM copy AND PUTS THEM TO formula.operators
	ptr = strtok(copy, numbers);
	i = 0;
	while(ptr != NULL)
	{
		formula.operators[i] = *ptr;
		printf("%c\n", formula.operators[i]);
		ptr = strtok(NULL, numbers);
		i++;
	}

	//ACTUAL CALCULATOR NOW

	//NUMBERS ARE STORED IN formula.nubers AND OPERATORS ARE STORED IN formula.operators

	//just add some logic to make it work now. 2moro...





	exit(0);
}
