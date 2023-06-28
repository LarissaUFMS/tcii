#pragma once
#include "util/SharedObject.h"
#include "ast/FunctionDeclaration.h"
#include "ast/ExpressionValue.h"
#include "ast/ExpressionList.h"


namespace calc::ast
{ // begin namespace calc::ast

	using Value = Expression::Value;


	class FrameFunction : util::SharedObject
	{
	public:
		FrameFunction(const int, const int);
		~FrameFunction();
		void writeInputs(const ExpressionList*, Frame*);
		void writeOutputs(Value*);
		void readInputs(Value*);
		void readOutputs(Value*);

	private:
		Value* _input;
		Value* _output;
		Value* _error;

		int _inpSize;
		int _outSize;
	};

} // end namespace calc::ast
#pragma once
