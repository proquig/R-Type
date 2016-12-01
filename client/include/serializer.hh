#ifndef SERIALIZER_HH__
# define SERIALIZER_HH__

# include "window.hh"

struct TMP_PACKET {
	size_t	size;
	char	*data;
};

class Serializer
{

public:
	TMP_PACKET	*serializeEvent(Event *);
};

#endif /* !SERIALIZER_HH__ */