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
	const int MAX_INPUT = 50;

	struct
	{
		char input[50];
		volatile char memory[50];
		double numbers[NUMBER_OF_OPERANDS];
		char operators[NUMBER_OF_OPERANDS - 1];
	} formula;


	while(1)
	{
		//initialize to be empty
		memset(formula.input, 0, 50*(sizeof formula.input[0]));
		gets(formula.input);
		//strcpy(formula.input, "15*0"); //only here for ddd debugging

		//if you type in mem, you get the last result
		if(!strcmp(formula.input, "mem"))
		{
			printf("memory: %s\n", formula.memory);
			continue;
		}

		//initialize to be empty
		memset(formula.operators, 0, (NUMBER_OF_OPERANDS-1)*(sizeof formula.operators[0]));

		int position = 0;
		int formula_position = 0;
		char read[100] = "";

		//goes through the entire input and splits it into numbers and operands
		for (int i = 1; i < MAX_INPUT; i++) //OD 1 PROTOZE RADEK MUZE ZACINAT minus
		{
			switch ((int)formula.input[i])
			{
				case 43:
				case 45:
				case 42:
				case 47:
					//if last char is symbol, skips
					if (i == MAX_INPUT -1)
					{
						break;
					}

					memset(read, 0, 50*(sizeof read[0]));
					//copies (i - position) chars from formula.input from position formula.input[position]
					memcpy(&read, &formula.input[position], (i - position)*sizeof(char));
					formula.numbers[formula_position] = atof(read);

					memset(read, 0, 50*(sizeof read[0]));
					//adds the opertor to formula.operators same as above
					memcpy(&read, &formula.input[i], sizeof(char));
					formula.operators[formula_position] = (char)read[0];
				
					//printf("%f\n", formula.numbers[formula_position]);	//used for debugging
					//printf("%c\n", formula.operators[formula_position]);	//used for debugging

					//iterates position in array
					formula_position++;
					//iterates i because next symbol could be "-" as to not read it as an operator
					i++;
					position = i;

					break;
			}

			//last number
			if (i == (MAX_INPUT -1))
			{
				if ((i - position) == 0)
				{
					memcpy(&read, &formula.input[position], sizeof(char));
					formula.numbers[formula_position] = atof(read);     //od pos1 do i-1
					//printf("%f\n", formula.numbers[formula_position]);
				}
				else
				{
					memcpy(&read, &formula.input[position], (i - position)*sizeof(char));
					formula.numbers[formula_position] = atof(read);     //od pos1 do i-1
					//printf("%f\n", formula.numbers[formula_position]);
				}
			}
		}

		//numbers are stored in formula.numbers and operators are stored in formula.operators
		int TRUE_NUM_OF_OPS = formula_position;

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
			for (int i = 0; i < TRUE_NUM_OF_OPS; i++)
			{
				if (op[i] == 0)
				{
					//when a*b was entered, last for loop in this if clause caused the calculation to continue indefinitely, this prevents it
					if(op_left == 0)
					{
						break;
					}
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
					if (formula.numbers[i+1] == 0)
					{
						printf("%s\n", "Division by zero!");
						break;
					}
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
			for (int i = 0; i < TRUE_NUM_OF_OPS; i++)
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

		char mem[50];
		snprintf(mem, 50, "%lf", formula.numbers[0]);
		strcpy(formula.memory, mem);
		//printf("mem = %s\n", formula.memory); //for debugging
		printf("= %lf\n",formula.numbers[0]);
	}

	return (0);
}
