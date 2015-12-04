#ifndef _PROJECT_HEADERS_H_
#define _PROJECT_HEADERS_H_

#pragma once 

#include "Dictionary.h"
#include "ExpressionCalculator.h"
#include <map>

using namespace std;
using namespace Postfix;
using namespace CShell;

//Errors and stuff
/* TODO(Garcia): Generally not a good idea to put errors as macros: consider a map maybe? */
#ifndef _ERROR_MESSAGE_
#define _ERROR_FILE_NOT_FOUND(a)                        ("File \"" + a + "\" was not found.\n")
#define _ERROR_NO_FILE_TO_SEARCH                         ("No file was specified to search.\n")
#define _ERROR_MORE_THAN_ONE_COMMAND ("More than one command detected. Specify one command.\n")
#define _ERROR_INCOMPATIBLE                               ("Incompatible types to calculate\n")
#define _ERROR_ASSIGN                ("You must assign a variable name to your declaration.\n")
#define _ERROR_VAR_NON_EXIST(a)               ("No variable by the name of " + a + " exists\n")
#define _ERROR_NO_NAME_INPUT(a)                 ("No input detected. Resolving to " + a + "\n")
#define _ERROR_FILE_NOT_NAMED                    ("No name detected. Unable to create file.\n")
#endif

#endif /* _PROJECT_HEADERS_H_ */