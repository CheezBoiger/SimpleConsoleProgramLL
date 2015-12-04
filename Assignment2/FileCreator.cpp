#include "FileCreator.h"

namespace CShell
{
	//Default Constructor
	__File_Dictionary__::__File_Dictionary__(void)
	{
		update();
	}

	void __File_Dictionary__::update(void)
	{
		if (files.size() > 0)
		{
			for (size_t i = 0; i < files.size(); i++)
			{
				delete files[i];
				files[i] = NULL;
			}
		}
		files.clear();
		//check if saved_files exists. If so, read from there
		std::ifstream file;
		file.open(saved_files);

		std::string words;
		if (file.is_open())
		{
			while (getline(file, words))
			{
				__file_information__ *info(new __file_information__());
				//Generate a string vector to read
				std::vector<std::string> strings;

				//break command down into tokens to read from
				std::istringstream iss(words);
				std::copy(std::istream_iterator< std::string >(iss),
					std::istream_iterator< std::string >(),
					std::back_inserter(strings));

				//store the tokens into the file information struct
				info->filename = strings.front();
				info->file_number = std::stoi(strings.at(1));
				info->owner = strings.back();
				//store into the directory
				files.push_back(info);
			}
			file.close();
		}
	}

	//Destructor
	__File_Dictionary__::~__File_Dictionary__(void)
	{
		for (size_t i = 0; i < files.size(); i++)
		{
			delete files[i];
			files[i] = NULL;
		}
		files.~vector();
	}

	//Create the name of the file, then create it.
	std::string __File_Dictionary__::createFile(std::vector< std::string > &strings)
	{
		std::string filename = "";
		for (size_t i = 1; i < strings.size(); i++)
		{
			filename.append(strings.at(i));
		}

		return filename;
	}
	
	//Write the file
	__file_information__* __File_Dictionary__::writeFile(std::string &filename, std::string &owner)
	{
		std::cout << "type \"SAVE\" to save and exit the file editor\n" << std::endl;
		std::ofstream file;
		std::string command;
		file.open(filename);
		do
		{
			std::cout << "> ";
			getline(std::cin, command);

			if (command != "SAVE")
				file << command << std::endl;

		} while (command != "SAVE");
		file.close();

		__file_information__* info(new __file_information__());
		info->filename = filename;
		info->file_number = number++;
		info->owner = owner;

		return info;
	}

	//Store the file into saved_files, this file will record all scripts created
	void __File_Dictionary__::storeFile(std::vector< std::string > &strings, std::string owner)
	{
		files.push_back(writeFile(createFile(strings), owner));

		std::ofstream file;
		file.open(saved_files, std::fstream::app);
		file << files.back()->filename << " " << files.back()->file_number
			<< " " << files.back()->owner << std::endl;
		file.close();
	}

	//Display the list of files in the directory
	void __File_Dictionary__::displayDirectory(void)
	{
		update();
		std::cout << std::endl << std::setw(25) << "File" << std::setw(25) << "Number" << std::setw(25)
			<< "Owner" << std::endl;
		std::cout << "-----------------------------------------------------------------------------"
			<< std::endl;
		for (size_t i = 0; i < files.size(); i++)
		{
			std::cout << std::setw(25) <<  files.at(i)->filename
				<< std::setw(25) << files.at(i)->file_number
				<< std::setw(25) << files.at(i)->owner
				<< std::endl;
		}
		std::cout << std::endl;
		std::cout << "number of files: " << files.size() << std::endl << std::endl;
	}
	
	// TODO(Garcia): Make sure to fix the delete function before implementing it into the shell 
	// commands.
	bool __File_Dictionary__::deleteFile(std::string &filename)
	{
		std::ifstream file;
		std::string words;
		std::vector<std::string> strings;
		std::ofstream temp;

		file.open(filename);

		if (!file.fail())
		{
			std::remove(filename.c_str());
			
		}
		else
		{
			file.close();
			return false;
		}

		file.close();
		file.open(saved_files);
		temp.open("temp.txt");

		if (file.is_open())
		{

			while (getline(file, words))
			{
				//break command down into tokens to read from
				std::istringstream iss(words);
				std::copy(std::istream_iterator< std::string >(iss),
					std::istream_iterator< std::string >(),
					std::back_inserter(strings));

				if (strings.front() == filename)
				{

				}
			}
			file.close();
			std::remove(saved_files.c_str());

		}

		return true;
	}
}