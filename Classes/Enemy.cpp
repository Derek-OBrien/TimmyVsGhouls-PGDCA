
#include "Enemy.h"



Enemy::Enemy(){
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}


void Enemy::spawnEnemy(int health, float speed, Layer* layer, int lane){

	auto enemySp = Sprite::create("enemy-hd-large.png");

	int yPos;

	switch (lane)
	{
	case 1:
		yPos = 450;
		break;
	case 2:
		yPos = 150;
		break;
	case 3:
		yPos = 250;
		break;
	case 4:
		yPos = 350;
		break;
	case 5:
		yPos = 450;
		break;
	case 6:
		yPos = 530;
		break;
	case 7:
		yPos = 630;
		break;
	case 8:
		yPos = 730;
		break;
	default:
		break;
	}

	enemySp->setPosition(Point(visibleSize.width, yPos));

	auto enemyMoveAction = MoveBy::create(speed, Point(-visibleSize.width - 200, 0));
	enemySp->runAction(enemyMoveAction);

	//Add to layer
	layer->addChild(enemySp, 3);
}



void Enemy::update(float dt){

}