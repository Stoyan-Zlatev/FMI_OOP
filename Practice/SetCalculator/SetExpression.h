#pragma once
#include "GlobalConstants.h"
#include "Utils.h"

class SetExpression
{
public:
	bool vars[ALPHABETLENGTH] = { false };
	size_t countVars = 0;


	struct Element
	{
		bool values[ALPHABETLENGTH] = { false };
		Element() {}

		void set(char ch, bool value)
		{
			if (!isCapitalLetter(ch))
				throw "error";

			values[getLetterPosition(ch)] = value;
		}
		bool get(char ch) const
		{
			if (!isCapitalLetter(ch))
				throw "error";
			return 	values[getLetterPosition(ch)];
		}
	};

	virtual bool eval(const Element& interpret) const = 0;

	virtual SetExpression* clone() const = 0;
	virtual ~SetExpression() = default;

};