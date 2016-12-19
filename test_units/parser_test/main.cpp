//
// Created by cloque_b on 08/12/16.
//

#include "GameHandler.hh"
#include "ControllerFactory.hh"
#include "File.hh"
#include "Parser.hh"
#include "Player.hh"
#include "ThreadPool.hh"
#include "ADLibrary.hh"

int main(int ac, char *av[])
{
	File *file = new File("./map.txt");

	ControllerFactory cf;

Parser parser(file);

//	 //parser.parseTitle();
//	 //parser.parsePlayer();

	return (0);
}
