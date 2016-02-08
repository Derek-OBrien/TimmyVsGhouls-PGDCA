
#include "Enemy.h"



Enemy::Enemy(){

	m_ypos = NULL;
}


void Enemy::spawnEnemy(int health, float speed, Layer* layer, int lane){


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto enemySp = Sprite::create("enemy.png");

	enemyBody = PhysicsBody::createBox(Size(enemySp->getContentSize().width / 2, enemySp->getContentSize().height), PhysicsMaterial(0, 0.1, 0));
	enemyBody->setDynamic(true);
	enemyBody->setGravityEnable(true);
	enemyBody->setCollisionBitmask(0x03);
	enemyBody->setContactTestBitmask(true);
	enemyBody->setRotationEnable(false);
	enemySp->setPhysicsBody(enemyBody);

	switch (lane)
	{
	case 0:
		m_ypos = origin.y;
		break;
	case 1:
		m_ypos = origin.y + visibleSize.height / 8;
		break;
	case 2:
		m_ypos = origin.y + visibleSize.height / 4;
		break;
	case 3:
		m_ypos = (origin.y + visibleSize.height / 2) - visibleSize.height / 8;
		break;
	case 4:
		m_ypos = (origin.y + visibleSize.height / 2);
		break;
	case 5:
		m_ypos = (origin.y + visibleSize.height / 2) + visibleSize.height / 8;
		break;
	case 6:
		m_ypos = (origin.y + visibleSize.height / 2) + visibleSize.height / 4;
		break;
	case 7:
		m_ypos = (origin.y + visibleSize.height) - visibleSize.height / 8;
		break;
	default:
		break;
	}

	enemySp->setAnchorPoint(Vec2(0, 0));
	enemySp->setPosition(Point(visibleSize.width, m_ypos));

	auto enemyMoveAction = MoveBy::create(speed, Point(-visibleSize.width - 200, 0));
	enemySp->runAction(enemyMoveAction);

	//Add to layer
	layer->addChild(enemySp, 3);

	if (enemySp->getPositionX() < -100){
		layer->removeChild(enemySp, true);
	}
}



void Enemy::update(float dt){

}