//
// Created by cloque_b on 08/12/16.
//

#include "GameHandler.hh"
#include "ControllerFactory.hh"
#include "Parser.hh"

int main(int ac, char *av[])
{
    File *file = new File(ac > 0 ? "../../ressources/map.txt" : "../../ressources/map2.txt");

    Parser parser(file);
    IElement *elem;
	std::cout <<  "Test sur le parsing de la carte : '" << file->getName() << "'" << std::endl;

    while ((elem = parser.parse()) != nullptr)
    {
        std::cout << "ELEMENT {\n\t{\n\t"
                  << elem->getX() << ":"
                  << elem->getY() << "\n\t}\n\t{\n\t"
                  << elem->getSizeX() << ":"
        << elem->getSizeY() << "\n\t}\n" << std::endl;
        std::cout << "};\n";

    }
    return (0);
}
