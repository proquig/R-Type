#include																	"CollisionHandler.hh"

/*! \brief Constructor of CollisionHandler
*/
CollisionHandler::CollisionHandler(int x, int y) : _quadtree(0, *(new Rectangle(x / 2, y / 2, x, y, -1)))
{
	_sizeX = x;
	_sizeY = y;
}

/*! \brief Constructor by copy of CollisionHandler
*/
CollisionHandler::CollisionHandler(const CollisionHandler & copy) : _quadtree(copy.getQuadtree())
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

bool																		CollisionHandler::doesAlreadyDetected(RType::IElement* first, RType::IElement* second, std::vector<std::pair<RType::IElement*, RType::IElement*>> vec, std::vector<RType::IElement*> entitys)
{
	std::pair<RType::IElement*, RType::IElement*>							pairone = std::make_pair<>(first, second);
	std::pair<RType::IElement*, RType::IElement*>							pairtwo = std::make_pair<>(second, first);

	for (std::pair<RType::IElement*, RType::IElement*> pair : vec)
	{
		if (pair == pairone || pair == pairtwo)
		{
			return true;
		}
	}
	if (second != NULL && first->getType() != second->getType() && first->getIdFrom() != second->getId() && second->getIdFrom() != first->getId())
	{
		return true;
	}
	int idone = first->getIdFrom();
	int idtwo = second->getIdFrom();
	for (RType::IElement* elem : entitys)
	{
		if (elem->getId() == idtwo && elem->getType() == first->getType())
		{
			return true;
		}
		if (elem->getId() == idone && elem->getType() == second->getType())
		{
			return true;
		}
	}
	return false;
}

/*! \brief foundCollisions of CollisionHandler
* takes a list of entitys on the map
* returns a vector of vectors of entitys in collision
*/
std::vector<std::pair<RType::IElement*, RType::IElement*> > 						CollisionHandler::foundCollisions(std::vector<RType::IElement*>& entitys, std::vector<int>* collisionId)
{
	std::vector<RType::IElement*>::iterator											it;
	std::map<RType::IElement*, Rectangle>::iterator									mit;
	std::map<RType::IElement*, Rectangle>::iterator									sit;
	std::vector<Rectangle>														current;
	std::vector<RType::IElement*>													tmp;
	RType::IElement*															first = NULL;
	RType::IElement*															second = NULL;
	std::vector<std::pair<RType::IElement*, RType::IElement*> >					result;

	_quadtree.clear();
	for (it = entitys.begin(); it != entitys.end(); it++)
	{
		_rectangles[(*it)] = *(new Rectangle((*it)->getX(), (*it)->getY(), (*it)->getSizeX(), (*it)->getSizeY(), (*it)->getId()));
		_quadtree.insert(_rectangles[(*it)]);
	}
	for (mit = _rectangles.begin(); mit != _rectangles.end(); mit++)
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
						if (first == NULL)
							first = tmp.back();
						else
							second = tmp.back();
						tmp.pop_back();
					}
					if (!doesAlreadyDetected(first, second, result, entitys))
						result.push_back(std::make_pair<>(first, second));
					first = NULL;
					second = NULL;
				}
			}
		}
	}
	return	result;
}

/*! \brief handleCollision of CollisionHandler
* takes two entitys Id and vector of entitys
* returns
*/
std::vector<RType::IElement*>														CollisionHandler::handleCollision(int id, int pid, std::vector<RType::IElement*>& entitys, std::vector<int>* collisionId)
{
	std::vector<RType::IElement*>													ret;
	RType::IElement																*f = NULL;
	RType::IElement																*s = NULL;
	std::vector<RType::IElement*>													tmp;
	int																		iF;
	int																		iS;

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
	ret = f->collideWith(s);
	if (f->getHp() <= 0)
	{
		collisionId->push_back(entitys[iF]->getId());
		addScore(entitys, entitys[iF]);
		//delete(entitys[iF]);
		//entitys.erase(entitys.begin() + iF);
		if (iF < iS)
			iS--;
	}
	if (s->getHp() <= 0)
	{
		collisionId->push_back(entitys[iS]->getId());
		if (entitys[iS])
			addScore(entitys, entitys[iS]);
		//delete(entitys[iS]);
		//entitys.erase(entitys.begin() + iS);
	}
	ret.push_back(f);
	ret.push_back(s);
	return (ret);
}

void																		CollisionHandler::addScore(std::vector<RType::IElement*>& entities, RType::IElement * entity)
{
	if (entity) {
		if (entity->getType() == RType::BULLET) {
			for (std::vector<RType::IElement *>::iterator it = entities.begin(); it != entities.end(); it++) {
				if (*it) {
					int id = (*it)->getId();
					if (entity->getIdFrom())
						if (id == entity->getIdFrom()) {
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
	return ((float)(a.getPosX() - (a.getSizeX() / 2)) <= (float)(b.getPosX() + (b.getSizeX() / 2)) &&
		(float)(a.getPosX() + (a.getSizeX() / 2)) >= (float)(b.getPosX() - (b.getSizeX() / 2)) &&
		(float)(a.getPosY() - (a.getSizeY() / 2)) <= (float)(b.getPosY() + (b.getSizeY() / 2)) &&
		(float)((a.getSizeY() / 2) + a.getPosY()) >= (float)(b.getPosY() - (b.getSizeY() / 2)));
}

/*! \brief getRectangles of CollisionHandler
* returns map of RType::IElement*,Rectange
*/
std::map<RType::IElement*, Rectangle>												CollisionHandler::getRectangles() const
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