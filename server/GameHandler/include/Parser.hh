#ifndef GAMEHANDLER_PARSER_HH
#define GAMEHANDLER_PARSER_HH

#include <vector>
#include "File.hh"
#include "GameElement.hpp"

class Parser
{
private:
	std::vector<GameElement> 	_line;
	File*						_file;
	std::string              	data;
	
public:
	Parser();
	Parser(File *);
	~Parser();

	void 						parseTitle();
	void        				parseObstacle();
	void             			parseElement();
	const std::vector<GameElement> &	getLine() const;
};

#endif