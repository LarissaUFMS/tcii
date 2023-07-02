#include "include/ast/FunctionDeclaration.h"
#include "symbol/Scope.h"
#include "AddBuiltinFunctions.h"
#include "BuiltinFunctions.h"


namespace calc::ast
{

ParameterList& addParameters(int n...)
{
	ParameterList* pl = new ParameterList;

	va_list args;
	va_start(args, n);

	for (int i = 0; i < n; i++)
	{
		pl->add(new Parameter{ new String { va_arg(args, const char*) } });
	}

	va_end(args);

	return *pl;
}

using Func = FunctionDeclaration::Func;

void addFunction(Func* f, const String name, ParameterList& params, ParameterList& output, Scope* scope)
{
	FunctionDeclaration fd{ f, name, params, output };

	fd.resolve(scope);
	scope->buildFunction(&fd);
}

void foo(const String& str)
{

}

void
addBuiltinFunctions(Scope* scope)
{
	addFunction(&zeroes, "zeroes", addParameters(2, "row_size", "col_size"), addParameters(1, "zero_matrix"), scope);
}

}