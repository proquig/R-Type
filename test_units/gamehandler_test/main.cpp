//
// Created by cloque_b on 08/12/16.
//

#include "GameHandler.hh"
#include "GameFactory.hh"
#include "ControllerFactory.hh"
#include "File.hh"
#include "Parser.hh"

    int main(int ac, char *av[])
    {
        File *file = new File("./map.txt");

        GameFactory             gf;
        ControllerFactory       controllerFactory;
        GameHandler             gh;
		std::vector<GameElement*> elems;

		for (int i = 0; i != 40; i++)
		{
			GameElement* g = new GameElement();
			g->setId(i);
			g->setSizeX(10);
			g->setSizeY(10);
			g->setX(i * 10);
			g->setY(i * 10);
			elems.push_back(g);
		}
		elems[0]->setX(15);
		elems[0]->setY(15);
        gh.addGame(gf.create());
        gh.addController(controllerFactory.create());
		gh.getControllers()[0]->setGame(gh.getGames()[0]);

       // Parser parser(file);

        //parser.parseTitle();
        //parser.parsePlayer();
		gh.getGames()[0]->getScene()->addElems(elems);
		std::cout << gh.getGames()[0]->getScene()->getMap().size() << std::endl;

		gh.getControllers()[0]->handleCollisions();
        std::cerr << "END" << std::endl;
        //parser.parseElement();
		
        return (0);
    }
