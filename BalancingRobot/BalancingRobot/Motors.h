#pragma once
class Motors
{

public:
	Motors();
	~Motors();
	void init();
	// speed in range -100..100
	void setSpeedBoth(float speed);
	void stopAll();
};

