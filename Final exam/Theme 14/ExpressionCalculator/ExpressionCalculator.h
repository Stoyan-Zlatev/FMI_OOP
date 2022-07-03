#include <iostream>
#include <exception>
#include "MyString.h"

const char AND = '^';
const char OR = 'v';
const char IMPL = '>'; //=>
const char IFF = '='; // <=>
const char XOR = '+';
const char NEG = '!';
const size_t ALPABET_LETTERS = 26;

class ExpressionCalculator
{
	class BooleanExpr
	{
	public:
		const bool* getVarsArr() const
		{
			bool* arr = new bool[ALPABET_LETTERS];

			for (size_t i = 0; i < ALPABET_LETTERS; i++)
				arr[i] = false;

			getVars(arr);
			return arr;
		}

		virtual void getVars(bool*) const = 0;
		virtual BooleanExpr* clone() const = 0;
		virtual bool eval(bool values[ALPABET_LETTERS]) const = 0;
		
		virtual ~BooleanExpr() = default;
	};

	class Variable : public BooleanExpr
	{
		char ch;
	public:
		Variable(char ch) : ch(ch) {} ///only CAPITALS

		bool eval(bool values[ALPABET_LETTERS]) const override
		{
			return values[ch - 'A'];
		}

		BooleanExpr* clone() const override
		{
			return new Variable(*this);
		}

		void getVars(bool* vars)const override
		{
			vars[ch - 'A'] = true;
		}
	};

	class BinaryOperation : public BooleanExpr
	{
		BooleanExpr* left;
		char op;
		BooleanExpr* right;
	public:
		BinaryOperation(BooleanExpr* left, char op, BooleanExpr* right) : left(left), op(op), right(right) {}
		BinaryOperation(const BinaryOperation&) = delete;
		BinaryOperation& operator=(const BinaryOperation&) = delete;

		bool eval(bool values[26]) const override
		{
			switch (op)
			{
			case OR: return  left->eval(values) || right->eval(values);
			case AND: return left->eval(values) && right->eval(values);
			case IMPL: return !left->eval(values) || right->eval(values);
			case IFF: bool first = left->eval(values); bool second = right->eval(values); return first == second;
			case XOR: bool first = left->eval(values); bool second = right->eval(values); return first != second;
			default: return false;
			}
		}

		BooleanExpr* clone() const override
		{
			return new BinaryOperation(left->clone(), op, right->clone());
		}

		virtual void getVars(bool* vars) const override
		{
			left->getVars(vars);
			right->getVars(vars);
		}

		~BinaryOperation()
		{
			delete left;
			delete right;
		}
	};

	class UnaryOperation : public BooleanExpr
	{
		char ch; //!
		BooleanExpr* expr;

	public:
		UnaryOperation(char ch, BooleanExpr* expr) : ch(ch), expr(expr) {}
		UnaryOperation(const UnaryOperation&) = delete;
		UnaryOperation& operator=(const UnaryOperation&) = delete;

		BooleanExpr* clone() const override
		{
			return new UnaryOperation(ch, expr->clone());
		}

		virtual void getVars(bool* vars) const override
		{
			expr->getVars(vars);
		}

		bool eval(bool values[ALPABET_LETTERS]) const
		{
			if (ch == '!')
			{
				return !expr->eval(values);
			}
			else
			{
				// 
				return false;
			}
		}
		~UnaryOperation()
		{
			delete expr;
		}
	};

	void convertFromNumber(size_t number, const bool vars[ALPABET_LETTERS], bool values[ALPABET_LETTERS]) const;
	bool checkAll(BooleanExpr* expr, bool value) const;

	BooleanExpr* expr;
	void copyFrom(const ExpressionCalculator& other);
	void free();

public:
	ExpressionCalculator(const MyString& str);
	ExpressionCalculator(const ExpressionCalculator& other);
	ExpressionCalculator& operator=(const ExpressionCalculator& other);
	~ExpressionCalculator();

	bool isTautology() const;
	bool isContradiction() const;

	friend BooleanExpr* parse(const MyString& str);
};
