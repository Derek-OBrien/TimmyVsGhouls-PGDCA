
#include "Player.h"
#include "GameDefines.h"

USING_NS_CC;
Player::Player(){

	m_playerSprite = NULL;
}

//Create Player with physics
void Player::create(Vec2(pos), Layer* layer){

	m_currState = STILL;
	
	initActions(layer);
	

	playerBody = PhysicsBody::createBox(Size(m_playerSprite->getContentSize().width / 4, m_playerSprite->getContentSize().height), PhysicsMaterial(0, 0.1, 0));
	playerBody->setDynamic(true);
	playerBody->setGravityEnable(true);
	playerBody->setCollisionBitmask(PLAYER_BITMASK);
	playerBody->setContactTestBitmask(true);
	playerBody->setRotationEnable(false);
	m_playerSprite->setPhysicsBody(playerBody);


	m_playerSprite->setAnchorPoint(Vec2(0, 0));
	m_playerSprite->setPosition(pos);
}

//Update sprite position and Animation 
void Player::update(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int pState = getCurrentState();
	int pPosition = m_playerSprite->getPositionX();
	
	if (pState == LEFT){
		this->m_playerSprite->stopAllActions();
		if (m_playerSprite->getPositionX() > origin.x){

			auto moveBy = MoveTo::create(0.5f, Vec2((pPosition - 100), m_playerSprite->getPositionY()));
			m_playerSprite->runAction(moveBy);
			m_playerSprite->runAction(this->leftAction);
		}
	}
	else if (pState == RIGHT){
		this->m_playerSprite->stopAllActions();
		if (m_playerSprite->getPositionX() < origin.x + visibleSize.width / 4){

			auto moveBy = MoveTo::create(0.5f, Vec2((pPosition + 100), m_playerSprite->getPositionY()));
			m_playerSprite->runAction(moveBy);
			m_playerSprite->runAction(this->rightAction);
		}
	}
	else if (pState == CLIMB){
		this->m_playerSprite->stopAllActions();
		if (m_playerSprite->getPositionY() < visibleSize.height + origin.y - m_playerSprite->getContentSize().height){

			this->m_playerSprite->runAction(this->climbAction);
			m_playerSprite->getPhysicsBody()->applyImpulse(Vec2(0, 100), Vec2::ZERO);
		}
	}
	else if (pState == DROP){
		this->m_playerSprite->stopAllActions();
		if (m_playerSprite->getPositionY() < visibleSize.height + origin.y - m_playerSprite->getContentSize().height){

			this->m_playerSprite->runAction(this->dropAction);
			m_playerSprite->getPhysicsBody()->applyImpulse(Vec2(0, -100), Vec2::ZERO);
		}
	}
	else if (pState == STILL){
		this->m_playerSprite->stopAllActions();
	}
}

//Set up players animations
void Player::initActions(Layer* layer){

	playerBatch = SpriteBatchNode::create("stickman/player.png");
	cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("stickman/player.plist");

	//set initial sprite from SpriteBatch
	m_playerSprite = Sprite::createWithSpriteFrameName("wl_01.png");
	playerBatch->addChild(m_playerSprite);
	layer->addChild(playerBatch, 3);
	
	//Create frame vector
	Vector<SpriteFrame*> animFrames(5);
	char str[100] = { 0 };
	
	//Left Action
	for (int i = 1; i <= 5; i++){
		sprintf(str, "wr_0%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	this->leftAction = RepeatForever::create(Animate::create(animation));
	this->leftAction->retain();
		

	//Right Action
	animFrames.clear();
	for (int i = 1; i <= 5; i++){
		sprintf(str, "wl_0%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	this->rightAction = RepeatForever::create(Animate::create(animation));
	this->rightAction->retain();
		
	
	//Climb animation
	animFrames.clear();
	for (int i = 1; i <= 5; i++){
		sprintf(str, "c_0%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	this->climbAction = RepeatForever::create(Animate::create(animation));
	this->climbAction->retain();


	//Drop animation
	animFrames.clear();
	for (int i = 1; i <= 5; i++){
		sprintf(str, "c_0%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	this->dropAction = RepeatForever::create(Animate::create(animation));
	this->dropAction->retain();
	
}

//Release Animations Actions
void Player::releaseActions(){
	this->leftAction->release();
	this->rightAction->release();
	this->climbAction->release();
	this->dropAction->release();
}

//Get the players current position
Vec2 Player::getCurrentPosition(){ 
	return m_playerSprite->getPosition(); 
}
