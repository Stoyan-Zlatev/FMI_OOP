#include <iostream>
#include <exception>
#include "MyString.h"

const char AND = '^';
const char OR = 'v';
const char IMP = '>';
const char XOR = '+';
const char NEG = '!';
const char IFF = '=';

class ExpressionCalculator
{
	class BooleanExpr
	{
	public:
		bool vars[26] = { false };
		size_t countVars;

		struct BooleanInterpretation
		{
			bool values[26] = { false };

			BooleanInterpretation() {}

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

		virtual bool eval(const BooleanInterpretation& interpret) const = 0;
		virtual BooleanExpr* clone() const = 0;
		virtual ~BooleanExpr() = default;
	};

	class Variable : public BooleanExpr
	{
		char ch;
	public:
		Variable(char ch) : ch(ch)
		{
			vars[ch - 'A'] = true;
			countVars = 1;
		}

		bool eval(const BooleanInterpretation& interpret) const override
		{
			return interpret.getValue(ch);
		}

		BooleanExpr* clone() const override
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
		BinaryOperation(BooleanExpr* left, char op, BooleanExpr* right) : left(left), right(right), op(op)
		{
			for (size_t i = 0; i < 26; i++)
			{
				vars[i] = left->vars[i] || right->vars[i];
				if (vars[i])
					countVars++;
			}
		}

		bool eval(const BooleanInterpretation& interpret) const override
		{
			switch (op)
			{
			case AND:return left->eval(interpret) && right->eval(interpret);
			case OR:return left->eval(interpret) || right->eval(interpret);
			case IMP: return !left->eval(interpret) || right->eval(interpret);
			case IFF: bool first = left->eval(interpret); bool second = right->eval(interpret); return first == second;
			case XOR:bool first = left->eval(interpret); bool second = right->eval(interpret); return first != second;
			default: return false;
			}
		}
		BooleanExpr* clone() const override
		{
			return new BinaryOperation(left->clone(), op, right->clone());
		}

		~BinaryOperation()
		{
			delete left;
			delete right;
		}
	};

	class UnaryOperation : public BooleanExpr
	{
		char op;
		BooleanExpr* expr;
	public:
		UnaryOperation(BooleanExpr* expr, char op) : expr(expr), op(op)
		{
			for (size_t i = 0; i < 26; i++)
			{
				vars[i] = expr->vars[i];
				if (vars[i])
					countVars++;
			}
		}

		bool eval(const BooleanInterpretation& interpret) const override
		{
			if (op == NEG)
				return !expr->eval(interpret);
			else
				return false;
		}

		BooleanExpr* clone() const override
		{
			return new UnaryOperation(expr->clone(), op);
		}

		~UnaryOperation()
		{
			delete expr;
		}
	};

	BooleanExpr* expr;
	BooleanExpr::BooleanInterpretation convertFromNumber(size_t number, bool vars[26]) const;
	bool checkAll(BooleanExpr* expr, bool value) const;

	void copyFrom(const ExpressionCalculator& other);
	void free();

public:
	ExpressionCalculator(const MyString& str);
	ExpressionCalculator(const ExpressionCalculator& other);
	ExpressionCalculator& operator=(const ExpressionCalculator& other);
	~ExpressionCalculator();

	bool isTautology() const;
	bool isContradiction() const;

	friend ExpressionCalculator::BooleanExpr* parse(const MyString& str);
};
