#pragma once
#include "cocos2d.h"

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


	void create(Vec2(pos),Layer* layer);
	void update();

	// setter and getter for player state
	int getCurrentState(){ return m_currState; };
	void setCurrentState( int state){ m_currState = state; };

	void changeAnimation(Layer* layer, int state);
	void releaseActions();

	Vec2 getCurrentPosition();


	Sprite* m_playerSprite;

	bool canFire(){ return m_canFire; }
	void setCanFire(bool fire){ m_canFire = fire; }
protected:

	int m_currState;

	bool m_canFire;
	
	PhysicsBody* playerBody; // physics body of the player

	//Projectile* projectile;
	//Projectile projectile;

	SpriteBatchNode* playerBatch;
	SpriteFrameCache* cache;

	// player animations
	Action* leftAction;
	Action* rightAction;
	Action* climbAction;
	Action* dropAction;
	Action* shootAction;
};

