#include "include/ast/FunctionDeclaration.h"
#include "symbol/Scope.h"
#include "AddBuiltinFunctions.h"
#include "BuiltinFunctions.h"

namespace calc::ast
{
using Func = FunctionDeclaration::Func;

void addFunction(Func* f, const char* c, Scope* scope)
{
	FunctionDeclaration fd;
	fd.setName(c);
	fd.setFunction(f);

	fd.resolve(scope);
	scope->buildFunction(&fd);
}

void
addBuiltinFunctions(Scope* scope)
{
	addFunction(&zeroes, "zeroes", scope);
}

}