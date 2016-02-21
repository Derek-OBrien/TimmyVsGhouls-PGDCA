#include "PauseScene.h"
#include "GameScene.h"
#include "LevelSelScene.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"
Scene* PauseScene::createScene(){

	auto scene = Scene::create();
	auto layer = PauseScene::create();

	scene->addChild(layer);

	return scene;
}

bool PauseScene::init(){

	if (!Layer::init()){ return false; }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto label = Label::createWithTTF("Pause", FONT, FONTSIZE);
	label->setColor(FONTCOLOR);
	label->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);


	// create and set position for Start Game button
	auto restart = MenuItemImage::create(
		"menu_images/replay.png",
		"menu_images/replay.png",
		CC_CALLBACK_1(PauseScene::restartLevel, this));

	restart->setPosition(Vec2(
		origin.x + visibleSize.width / 8,		//X Position
		origin.y + visibleSize.height / 2));	//Y Position


	// create and set position for Start Game button
	auto exit = MenuItemImage::create(
		"menu_images/exit.png",
		"menu_images/exit.png",
		CC_CALLBACK_1(PauseScene::exitGame, this));

	exit->setPosition(Vec2(
		origin.x + visibleSize.width / 2 - visibleSize.width / 8,		//X Position
		origin.y + visibleSize.height / 2));	//Y Position


	// create and set position for Start Game button
	auto returntogame = MenuItemImage::create(
		"menu_images/pause.png",
		"menu_images/pause.png",
		CC_CALLBACK_1(PauseScene::returnToGame, this));

	returntogame->setPosition(Vec2(
		origin.x + visibleSize.width / 2 + visibleSize.width / 8,		//X Position
		origin.y + visibleSize.height / 2));	//Y Position

	// create and set position for Start Game button
	auto mainmenu = MenuItemImage::create(
		"menu_images/play.png",
		"menu_images/play.png",
		CC_CALLBACK_1(PauseScene::gotoStart, this));

	mainmenu->setPosition(Vec2(
		origin.x + visibleSize.width - visibleSize.width / 8,		//X Position
		origin.y + visibleSize.height / 2));	//Y Position


	// create menu, it's an autorelease object
	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);

	// add items to the menu
	menu->addChild(restart);
	menu->addChild(exit);
	menu->addChild(returntogame);
	menu->addChild(mainmenu);


	this->addChild(menu, 1);

	//Add Background
	auto bg = Sprite::create("bgmenu.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0);

	return true;
}

void PauseScene::restartLevel(Ref* pSender){
	//as current level is stored and read at start of game scene in order to restart game just reload game scene
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.1, scene));
}

void PauseScene::exitGame(Ref* pSender){
	Director::getInstance()->end();
}

void PauseScene::gotoStart(Ref* pSender){
	auto scene = MainMenu::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void PauseScene::returnToGame(Ref* pSender){
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	auto scene = GameScene::createScene();
	Director::getInstance()->popScene();
}
