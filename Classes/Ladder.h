#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Ladder : public  Sprite
{
public:
	Ladder();
	~Ladder();

	void create(Vec2 pos, Layer* layer);

private:


	// Size & Origin or screen
	Size visibleSize;
	Vec2 origin;

	Sprite* m_ladderSprite;

};