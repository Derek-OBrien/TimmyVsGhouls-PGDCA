#include "LevelSelScene.h"

#include "GameScene.h"

USING_NS_CC;

Scene* LevelSel::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LevelSel::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LevelSel::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()){return false;}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"menu_images/CloseNormal.png",
		"menu_images/CloseSelected.png",
		CC_CALLBACK_1(LevelSel::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));


	// create and set position for Start Game button
	auto level0 = MenuItemImage::create(
		"levelbtns/zero.png",
		"levelbtns/zero.png",
		CC_CALLBACK_1(LevelSel::GoToGameScene, this, 0));

	level0->setPosition(Vec2(
		origin.x + visibleSize.width / 6,		//X Position
		(origin.y + visibleSize.height) - visibleSize.height /4));	//Y Position

	// create and set position for Settings
	auto level1 = MenuItemImage::create(
		"levelbtns/one.png",
		"levelbtns/one.png",
		CC_CALLBACK_1(LevelSel::GoToGameScene, this, 1));

	level1->setPosition(Vec2(
		origin.x + visibleSize.width / 2,		//X Position
		(origin.y + visibleSize.height) - visibleSize.height / 4));	//Y Position


	// create and set position for Settings
	auto level2 = MenuItemImage::create(
		"levelbtns/two.png",
		"levelbtns/two.png",
		CC_CALLBACK_1(LevelSel::GoToGameScene, this, 2));

	level2->setPosition(Vec2(
		(origin.x + visibleSize.width) - visibleSize.width / 6,		//X Position
		(origin.y + visibleSize.height) - visibleSize.height / 4));	//Y Position



	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);



	// add items to the menu
	menu->addChild(level0);
	menu->addChild(level1);
	menu->addChild(level2);

	this->addChild(menu, 1);

	//Add Label
	auto label = Label::createWithTTF("Select Level", "fonts/Marker Felt.ttf", 48);
	label->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	//Add Background
	auto bg = Sprite::create("bg2.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0);

	return true;
}


void LevelSel::menuCloseCallback(Ref* pSender){
	Director::getInstance()->end();
}

//Call Game Scene When Start Item Selected
void LevelSel::GoToGameScene(Ref* pSender, int x){


	UserDefault* ud = UserDefault::getInstance();
	ud->setIntegerForKey("level", x);
	ud->flush();

	//call next scene to load
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.1, scene));
}

