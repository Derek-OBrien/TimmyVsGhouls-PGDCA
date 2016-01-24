#pragma once

#include "cocos2d.h"

#include "Enemy.h"

USING_NS_CC;

class WaveFactory : public Layer
{
public:
	WaveFactory();
	
	void createWave(Layer* layer);

	CREATE_FUNC(WaveFactory);
private:

	Enemy* enemy;
	float speed;
	int lane;
};
