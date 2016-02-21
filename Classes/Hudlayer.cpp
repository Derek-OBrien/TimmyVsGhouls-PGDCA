

#include "HudLayer.h"
#include "PauseScene.h"
#include "GameOverScene.h"

#include "SimpleAudioEngine.h"
Hud::Hud(){
	Hud::init();
}

bool Hud::init(){

	if (!Layer::init()){
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	//pause button
	auto pauseBtn = MenuItemImage::create(
		"menu_images/pause.png",
		"menu_images/pause.png",
		CC_CALLBACK_1(Hud::goToPauseScene, this));

	pauseBtn->setPosition(Vec2(
		origin.x + visibleSize.width /2 ,	
		origin.y + visibleSize.height - visibleSize.height / 8 - pauseBtn->getContentSize().height / 3));

	pauseBtn->setScaleY(0.5);
	auto menu = Menu::create(pauseBtn, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//create and add lables to hud
	m_PamountLabel = addPAmountLabel();
	m_EamountLabel = addEAmountLabel();
	m_timerLabel = addTimerLabel();

	this->addChild(m_PamountLabel, 2);
	this->addChild(m_EamountLabel, 2);
	this->addChild(m_timerLabel, 2);

	return true;
}

Label* Hud::addPAmountLabel(){
	m_Pamount = 0;
	auto temp = __String::createWithFormat("[ %i ]", getPAmount());
	m_PamountLabel = Label::createWithTTF(temp->getCString(), FONT, 120);
	m_PamountLabel->setPosition(Point(
		origin.x + visibleSize.width / 2 - visibleSize.width / 4 - m_PamountLabel->getContentSize().width,
		origin.y + visibleSize.height - visibleSize.height / 8 - m_PamountLabel->getContentSize().height / 2));

	m_PamountLabel->setColor(FONTCOLOR);
	return m_PamountLabel;
}

Label* Hud::addEAmountLabel(){
	m_Eamount = 0;
	auto temp = __String::createWithFormat("[ %i ]", getEAmount());
	m_EamountLabel = Label::createWithTTF(temp->getCString(), FONT, 120);
	m_EamountLabel->setPosition(Point(
		origin.x + visibleSize.width / 2 + visibleSize.width / 4 + m_EamountLabel->getContentSize().width,
		origin.y + visibleSize.height - visibleSize.height / 8 - m_EamountLabel->getContentSize().height / 2));

	m_EamountLabel->setColor(FONTCOLOR);
	return m_EamountLabel;
}

Label* Hud::addTimerLabel(){
	m_timer = 60;
	auto temp = __String::createWithFormat("[ %i ]", getTimer());
	m_timerLabel = Label::createWithTTF(temp->getCString(), FONT, 120);
	m_timerLabel->setPosition(Point(
		origin.x + visibleSize.width / 2 ,
		origin.y + visibleSize.height - m_timerLabel->getContentSize().height / 2));

	m_timerLabel->setColor(FONTCOLOR);
	return m_timerLabel;
}

//Update score label for player
void Hud::updatePAmount(int amt){
	m_Pamount += amt;
	auto temp = __String::createWithFormat("[ %i ]", getPAmount());
	m_PamountLabel->setString(temp->getCString());
}

//Update socre lable for enemy
void Hud::updateEAmount(int amt){
	m_Eamount += amt;
	auto temp = __String::createWithFormat("[ %i ]", getEAmount());
	m_EamountLabel->setString(temp->getCString());
}

//Update level Timer
void Hud::updateTimer(){

	m_timer -= 1;
	auto temp = __String::createWithFormat("[ %i ]", getTimer());
	m_timerLabel->setString(temp->getCString());

	if (m_timer == 0){

		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		UserDefault* ud = UserDefault::getInstance();

		/*Save Scores for current level*/
		char saveEscore[30] = { 0 };
		sprintf(saveEscore, "enemyScorelevel%d", ud->getIntegerForKey("level"));
		ud->setIntegerForKey(saveEscore, getEAmount());

		char savePscore[30] = { 0 };
		sprintf(savePscore, "playerScorelevel%d", ud->getIntegerForKey("level"));
		ud->setIntegerForKey(savePscore, getPAmount());

		auto scene = GameOverScene::createScene();
		Director::getInstance()->replaceScene(TransitionCrossFade::create(TRANSITION_TIME, scene));
	}
}


//Go to Pause Scene
void Hud::goToPauseScene(Ref* pSender){
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(TRANSITION_TIME, scene));
}
