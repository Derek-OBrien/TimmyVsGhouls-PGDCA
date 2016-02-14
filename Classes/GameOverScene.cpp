
#include "GameOverScene.h"
#include "GameDefines.h"
#include "MainMenu.h"
#include "GameScene.h"
USING_NS_CC;


Scene* GameOverScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameOverScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"exit.png",
		"exit.png",
		CC_CALLBACK_1(GameOverScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));


	// create and set position for Start Game button
	auto restart = MenuItemImage::create(
		"menu_images/replay.png",
		"menu_images/replay.png",
		CC_CALLBACK_1(GameOverScene::restartLevel, this));

	restart->setPosition(Vec2(
		origin.x + visibleSize.width / 8,		//X Position
		origin.y + visibleSize.height / 2));	//Y Position



	// create and set position for Start Game button
	auto mainmenu = MenuItemImage::create(
		"menu_images/play.png",
		"menu_images/play.png",
		CC_CALLBACK_1(GameOverScene::gotoStart, this));

	mainmenu->setPosition(Vec2(
		origin.x + visibleSize.width - visibleSize.width / 8,		//X Position
		origin.y + visibleSize.height / 2));	//Y Position

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);

	menu->addChild(restart);
	menu->addChild(mainmenu);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	auto label = Label::createWithTTF("Game Over Scene", FONT, FONTSIZE);
	label->setColor(FONTCOLOR);

	label->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 + label->getContentSize().height));
	this->addChild(label, 1);

	
	auto sprite = Sprite::create("bg2.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	return true;
}


void GameOverScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameOverScene::gotoStart(Ref* pSender){
	auto scene = MainMenu::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameOverScene::restartLevel(Ref* pSender){
	//as current level is stored and read at start of game scene in order to restart game just reload game scene
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.1, scene));
}