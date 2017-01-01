#include <stdlib.h>
#include <ElementFactory.hh>
#include "Parser.hh"

Parser::Parser(ElementFactory* factory)
{
	_factory = factory;
}

Parser::~Parser()
{
	delete _file;
}

int								Parser::decal(int x, int sizex)
{ return x + (sizex / 2); }

void							Parser::setFile(File* file)
{
	_end = false;
	_file = file;
	_file->read();
	data = _file->getData();
}

const std::vector<RType::AElement*>&	Parser::getLine() const {
	return _line;
}

void    Parser::parsePlayer() {
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
		}
		catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
		_line.push_back(_factory->create(-1, -1, RType::PLAYER, decal(value[0], value[2]), decal(value[1], value[3]), value[4], value[2], value[3], value[5], value[6], value[7]));
		data.erase(pos, pos1 - pos);
		data.erase(0, data.find('J') != std::string::npos ? data.find('J') : 1);
		pos1 = 0;
	}
}

void     Parser::parseElement()
{
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
				value[i++] = (uint32_t)std::stoi(players.substr(position + 1, players.find(';', position)));
				position1 = position + 1;
			}
		}
		catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
		_line.push_back(_factory->create(0, 0, RType::DECOR, decal(value[0], value[2]), decal(value[1], value[3]), 0, value[2], value[3], 0, 0, 0));
		data.erase(pos, pos1 - pos);
		data.erase(0, data.find('D') != std::string::npos ? data.find('D') : 1);
		pos1 = 0;
	}
}

void    Parser::parseMonster()
{
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
		}
		catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
		_line.push_back(_factory->create(-1, -1, RType::MONSTER, decal(value[0], value[2]), decal(value[1], value[3]), value[4], value[2], value[3], value[5], value[6], value[7]));
		data.erase(pos, pos1 - pos);
		data.erase(0, data.find('M') != std::string::npos ? data.find('M') : 1);
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
		pos = title.find(';', pos);
		pos1 = title.find(';', pos + 1);
		gameElement->setX((uint16_t)std::stoi(title.substr(pos + 1, title.find(';', pos))));
		gameElement->setY((uint16_t)std::stoi(title.substr(pos1 + 1)));
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	gameElement->setId(0);
	data.erase(0, data.find('\n'));
}


RType::IElement *Parser::parse()
{
	RType::IElement* element;
	if (!_end) {
		parseTitle();
		parsePlayer();
		parseElement();
		it = _line.begin();
		_end = true;
	}
	if (it != _line.end())
		element = (*it);
	else
		return NULL;
	it++;
	return element;
}

RType::AElement* Parser::get_map() const {
	return _map;
}

