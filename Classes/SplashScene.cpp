#include "SplashScene.h"
#include "GameDefines.h"
#include "MainMenu.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* SpalshScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
	auto layer = SpalshScene::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool SpalshScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
	//Add Background
	auto bg = Sprite::create("bg2.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0);

	//Set Time to display
	this->schedule(CC_SCHEDULE_SELECTOR(SpalshScene::goToMenu), DISPLY_TIME_SPLASH_SCENCE);

	
	auto label = Label::createWithTTF("Timmy", FONT, FONTSIZE * 3);
	label->setColor(FONTCOLOR);
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2 - visibleSize.width /4,
		origin.y + visibleSize.height - visibleSize.height / 4));

	label->setRotation(-33);
    // add the label as a child to this layer
    this->addChild(label, 2);
    

	auto label2 = Label::createWithTTF("VS", FONT, FONTSIZE * 3);
	label2->setColor(FONTCOLOR);
	// position the label on the center of the screen
	label2->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - visibleSize.height / 4));

	// add the label as a child to this layer
	this->addChild(label2, 2);
    

	auto label3 = Label::createWithTTF("Ghoul", FONT, FONTSIZE * 3);
	label3->setColor(FONTCOLOR);
	// position the label on the center of the screen
	label3->setPosition(Vec2(origin.x + visibleSize.width - visibleSize.width / 4,
		origin.y + visibleSize.height - visibleSize.height /4));

	label3->setRotation(-33);
	// add the label as a child to this layer
	this->addChild(label3, 2);


	auto timmy = Sprite::create("timmy.png");
	timmy->setPosition(Vec2(
		origin.x + visibleSize.width / 4, 
		origin.y + visibleSize.height / 3 ));
	this->addChild(timmy, 1);
	
	auto ghoul = Sprite::create("enemy2.png");
	ghoul->setPosition(Vec2(
		origin.x + visibleSize.width - visibleSize.width / 4,
		origin.y + visibleSize.height / 3));
	this->addChild(ghoul, 1);

	return true;
}


void SpalshScene::goToMenu(float dt){

	//Preload Sounds
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/bg.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/pew.wav");
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/bg.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/pew.mp3");

#endif
	//call next scene to load
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME * 3, scene));
}
