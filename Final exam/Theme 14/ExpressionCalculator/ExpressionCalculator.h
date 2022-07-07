#pragma once
#include <iostream>
#include <exception>
#include "MyString.h"

const char AND = '^';
const char OR = 'v';
const char IFF = '=';
const char XOR = '+';
const char IMPL = '>';
const char NEG = '!';

class ExpressionCalculator
{
	class BooleanExpr
	{
	public:
		bool vars[26] = { false };
		size_t varsCount;

		struct BooleanInterpretation
		{
			bool values[26] = { false };
			BooleanInterpretation() {};

			void setValue(char ch, bool value)
			{
				if (!(ch <= 'Z' && ch >= 'A'))
					throw "Error";
				values[ch - 'A'] = value;
			}

			bool getValue(char ch) const
			{
				if (!(ch <= 'Z' && ch >= 'A'))
					throw "Error";

				return values[ch - 'A'];
			}
		};

		virtual ~BooleanExpr() = default;
		virtual bool eval(const BooleanInterpretation& interpret) const = 0;
		virtual BooleanExpr* clone() const = 0;
	};

	class Variable :public BooleanExpr
	{
		char ch;
	public:

		Variable(char ch) : ch(ch)
		{
			vars[ch - 'A'] = true;
			varsCount = 1;
		}

		bool eval(const BooleanInterpretation& interpret) const
		{
			return interpret.getValue(ch);
		}

		BooleanExpr* clone() const
		{
			return new Variable(*this);
		}
	};

	class BinaryOperation : public BooleanExpr
	{
		BooleanExpr* left;
		char op;
		BooleanExpr* right;
	public:
		BinaryOperation(BooleanExpr* left, char op, BooleanExpr* right) : left(left), op(op), right(right)
		{
			for (size_t i = 0; i < 26; i++)
			{
				vars[i] = left->vars[i] || right->vars[i];
				if (vars[i])
					varsCount++;
			}
		}

		bool eval(const BooleanInterpretation& interpret) const
		{
			switch (op)
			{
			case AND: return left->eval(interpret) && right->eval(interpret);
			case OR: return left->eval(interpret) || right->eval(interpret);
			default: return false;
			}
		}

		BooleanExpr* clone() const
		{
			return new BinaryOperation(left->clone(), op, right->clone());
		}

		~BinaryOperation()
		{
			delete left;
			delete right;
		}
	};

	class UnaryOperation :public BooleanExpr
	{
		char op;
		BooleanExpr* expr;
	public:
		UnaryOperation(char op, BooleanExpr* expr) : op(op), expr(expr)
		{
			for (size_t i = 0; i < 26; i++)
			{
				vars[i] = expr->vars[i];
				if (vars[i])
					varsCount++;
			}
		}

		bool eval(const BooleanInterpretation& interpret) const
		{
			if (op == NEG)
				return !(expr->eval(interpret));
			else
				return false;
		}

		BooleanExpr* clone() const
		{
			return new UnaryOperation(op, expr->clone());
		}

		~UnaryOperation()
		{
			delete expr;
		}
	};

	BooleanExpr* expr;
	void copyFrom(const ExpressionCalculator& other);
	void free();

	bool checkAll(BooleanExpr* expr, bool value) const;
	BooleanExpr::BooleanInterpretation convertFromNumber(size_t number, bool vars[26]) const;
public:
	ExpressionCalculator(const MyString& str);
	ExpressionCalculator(const ExpressionCalculator& other);
	ExpressionCalculator& operator=(const ExpressionCalculator& other);
	~ExpressionCalculator();

	bool isTautology() const;
	bool isContradiction() const;

	friend ExpressionCalculator::BooleanExpr* parse(const MyString& str);
};
