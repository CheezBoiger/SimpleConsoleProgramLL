#ifndef _CAT_SHELL_H_
#define _CAT_SHELL_H_

#pragma once

#include "ProjectHeaders.h"


#ifndef _STD_LIBRARY_
//std library scope resolution operator to display
#define _DISPLAY(a) (std::cout << a << std::endl)
#endif

namespace CShell
{
	static int shellID = 1;
	//-----------------------------------------------------------------------
	//Cat Shell acts a a translater, since being the middle man between the
	//user and the expression calculator and dictionary it surely must be the 
	//one to help with proper communication. The shell is supposed to obtain user
	//input and translate it, to the best of its ability, in order to figure out 
	//how the user wants to communicate to the data structure. 
	//-----------------------------------------------------------------------
	class CatShell : private __keywords_reserved__
	{
	private:
		//pointer to a dictionary data structure
		Dictionary *dictionary;

		Postfix::ExpressionCalculator *calc;

		std::string name;
	
		const std::string version = "Fluffy Cat Shell v3.0_3";

		std::string checkForVariables(std::vector< std::string > &strings, char &type, bool &typeCheck);

		void read(std::vector< std::string > &v, bool &escape);

		int ID;

	protected:

		//do the post fix calculations
		void performCalculations(std::vector< std::string > &strings, bool &escape);

		//performs the out command output
		void performOutCommand(std::string var);
		
		//checks if the string is a variable
		bool isVariable(std::string var);

		//expression calculation evaluation
		void expressionEvaluate(char type, std::string expression, std::string var);

		//runs the file that user specifies
		void runFile(std::vector< std::string > &strings, bool &escape);

		//get the current version of this shell
		std::string getVersion(void) { return version; }

	public:
	
		//Constructor/Destructor
		CatShell(void) : name("anonymous"), dictionary(new Dictionary()), calc(new Postfix::ExpressionCalculator()) { ID = shellID++; }
		virtual ~CatShell(void) { delete dictionary; dictionary = NULL; delete calc; calc = NULL; shellID--; }

		//Void functions used to display info or perform a task
		void intro(void);
		void help(void);
		void setName(std::string name) { this->name = name; }
		int getShellID() { return ID; }

		bool readCommand(std::string &command, bool &escape);

		std::string getName(void) { return name; }

	};

	inline void activateShell(void);
} /* Fluffy Cat Shell */



#endif /* _CAT_SHELL_H_ */