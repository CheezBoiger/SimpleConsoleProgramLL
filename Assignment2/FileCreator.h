#ifndef _FILE_CREATOR_H_
#define _FILE_CREATOR_H_

#pragma once

#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <cstdio>

namespace CShell
{

	//-----------------------------------------------------------------------------
	//Cat shell, since dictionary doesn't know anything about this class,
	//needs to know what words are reserved, that way it has a way of properly
	//communicating to the dictionary that it points to, as well as the calculator
	//that it creates.
	//-----------------------------------------------------------------------------
	typedef struct __keywords_reserved__
	{
		std::string _exit    = "exit";
		std::string _out     = "OUT";
		std::string _create  = "CREATE";
		std::string _run     = "RUN";
		std::string _dir     = "DIR";
		std::string _shell   = "shell";
		std::string _version = "version";
		std::string _whoami  = "whoami";
		std::string _help    = "help";
		std::string _name    = "name";
		std::string _assign  = "=";
		std::string _list    = "VARLIST";
		std::string _ID      = "ID";
	} __reserved__;

	//--------------------------------------------------------------------------
	// File information that will be used and stored into the file dictionary.
	// This information will then be displayed at the user's will.
	//--------------------------------------------------------------------------
	typedef struct __file_information__
	{
		int file_number;
		std::string filename;
		std::string owner;
	} __file_info__;

	//-----------------------
	// Abstract File class
	//-----------------------
	class __File_Creator__
	{
	private:

	protected:
	
		virtual std::string createFile(std::vector< std::string > &strings) = 0;

		virtual __file_information__ *writeFile(std::string &filename, std::string &owner) = 0;
	
		virtual void update(void) = 0;

		virtual bool deleteFile(std::string &filename) = 0;

	public:

		virtual ~__File_Creator__(void) {}
	}; // __File__ abstract class, CAN NOT instantiate
	
	static int number = 1;

	//---------------------------------------------------------------------
	// File dictionary holds information of files that were created.
	// These files should actually be scripts for the shell to run.
	//---------------------------------------------------------------------
	class __File_Dictionary__ : public __File_Creator__
	{
	private:

		std::vector< __file_information__ *> files;
		/* files will be saved, yet one file will record the info of all files created */
		std::string saved_files = "saved_files.txt"; 

	protected:

		virtual std::string createFile(std::vector< std::string > &strings);

		virtual __file_information__ *writeFile(std::string &filename, std::string &owner);

		void update(void);

	public:

		virtual ~__File_Dictionary__(void);
		__File_Dictionary__(void);

		void storeFile(std::vector< std::string > &strings, std::string owner);
		void displayDirectory(void);
		bool deleteFile(std::string &filename); // Not implemented yet, this function is not 
		                                        // ready.

	}; // __File_Dictionary__
}

#endif // _FILE_CREATOR_H_
