#include																	"CollisionHandler.hh"

/*! \brief Constructor of CollisionHandler
*/
CollisionHandler::CollisionHandler(int x, int y) :							_quadtree(0, *(new Rectangle(x / 2, y / 2, x, y, -1)))
{
	_sizeX = x;
	_sizeY = y;
}

/*! \brief Constructor by copy of CollisionHandler
*/
CollisionHandler::CollisionHandler(const CollisionHandler & copy) :			_quadtree(copy.getQuadtree())
{
	_sizeX = copy.getSizeX();
	_sizeY = copy.getSizeY();
	_rectangles = copy.getRectangles();
}

/*! \brief Destructor of CollisionHandler
*/
CollisionHandler::~CollisionHandler()
{
}

/*! \brief operator = for CollisionHandler
*/
CollisionHandler&															CollisionHandler::operator=(const CollisionHandler &)
{
	return *this;
}

/*! \brief foundCollisions of CollisionHandler
* takes a list of entitys on the map 
* returns a vector of vectors of entitys in collision
*/
std::vector<GameElement*> 														CollisionHandler::foundCollisions(std::vector<GameElement*>& entitys, std::vector<int>* collisionId)
{
	std::vector<GameElement*>::iterator											it;
	std::map<GameElement*, Rectangle>::iterator									mit;
	std::map<GameElement*, Rectangle>::iterator									sit;
	std::vector<Rectangle>														current;
	std::vector<GameElement*>													ret;
	std::vector<GameElement*>													tmp;

	_quadtree.clear();
	for (it = entitys.begin(); it != entitys.end(); it++)
	{
		_rectangles[(*it)] = *(new Rectangle((*it)->getX(), (*it)->getY(), (*it)->getSizeX(), (*it)->getSizeY(), (*it)->getId()));
		_quadtree.insert(_rectangles[(*it)]);
	}
	_quadtree.display();
	for(mit = _rectangles.begin(); mit != _rectangles.end(); mit++)
	{
		current.clear();
		current = _quadtree.retrieve(current, (*mit).second);
		for (std::vector<Rectangle>::iterator vit = current.begin(); vit != current.end(); vit++)
		{
			if (isCollision((*vit), (*mit).second))
			{
				if ((*mit).first && collisionId) {
					tmp = handleCollision((*vit).getId(), (*mit).first->getId(), entitys, collisionId);
					while (tmp.size() != 0) {
						ret.push_back(tmp.back());
						tmp.pop_back();
					}
				}
			}
		}
	}
	return (ret);
}

/*! \brief handleCollision of CollisionHandler
* takes two entitys Id and vector of entitys
* returns 
*/
std::vector<GameElement*>														CollisionHandler::handleCollision(int id, int pid, std::vector<GameElement*>& entitys, std::vector<int>* collisionId)
{
	std::vector<GameElement*>													ret;
	GameElement																	*f = NULL;
	GameElement																	*s = NULL;
	std::vector<GameElement*>													tmp;
	int																			iF;
	int																			iS;

	for (unsigned int i = 0; i < entitys.size(); ++i)
	{
		if (entitys[i]->getId() == id)
		{
			f = entitys[i];
			iF = i;
		}
		else if (entitys[i]->getId() == pid)
		{
			s = entitys[i];
			iS = i;
		}
	}
	if (f == NULL || s == NULL)
		return ret;
		std::cout << "Collision here between " << f->getId() << " and " << s->getId() << std::endl;
	//ret = f->collision(s);
	//if (f->getHp() <= 0)
	//{
	//	collisionId->push_back(entitys[iF]->getId());
	//	addScore(entitys, entitys[iF]);
	//	delete(entitys[iF]);
	//	entitys.erase(entitys.begin() + iF);
	//	if (iF < iS)
	//		iS--;
	//}
	//if (s->getHp() <= 0)
	//{
	//	collisionId->push_back(entitys[iS]->getId());
	//	if (entitys[iS])
	//		addScore(entitys, entitys[iS]);
	//	delete(entitys[iS]);
	//	entitys.erase(entitys.begin() + iS);
	//}
	return (ret);
}

void																		CollisionHandler::addScore(std::vector<GameElement*>& entities, GameElement * entity)
{
	if (entity) {
		if (entity->getType() == /*GameElement::BULLET*/ 0) {
			for (std::vector<GameElement *>::iterator it = entities.begin(); it != entities.end(); it++) {
				if (*it) {
					int id = (*it)->getId();
					if (entity->getIdFrom())
						if ( id == entity->getIdFrom()) {
							std::cout << "id = " << entity->getIdFrom();
							//(*it)->setHighScore((*it)->getHighScore() + 10);
						}
				}
			}
		}
	}
}

/*! \brief isCollision of CollisionHandler
* takes two rectangles
* returns boolean for presence of a collision or not
*/
bool																		CollisionHandler::isCollision(const Rectangle a, const Rectangle b) const
{
	if (a.getId() == b.getId())
		return (false);
	if (a.getPosX() - (a.getSizeX() / 2) < b.getPosX() + (b.getSizeX() / 2) &&
		a.getPosX() + (a.getSizeX() / 2) > b.getPosX() - (b.getSizeX() / 2) &&
		a.getPosY() - (a.getSizeY() / 2) < b.getPosY() + (b.getSizeY() / 2) &&
		(a.getSizeY() / 2) + a.getPosY() > b.getPosY() - (b.getSizeY() / 2))
		return (true);
	return (false);
}

/*! \brief getRectangles of CollisionHandler
* returns map of GameElement*,Rectange
*/
std::map<GameElement*, Rectangle>												CollisionHandler::getRectangles() const
{
	return (_rectangles);
}

/*! \brief getSizeX of CollisionHandler
* returns _sizeX;
*/
int																			CollisionHandler::getSizeX() const
{
	return (_sizeX);
}

/*! \brief getSizeY of CollisionHandler
* returns _sizeY;
*/
int																			CollisionHandler::getSizeY() const
{
	return (_sizeY);
}

/*! \brief getQuadtree of CollisionHandler
* returns _quadtree
*/
Quadtree																	CollisionHandler::getQuadtree() const
{
	return (_quadtree);
}