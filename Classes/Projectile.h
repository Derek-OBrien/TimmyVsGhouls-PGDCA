#pragma once

#include "cocos2d.h"

#include "Player.h"


USING_NS_CC;

class Projectile{

public:

	Projectile();

	void spawnProjectile(Vec2 position, Layer* layer);

private:
	int m_damage;
};