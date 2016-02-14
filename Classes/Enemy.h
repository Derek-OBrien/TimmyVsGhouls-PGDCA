#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Enemy : public Sprite{
public:

	Enemy();

	void create(int health, float speed, Layer* layer, int lane );

	//Vec2 getPosition(){ return enemySprite->getPosition(); }
	void update(float dt);


	void setHealth(int health){ m_health = health; }
	int getHealth(){ return m_health; }

	CREATE_FUNC(Enemy);
private:


	// Size & Origin or screen
	Size visibleSize;
	Vec2 origin;

	//Sprite* enemySprite;
	//PhysicsBody* enemyBody;
	int m_health;

};