
#include "Player.h"

USING_NS_CC;
Player::Player(){

	m_playerSprite = NULL;
}

//Create Tower on Touch
void Player::create(cocos2d::Vec2 spawnPos, Layer* layer){

	m_currState = STILL;
	m_playerSprite = Sprite::create("stickman/wl_01.png");
	
	m_playerSprite->setAnchorPoint(Vec2(0, 0));
	m_playerSprite->setPosition(spawnPos);
	layer->addChild(m_playerSprite, 2);
}

void Player::update(){

}

void Player::fireProjectile(){

}


void Player::changeAnimation(Layer* layer, int state){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vector<SpriteFrame*> animFrames(5);
	char str[100] = { 0 };
	auto animation = new Animation();

	switch (m_currState)
	{
	case LEFT:
		for (int i = 1; i < 5; i++){
			sprintf(str, "stickman/wl_0%d.png", i);
			auto frame = SpriteFrame::create(str, Rect(0, 0, 300, 300));
			animFrames.pushBack(frame);
		}
		animation = Animation::createWithSpriteFrames(animFrames, 0.4f);
		m_playerSprite->runAction(RepeatForever::create(Animate::create(animation)));
		if (m_playerSprite->getPositionX() > origin.x){
			m_playerSprite->setPositionX(m_playerSprite->getPositionX() - 2.0);
		}
		break;
	case RIGHT:
		for (int i = 1; i < 5; i++){
			sprintf(str, "stickman/wl_0%d.png", i);
			auto frame = SpriteFrame::create(str, Rect(0, 0, 300, 300));
			animFrames.pushBack(frame);
		}
		animation = Animation::createWithSpriteFrames(animFrames, 0.4f);
		m_playerSprite->runAction(RepeatForever::create(Animate::create(animation)));
		if (m_playerSprite->getPositionX() < origin.x + visibleSize.width / 4){
			m_playerSprite->setPositionX(m_playerSprite->getPositionX() + 2.0);
		}
		break;
	case CLIMB:
		for (int i = 1; i < 5; i++){
			sprintf(str, "stickman/c_0%d.png", i);
			auto frame = SpriteFrame::create(str, Rect(0, 0, 300, 300));
			animFrames.pushBack(frame);
		}
		animation = Animation::createWithSpriteFrames(animFrames, 0.4f);
		m_playerSprite->runAction(RepeatForever::create(Animate::create(animation)));

		if (m_playerSprite->getPositionY() < origin.y + visibleSize.height / 2){
			m_playerSprite->setPositionY(m_playerSprite->getPositionY() + 2.0);
		}

		break;
	case DROP:
		for (int i = 1; i < 5; i++){
			sprintf(str, "stickman/c_0%d.png", i);
			auto frame = SpriteFrame::create(str, Rect(0, 0, 300, 300));
			animFrames.pushBack(frame);
		}
		animation = Animation::createWithSpriteFrames(animFrames, 0.4f);
		m_playerSprite->runAction(RepeatForever::create(Animate::create(animation)));
		
		if (m_playerSprite->getPositionY() > origin.y - visibleSize.height / 2){
			m_playerSprite->setPositionY(m_playerSprite->getPositionY() - 2.0);
		}
		break;
	default:
		break;
	}
}


