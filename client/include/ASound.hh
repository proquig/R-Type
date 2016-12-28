#pragma once

class ASound
{
private:
	void*			_sound;

public:
	virtual			~ASound() {};
	virtual	void*	getSound() = 0;
	virtual void	play() = 0;
	virtual void	pause() = 0;
	virtual void	stop() = 0;
};