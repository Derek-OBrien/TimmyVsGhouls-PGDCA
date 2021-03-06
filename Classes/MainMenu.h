#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "HttpConnection.h"
class MainMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// selector callbacks
	void GoToGameScene(Ref* pSender);		//Start Game Button
	void GoToSettingsScene(Ref* pSender);	//Settings Button
	void GoToStoreScene(Ref* pSender);		//Store Button

	HttpConnection* connection;
	// implement the "static create()" method manually
	CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_SCENE_H__
