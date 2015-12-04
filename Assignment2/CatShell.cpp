#include "CatShell.h"
namespace CShell
{
	//introduction for the shell. 
	void CatShell::intro(void)
	{
		std::cout << version << "\nCopyright (c)  2015"
			<< ", Sugar Cats Software. All rights reserved\n\nUse, distribution, and modification of this source code and/or resulting"
			<< "\nobject code is restricted to educational enhancements to products from"
			<< "\nSugar Cats Corporation. All other use, distribution, or modification is \nprohibited"
			<< " without written permission from Sugar Cats Corporation.\n"
			<< "\nAuthor: Mario Garcia \nInstructor: Professor Zaidi\n"
			<< "\nWelcome to the Fluffy Cat Shell(TM) terminal!!\n";
		std::cout << "\nEnter commands for the shell! (type \"" << _help << "\" for manual, \""
			<< _exit << "\" to quit): \n";
	}

	//help display
	void CatShell::help(void)
	{
		std::cout << "\nPerform postfix expression calculations with this shell!\n"
			<< "\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n"
			<< "\n" << _out <<  " [var] -- Output a variable value from the dictionary.\n\n"
			<< "[var] [postfix expr] =  -- Calculate a postfix expression and store into var\n\n"
			<< _name << " [input] -- Set the shell name to what ever the first word that the shell \nsees.\n\n"
			<< _list <<" -- Display the variables, their values, and data types, that have been \ndefined.\n\n"
			<< _dir << " -- Display the filenames, numbered issues, and owner.\n\n"
			<< _create << " [filename] -- Create a file script and add content into it. Type "
			<< "\"SAVE\"\nto save file and return to command shell.\n\n"
			<< _run << " [filename] -- Search file script in the directory, and run it.\n\n"
			<< _whoami << " -- Check the current user name.\n\n"
			<< _version <<" -- Display current shell version.\n\n"
			<< _shell << " -- Open a new shell.\n\n"
			<< _ID << " -- Get shell ID (so you can see which shell you are currently in)\n\n"
			<< _exit <<" -- Quit the shell terminal.\n\n" 
			<< "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" 
			<< std::endl;
	}

	//begin reading the command
	bool CatShell::readCommand(std::string &command, bool &escape)
	{
		//make sure there are no whitespaces in the command
		if (command.find_first_not_of(' ') != std::string::npos)
		{
			//Generate a string vector to read in the shell
			std::vector<std::string> strings;

			//break command down into tokens to read from
			std::istringstream iss(command);
			std::copy(std::istream_iterator< std::string >(iss),
				std::istream_iterator< std::string >(),
				std::back_inserter(strings));

			//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			//find and combine quoted tokens into one
			std::string variable = "";
			if (strings.size() > 1)
			{
				for (unsigned int i = 0; i < strings.size(); i++)
				{
					if (strings.at(i).front() == '\"')
					{
						int locate = i;

						while (strings.at(i).back() != '\"')
						{
							variable.append(strings.at(i) + " ");

							//if (strings.at(i).back() != '\"')
							i++;
						};
						variable.append(strings.at(i) + " ");
						strings[locate] = variable;
						strings.erase(strings.begin() + (++locate), strings.begin() + (i + 1));
					}
				}
			}
			//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

			//check the type 
			read(strings, escape);
		}

		return escape;
	}

	// Read function, Determine what the user is commanding the shell to do
	void CatShell::read(std::vector< std::string > &strings, bool &escape)
	{
		//OUT command
		if (strings.front() == _out)
		{
			if (strings.size() > 1)
				performOutCommand(strings.at(1));
		}
		else if (strings.front() == _dir)
			dictionary->displayDirectory();
		//RUN command
		else if (strings.front() == _run)
		{
			if (strings.size() > 1 && strings.at(1) != "")
			{
				runFile(strings, escape);
			}
			else
				_DISPLAY(_ERROR_NO_FILE_TO_SEARCH);
		}
		//CREATE command
		else if (strings.front() == _create)
		{
			if (strings.size() > 1 && strings.at(1) != "")
			{
				dictionary->storeFile(strings, name);
			}
			else
				_DISPLAY(_ERROR_FILE_NOT_NAMED);
		}
		//exit command
		else if (strings.front() == _exit)
			escape = true;
		//version command
		else if (strings.front() == _version)
			_DISPLAY(getVersion() + '\n');
		//help command
		else if (strings.front() == _help)
			help();
		// shell command
		else if (strings.front() == _shell)
		{
			activateShell();
		}
		// list command
		else if (strings.front() == _list)
			dictionary->getDictionaryList();
		//name command
		else if (strings.front() == _name)
		{
			if (strings.size() > 1 && strings.at(1) != "")
				setName(strings.at(1));
			else
				_DISPLAY(_ERROR_NO_NAME_INPUT(name));
		}
		//whoami command
		else if (strings.front() == _whoami)
			_DISPLAY(name + "\n");
		// ID command
		else if (strings.front() == _ID)
			cout << "Shell ID: " << getShellID() << endl << endl; /* can not use _DISPLAY ON */
		//Expression storing and variable creation/storing.
		else if (strings.back() == _assign)
		{
			//make sure user is not trying to create a variable named "="
			if (strings.front() != _assign )
			{
				performCalculations(strings, escape);
			}
			else
				_DISPLAY(_ERROR_ASSIGN);
		}
	}

	void CatShell::performCalculations(std::vector< std::string > &strings, bool &escape)
	{
		char type = _NUMBER;
		//flag if the data types in the expression are not compatible with each other.
		bool typeCheck = true;
		//erase the assignment operator
		strings.erase(strings.end() - 1);

		for (unsigned int i = 1; i < strings.size(); i++)
		{
			//check to see if the string is referencing a variable
			if (isVariable(strings.at(i)))
			{
				//check if the variable is the first string in the vector
				if (strings.at(i) == strings.at(1))
					type = dictionary->getVariableType(strings.at(i));
			}
			//Obtain string format of the variable
			if (strings.at(i) == "@")
				type = _STRING;
			else if (strings.at(i) == "#")
				type = _NUMBER;
			else
			{
				//If double quotes found, erase them 
				if (strings.at(i).find('\"') != std::string::npos)
				{
					type = _STRING;
					strings[i].erase(remove(strings[i].begin(),
						strings[i].end(),
						'\"'), strings[i].end());
				}
			}
		}

		std::string expression = checkForVariables(strings, type, typeCheck);

		//determine whether the calcuations are safe to proceed.
		if (!typeCheck)
		{
			//send out an error mang that these types are not compatible
			_DISPLAY(_ERROR_INCOMPATIBLE);
		}
		else
		{
			//evaluate the expression
			expressionEvaluate(type, expression, strings.front());
		}
	}

	std::string CatShell::checkForVariables(std::vector< std::string > &strings, char &type, bool &typeCheck)
	{
		std::string expression = "";
		//Go through vector again and inject variable values in
		for (unsigned int i = 1; i < strings.size(); i++)
		{
			if (isVariable(strings.at(i)))
			{
				//check to make sure that the data types are compatible
				if (dictionary->getVariableType(strings.at(i)) != type)
				{
					//check if the string is not at the end of the vector
					if (strings.at(i) != strings.back())
					{
						if (type == _STRING)
						{
							if (strings.at(i + 1) != "@")
								typeCheck = false;
						}
						else if (type == _NUMBER)
						{
							if (strings.at(i + 1) != "#")
								typeCheck = false;
						}
					}
					else
						typeCheck = false;
				}

				strings[i] = dictionary->getVariable(strings.at(i));
			}
			//skip over the symbols # and @
			if (strings.at(i) != "#" && strings.at(i) != "@")
			{
				expression += strings.at(i) + " ";
			}
		}

		return expression;
	}

	//Sends out the values of a specified variable.
	void CatShell::performOutCommand(std::string var)
	{
		//type is assigned whatever the dictionary references the variable as.
		char type(dictionary->getVariableType(var));
		std::string value(dictionary->getVariable(var));

		if (type == _NUMBER)
		{
			float buffer = stof(value);

			_DISPLAY(buffer);
		}
		else if (type == _STRING)
		{
			_DISPLAY(value);
		}
		else
			//Send out an exception that the variable name is not in the data structure
			_DISPLAY(_ERROR_VAR_NON_EXIST(var));
	}

	//Run the file once the user specifies it.
	void CatShell::runFile(std::vector< std::string > &strings, bool &escape)
	{
		//check to see if the user is not specifying more than one file
		if (strings.size() > 2)
		{
			_DISPLAY(_ERROR_MORE_THAN_ONE_COMMAND);
		}
		else
		{
			std::string command;
			std::ifstream file;
			file.open(strings.back());
			if (file.is_open())
			{
				while (getline(file, command))
				{
					readCommand(command, escape);
				}
				file.close();
			}
			else /* send out error that the file was not found */
				_DISPLAY(_ERROR_FILE_NOT_FOUND(strings.back()));
		}
	}

	//Check if the string is a reference to a variable
	bool CatShell::isVariable(std::string var)
	{
		return dictionary->isVariable(var);
	}

	//Evaluate the expression, depending on the data type
	void CatShell::expressionEvaluate(char type, std::string expression, std::string var)
	{
		//calculate the expression
		calc->evaluate(expression, type);
		dictionary->storeVariable(var, calc->getResult(), type);
	}

	/* Activate the shell */
	inline void activateShell(void)
	{
		//check to see if the user is trying to escape the shell!
		bool escape = false;
		//Create a shell object
		CatShell *shell(new CatShell());
		string expression;

		shell->intro();
		// Enter the shell loop.
		while (!escape)
		{
			//Pretend you are root with root access
			cout << "[" << shell->getName() << "] ~ $ ";
			getline(cin, expression);
			shell->readCommand(expression, escape);
		}

		delete shell;
		shell = NULL;
	}
} /* CShell */
