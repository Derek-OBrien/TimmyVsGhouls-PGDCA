#pragma once

#include "cocos2d.h"
#include "HudLayer.h"
USING_NS_CC;

class CollisionCheck
{
public:
	CollisionCheck();
	
	/*Check for collisons in game and update score*/
	bool checkForCollision(PhysicsContact &contact, Layer* layer, Hud* hud);
private:

};
