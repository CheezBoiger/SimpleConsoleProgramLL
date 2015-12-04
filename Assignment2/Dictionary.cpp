#include "Dictionary.h"

namespace CShell
{
	/*
	* Searches the dictionary data structure for the variable that is 
	* requested. Returns the index at which it is found
	*/
	int Dictionary::searchVariable(std::string &var)
	{
		for (unsigned int i = 0; i < _variables.size(); i++)
		{
			if (_variables.at(i) == var)
				return i;
		}
		return -1;
	}

	char Dictionary::getVariableType(std::string &var)
	{
		size_t index = searchVariable(var);
		//check if the variable is there, otherwise send error type
		if (index < 0 || index > _variables.size())
			return _UNKNOWN;
		else
			return _data_type.at(index);
	}

	bool Dictionary::isVariable(std::string &var)
	{
		int index = searchVariable(var);
		if (index != -1)
			return true;
		else
			return false;
	}

	void Dictionary::storeVariable(std::string &variable, std::string &value, char type)
	{
		int index = searchVariable(variable);

		if (index != -1)
		{
			_values[index] = value;
			_data_type[index] = type;
		}
		else
		{
			_variables.push_back(variable);
			_values.push_back(value);
			_data_type.push_back(type);
		}
	}

	std::string Dictionary::getVariable(std::string &var)
	{
		int index = searchVariable(var);

		if (index == -1)
			return "NULL";
		else
			return _values.at(index);
	}

	void Dictionary::getDictionaryList(void)
	{
		std::cout << std::endl << std::setw(25) << "variables" << std::setw(25)
			<< "value" << std::setw(25) << "type" << std::endl;
		std::cout << "-----------------------------------------------------------------------------" 
			<< std::endl;
		for (unsigned int i = 0; i < _variables.size(); i++)
		{
			std::cout << std::setw(25) << _variables.at(i) << std::setw(25)
				<< _values.at(i);
			if (_data_type.at(i) == _NUMBER)
				std::cout << std::setw(25) << "Number" << std::endl;
			else if (_data_type.at(i) == _STRING)
				std::cout << std::setw(25) << "String" << std::endl;
		}
		std::cout << std::endl;
	}

} /* CShell */