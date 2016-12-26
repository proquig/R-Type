#ifndef GAMEHANDLER_PARSER_HH
#define GAMEHANDLER_PARSER_HH

#include <vector>
#include "File.hh"
#include "AElement.hh"
#include "ElementFactory.hh"

class Parser
{
private:
	File*						        _file;
	std::vector<RType::AElement*> 		        _line;
	RType::AElement*	 	                    _map;
	std::string              	        data;
	void 						        parseTitle();
	void        				        parsePlayer();
	void        				        parseMonster();
	void             			        parseElement();
    bool                                _end;
    std::vector<RType::AElement *>::iterator   it;
	ElementFactory*						_factory;

	int									decal(int, int);

public:
	Parser(ElementFactory* factory);
	~Parser();

	RType::IElement					*parse();

	const std::vector<RType::AElement*> &	getLine() const;
	RType::AElement							*get_map() const;
	void								setFile(File*);
};

#endif