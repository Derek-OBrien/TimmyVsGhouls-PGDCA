#pragma once

#include "cocos2d.h"
#include "HudLayer.h"
USING_NS_CC;

class CollisionCheck
{
public:
	CollisionCheck();
	
	bool checkForCollision(PhysicsContact &contact, Layer* layer, Hud* hud);
private:

};
