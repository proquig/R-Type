#include "File.hh"

File::File() : _name("map.txt")
{
}

File::File(const std::string& name) : _name(name) {
}

File::File(const File& file) {
	_name = file.getName();
	_data = file.getData();
}

File::~File()
{
}

bool				File::write(const std::string& data)
{
	std::ofstream file(_name);
	
	if (file.is_open())
	{
		file << data;
		file.close();
		return true;
	}
	std::cerr << "Unable to open file" << std::endl;
	return false;
}

bool				File::read()
{
	std::ifstream	file(_name);
	std::string		line;
	
	if (file.is_open())
	{
		while(getline(file, line))
		{
			_data += line + "\n";
		}
		file.close();
		return true;
	}
	std::cerr << "Unable to open file" << std::endl;
	return false;
} 

const std::string&	File::getData() const
{
	return _data;
}

const std::string& 	File::getName() const 
{
	return _name;
}

void 				File::flush() 
{
	_data = "";
}