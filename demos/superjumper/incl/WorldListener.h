#pragma once

class WorldListener
{
public:
	virtual ~WorldListener() {};
	virtual void jump() = 0;
	virtual void highJump() = 0;
	virtual void hit() = 0;
	virtual void coin() = 0;
};
