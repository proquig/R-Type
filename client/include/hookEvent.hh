#ifndef HOOK_EVENT_HH__
# define HOOK_EVENT_HH__

# include "window.hh"
# include "workQueue.hh"
# include "coords.hh"



class IHookEvent
{
public:
	virtual void	pollEvent(WorkQueue<Event *> *) = 0;
};

class AHookEvent : public IHookEvent
{

protected:

	WorkQueue<Event *>	*eventQueue;

};

#endif /* !HOOK_EVENT_HH__ */