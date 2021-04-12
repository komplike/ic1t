#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() 
{
    char op;
    double num1, num2, res = 0;
    printf("Solve:\n");
    while(1)
    {
    scanf("%lf",&num1);
    scanf("%c",&op);
    scanf("%lf",&num2);
    switch ((int)op)
    {
        case 43:
            res = num1 + num2;
            break;
        case 45:
            res = num1 - num2;
            break;
        case 42:
            res = num1 * num2;
            break;
        case 47:
            if (num2 == 0) 
            {
                printf("Zero division!\n");
            }
            res = num1 / num2;
            break;
        default:
            printf("Wrong operation!");
            break;
        }
        
    printf("= %lf\n",res);
    }
    return 0;
}
