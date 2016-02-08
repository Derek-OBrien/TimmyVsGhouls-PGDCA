
#include "Enemy.h"



Enemy::Enemy(){

	//enemySprite = Sprite::create("enemy.png");
	m_speed = 0;
}


Enemy* Enemy::spawnEnemy(int health, float speed, Layer* layer, int lane){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->setSpeed(speed);
	this->enemySprite = Sprite::create("enemy.png");

	enemyBody = PhysicsBody::createBox(Size(enemySprite->getContentSize().width / 2, enemySprite->getContentSize().height), PhysicsMaterial(0, 0.1, 0));
	enemyBody->setDynamic(true);
	enemyBody->setGravityEnable(true);
	enemyBody->setCollisionBitmask(0x03);
	enemyBody->setContactTestBitmask(true);
	enemyBody->setRotationEnable(false);
	this->enemySprite->setPhysicsBody(enemyBody);

	enemySprite->setAnchorPoint(Vec2(0, 0));

	this->enemySprite->setPosition(Point(visibleSize.width, lane));

	//Add to layer
	layer->addChild(this, 3);

	enemyMoveAction = MoveBy::create(speed, Point(-visibleSize.width - 200, 0));
	this->enemyMoveAction->retain();

	return this;

}



void Enemy::update(float dt){
	

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->runAction(this->enemyMoveAction);
}