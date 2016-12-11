#include "SFMLSprite.hh"

void	SFMLSprite::load(void)
{
	this->texture = new sf::Texture();
	this->sprite = new sf::Sprite();

	this->texture->loadFromFile(this->path);
	this->sprite->setTexture(*this->texture);
	this->sprite->setTextureRect(
		sf::IntRect(
			this->begin->x, this->begin->y,
			this->end->x, this->end->y
		));
}

void	SFMLSprite::print(Coords *pos, float angle)
{
	this->sprite->setPosition(pos->x, pos->y);
	this->window->draw(*this->sprite);
}

void	SFMLSprite::free()
{
	// TO-DO
}