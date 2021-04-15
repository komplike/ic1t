#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *gets(char *);

int main() {
	struct {
		char str[100];
		double num[];
	} op;

	const int NUMBER_OF_OPERANDS = 5;
	char delim[] = "+-*/";

	gets(op.str);
	char *ptr = strtok(op.str, delim);

	int i = 0;
	while(ptr != NULL)
	{
		if (i >= NUMBER_OF_OPERANDS)
		{
			break;
		}

		//printf("%s\n", ptr);
		op.num[i] = atof(ptr);
		//printf("%f\n", op.num[i]);
		ptr = strtok(NULL, delim);
		i++;
	}

	for (int j = 0; j<NUMBER_OF_OPERANDS;j++)
	{
		printf("%f\n", op.num[j]);
	}

	exit(0);
}