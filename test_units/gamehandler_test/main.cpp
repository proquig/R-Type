//
// Created by cloque_b on 08/12/16.
//

#include "Game.hh"
#include "GameController.hh"
#include "GameHandler.hh"
#include "ControllerFactory.hh"
#include "File.hh"
#include "Parser.hh"
#include "Player.hh"
#include "ThreadPool.hh"
#include "ADLibrary.hh"

void run(IThreadPool* pool)
{
	std::cout << "Hello world" << std::endl;
	if (pool)
	pool->stop();
}

void loadPool()
{
	Dictionary dic;
	IThreadPool *pool;
#ifdef RT_UNIX
	IDLibrary *lib = ADLibrary::createLibrary(0, "threadpool", "./libthreadpool.so");
#elif RT_WIN
	IDLibrary *lib = ADLibrary::createLibrary(0, "threadpool", "threadpool.dll");
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
				if ((pool = reinterpret_cast<IThreadPool *(*)(int)>(dic->at("instantiate"))(4)) != nullptr)
				{
					pool->addTask(pool->createTask(std::bind(run, pool)));
					reinterpret_cast<void *(*)(IThreadPool *)>(dic->at("destroy"))(pool);
				}
			}
			else
				std::cout << "dic empty" << std::endl;
			delete dic;
		}
		lib->close();
	}
	else
		std::cout << "Library load failed" << std::endl;
	ADLibrary::deleteLibrary(lib);
}

int main(int ac, char *av[])
{
	File *file = new File("../../ressources/samtest.txt");

	ControllerFactory cf;
	GameController* gc = cf.create(file);
	gc->startGame();
	int i = 10;
//	while (i < 500)
//	{
	gc->update(i++);
	gc->update(i++);
	gc->update(i++);
	gc->update(i++);
	//	}





	//loadPool();
//	Game* game = (Game*)gc->getGame();

//	game->addPlayer(gc->getElementFactory().createPlayer(0, 0, 50, 20, 20, 10, 0, 2));
//	game->addPlayer(gc->getElementFactory().createPlayer(0, 0, 50, 10, 10, 10, 0, 2));
//	game->addPlayer(gc->getElementFactory().createPlayer(5, 5, 50, 10, 10, 10, 0, 2));
//	game->addPlayer(gc->getElementFactory().createPlayer(25, 25, 50, 50, 50, 10, 0, 2));
//	game->getScene()->addElem(gc->getElementFactory().createDecor(0, 0, 1920, 1));
//	game->getScene()->addElem(gc->getElementFactory().createDecor(0, 1079, 1920, 1));

//	GameFactory             gf;
//	ControllerFactory       controllerFactory;
//	GameHandler             gh;
//	std::vector<IElement*> elems;
//
//	IElement* first = new Player();
//	IElement* second = new Player();
//	elems.push_back(first);
//	elems.push_back(second);
//
//	first->setId(0);
//	second->setId(1);
//	first->setType(AElement::PLAYER);
//	second->setType(AElement::PLAYER);
//
//	first->setX(60);
//	first->setY(60);
//	first->setSizeX(20);
//	first->setSizeY(20);
//
//	second->setX(70);
//	second->setY(70);
//	second->setSizeX(12);
//	second->setSizeY(12);
//
//	gh.addGame(gf.create());
//	gh.addController(controllerFactory.create());
//	gh.getControllers()[0]->setGame(gh.getGames()[0]);
//
//	// Parser parser(file);
//
//	 //parser.parseTitle();
//	 //parser.parsePlayer();
//	gh.getGames()[0]->getScene()->addElems(elems);
//	std::cout << gh.getGames()[0]->getScene()->getMap().size() << std::endl;
//
//	gh.getControllers()[0]->handleCollisions();
//
//	//parser.parseElement();
//
	return (0);
}
