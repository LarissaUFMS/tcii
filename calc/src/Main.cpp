//#include "MatTest.h"
#include "ast/ExpressionValue.h"
#include "Calc.h"
#include "AddBuiltinFunctions.h"

//
// Auxiliary function
//
char*
readLine(const char* prompt)
{
  constexpr auto maxLine = 1024;
  static char line[maxLine];

  fputs(prompt, stdout);
  return fgets(line, maxLine, stdin);
}

//
// Main function
//
int
main()
{
  /*
  calc::matTest();
  (void)getchar();
  return 0;
  */
  puts("Simple Matrix Calculator Copyright(c), 2023. FACOM-UFMS, TCII guys");

  calc::Calc calc;
  calc::ast::addBuiltinFunctions(calc.getGlobalScope());

  for (;;)
  {
    auto input = readLine(">");

    if (input && !calc.execute(input))
    {
      printf("Bye\n");
      return 0;
    }
  }
}
