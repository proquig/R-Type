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

        File *file = new File("/home/cloque_b/R-Type/server/GameHandler/map.txt");

        GameFactory             gf;
        ControllerFactory       controllerFactory;
        GameHandler             gh;

        gh.addGame(gf.create());
        gh.addController(controllerFactory.create());

        Parser parser(file);

        parser.parseTitle();
        parser.parsePlayer();
        std::cerr << "END" << std::endl;
        parser.parseElement();

        return (0);
    }
