#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

#define ARG_COUNT 4
#define ARG_POS_1 1
#define ARG_POS_OPERAND 2
#define ARG_POS_2 3

void PrintOperators();
double CheckAndConvert(char *num);

int main(int argc, char **argv)
{
  for (int i = 1; i < argc; ++i)
  {
    if (strcmp(argv[i], "--help") == 0)
    {
      PrintOperators();
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[i], "--sqrt") == 0)
    {
      if (i + 1 >= argc) 
      {
        fprintf(stderr, "Error: not enough arguments!\n");
        return EXIT_FAILURE;
      }
      double num = CheckAndConvert(argv[i+1]);
      printf("%lf\n", sqrt(num));
      return EXIT_SUCCESS;
    }
  }
  if (argc < ARG_COUNT)
  {
    fprintf(stderr, "Error: not enough arguments!\n");
    return EXIT_FAILURE;
  }
  if (argc > ARG_COUNT + 1)
  {
    fprintf(stderr, "Error: too many arguments!\n");
    return EXIT_FAILURE;
  }

  double num1 = CheckAndConvert(argv[ARG_POS_1]);
  char operator= argv[ARG_POS_OPERAND][0];
  double num2 = CheckAndConvert(argv[ARG_POS_2]);

  double result;
  switch (operator)
  {
  case '+':
  {
    result = num1 + num2;
  }
  break;
  case '-':
  {
    result = num1 - num2;
  }
  break;
  case '*':
  {
    result = num1 * num2;
  }
  break;
  case '/':
  {
    if (num2 == 0)
    {
      fprintf(stderr, "Error: Division by zero!\n");
      return 1;
    }
    result = num1 / num2;
  }
  break;
  case '%':
  {
    result = (int)num1 % (int)num2;
  }
  break;
  case '^':
  {
    result = pow(num1, num2);
  }
  break;
  case '<':
  {
    if (argv[ARG_POS_OPERAND][1] == '=')
    {
      result = num1 <= num2;
    }
    else
    {
      result = num1 < num2;
    }
  }
  break;
  case '>':
  {
    if (argv[ARG_POS_OPERAND][1] == '=')
    {
      result = num1 >= num2;
    }
    else
    {
      result = num1 > num2;
    }
  }
  break;
  default:
  {
    fprintf(stderr, "\e[1;91mInvalid operator!\e[0m\n");
    PrintOperators();
    return EXIT_FAILURE;
  }
  }

  // if (takeSQRT)
  // {
  //   printf("sqrt\n");
  //   result = sqrt(result);
  // }

  fprintf(stdout, "%.2lf %s %.2lf = %.2lf\n", num1, argv[2], num2, result);

  return EXIT_SUCCESS;
}

double CheckAndConvert(char *num)
{
  int fpIdx = -1;
  for (int i = 0; i < strlen(num); ++i)
  {
    if (num[i] == '.' && fpIdx == -1)
    {
      fpIdx = i;
      continue;
    }
    if ((!isdigit(num[i]) && num[i] != '.' && num[i] != '-' && num[i] != 'e') ||
        (num[i] == 'e' && (i < 1 || !isdigit(num[i - 1]))) ||
        (i != 0 && (num[i] == '-' || num[i] == '+')) ||
        (fpIdx != -1 && num[i] == '.'))
    {
      fprintf(stderr, "\e[1;91mInvalid character in number!\e[0m\n");
      PrintOperators();
      exit(EXIT_FAILURE);
    }
  }

  return atof(num);
}

void PrintOperators()
{
  printf("Supported operators:\n\e[0;34m[note that some operators\
  need to be encased in quotes!]\e[0m\n");
  printf("\t\e[1;32m+\e[0m Addition\n");
  printf("\t\e[1;32m-\e[0m Subtraction\n");
  printf("\t\e[1;32m*\e[0m Multiplication\n");
  printf("\t\e[1;32m/\e[0m Division\n");
  printf("\t\e[1;32m%%\e[0m Modulus\n");
  printf("\t\e[1;32m^\e[0m Exponentiation\n");
  // printf("\t\e[1;32m<<\e[0m Left Shift\n");
  // printf("\t\e[1;32m>>\e[0m Right Shift\n");
  printf("\t\e[1;32m<\e[0m Less Than\n");
  printf("\t\e[1;32m>\e[0m Greater Than\n");
  printf("\t\e[1;32m<=\e[0m Less Than or Equal\n");
  printf("\t\e[1;32m>=\e[0m Greater Than or Equal\n");
  // printf("\t\e[1;32m==\e[0m Equal To\n");
  // printf("\t\e[1;32m!=\e[0m Not Equal To\n");
  // printf("\t\e[1;32m&&\e[0m Logical AND\n");
  // printf("\t\e[1;32m||\e[0m Logical OR\n");
  // printf("\t\e[1;32m!\e[0m Logical NOT\n");
  // printf("\t\e[1;32m=\e[0m Assignment\n");
  printf("\t\e[1;32m--sqrt <n>\e[0m Square root of the next argument, this is an additional flag you put anywhere! !this discards all other functionality!\n");
}