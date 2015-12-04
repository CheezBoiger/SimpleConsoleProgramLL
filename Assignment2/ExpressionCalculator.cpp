#include "ExpressionCalculator.h"

namespace Postfix
{
	/**
	@param op The operator to be tested for operator status...
	@return The boolean true if the character is an operator. False otherwise.
	*/
	bool isOperator(char &op)
	{
		if (op == '-' || op == '+' || op == '*' || op == '/')
			return true;

		return false;
	}


	/**
	* Performs the necessary calculations depending on what the operator is...
	* @param opLeft The left hand operand.
	* @param opRight The right hand operand.
	* @param &op the operator reference!
	* @return The calculations!! In Floats!!
	*/
	float ExpressionCalculator::performOperation(float opLeft, float opRight
		, const char &op)
	{

		switch (op)
		{
		case '*':
			return (opLeft * opRight);
		case '/':
			return (opLeft / opRight);
		case '+':
			return (opLeft + opRight);
		case '-':
			return (opLeft - opRight);
		default:
			return NULL;
		}
	}

	void ExpressionCalculator::performExpressionNumberCalc(std::string &postfix)
	{
		CustomStack<float> stack;
		char* chptr = NULL;
		char* pch = strtok_s((char *)postfix.c_str(), " ", &chptr);
		while (pch != NULL)
		{
			//check if the token is an operator
			if (isOperator(*pch))
			{
				//perform the calculations and store into the stack
				float solution = performOperation(stack.pop(), stack.pop(), *pch);
				stack.push(solution);
			}
			else
			{
				//store the token (dont forget to convert first!!) into the stack
				stack.push(static_cast<float>(atof(pch)));
			}
			pch = strtok_s(NULL, " ", &chptr);
		}
		result = std::to_string(stack.pop());
		stack.~CustomStack();
	}

	//------------------------------------------------------------------
	//Performs the necessary string expression calculations.
	//------------------------------------------------------------------
	void ExpressionCalculator::performExpressionStringCalc(std::string &postfix)
	{
		std::vector<std::string> stack;
		char* chptr = NULL;
		char* pch = strtok_s((char*)postfix.c_str(), " ", &chptr);
		while (pch != NULL)
		{
			//check if the token is an operator, preferably plus. Only works for appending
			if (isOperator(*pch) && (*pch) == '+')
			{
				std::string solution;
				//check if there is only one string in the stack
				if (stack.size() == 1)
				{
					solution = stack.back() + " ";
					stack.pop_back();
				}
				else
				{
					//dual string appending
					std::string right = stack.back();
					stack.pop_back();
					std::string left = stack.back();
					stack.pop_back();
					solution = " " + left + " " + right;
				}
				stack.push_back(solution);
			}
			else
			{
				//push strings into the stack if all else does not go well
				stack.push_back(pch);
			}
			pch = strtok_s(NULL, " ", &chptr);
		}
		result = "";

		//all strings left over from the algorithm shall be thrown into the result.
		for (unsigned int i = 0; i < stack.size(); i++)
			result += stack[i] + " ";

		//clean up
		stack.~vector();
	}

	//Peform evaluation of the postfix expression
	void ExpressionCalculator::evaluate(std::string &expression, const char &type)
	{
		if (expression.size() > 0)
		{
			if (type == 'N')
				performExpressionNumberCalc(expression);
			else if (type == 'S')
				performExpressionStringCalc(expression);
			else
				result = "0";
		}
		else
			result = "0";
	}
} /* Postfix */






