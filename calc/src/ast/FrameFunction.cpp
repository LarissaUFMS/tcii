#include "util/SharedObject.h"
#include "ast/FunctionDeclaration.h"
#include "ast/ExpressionValue.h"
#include "ast/ExpressionList.h"
#include "ast/FrameFunction.h"

namespace calc::ast
{ // begin namespace calc::ast

using Value = Expression::Value;

FrameFunction::FrameFunction(const int input_size, const int output_size)
{
	_input = new Value[input_size];
	_output = new Value[output_size];

	_inpSize = input_size;
	_outSize = output_size;
}

FrameFunction::~FrameFunction()
{
	delete _input;
	delete _output;
}

void
FrameFunction::writeInputs(const ExpressionList* arguments, Frame* frame)
{
	auto arg_list = arguments->begin();

	for (int i = 0; i < _inpSize; i++)
	{
		_input[i] = arg_list->eval(frame);
		arg_list++;
	}
}

void
FrameFunction::readInputs(Value* inputs)
{
	for (int i = 0; i < _inpSize; i++)
	{
		inputs[i] = _input[i];
	}
}

void
FrameFunction::writeOutputs(Value* outputs)
{
	for (int i = 0; i < _outSize; i++)
	{
		_output[i] = outputs[i];
	}
}

void
FrameFunction::readOutputs(Value* outputs)
{
	for (int i = 0; i < _outSize; i++)
	{
		outputs[i] = _output[i];
	}
}

void
FrameFunction::setError(int error)
{
	_error = error;
}

void
FrameFunction::printError()
{
	switch (_error)
	{
	case 1: // invalid inputs
		// throw exception? quando usar exception, quando apenas printar na tela
	case 2: // catch-all error
		// função não conseguiu executar por motivo não determinado
	default:
		break;
	}
}

} // end namespace calc::ast

