#include "MainMenu.h"

#include "GameScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));


	// create and set position for Start Game button
	auto startItem = MenuItemImage::create(
		"PlayNormal.png",
		"PlaySelected.png",
		CC_CALLBACK_1(MainMenu::GoToGameScene, this));

	startItem->setScale(2, 2);
	startItem->setPosition(Vec2(
		origin.x + visibleSize.width / 4,		//X Position
		origin.y + visibleSize.height / 2));	//Y Position

	// create and set position for Settings
	auto settingsItem = MenuItemImage::create(
		"SettingsNormal.png",
		"SettingsSelected.png",
		CC_CALLBACK_1(MainMenu::GoToSettingsScene, this));

	settingsItem->setScale(2, 2);
	settingsItem->setPosition(Vec2(
		origin.x + visibleSize.width / 2,		//X Position
		origin.y + visibleSize.height / 2));	//Y Position


	
	
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);



	// add items to the menu
	menu->addChild(startItem);
	menu->addChild(settingsItem);


	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Menu", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "HelloWorld" splash screen"
	//auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	//sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	//this->addChild(sprite, 0);

	
	
	
	return true;
}


void MainMenu::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

//Call Game Scene When Start Item Selected
void MainMenu::GoToGameScene(Ref* pSender){
	//call next scene to load
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.1, scene));
}

//Call Settings Scene When Settings Item Selected
void MainMenu::GoToSettingsScene(Ref* pSender){
	//call next scene to load
	//auto scene = SettingsScene::createScene();
	//Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

