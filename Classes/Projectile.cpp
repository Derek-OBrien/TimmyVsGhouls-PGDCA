
#include "Projectile.h"


Projectile::Projectile(){
	m_damage = 100;
}


void Projectile::spawnProjectile(Vec2 position, Layer* layer){


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto proSprite =  Sprite::create("projectile.png");

	float posX = position.x;
	float posY = position.y;

	proSprite->setPosition(position.x, position.y);


	auto projectileMove = MoveBy::create(3, Vec2(visibleSize.width, position.y));
	proSprite->runAction(projectileMove);

	layer->addChild(proSprite, 3);
}
