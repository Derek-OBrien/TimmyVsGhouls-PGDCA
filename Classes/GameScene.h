//
// Created by Derek on 18/01/2016.
//

#ifndef PGDCA_GAMESCENE_H
#define PGDCA_GAMESCENE_H

#include "cocos2d.h"
#include "Player.h"
#include "Ladder.h"
#include "Enemy.h"
#include "WaveFactory.h"
#include "LaneEdges.h"
#include "Projectile.h"


#include <vector>

USING_NS_CC;

class GameScene : public Layer
{
public:
    static Scene* createScene();

    virtual bool init();

    
	// Get & Handle Touch
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	void onTouchCancelled(Touch *touch, Event *event);



	void update(float dt);
	//Spawn Game objects
	void createWaves(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);


	void loadLevel(int level);
private:

	//Set physics world
	void SetPhysicsWorld(PhysicsWorld *world) { sceneWorld = world; };
	PhysicsWorld *sceneWorld;


	Player* m_player;
	Enemy* enemy;
	Ladder* m_ladder;
	LaneEdge* m_laneEdge;
	WaveFactory* m_wf;
	Projectile* projectile;

	ValueMap* m_enemiesPool;
	//ValueMap m_levels;

	Vector<Ladder*> m_ladderPool;

	int m_currentLevel;
	int m_ladderPoolIndex;

	bool isTouchDown;

	float initialTouchPos[2];
	float currentTouchPos[2];


	void resetLevel(void);
	void levelCompleted(void);
	void createLadders(int x, int y);
	void clearLayer(void);

	int getLane(int x);
};



#endif //PGDCA_GAMESCENE_H
