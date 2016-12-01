#include "serializer.hh"

TMP_PACKET *	Serializer::serializeEvent(Event *event)
{
	if (!event)
		return (NULL);
	TMP_PACKET	*packet = new TMP_PACKET();

	switch (event->type) {
	case Event::QUIT :
		packet->size = 5;
		packet->data = "QUIT";
		break;
	case Event::ENTER:
		packet->size = 6;
		packet->data = "ENTER";
		break;
	case Event::UP:
		packet->size = 3;
		packet->data = "UP";
		break;
	case Event::LEFT:
		packet->size = 5;
		packet->data = "LEFT";
		break;
	case Event::RIGHT:
		packet->size = 6;
		packet->data = "RIGHT";
		break;
	case Event::DOWN:
		packet->size = 5;
		packet->data = "DOWN";
		break;
	case Event::CLICK:
		packet->size = 6;
		packet->data = "CLICK";
		break;
	default :
		packet->size = 7;
		packet->data = "UNKNOW";
		break;
	}
	return (packet);
}