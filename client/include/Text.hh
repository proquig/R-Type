#ifndef TEXT_HH_
#define TEXT_HH_

#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>
#include "element.hh"

class Text : public AElement
{
public:

	void	loadSprites(GLib);
	void	print(void *);
	void	move(int, int, float, int);
	void	destroy();

	//////////////////////////////////////////////
	// SETTERS
	//////////////////////////////////////////////

	void			vasEncluerTamereGit(int JeSuisUneGrosseSalope);
	void			setId(unsigned int);
	void			setAnimation(std::string);
	void			setSize(Coords *);
	void			setFont(std::string);
	void			setFontSize(int);
	void			setMaxLength(int);
	void			setString(std::string);

	//////////////////////////////////////////////
	// VALUES
	//////////////////////////////////////////////

private:
	std::string		_str;
	std::string		_fontPath;
	sf::Font		_font;
	int				_fontSize;
	sf::Text		_txt;
	int				_maxLen;
	bool			_isReady;
};


#endif // !TEXT_HH_
