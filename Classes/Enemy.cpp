
#include "Enemy.h"

#include "GameDefines.h"

Enemy::Enemy(){

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}


//Create enemy
void Enemy::create(int health, float speed, Layer* layer, int lane){

	auto enemySprite = Sprite::create("enemy.png");
	enemySprite->setAnchorPoint(Vec2(0, 0));

	auto enemyBody = PhysicsBody::createBox(Size(enemySprite->getContentSize().width / 2, enemySprite->getContentSize().height), PhysicsMaterial(0, 0.1, 0));
	enemyBody->setDynamic(true);
	enemyBody->setGravityEnable(true);
	enemySprite->setPhysicsBody(enemyBody);
	enemyBody->setCollisionBitmask(ENEMY_BITMASK);
	enemyBody->setTag(02);

	enemyBody->setContactTestBitmask(true);
	enemyBody->setRotationEnable(false);


	enemySprite->setPosition(Vec2(visibleSize.width, lane));

	auto enemyMoveAction = MoveBy::create(speed, Point(-visibleSize.width - enemySprite->getContentSize().width, 0));
	enemySprite->runAction(enemyMoveAction);

	
	//Add to layer
	layer->addChild(enemySprite, 3);
}



void Enemy::update(float dt){

}