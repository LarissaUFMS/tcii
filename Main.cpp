#define _DEBUG_ALLOCATOR

#include "tests/BLASTest.h"
#include "tests/DflOpTest.h"
#include "tests/FuncTemplateTest.h"
#include "tests/LambdaTest.h"
#include "tests/ListTest.h"
#include "tests/MatrixTest.h"
#include "tests/RefTest.h"
#include "tests/ShapeTest.h"
#include "tests/TypeTest.h"

int
main()
{
  using TestFunc = std::function<void()>;

  const struct
  {
    const char* title;
    int cmd;
    TestFunc func;

  } tests[]
  {
    {"Types: numeric/struct/pointer/array/function", '1', typeTest},
    {"Simple inheritance/dynamic binding", '2', shapeTest},
    {"Lvalue/Rvalue reference tutorial", '3', refTest},
    {"Special member functions", '4', dflOpTest},
    {"Function templates/constexpr function", '5', funcTemplateTest},
    {
      "Class templates", '6', []()
      {
        puts("\n**CLASS TEMPLATES");
        objectPtrListTest();
        listTest();
      }
    },
    {
      "Exceptions/Copy&Move/Smart pointers", '7', []()
      {
        puts("\n**EXCEPTIONS/COPY&MOVE/SMART POINTERS");
        matrixTest();
        vectorTest();
      }
    },
    {"Variadic templates", '8', nullptr},
    {"Lambda/Fold expression", '9', lambdaTest},
    {"Concepts test", 'c', blasTest}
  };

  for (bool found;;)
  {
    puts("**C++ feature tests (SEE THE CODE):");
    for (const auto& test : tests)
      printf("[%c] %s\n", test.cmd, test.title);
    puts("[x] Exit\n**Enter an option<x>: ");

    char input[3];

    fgets(input, sizeof input, stdin);

    auto option = *input;

    if (option == '\n')
      break;
    found = false;
    if (input[1] != '\n')
      while (getchar() != '\n')
        ;
    else
    {
      if (option == 'x')
        break;
      for (const auto& test : tests)
        if (option == test.cmd)
        {
          found = true;
          if (test.func == nullptr)
            puts("**Test not implemented yet");
          else
            try
            {
              test.func();
            }
            catch (const std::exception& e)
            {
              printf("**Error: %s\n", e.what());
            }
        }
    }
    if (!found)
      puts("**Invalid option. Try again");
    putchar('\n');
  }
  /*
  puts("Press any key to exit...");
  (void)getchar();
  */
  return 0;
}
