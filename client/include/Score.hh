#ifndef SCORE_HH_
#define SCORE_HH_

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "element.hh"

class Score : public AElement
{
public:

	void	loadSprites(GLib);
	void	print(void *);
	void	move(int, int, float, int);
	void	destroy();

	//////////////////////////////////////////////
	// SETTERS
	//////////////////////////////////////////////

	void			setId(unsigned int);
	void			setAnimation(std::string);
	void			setSize(Coords *);
	void			setFont(std::string);
	void			setFontSize(int);
	void			setMaxLength(int);
	void			setString(std::string);
	void			rmString();


	//////////////////////////////////////////////
	// SETTERS
	//////////////////////////////////////////////

	std::string		getString() const;
	//////////////////////////////////////////////
	// VALUES
	//////////////////////////////////////////////

private:
	std::string		_str;
	std::string		_save;
	std::string		_fontPath;
	sf::Font		_font;
	int				_fontSize;
	int				_cnt;
	sf::Text		_txt;
	int				_maxLen;
	bool			_isReady;
};


#endif // !SCORE_HH_
