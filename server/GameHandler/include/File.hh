#ifndef GAMEHANDLER_FILE_HH
#define GAMEHANDLER_FILE_HH

#include <fstream>
#include <iostream>
#include <string>

class File
{
private:

	std::string 		_name;
	std::string			_data;
	
public:
	File(const std::string&);
	File(const File&);
	File();
	~File();
	
	bool				write(const std::string&);
	bool				read();
	const std::string&	getData() const;
	const std::string& 	getName() const;
	void 				flush();
};

#endif