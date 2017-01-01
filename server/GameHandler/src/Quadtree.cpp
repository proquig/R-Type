#include												"Quadtree.hh"

/*! \brief Constructor of Quadtree
* params are plevel and bounds
*/
Quadtree::Quadtree(int plevel, Rectangle bounds) :		 _bounds(bounds)
{
	_maxLvl = 5;
	_maxObj = 4;
	_level = plevel;
}

/*! \brief Destructor of Quadtree
*/
Quadtree::~Quadtree()
{
}

/*! \brief clear of Quadtree
* clear a Quadtree and subs quadtrees
*/
void													Quadtree::clear()
{
	_objects.clear();
	for (unsigned int i = 0; i != _nodes.size(); i++)
	{
		delete (_nodes[i]);
		_nodes[i] = NULL;
	}
}

/*! \brief split of Quadtree
* split a Quadtree in 4 subs quadtrees
*/
void													Quadtree::split()
{
	int			subH = (int)(_bounds.getSizeX() / 4);
	int			subV = (int)(_bounds.getSizeY() / 4);
	int			x = (int)(_bounds.getPosX());
	int			y = (int)(_bounds.getPosY());

	_nodes[0] = new Quadtree(_level + 1, *(new Rectangle(x - subH, y - subV, subH * 2, subV * 2, _bounds.getId() - 1)));
	_nodes[1] = new Quadtree(_level + 1, *(new Rectangle(x - subH, y + subV, subH * 2, subV * 2, _bounds.getId() - 2)));
	_nodes[2] = new Quadtree(_level + 1, *(new Rectangle(x + subH, y - subV, subH * 2, subV * 2, _bounds.getId() - 3)));
	_nodes[3] = new Quadtree(_level + 1, *(new Rectangle(x + subH, y + subV, subH * 2, subV * 2, _bounds.getId() - 4)));
}

int				Quadtree::getIndex(Rectangle rect)
{
	int			index = -1;
	bool		topQ = (rect.getPosY() + (rect.getSizeY() / 2) < _bounds.getPosY());
	bool		botQ = (rect.getPosY() - (rect.getSizeY() / 2) > _bounds.getPosY());

	if (rect.getPosX() + (rect.getSizeX() / 2) < _bounds.getPosX())
	{
		if (topQ)
			index = 0;
		else if (botQ)
			index = 1;
	}
	else if (rect.getPosX() - (rect.getSizeX() / 2) > _bounds.getPosX())
	{
		if (topQ)
			index = 2;
		else if (botQ)
			index = 3;
	}
	return (index);
}

/*! \brief insert of Quadtree
*/
void													Quadtree::insert(Rectangle rect)
{
	int													index;
	std::vector<Rectangle>::iterator					it;
	
	if (_nodes[0] != NULL)
	{
		index = getIndex(rect);
		if (index != -1)
		{
			_nodes[index]->insert(rect);
			return;
		}
	}
	_objects.push_back(rect);
	if (_objects.size() > _maxObj && _level < _maxLvl)
	{
		if (_nodes[0] == NULL)
			split();
		it = _objects.begin();
		for (int i = 0; i != _objects.size(); i++)
		{
			index = getIndex(_objects.back());
			if (index != -1)
			{
				_nodes[index]->insert(_objects.back());
				_objects.pop_back();
				i = -1;
			}
			else
			{
				_objects.insert(_objects.begin(), _objects.back());
				_objects.pop_back();
			}
		}
	}
}

/*! \brief retrieve of Quadtree
* returns list of objects in the current index
*/
std::vector<Rectangle>&									Quadtree::retrieve(std::vector<Rectangle>& ret, Rectangle rect)
{
	int													index;

	index = getIndex(rect);
	if (index != -1 && _nodes[0] != NULL)
	{
		ret = _nodes[index]->retrieve(ret, rect);
	}
	else if (index == -1)
	{
		if (_nodes[0] != NULL)
		{
			ret = _nodes[0]->retrieve(ret, rect);
			ret = _nodes[1]->retrieve(ret, rect);
			ret = _nodes[2]->retrieve(ret, rect);
			ret = _nodes[3]->retrieve(ret, rect);
		}
	}
	for (std::vector<Rectangle>::iterator it = _objects.begin(); it != _objects.end(); it++)
		ret.push_back((*it));
	return (ret);
}

/*! \brief getMaxLvl of Quadtree
* returns _maxLvl
*/
int														Quadtree::getMaxLvl() const
{
	return (_maxLvl);
}

/*! \brief getMaxObj of Quadtree
* returns _maxObj
*/
unsigned int									Quadtree::getMaxObj() const
{
	return (_maxObj);
}

/*! \brief getLevel of Quadtree
* returns _level
*/
int														Quadtree::getLevel() const
{
	return (_level);
}

/*! \brief getObjects of Quadtree
* returns _objects
*/
const std::vector<Rectangle>&							Quadtree::getObjects() const
{
	return (_objects);
}

/*! \brief getBounds of Quadtree
* returns _bounds
*/
const Rectangle&										Quadtree::getBounds() const
{
	return (_bounds);
}

/*! \brief getNodes of Quadtree
* returns _nodes
*/
const std::map<int, Quadtree*>&							Quadtree::getNodes() const
{
	return (_nodes);
}

void													Quadtree::display() const
{
	std::cout << std::endl << "Quadtree " << _level << ": " << std::endl;
	for (Rectangle r : _objects)
	{
		std::cout << "Object " << r.getId() << ": " << r.getPosX() << "|" << r.getPosY() << std::endl;
	}
}