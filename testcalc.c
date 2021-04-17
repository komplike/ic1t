#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *gets(char *);

// debugging function to see results after each opperation
void printStatus(double *numbers, int *ops, int op_left)
{
	while (op_left != 0)
	{
		for (int i = 0; i < op_left+1; i++)
		{
			printf("%lf ",numbers[i]);
		}
		printf("\n");
		for (int i = 0; i < op_left; i++)
		{
			printf("%d ",ops[i]);
		}
		printf("\n");
		op_left--;
	}
}

int main()
{

	const int NUMBER_OF_OPERANDS = 5;

	struct
	{
		char input[100];
		double numbers[NUMBER_OF_OPERANDS];
		char operators[NUMBER_OF_OPERANDS - 1];
	} formula;

	char delimiters[] = "+-*/";
	char numbers[] = "0123456789.";
	char copy[100];

	//ACQUIRES INPUT FROM USER

	gets(formula.input);
	//strcpy(formula.input, "45+6-7*89/10"); //ONLY USED FOR DEBUGGING WITH DDD

	//MAKES A COPY TO ACQUIRE OPERATORS LATER
	strcpy(copy, formula.input);

	//READS NUMBERS FROM formula.input AND PUTS THEM TO formula.numbers
	char *ptr = strtok(formula.input, delimiters);
	int i = 0;
	while (ptr != NULL)
	{
		if (i >= NUMBER_OF_OPERANDS)
		{
			break;
		}
		formula.numbers[i] = atof(ptr);
		// printf("%f\n", formula.numbers[i]);
		ptr = strtok(NULL, delimiters);
		i++;
	}

	//READS OPERATOR SYMBOLS FROM copy AND PUTS THEM TO formula.operators
	ptr = strtok(copy, numbers);
	i = 0;
	while (ptr != NULL)
	{
		formula.operators[i] = *ptr;
		// printf("%c\n", formula.operators[i]);
		ptr = strtok(NULL, numbers);
		i++;
	}
	int TRUE_NUM_OF_OPS = i;
	//ACTUAL CALCULATOR NOW

	//NUMBERS ARE STORED IN formula.numbers AND OPERATORS ARE STORED IN formula.operators

	//represent operands as numbers
	int op[TRUE_NUM_OF_OPS];
	for (int i = 0; i < TRUE_NUM_OF_OPS; i++)
	{
		switch (formula.operators[i])
		{
		case '*':
			op[i] = 0;
			break;
		case '/':
			op[i] = 1;
			break;
		case '+':
			op[i] = 2;
			break;
		case '-':
			op[i] = 3;
			break;
		default:
			break;
		}
	}

	// solve expression by operand priority
	int op_left = TRUE_NUM_OF_OPS;
	while (op_left != 0)
	{
		//operation priority * /
		for (int i = 0; i < NUMBER_OF_OPERANDS - 1; i++)
		{
			if (op[i] == 0)
			{
				op_left -= 1;
				//do *
				formula.numbers[i] = formula.numbers[i] * formula.numbers[i+1];
				//shift left
				for (int j = i+1; j < NUMBER_OF_OPERANDS; j++)
				{
					formula.numbers[j] = formula.numbers[j+1];
				}
				for (int j = i; j < NUMBER_OF_OPERANDS-1; j++)
				{
					op[j] = op[j+1];
				}
				i -= 1;
				// printStatus(formula.numbers, op, op_left);
			}
			else if (op[i] == 1)
			{
				op_left -= 1;
				//do /
				formula.numbers[i] = formula.numbers[i] / formula.numbers[i+1];
				//shift left
				for (int j = i+1; j < NUMBER_OF_OPERANDS; j++)
				{
					formula.numbers[j] = formula.numbers[j+1];
				}
				for (int j = i; j < NUMBER_OF_OPERANDS-1; j++)
				{
					op[j] = op[j+1];
				}
				i -= 1;
				// printStatus(formula.numbers, op, op_left);
			}
		}
		//operation priority + -
		for (int i = 0; i < NUMBER_OF_OPERANDS - 1; i++)
		{
			if (op[i] == 2)
			{
				op_left -= 1;
				//do +
				formula.numbers[i] = formula.numbers[i] + formula.numbers[i+1];
				//shift left
				for (int j = i+1; j < NUMBER_OF_OPERANDS; j++)
				{
					formula.numbers[j] = formula.numbers[j+1];
				}
				for (int j = i; j < NUMBER_OF_OPERANDS-1; j++)
				{
					op[j] = op[j+1];
				}
				i -= 1;
				// printStatus(formula.numbers, op, op_left);
			}
			else if (op[i] == 3)
			{
				op_left -= 1;
				//do -
				formula.numbers[i] = formula.numbers[i] - formula.numbers[i+1];
				//shift left
				for (int j = i+1; j < NUMBER_OF_OPERANDS; j++)
				{
					formula.numbers[j] = formula.numbers[j+1];
				}
				for (int j = i; j < NUMBER_OF_OPERANDS-1; j++)
				{
					op[j] = op[j+1];
				}
				i -= 1;
				// printStatus(formula.numbers, op, op_left);
			}
		}
	}
	printf("= %lf",formula.numbers[0]);

	return (0);
}
