#ifndef _EXPRESSION_CALC_H_
#define _EXPRESSION_CALC_H_

#pragma once 

#include "CustomStack.h"
#include <string>

namespace Postfix
{
	//-------------------------------------------------------
	// The object that will perform the postfix calculations
	//-------------------------------------------------------
	class ExpressionCalculator
	{
	private:
		//---------------------------------------------------------
		//Class variable
		//---------------------------------------------------------

		std::string result;         // the result after calculations

		//------------------------------------------------------------
		//Function declarations 
		//------------------------------------------------------------


		//performs the necessary operation between the left and right operands
		float performOperation(float opLeft, float opRight, const char& op);

		std::string appendString(std::string opLeft, std::string opRight);

		//stores the expression inside the object
		//@param expression - pointer to a character array expression
		inline void storeExpression(std::string expression);

		//Performs calculations on string data type expressions
		void performExpressionStringCalc(std::string &postfix);

		//performs calculations on float data type expressions
		void performExpressionNumberCalc(std::string &postfix);

	protected:
		//nothing to protect!
	public:
		//constuctor that takes the pointer to array as a parameter
		ExpressionCalculator(void) {}

		//TODO(Garcia) Do not forget to delete and set the dangling pointer to NULL!! or nullptr...
		~ExpressionCalculator(void) {}

		std::string getResult(void) { return result; }

		//algorithm to perform the calculations!
		void evaluate(std::string &expression, const char &type);

	}; /* ExpressionCalculator */

	//figure out whether a character is an operator
	bool isOperator(char& op);

}
#endif /* _EXPRESSION_CALC_H_ */