#include "include/ast/FunctionDeclaration.h"

#include "src/Built-in functions/Zeroes.cpp"

namespace calc::ast
{


void
addBuiltinFunctions(Scope* scope)
{
	using Func = FunctionDeclaration::Func;

	FunctionDeclaration fd_zeroes;
	fd_zeroes.setName("zeroes");
	fd_zeroes.setFunction(zeroes);

	fd_zeroes.resolve(scope); // precisa de escopo global, dentro de calc, onde colocar esta função?
}


}