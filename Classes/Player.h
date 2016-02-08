#pragma once
#include "cocos2d.h"

#include "Enemy.h"
#include "Projectile.h"

USING_NS_CC;

enum ePlayerState{
	LEFT,
	RIGHT,
	CLIMB,
	DROP,
	SHOOT,
	STILL
};


class Player : public Sprite{

public:

	Player();


	void create(Layer* layer);
	void update();

	void fireProjectile(Layer* layer);

	// setter and getter for player state
	int getCurrentState(){ return m_currState; };
	void setCurrentState( int state){ m_currState = state; };

	void changeAnimation(Layer* layer, int state);
	void releaseActions();

	Vec2 getCurrentPosition();


	Sprite* m_playerSprite;

protected:

	int m_currState;

	bool m_canFire;
	
	PhysicsBody* playerBody; // physics body of the player

	//Projectile* projectile;

	SpriteBatchNode* playerBatch;
	SpriteFrameCache* cache;

	// player animations
	Action* leftAction;
	Action* rightAction;
	Action* climbAction;
	Action* dropAction;
	Action* shootAction;
};

