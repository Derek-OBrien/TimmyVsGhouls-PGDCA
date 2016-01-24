//
// Created by Derek on 18/01/2016.
//

#include "GameScene.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 18.8f));


    auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() ){return false;}


    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size windowSize = Director::getInstance()->getWinSize();

	//Add lane physics edges
	m_laneEdge = new LaneEdge();
	m_laneEdge->create(this);

	//Add Background
	auto bg = Sprite::create("bg2.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(bg, 0);

	auto fg = Sprite::create("fg.png");
	fg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(fg, 5);



	//Add Ladders
	m_ladder = new Ladder();
	m_ladder->create(Vec2(origin.x + visibleSize.width / 8, origin.y), this); //ok
	m_ladder->create(Vec2(origin.x, origin.y + visibleSize.height / 8), this); //ok
	m_ladder->create(Vec2(origin.x + visibleSize.width / 8, origin.y + visibleSize.height / 4), this); //ok
	m_ladder->create(Vec2(origin.x, (origin.y + visibleSize.height / 2 ) - visibleSize.height / 8), this); // ok
	m_ladder->create(Vec2(origin.x + visibleSize.width / 8, origin.y + visibleSize.height / 2), this); //ok
	m_ladder->create(Vec2(origin.x, (origin.y + visibleSize.height / 2) + visibleSize.height / 8), this);
	m_ladder->create(Vec2(origin.x + visibleSize.width / 8, (origin.y + visibleSize.height / 2) + visibleSize.height / 4), this);
	

	//Add Player
	m_player = new Player();
	m_player->create(this);

	//enemy = new Enemy();
	
	m_wf = new WaveFactory();


	//Add Touch Listener
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	
	isTouchDown = false;
	initialTouchPos[0] = 0;
	initialTouchPos[1] = 0;


	//To call main Update
	this->scheduleUpdate();

	return true;
}


void GameScene::update(float dt){

	this->schedule(schedule_selector(GameScene::createWaves), 0.5);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (true == isTouchDown){
		if (initialTouchPos[0] - currentTouchPos[0] > visibleSize.width * 0.05)
		{
			CCLOG("SWIPED LEFT");
			m_player->setCurrentState(LEFT);

			isTouchDown = false;
		}
		else if (initialTouchPos[0] - currentTouchPos[0] < -visibleSize.width * 0.05)
		{
			CCLOG("SWIPED RIGHT");
			m_player->setCurrentState(RIGHT);
			isTouchDown = false;
		}
		else if (initialTouchPos[1] - currentTouchPos[1] > visibleSize.width * 0.05)
		{
			CCLOG("SWIPED DOWN");
			m_player->setCurrentState(DROP);
			isTouchDown = false;
		}
		else if (initialTouchPos[1] - currentTouchPos[1] < -visibleSize.width * 0.05)
		{
			CCLOG("SWIPED UP");
			m_player->setCurrentState(CLIMB);
			isTouchDown = false;
		}
	}
	//else if (isTouchDown == false){
	//	m_player->setCurrentState(STILL);
	//}

	m_player->changeAnimation(this, m_player->getCurrentState());

}

//Create Waves
void GameScene::createWaves(float dt) {
	m_wf->createWave(this);
}


//On Touch
bool GameScene::onTouchBegan(Touch *touch, Event * event){
	initialTouchPos[0] = touch->getLocation().x;
	initialTouchPos[1] = touch->getLocation().y;
	currentTouchPos[0] = touch->getLocation().x;
	currentTouchPos[1] = touch->getLocation().y;

	isTouchDown = true;
	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event * event){
	currentTouchPos[0] = touch->getLocation().x;
	currentTouchPos[1] = touch->getLocation().y;
}

void GameScene::onTouchEnded(Touch *touch, Event * event){
	isTouchDown = false;
}


void GameScene::onTouchCancelled(Touch *touch, Event *event){
	onTouchEnded(touch, event);
}

