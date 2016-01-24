
#include "Player.h"

USING_NS_CC;
Player::Player(){

	m_playerSprite = NULL;
}

//Create Tower on Touch
void Player::create(Layer* layer){

	m_currState = STILL;

	m_playerSprite = Sprite::create("stickman/wl_01.png");
	
	playerBody = PhysicsBody::createBox(Size(m_playerSprite->getContentSize().width / 2, m_playerSprite->getContentSize().height), PhysicsMaterial(0, 0.1, 0));
	playerBody->setDynamic(true);
	playerBody->setGravityEnable(true);
	playerBody->setCollisionBitmask(0x01);
	playerBody->setContactTestBitmask(true);
	playerBody->setRotationEnable(false);
	m_playerSprite->setPhysicsBody(playerBody);


	m_playerSprite->setAnchorPoint(Vec2(0, 0));
	m_playerSprite->setPosition(Vec2(0, 0));
	layer->addChild(m_playerSprite, 2);
}

void Player::update(){

}

void Player::fireProjectile(){

}


void Player::changeAnimation(Layer* layer, int state){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size windowSize = Director::getInstance()->getWinSize();

	Vector<SpriteFrame*> animFrames(5);
	char str[100] = { 0 };
	auto animation = new Animation();

	switch (m_currState)
	{
	case LEFT:
		for (int i = 1; i < 5; i++){
			sprintf(str, "stickman/wl_0%d.png", i);
			auto frame = SpriteFrame::create(str, Rect(0, 0, 150, 150));
			animFrames.pushBack(frame);
		}
		animation = Animation::createWithSpriteFrames(animFrames, 0.4f);
		m_playerSprite->runAction(RepeatForever::create(Animate::create(animation)));
		if (m_playerSprite->getPositionX() > origin.x){
			m_playerSprite->setPositionX(m_playerSprite->getPositionX() -5.0);
		}
		break;
	case RIGHT:
		for (int i = 1; i < 5; i++){
			sprintf(str, "stickman/wl_0%d.png", i);
			auto frame = SpriteFrame::create(str, Rect(0, 0, 150, 150));
			animFrames.pushBack(frame);
		}
		animation = Animation::createWithSpriteFrames(animFrames, 0.4f);
		m_playerSprite->runAction(RepeatForever::create(Animate::create(animation)));
		if (m_playerSprite->getPositionX() < origin.x + visibleSize.width / 4){
			m_playerSprite->setPositionX(m_playerSprite->getPositionX() + 5.0);
		}
		break;
	case CLIMB:
		for (int i = 1; i < 5; i++){
			sprintf(str, "stickman/c_0%d.png", i);
			auto frame = SpriteFrame::create(str, Rect(0, 0, 150, 150));
			animFrames.pushBack(frame);
		}
		animation = Animation::createWithSpriteFrames(animFrames, 0.4f);
		m_playerSprite->runAction(RepeatForever::create(Animate::create(animation)));

		if (m_playerSprite->getPositionY() < visibleSize.height + origin.y - m_playerSprite->getContentSize().height){
			m_playerSprite->setPositionY(m_playerSprite->getPositionY() + 5.0);
		}

		break;
	case DROP:
		for (int i = 1; i < 5; i++){
			sprintf(str, "stickman/c_0%d.png", i);
			auto frame = SpriteFrame::create(str, Rect(0, 0, 150, 150));
			animFrames.pushBack(frame);
		}
		animation = Animation::createWithSpriteFrames(animFrames, 0.4f);
		m_playerSprite->runAction(RepeatForever::create(Animate::create(animation)));
		
		if (m_playerSprite->getPositionY() > origin.y - visibleSize.height / 2){
			m_playerSprite->setPositionY(m_playerSprite->getPositionY() - 5.0);
		}
		break;
	default:
		break;
	}
}


