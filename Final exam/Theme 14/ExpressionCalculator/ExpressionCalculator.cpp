#include "ExpressionCalculator.h"

void ExpressionCalculator::copyFrom(const ExpressionCalculator& other)
{
	expr = other.expr->clone();
}

void ExpressionCalculator::free()
{
	delete expr;
}

ExpressionCalculator::ExpressionCalculator(const ExpressionCalculator& other)
{
	copyFrom(other);
}

ExpressionCalculator& ExpressionCalculator::operator=(const ExpressionCalculator& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

ExpressionCalculator::~ExpressionCalculator()
{
	free();
}

bool isOperator(char el)
{
	return el == AND || el == OR || el == IMPL || el == IFF;
}

ExpressionCalculator::BooleanExpr* parse(const MyString& str)
{
	if (str.getSize() == 1)
		return new ExpressionCalculator::Variable(str[0]);

	size_t counter = 0;
	MyString strBr = str.subString(1, str.getSize() - 2);

	for (size_t i = 0; i < strBr.getSize(); i++)
	{
		if (strBr[i] == '(')
			counter++;
		else if (strBr[i] == ')')
			counter--;
		else if (isOperator(strBr[i]) && counter == 0)
		{
			if (strBr[i] == NEG)
				return new ExpressionCalculator::UnaryOperation(NEG, parse(strBr.subString(i+1, strBr.getSize() - 2)));
			else
				return new ExpressionCalculator::BinaryOperation(parse(strBr.subString(0, i - 1)), strBr[i], parse(strBr.subString(i + 1, strBr.getSize() - 1)));
		}
	}
}

ExpressionCalculator::BooleanExpr::BooleanInterpretation ExpressionCalculator::convertFromNumber(size_t number, bool vars[26]) const
{
	ExpressionCalculator::BooleanExpr::BooleanInterpretation interpret;
	for (size_t i = 25; i >= 0; i--)
	{
		if (vars[i])
		{
			if (number % 2 == 1)
				interpret.setValue(i + 'A', true);
			number /= 2;
		}
	}

	return interpret;
}

bool ExpressionCalculator::checkAll(BooleanExpr* expr, bool value) const
{
	size_t varsCount = expr->varsCount;
	size_t intersCount = 1 << varsCount;
	
	for (size_t i = 0; i < intersCount; i++)
	{
		if (expr->eval(convertFromNumber(i, expr->vars)) != value)
			return false;
	}

	return true;
}


ExpressionCalculator::ExpressionCalculator(const MyString& str)
{
	expr = parse(str);
}

bool ExpressionCalculator::isTautology() const
{
	return checkAll(expr, true);
}

bool ExpressionCalculator::isTautology()const
{
	return checkAll(expr, true);
}
