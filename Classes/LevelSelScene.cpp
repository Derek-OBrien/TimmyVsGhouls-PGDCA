#include "LevelSelScene.h"

#include "GameScene.h"

USING_NS_CC;

Scene* LevelSel::createScene(){
	auto scene = Scene::create();
	auto layer = LevelSel::create();
	scene->addChild(layer);
	return scene;
}


bool LevelSel::init(){
	if (!Layer::init()){return false;}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"menu_images/exit.png",
		"menu_images/exit.png",
		CC_CALLBACK_1(LevelSel::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));


	//set up userdefault to store level details
	UserDefault* ud = UserDefault::getInstance();

	//if first time playing set level0 to true rest to false
	if (!ud->getBoolForKey("firstPlay")){
		ud->setBoolForKey("firstPlay", true);
	}
	if (ud->getBoolForKey("firsPlay")){
		ud->setBoolForKey("level0", true);
		ud->setBoolForKey("level1", false);
		ud->setBoolForKey("level2", false);
	}


	// create and set position for level button
	auto level0 = MenuItemImage::create(
		"levelbtns/zero.png",
		"levelbtns/zero.png",
		CC_CALLBACK_1(LevelSel::GoToGameScene, this, 0));

	level0->setPosition(Vec2(
		origin.x + visibleSize.width / 6,		//X Position
		(origin.y + visibleSize.height) - visibleSize.height /4));	//Y Position

	// create and set position for level 1 button
	//create two buttons one for open one for locked
	auto level1 = MenuItemImage::create(
		"levelbtns/one.png",
		"levelbtns/one.png",
		CC_CALLBACK_1(LevelSel::GoToGameScene, this, 1));

	level1->setPosition(Vec2(
		origin.x + visibleSize.width / 2,		//X Position
		(origin.y + visibleSize.height) - visibleSize.height / 4));	//Y Position

	auto level1X = MenuItemImage::create(
		"levelbtns/oneX.png",
		"levelbtns/oneX.png",
		CC_CALLBACK_1(LevelSel::onLockedButtonPress, this));

	level1X->setPosition(Vec2(
		origin.x + visibleSize.width / 2,		//X Position
		(origin.y + visibleSize.height) - visibleSize.height / 4));	//Y Position

	// create and set position for Level 2
	//create two buttons one for open one for locked
	auto level2 = MenuItemImage::create(
		"levelbtns/two.png",
		"levelbtns/two.png",
		CC_CALLBACK_1(LevelSel::GoToGameScene, this, 2));

	level2->setPosition(Vec2(
		(origin.x + visibleSize.width) - visibleSize.width / 6,		//X Position
		(origin.y + visibleSize.height) - visibleSize.height / 4));	//Y Position

	auto level2X = MenuItemImage::create(
		"levelbtns/twoX.png",
		"levelbtns/twoX.png",
		CC_CALLBACK_1(LevelSel::onLockedButtonPress, this));

	level2X->setPosition(Vec2(
		(origin.x + visibleSize.width) - visibleSize.width / 6,		//X Position
		(origin.y + visibleSize.height) - visibleSize.height / 4));	//Y Position


	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);



	// add items to the menu
	// Add locked buttons first time round
	menu->addChild(level0);
	menu->addChild(level1X);
	menu->addChild(level2X);

	//If levels unlockd replace locked buttons with normal
	if (ud->getBoolForKey("level1")){
		menu->addChild(level1);
		menu->removeChild(level1X, true);
	}
	if (ud->getBoolForKey("level2")){
		menu->addChild(level2);
		menu->removeChild(level2X, true);
	}


	this->addChild(menu, 1);

	//Add Label
	auto label = Label::createWithTTF("Select Level", FONT, FONTSIZE);
	label->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(FONTCOLOR);
	this->addChild(label, 1);

	//Add Background
	auto bg = Sprite::create("levelsbg.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0);

	return true;
}


void LevelSel::menuCloseCallback(Ref* pSender){
	Director::getInstance()->end();
}

//Call Game Scene When Start Item Selected
//Pass in level number which corrispondes to level
void LevelSel::GoToGameScene(Ref* pSender, int level){

	//Save level so it can be read in game scene
	UserDefault* ud = UserDefault::getInstance();
	ud->setIntegerForKey("level", level);
	
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.3, scene));
}

//If locked level button selected display message
void LevelSel::onLockedButtonPress(Ref* pSender){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("Level Not Unlocked", FONT, FONTSIZE);
	label->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2  - label->getContentSize().height / 2 ));
	label->setColor(FONTCOLOR);
	this->addChild(label, 1);
}