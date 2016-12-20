#include <stdlib.h>
#include <ElementFactory.hh>
#include "Parser.hh"

Parser::Parser()
{

}

Parser::Parser(File* file) : _file(file)
{
    _end = false;
	_file->read();
	data = _file->getData();
}

Parser::~Parser()
{
	delete _file;
}

const std::vector<AElement*>&	Parser::getLine() const {
	return _line;
}

void    Parser::parsePlayer() {
	ElementFactory				factory;
	std::string                  players;
	size_t                       pos1 = 0;
	size_t                       pos = 0;
	uint32_t                    id = 1;
	int 						value[8];
	int 						i;

	while ((pos = data.find("J", pos1)) != std::string::npos) {
		pos1 = data.find('\n', pos);
		players = data.substr(pos, pos1 - pos);
		try {
			size_t position = 0;
			size_t position1 = 0;
			i = 0;
			while ((position = players.find(";", position1)) != std::string::npos) {
				value[i++] = std::stoi(players.substr(position + 1, players.find(';', position)));
				position1 = position + 1;
			}
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
		_line.push_back(factory.create(-1, -1, AElement::PLAYER, value[0], value[1], value[4], value[2], value[3], value[5], value[6], value[7]));
		data.erase(pos, pos1 - pos);
		data.erase(0, data.find('J')  != std::string::npos ? data.find('J') : 1 );
		pos1 = 0;
	}
}

void     Parser::parseElement()
{
	ElementFactory				factory;
	std::string                  players;
	size_t                       pos1 = 0;
	size_t                       pos = 0;
	uint32_t                    id = 1;
    uint32_t					value[4];
	int 						i;

	while ((pos = data.find("D", pos1)) != std::string::npos) {
		pos1 = data.find('\n', pos);
		players = data.substr(pos, pos1 - pos);
		try {
			size_t position = 0;
			size_t position1 = 0;
			i = 0;
			while ((position = players.find(";", position1)) != std::string::npos) {
				value[i++] = (uint32_t) std::stoi(players.substr(position + 1, players.find(';', position)));
				position1 = position + 1;
			}
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
		_line.push_back(factory.create(0, 0, AElement::DECOR, (value[0] + value[2]) / 2 , (value[1] + value[3]) / 2, 0, value[2], value[3], 0, 0, 0));
		data.erase(pos, pos1 - pos);
		data.erase(0, data.find('D')  != std::string::npos ? data.find('D') : 1 );
		pos1 = 0;
	}
}

void    Parser::parseMonster()
{
	ElementFactory				factory;
	std::string                  players;
	size_t                       pos1 = 0;
	size_t                       pos = 0;
	uint32_t                    id = 1;
	int 						value[8];
	int 						i;

	while ((pos = data.find("M", pos1)) != std::string::npos) {
		pos1 = data.find('\n', pos);
		players = data.substr(pos, pos1 - pos);
		try {
			size_t position = 0;
			size_t position1 = 0;
			i = 0;
			while ((position = players.find(";", position1)) != std::string::npos) {
				value[i++] = std::stoi(players.substr(position + 1, players.find(';', position)));
				position1 = position + 1;
			}
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
		_line.push_back(factory.create(-1, -1, AElement::MONSTER, value[0], value[1], value[4], value[2], value[3], value[5], value[6], value[7]));
		data.erase(pos, pos1 - pos);
		data.erase(0, data.find('M')  != std::string::npos ? data.find('M') : 1 );
		pos1 = 0;
	}
}


void    Parser::parseTitle() {
	GameElement                  *gameElement = new GameElement;
	std::string                  title;

	title = data.substr(0, data.find('\n'));
	try {
		size_t                       pos = 0;
		size_t                       pos1 = 0;
		pos =   title.find(';', pos);
		pos1 =  title.find(';', pos + 1);
		gameElement->setX((uint16_t) std::stoi(title.substr(pos + 1, title.find(';', pos))));
		gameElement->setY((uint16_t) std::stoi(title.substr(pos1 + 1)));
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	gameElement->setId(0);
	data.erase(0, data.find('\n'));
}


IElement *Parser::parse()
{
	if (!_end) {
		parseTitle();
		parsePlayer();
		parseElement();
        it = _line.begin();
        _end = true;
    }
    IElement * element = it == _line.end() ? nullptr : (*it);
	it++;
    return element;
}

AElement* Parser::get_map() const {
	return _map;
}

