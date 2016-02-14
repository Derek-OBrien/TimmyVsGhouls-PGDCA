#pragma once

#include "cocos2d.h"

#include "Enemy.h"

USING_NS_CC;

class WaveFactory : public Layer
{
public:
	WaveFactory();
	void getData(int amount, int minLane, int maxLane, float speed);
	void createWave(Layer* layer);

	int getLane(int x);

	void update(float dt);

	CREATE_FUNC(WaveFactory);
private:


	// Size & Origin or screen
	Size visibleSize;
	Vec2 origin;

	Enemy* enemy;
	float speed;
	int minLane;
	int maxLane;
	int amount;
};
