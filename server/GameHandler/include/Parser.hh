#ifndef GAMEHANDLER_PARSER_HH
#define GAMEHANDLER_PARSER_HH

#include <vector>
#include "File.hh"
#include "AElement.hh"

class Parser
{
private:
	File*						        _file;
	std::vector<AElement*> 		        _line;
	AElement*	 	                    _map;
	std::string              	        data;
	void 						        parseTitle();
	void        				        parsePlayer();
	void        				        parseMonster();
	void             			        parseElement();
    bool                                _end;
    std::vector<AElement *>::iterator   it;

public:
	Parser();
	Parser(File *);
	~Parser();

	IElement					*parse();

	const std::vector<AElement*> &	getLine() const;
	AElement *get_map() const;
};

#endif