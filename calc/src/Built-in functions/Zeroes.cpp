#include "ast/FrameFunction.h"
#include "ast/ExpressionValue.h"

namespace calc::ast
{ // begin namespace calc::ast

// Param: int size_row, int size_col
	void zeroes(FrameFunction ff)
	{
		Value inputs[2];

		ff.readInputs(inputs);
		inputs[0] = inputs[0].castTo(Type::Int());
		inputs[1] = inputs[1].castTo(Type::Int());

		int size_row; // como pegar o numero dentro de Value?
		int size_col;

		IntMatrix zeroMatrix{ size_row, size_col };

		zeroMatrix *= 0;

		Value ret{ zeroMatrix };

		ff.writeOutputs(&ret);
	}

} // end namespace calc::ast