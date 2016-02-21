#include "MainMenu.h"

#include "GameScene.h"

#include "LevelSelScene.h"
USING_NS_CC;

Scene* MainMenu::createScene(){

	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);

	return scene;
}


bool MainMenu::init(){

	if (!Layer::init())	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"menu_images/exit.png",
		"menu_images/exit.png",
		CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));


	// create and set position for Start Game button
	auto startItem = MenuItemImage::create(
		"menu_images/play.png",
		"menu_images/play.png",
		CC_CALLBACK_1(MainMenu::GoToGameScene, this));

	startItem->setPosition(Vec2(
		origin.x + visibleSize.width / 4,		//X Position
		origin.y + visibleSize.height / 2));	//Y Position


	
	
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);



	// add items to the menu
	menu->addChild(startItem);
	this->addChild(menu, 1);

	
	auto label = Label::createWithTTF("Menu", FONT, FONTSIZE);
	label->setColor(FONTCOLOR);
	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);




	//Add Background
	auto bg = Sprite::create("bgmenu.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0);

	
	
	
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
	auto scene = LevelSel::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.1, scene));
}

//Call Settings Scene When Settings Item Selected
void MainMenu::GoToSettingsScene(Ref* pSender){

}

