//
// Created by Derek on 18/01/2016.
//

#include "GameScene.h"
#include "GameOverScene.h"

#include "SimpleAudioEngine.h"  

USING_NS_CC;

Scene* GameScene::createScene(){
    auto scene = Scene::createWithPhysics();

	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, -9.8f));

    auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() ){return false;}

	//Play background audio depending on platform
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bg.mp3", true);
#else
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bg.wav", true);
#endif
	
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	//Add Background
	auto bg = Sprite::create("bg2.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(bg, 0);

	auto fg = Sprite::create("fg.png");
	fg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(fg, 10);


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


	//Add Contact Listener for Collision
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	//Add lane physics edges
	m_laneEdge = new LaneEdge();
	m_laneEdge->create(this);

	//Add Hud Layer
	m_hud = new Hud();
	this->addChild(m_hud, 20);

	//Add Player
	m_player = new Player();

	//Wave Factory For Enemies
	m_wf = new WaveFactory();

	//Load Level from plist
	loadLevel();

	//To call main Update
	this->scheduleUpdate();

	return true;
}


void GameScene::update(float dt){

	//m_player->update();
	this->schedule(schedule_selector(GameScene::updatePlayer), 0.2f);

	//Update timer and spawn enemies dependent on their level spawn rate
	this->schedule(schedule_selector(GameScene::updateTimer),1.0f);
	this->schedule(schedule_selector(GameScene::createWaves), m_spawnRate);

	//Check for touch and check which direction swipe was
	if (true == isTouchDown){
		if (initialTouchPos[0] - currentTouchPos[0] > visibleSize.width * 0.05){
			m_player->setCurrentState(LEFT);
			isTouchDown = false;
		}
		else if (initialTouchPos[0] - currentTouchPos[0] < -visibleSize.width * 0.05){
			m_player->setCurrentState(RIGHT);
			isTouchDown = false;
		}
		else if (initialTouchPos[1] - currentTouchPos[1] > visibleSize.width * 0.05){
			m_player->setCurrentState(DROP);
			isTouchDown = false;
		}
		else if (initialTouchPos[1] - currentTouchPos[1] < -visibleSize.width * 0.05){
			m_player->setCurrentState(CLIMB);
			isTouchDown = false;
		}
		else if (initialTouchPos[1] < m_player->getPositionY()){
			m_player->setCurrentState(TELEPORT);
			isTouchDown = false;
		}
	}

	/*if touch on right half of screen*/
	if (initialTouchPos[0] > visibleSize.width / 2 && isTouchDown){
		projectile->spawnProjectile(Vec2(
			m_player->getCurrentPosition().x + m_player->getContentSize().width / 2,
			m_player->getCurrentPosition().y + m_player->getContentSize().height ), this);

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/pew.mp3");
#else
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/pew.wav");
#endif
		isTouchDown = false;
	}
}

//Call hud update timer
void GameScene::updateTimer(float dt){
	m_hud->updateTimer();
}

//Update Player
void GameScene::updatePlayer(float dt){
	m_player->update();
}

//On Touch
bool GameScene::onTouchBegan(Touch *touch, Event * event){
	initialTouchPos[0] = touch->getLocation().x;
	initialTouchPos[1] = touch->getLocation().y;
	currentTouchPos[0] = touch->getLocation().x;
	currentTouchPos[1] = touch->getLocation().y;

	isTouchDown = true;
	return isTouchDown;
}
//Is touch a swipe
void GameScene::onTouchMoved(Touch *touch, Event * event){
	currentTouchPos[0] = touch->getLocation().x;
	currentTouchPos[1] = touch->getLocation().y;
}
//has Touch ended
void GameScene::onTouchEnded(Touch *touch, Event * event){
	isTouchDown = false;
}
//Is the touch cancled
void GameScene::onTouchCancelled(Touch *touch, Event *event){
	onTouchEnded(touch, event);
}


//OnContactBegin Call CheckCollision Class
bool GameScene::onContactBegin(PhysicsContact &contact){
	return collisionChecker->checkForCollision(contact, this, m_hud);
}



//Load Level from plist file
void GameScene::loadLevel(){

	//Get current level
	UserDefault* ud = UserDefault::getInstance();
	m_currentLevel = ud->getIntegerForKey("level");

	//level file
	char file[200] = { 0 };

	//Get level plist file for  assets folder (Note: Path different on different Platforms)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	sprintf(file, "../../Resources/level%d.plist", m_currentLevel);
	std::string levelsFile = FileUtils::getInstance()->fullPathForFilename(file);
#endif
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	sprintf(file, "level%d.plist", m_currentLevel);
	std::string levelsFile = FileUtils::getInstance()->fullPathForFilename(file);
#endif

	//read in full file as a map
	ValueMap m_levels = FileUtils::getInstance()->getValueMapFromFile(levelsFile);

	//Different Vectors for different level data
	auto& LadderData = m_levels["ladders"].asValueVector();
	auto& PlayerData = m_levels["player"].asValueVector();
	auto& MetaData = m_levels["meta"].asValueVector();

	/*
		Get player data from file
		and create palyer
	*/
	for (auto i = PlayerData.begin(); i != PlayerData.end(); i++){
		ValueMap& sdata = i->asValueMap();
		m_player->create(Vec2(sdata["posX"].asInt(), m_wf->getLane(sdata["posY"].asInt())), this);
	}

	/*
		Get Ladder data from file
		and create ladders
	*/
	for (auto i = LadderData.begin(); i != LadderData.end(); i++){
		ValueMap& sdata = i->asValueMap();
		createLadders(sdata["x"].asInt(), sdata["y"].asInt());
	}

	/*
		Get Level Meta Data
		contains lane numbers
		speed of ghouls
		and spawn rate
	*/
	for (auto i = MetaData.begin(); i != MetaData.end(); i++){
		ValueMap& sdata = i->asValueMap();
		
		int amount = sdata["amount"].asInt();
		int minLane = sdata["minlane"].asInt();
		int maxLane = sdata["maxlane"].asInt();
		float speed = sdata["speed"].asFloat();
		m_spawnRate = sdata["spawnrate"].asFloat();
		
		//pass it to the wave factory
		m_wf->getData(amount, minLane, maxLane, speed);
	}
}


//Create Waves
void GameScene::createWaves(float dt) {
	m_wf->createWave(this);
}


//Create the ladders 
void GameScene::createLadders(int x, int y){
	
	m_ladder = new Ladder();
	int pX;

	if (x == 0)
		pX = origin.x;
	
	if (x == 1)
		pX = origin.x + visibleSize.width / 8;
	
	m_ladder->create(Vec2(pX, m_wf->getLane(y)), this);
}

