
#include "Projectile.h"
#include "GameDefines.h"

Projectile::Projectile(){
	m_damage = 100;
}


void Projectile::spawnProjectile(Vec2 position, Layer* layer){


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto proSprite = Sprite::create("projectile.png");

	float posX = position.x;
	float posY = position.y;

	auto pyBody = PhysicsBody::createBox(Size(proSprite->getContentSize().width / 2, proSprite->getContentSize().height / 2), PhysicsMaterial(0, 0.1, 0));
	pyBody->setDynamic(true);
	pyBody->setGravityEnable(false);
	pyBody->setCollisionBitmask(PROJECTILE_BITMASK);
	pyBody->setContactTestBitmask(true);
	pyBody->setTag(01);

	proSprite->setPhysicsBody(pyBody);
	proSprite->setPosition(position.x, position.y + proSprite->getContentSize().height / 2);
	proSprite->setAnchorPoint(Vec2(0, 0));

	auto projectileMove = MoveBy::create(4, Vec2(visibleSize.width, 0));
	proSprite->runAction(projectileMove);

	layer->addChild(proSprite);

}
