#include <iostream>
#include <exception>
#include "MyString.h"
#include "GlobalConstants.h"
#include "Utils.h"
#include "SetExpression.h"

class SetCalculator
{
	class Variable : public SetExpression
	{
		char ch;
	public:
		Variable(char ch) : ch(ch)
		{
			vars[ch - 'A'] = true;
			countVars = 1;
		} 

		bool eval(const Element& interpret) const override
		{
			return interpret.get(ch);
		}
		SetExpression* clone() const override
		{
			return new Variable(*this);
		}

	};

	class BinaryOperation : public SetExpression
	{
		SetExpression* left;
		char op;
		SetExpression* right;
	public:
		BinaryOperation(SetExpression* left, char op, SetExpression* right) : left(left), op(op), right(right)
		{
			for (int i = 0; i < 26; i++)
			{
				vars[i] = left->vars[i] || right->vars[i];
				if (vars[i])
					countVars++;

			}
		}

		bool eval(const Element& interpret) const override
		{

			switch (op)
			{
			case 'v': return  left->eval(interpret) || right->eval(interpret);
			case '^': return left->eval(interpret) && right->eval(interpret);
			default: return false;
				break;
			}
		}

		SetExpression* clone() const override
		{
			return new BinaryOperation(left->clone(), op, right->clone());
		}

		~BinaryOperation()
		{
			delete left;
			delete right;
		}
	};

	class UnaryOperation : public SetExpression
	{
		char ch; 
		SetExpression* expr;

	public:
		UnaryOperation(char ch, SetExpression* expr) : ch(ch), expr(expr)
		{
			for (int i = 0; i < 26; i++)
			{
				vars[i] = expr->vars[i];
				if (vars[i])
				{
					countVars++;
				}
			}
		}

		SetExpression* clone() const override
		{
			return new UnaryOperation(ch, expr->clone());
		}

		bool eval(const Element& interpret) const
		{
			if (ch == '!')
			{
				return !expr->eval(interpret);
			}
			else
			{
				return false;
			}
		}
		~UnaryOperation()
		{
			delete expr;
		}
	};

	SetExpression::Element convertFromNumber(size_t number, bool vars[26]) const;
	SetExpression::Element convertFromElement(const SetExpression::Element& element, bool vars[26]) const;
	bool compareSets(SetExpression* expr, SetExpression* other) const;
	bool compareSetsVariables(SetExpression* expr, SetExpression* other) const;

	SetExpression* expr;
	void copyFrom(const SetCalculator& other);
	void free();

public:
	SetCalculator(const MyString& str);
	SetCalculator(const SetCalculator& other);
	SetCalculator& operator=(const SetCalculator& other);
	~SetCalculator();

	bool isElementIn(const SetExpression::Element& element) const;
	bool operator==(const SetCalculator& other) const;

	friend SetExpression* parse(const MyString& str);
};