#include <cstring>
#include "serializer.hh"

////////////////////////////////////////////////////////////////
// INPUT
////////////////////////////////////////////////////////////////

bool	clientUDP::Serializer::unserializeElement(Packet *packet)
{
	GameElement				*elems;
	int						nbElems = 0;

	if (!(packet->opCode & ELEMENTS)
		|| (packet->size % sizeof(GameElement)))
		return (false);
	elems = (GameElement *)packet->data;
	nbElems = packet->size / sizeof(GameElement);
	for (int i = 0; i < nbElems; ++i)
	{
		// TO-DO
	}
	return (true);
}

////////////////////////////////////////////////////////////////
// OUTPUT
////////////////////////////////////////////////////////////////

clientUDP::Packet *	clientUDP::Serializer::createPacket(char _o, unsigned int _s, int _t, char *_d)
{
	clientUDP::Packet	*packet = new clientUDP::Packet();

	packet->magic = this->magic;
	packet->gameId = this->gameId;
	packet->packetId = this->packetId;
	packet->opCode = _o;
	packet->size = _s;
	packet->timer = _t;
	packet->data = _d;
	this->packetId += 1;
	return (packet);
}

clientUDP::Packet *	clientUDP::Serializer::serializeEvent(Event *event)
{
	if (!event)
		return (NULL);
	Packet	*packet = this->createPacket(
		INPUT_SNAPSHOT, 
		strlen(event->name), 
		EVENT_TIMER, 
		event->name
	);
	return (packet);
}
