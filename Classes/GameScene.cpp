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
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, -18.8f));


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


	//Add Player
	m_player = new Player();
	
	//Enemy Wave
	//m_wf = new WaveFactory();

	projectile = new Projectile();

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


	loadLevel(0);
	//To call main Update
	this->scheduleUpdate();

	return true;
}


void GameScene::update(float dt){

	//this->schedule(schedule_selector(GameScene::spawnWaves), 2);

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

	m_player->changeAnimation(this, m_player->getCurrentState());


	/*if touch on right half of screen*/
	if (initialTouchPos[0] > visibleSize.width / 2){
		m_player->fireProjectile(this);
	}
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



void GameScene::loadLevel(int level){

	//m_currentLevel = level;

	UserDefault* ud = UserDefault::getInstance();
	m_currentLevel = ud->getIntegerForKey("level");
	//ud->deleteValueForKey("level");
	char file[200] = { 0 };

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	sprintf(file, "../../Resources/level%d.plist", m_currentLevel);
	std::string levelsFile = FileUtils::getInstance()->fullPathForFilename(file);
#endif
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	sprintf(file, "level%d.plist", m_currentLevel);
	std::string levelsFile = FileUtils::getInstance()->fullPathForFilename(file);
#endif


	ValueMap m_levels = FileUtils::getInstance()->getValueMapFromFile(levelsFile);

	auto& LadderData = m_levels["ladders"].asValueVector();
	auto& EnemyData = m_levels["enemies"].asValueVector();
	auto& PlayerData = m_levels["player"].asValueVector();
	auto& MetaData = m_levels["meta"].asValueVector();
	auto& TestData = m_levels["test"].asValueVector();

	/*
		Gat MetaData data from file
	*/
	for (auto i = MetaData.begin(); i != MetaData.end(); i++){
		ValueMap& sdata = i->asValueMap();

	}
	/*
		Get player data from file
	*/
	for (auto i = PlayerData.begin(); i != PlayerData.end(); i++){
		ValueMap& sdata = i->asValueMap();
		m_player->create(Vec2(sdata["posX"].asInt(), getLane(sdata["posY"].asInt())), this);
	}

	/*
		Get Ladder data from file
	*/
	for (auto i = LadderData.begin(); i != LadderData.end(); i++){
		ValueMap& sdata = i->asValueMap();
		createLadders(sdata["x"].asInt(), sdata["y"].asInt());
	}

	/*
		Gat enemy data from file
	*/
	for (auto i = EnemyData.begin(); i != EnemyData.end(); i++){
		ValueMap& sdata = i->asValueMap();
		enemy = new Enemy();
		enemy->spawnEnemy(100, sdata["speed"].asInt(), this, sdata["lane"].asInt());
	}

	for (auto i = TestData.begin(); i != TestData.end(); i++){
		ValueMap& sdata = i->asValueMap();
		
		int amount = sdata["amount"].asInt();
		int minLane = sdata["minlane"].asInt();
		int maxLane = sdata["maxlane"].asInt();
		int speed = sdata["speed"].asInt();
		float spawnRate = sdata["spawnrate"].asFloat();
		

		//createWaves(spawnRate, minLane, maxLane, speed, amount);
		//enemy->spawnEnemy(100, sdata["speed"].asInt(), this, sdata["lane"].asInt());
	}
}

void GameScene::spawnWaves(float dt){

	for (int i = 0; i < m_enemiesPool.size(); i++){
		m_enemiesPool.at(i)->update(dt);
	}
}

//Create Waves
void GameScene::createWaves(float dt, int mil, int mxl, float speed, int num) {
	//m_wf->createWave(num,min,max,speed, this);


	std::random_device rd;     // only used once to initialise (seed) engine

	for (int i = 0; i < num; i++){
		std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
		std::uniform_int_distribution<int> uni(mil, mxl); // guaranteed unbiased
		auto randLane = uni(rng);

		enemy = new Enemy();

		m_enemiesPool.pushBack(enemy->spawnEnemy(100, speed, this, getLane(randLane)));
	}
}


void GameScene::createLadders(int x, int y){
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_ladder = new Ladder();

	int pX;

	switch (x){
	case 0:
		pX = origin.x;
		break;
	case 1:
		pX = origin.x + visibleSize.width / 8;
		break;
	default:
		break;
	}

	m_ladder->create(Vec2(pX, getLane(y)), this);

}

int GameScene::getLane(int x){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	int l = 0;

	switch (x)
	{
	case 0:
		l = origin.y;
		break;
	case 1:
		l = origin.y + visibleSize.height / 8;
		break;
	case 2:
		l = origin.y + visibleSize.height / 4;
		break;
	case 3:
		l = (origin.y + visibleSize.height / 2) - visibleSize.height / 8;
		break;
	case 4:
		l = (origin.y + visibleSize.height / 2);
		break;
	case 5:
		l = (origin.y + visibleSize.height / 2) + visibleSize.height / 8;
		break;
	case 6:
		l = (origin.y + visibleSize.height / 2) + visibleSize.height / 4;
		break;
	case 7:
		l = (origin.y + visibleSize.height) - visibleSize.height / 8;
		break;
	default:
		break;
	}

	return l;
}

void GameScene::clearLayer(void){}
void GameScene::resetLevel(void){}
void GameScene::levelCompleted(void){}

