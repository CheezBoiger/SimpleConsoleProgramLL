#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>
#include <iomanip>

#include "FileCreator.h"

//in case we have to deal with c-style strings
#ifndef _STR_CONVERT_
#define _str(a) (#a)
#endif

namespace CShell
{
	//-----------------------------------------
	//data type interpreter, to see how the 
	//shell is supposed to interpret data 
	//types.
	//-----------------------------------------
	typedef enum _command_data_type_interpreter_
	{
		_STRING  = 'S',
		_NUMBER  = 'N',
		_UNKNOWN = 'E',
	} __command_data_type_interpret__;

	//--------------------------------------------------------------------------
	//Data structure that holds all variables created. This data structure can 
	//then be used for referencing variables, or redefining them if so desired,
	// like an actual "dictionary".
	//--------------------------------------------------------------------------
	class Dictionary : public __File_Dictionary__
	{
	private:

		std::vector<std::string> _variables;    //key 
		std::vector<std::string> _values;       //value
		std::vector<char>        _data_type;    //how it should be displayed

	protected:

		int searchVariable(std::string &var);
	
	public:

		Dictionary(void) { }
		~Dictionary(void) { _variables.~vector(); _values.~vector(); _data_type.~vector(); }

		void storeVariable(std::string &variable, std::string &value, char type= 'N');

		char getVariableType(std::string &var);

		//TODO(Garcia) Not needed for security reasons.
#if 0
		void changeVariableType(std::string var, char type);
#endif

		bool isVariable(std::string &var);

		std::string getVariable(std::string &var);

		void getDictionaryList(void);
	};

}

#endif /* _DICTIONARY_H_ */