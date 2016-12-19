#include <stdlib.h>
#include "Parser.hh"

Parser::Parser()
{

}

Parser::Parser(File* file) : _file(file)
{
	_file->read();
	data = _file->getData();
}

Parser::~Parser()
{
	delete _file;
}

const std::vector<GameElement>&	Parser::getLine() const {
	return _line;
}

void    Parser::parseObstacle() {
	std::string                  Obstacles;
	size_t                       pos1 = 0;
	size_t                       pos = 0;
	uint32_t                    id = 1;


	while ((pos = data.find("J", pos1)) != std::string::npos)
	{
		pos1 = data.find('\n', pos);
		Obstacles = data.substr(pos, pos1 - pos);
		GameElement                  *gameElement = new GameElement;
		try {
			size_t                       position = 0;
			size_t                       position1 = 0;
			position =   Obstacles.find(';', position);
			position1 =  Obstacles.find(';', position + 1);
			gameElement->setX((uint16_t) std::stoi(Obstacles.substr(position + 1, Obstacles.find(';', position))));
			gameElement->setY((uint16_t) std::stoi(Obstacles.substr(position1 + 1)));
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
		gameElement->setId(id++);
		_line.push_back(*gameElement);
		data.erase(0, data.find('\n') + 1);
		data.erase(0, data.find('\n') + 1);
	}
	data.erase(0, data.find('\n') + 1);
}

void     Parser::parseElement() {
	std::cout << "DATA:" << data << std::endl;

    std::string                  Obstacles;
	size_t                       pos1 = 0;
	size_t                       pos = 0;
	uint32_t                    id = 1;

	while ((pos = data.find("\n", pos1)) != std::string::npos)
	{
//		pos1 = data.find('\n', pos);
		Obstacles = data.substr(pos1, pos);
        std::cout<< "LOL:" << Obstacles << std::endl;
        data.erase(0, pos + 1);
		GameElement                  *gameElement = new GameElement;
/*		try {
			while ((pos = data.find(";", pos1)) != std::string::npos) {
				size_t position = 0;
				size_t position1 = 0;
				position = Obstacles.find(';', position);
				position1 = Obstacles.find(';', position + 1);
				gameElement->setX((u_int16_t) std::stoi(Obstacles.substr(position + 1, Obstacles.find(';', position))));
				gameElement->setY((u_int16_t) std::stoi(Obstacles.substr(position1 + 1)));
			}
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}*/
	//	_line.push_back(gameElement);
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
	_line.push_back(*gameElement);
	data.erase(0, data.find('\n'));
}
