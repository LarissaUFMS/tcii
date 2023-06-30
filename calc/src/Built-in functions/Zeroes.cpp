#include "ast/FrameFunction.h"
#include "ast/ExpressionValue.h"
#include "BuiltinFunctions.h"

namespace calc::ast
{ // begin namespace calc::ast

// Param: int size_row, int size_col
	bool zeroes(FrameFunction& ff)
	{
		Value inputs[2];

		ff.readInputs(inputs);
		inputs[0] = inputs[0].castTo(Type::Int());
		inputs[1] = inputs[1].castTo(Type::Int());

		int size_row = 1; // como pegar o numero dentro de Value?
		int size_col = 1;

		if (size_row > 0 && size_col > 0)
		{
			IntMatrix zeroMatrix{ (size_t)size_row, (size_t)size_col };

			zeroMatrix *= 0;

			Value ret{ zeroMatrix };

			ff.writeOutputs(&ret);

			return 1;
		}
		else
		{
			ff.setError(1);
			return 0;
		}

	}

} // end namespace calc::ast