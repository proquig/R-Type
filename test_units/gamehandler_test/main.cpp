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

		GameElement* first = new GameElement();
		GameElement* second = new GameElement();
		elems.push_back(first);
		elems.push_back(second);

		first->setId(0);
		second->setId(1);

		first->setX(60);
		first->setY(60);
		first->setSizeX(10);
		first->setSizeY(10);

		second->setX(70);
		second->setY(70); 
		second->setSizeX(12);
		second->setSizeY(10);
		
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
