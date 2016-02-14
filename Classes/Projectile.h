#pragma once

#include "cocos2d.h"

#include "Player.h"


USING_NS_CC;

class Projectile : public Sprite{

public:

	Projectile();

	void spawnProjectile(Vec2 position, Layer* layer);

	CREATE_FUNC(Projectile);

private:
	int m_damage;
};