#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Enemy : public Sprite{
public:

	Enemy();

	Enemy* spawnEnemy(int health, float speed, Layer* layer, int lane );

	Vec2 getPosition(){ return enemySprite->getPosition(); }
	void update(float dt);


	void setHealth(int health){ m_health = health; }
	int getHealth(){ return m_health; }

	void setSpeed(float speed){ m_speed = speed; }
	float getSpeed(){ return m_speed; }

	CREATE_FUNC(Enemy);
private:
	PhysicsBody* enemyBody; // physics body of the player

	Enemy* enemy;
	Sprite* enemySprite;
	int m_health;
	float m_speed;

	MoveBy* enemyMoveAction;

};