#ifndef SERIALIZER_HH__
# define SERIALIZER_HH__

# include "window.hh"
# include "element.hh"
# include <vector>

namespace clientUDP {

# define INPUT_SNAPSHOT		(char)1
# define ELEMENTS			(char)2
# define DESTROY_ELEMENTS	(char)4
# define GAME_STATE			(char)8

# define ACK_NEED			(char)16
# define ACK_DONE			(char)32

	struct ObstacleGame {
		unsigned short	id;
		unsigned short	lives;
		unsigned int	score;
	};

	struct GameElement {
		unsigned int	id;
		unsigned int	timer;
		unsigned short	x;
		unsigned short	y;
		float			angle;
		unsigned char	speed;
		unsigned char	properties[3];
	};

	struct				Packet {
		char			magic;
		char			gameId;
		char			packetId;
		char			opCode;
		int				size;
		unsigned int	timer;
		void			*data;
	};

	class Serializer
	{

		char	magic;
		char	gameId;
		char	packetId;

		std::vector<AElement *>	*elements;

	public:

		Serializer(char _magic, char _gameId) : magic(_magic), gameId(_gameId), packetId(0) {};

		////////////////////////////////////////////////////////////////
		// INPUT
		////////////////////////////////////////////////////////////////

		bool	unserializeElement(Packet *);

		////////////////////////////////////////////////////////////////
		// OUTPUT
		////////////////////////////////////////////////////////////////

		Packet	*createPacket(char, unsigned int, int, char *);
		Packet	*serializeEvent(Event *);
	};
}

#endif /* !SERIALIZER_HH__ */