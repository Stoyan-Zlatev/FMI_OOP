#include "SetCalculator.h"

void SetCalculator::copyFrom(const SetCalculator& other)
{
	expr = other.expr->clone();
}

void SetCalculator::free()
{
	delete expr;
}

bool isOperator(char ch)
{
	return ch == AND || ch == OR || ch == IFF || ch == IMPL || ch == XOR || ch == NEG;
}

SetExpression* parse(const MyString& str)
{

	if (str.getSize() == 1)
	{
		return new SetCalculator::Variable(str[0]);
	}

	MyString strWithoutBrackets = str.subString(1, str.getSize() - 2); //We remove the brackets.


	int countBrackets = 0;
	for (size_t i = 0; i < strWithoutBrackets.getSize(); i++) //we start searching for the operation.
	{														 // then we split to two expressions
		if (strWithoutBrackets[i] == '(')
		{
			countBrackets++;
		}
		else if (strWithoutBrackets[i] == ')')
		{
			countBrackets--;
		}
		else if (isOperator(strWithoutBrackets[i]) && countBrackets == 0)
		{
			if (strWithoutBrackets[i] == NEG)
			{
				return new SetCalculator::UnaryOperation('!', parse(strWithoutBrackets.subString(i + 1, strWithoutBrackets.getSize() - 1)));
			}
			else
			{
				return new SetCalculator::BinaryOperation(parse(strWithoutBrackets.subString(0, i - 1)), strWithoutBrackets[i],
					parse(strWithoutBrackets.subString(i + 1, strWithoutBrackets.getSize() - 1)));
			}
		}

	}
}

SetCalculator::SetCalculator(const MyString& str)
{
	expr = parse(str);

}
SetCalculator::SetCalculator(const SetCalculator& other)
{
	copyFrom(other);
}
SetCalculator& SetCalculator::operator=(const SetCalculator& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
SetCalculator::~SetCalculator()
{
	free();
}

SetExpression::Element SetCalculator::convertFromNumber(size_t number, bool vars[ALPHABETLENGTH]) const
{
	SetExpression::Element inter;
	
	for (int i = 25; i >= 0; i--)
	{
		if (vars[i])
		{
			if (number % 2 == 1)
				inter.set('A' + i, 1);
			number /= 2;
		}
	}
	return inter;
}

SetExpression::Element SetCalculator::convertFromElement(const SetExpression::Element& element, bool vars[26]) const
{
	SetExpression::Element inter;

	for (int i = 25; i >= 0; i--)
	{
		if (vars[i])
		{
			inter.set('A' + i, element.get(i + 'A'));
		}
	}
	return inter;
}

bool SetCalculator::isElementIn(const SetExpression::Element& element) const
{
	if (!expr->eval(convertFromElement(element, expr->vars)))
		return false;
	
	return true;
}

bool SetCalculator::operator==(const SetCalculator& other) const
{
	return compareSets(expr, other.expr);
}

bool SetCalculator::compareSets(SetExpression* expr,SetExpression* other) const
{ 
	size_t varsCount = expr->countVars;

	if (varsCount != other->countVars)
		return false;

	size_t intersCount = 1 << varsCount; ///!!!!! 2^varsCount

	if (!compareSetsVariables(expr, other))
		return false;

	for (int i = 0; i < intersCount; i++)
	{
		if (expr->eval(convertFromNumber(i, expr->vars)) != other->eval(convertFromNumber(i, other->vars)))
			return false;
	}
	return true;
}

bool SetCalculator::compareSetsVariables(SetExpression* expr, SetExpression* other) const
{
	for (size_t i = 0; i < ALPHABETLENGTH; i++)
	{
		if (expr->vars[i] != other->vars[i])
			return false;
	}

	return true;
}
