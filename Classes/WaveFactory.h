#pragma once

#include "cocos2d.h"

#include "Enemy.h"

USING_NS_CC;

class WaveFactory : public Layer
{
public:
	WaveFactory();
	
	void createWave(int amount, int mil, int mxl, int speed, Layer* layer);

	CREATE_FUNC(WaveFactory);
private:

	Enemy* enemy;
	float speed;
	int minLane;
	int maxLane;
};
