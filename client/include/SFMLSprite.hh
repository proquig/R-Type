#ifndef SFML_SPRITE_HH__
# define SFML_SPRITE_HH__

# include <SFML/Graphics.hpp>
# include "SFMLWindow.hh"
# include "sprite.hh"

class													SFMLSprite : public ASprite, public sf::Drawable
{
// Private values
private:
	sf::Time											_delta;
	sf::Time											_animTime;
	sf::Clock											_clock;
	std::map<std::string, std::vector<sf::IntRect> *>	_anim;
	std::vector<sf::IntRect>							*_currAnim;
	std::pair<unsigned int, unsigned int>				_pos;
	std::pair<float, float>								_size;
	sf::Texture											_tex;
	sf::Image											_img;
	sf::Sprite											_spr;
	//int													_cnt;
	// Not usefull										_notUsed;
	sf::Vertex											_vert[4];
	std::string											_name;
// Public Functions
public:
	SFMLSprite(std::string _path) : ASprite(_path) {}
	void	addRessource(std::string, const std::vector<Cut *>);
	void	print(void *);
	void	setAnimation(std::string, Coords *, float);
	bool	isOver(void) const;
	bool	getLoop() const;
	void	setLoop(bool);
	void	setAnimTime(float);
	bool	getAnimated() const;
	void	setAnimated(bool);
	void	setScale(float);

	//Private Functions
private:
	void			init();
	void			update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif /* !SFML_SPRITE_HH__ */
