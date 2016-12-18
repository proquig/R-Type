#include			"Rectangle.hh"

/*! \brief Constructor of Rectangle
* params are sizeX, sizeY, posX, posY
*/
Rectangle::Rectangle(int posX, int posY, int sizeX, int sizeY, int id)
{
	_sizeX = sizeX;
	_sizeY = sizeY;
	_posX = posX;
	_posY = posY;
	_id = id;
}

/*! \brief Constructor by copy of Rectangle
*/
Rectangle::Rectangle(const Rectangle& cpy)
{
	_sizeX = cpy.getSizeX();
	_sizeY = cpy.getSizeY();
	_posX = cpy.getPosX();
	_posY = cpy.getPosY();
	_id = cpy.getId();
}

/*! \brief Destructor of Rectangle
*/
Rectangle::~Rectangle()
{
}

/*! \brief getSizeX of Rectangle
* returns _sizeX
*/
int					Rectangle::getSizeX() const
{
	return (_sizeX);
}

/*! \brief getSizeY of Rectangle
* returns _sizeY
*/
int					Rectangle::getSizeY() const
{
	return (_sizeY);
}

/*! \brief getPosX of Rectangle
* returns _posX
*/
int					Rectangle::getPosX() const
{
	return (_posX);
}

/*! \brief getPosY of Rectangle
* returns _posY
*/
int					Rectangle::getPosY() const
{
	return (_posY);
}

/*! \brief getId of Rectangle
* returns _id
*/
int					Rectangle::getId() const
{
	return (_id);
}

void				Rectangle::display() const
{
	std::cout << "Rectangle " << _id << ":(" << _posX << ";" << _posY << ")|(" << _sizeX  << ";" << _sizeY << ");" << std::endl;
}
