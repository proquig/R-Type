#ifdef RT_UNIX
#include <unistd.h>

#elif RT_WIN
#include <Windows.h>
#endif

#include <iostream>


#include "ADLibrary.hh"
#include "Bildo.hh"


void splash(void)
{
    std::cout << "Splash" << std::endl;
}

int main(int ac, char **av)
{
    Dictionary dic;
    Bildo *monster;
    ElementFactory *elementFactory = new ElementFactory;
    RType::IElement *decor = elementFactory->createDecor(0, 5, 1, 1);

#ifdef RT_UNIX
    IDLibrary *lib = ADLibrary::createLibrary(0, "bildo", "./libbildo.so");
#elif RT_WIN
    IDLibrary *lib = ADLibrary::createLibrary(0, "monster", "monster.dll");
#endif
    if (lib->load())
    {
        std::cout << "Library load success" << std::endl;
        if ((dic = lib->getDictionary()) != NULL)
        {
            if (!dic->empty())
            {
                for (std::map<std::string, void *>::iterator sit = dic->begin(); sit != dic->end(); sit++)
                    std::cout << "key=" << sit->first.c_str() << std::endl;
                if ((monster = reinterpret_cast<Bildo *(*)(int, int, int, void *)>(dic->at("new"))(4,0,0, elementFactory)) != nullptr)
                {
                    for (int i = 0; i < 20; i++)
                    {
                        monster->collideWith(decor);
                        std::cout << decor->getX() << ":" << decor->getY() << std::endl;
                        std::cout << "X=" << monster->getX() << ":" << "Y=" << monster->getY() << std::endl;
                        if (!monster->move()) {
                            monster->shot();
                            std::cout << "Shot at :" << monster->getX() << ":" << monster->getY() << std::endl;
                        }
                    }
                }
            } else
                std::cout << "dic empty" << std::endl;
            delete dic;
        }
        lib->close();
    } else
        std::cout << "Library load failed" << std::endl;
    ADLibrary::deleteLibrary(lib);
}
