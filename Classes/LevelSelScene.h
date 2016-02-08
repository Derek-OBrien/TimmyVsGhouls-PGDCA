#ifndef __LEVEL_SEL_H__
#define __LEVEL_SEL_H__

#include "cocos2d.h"

class LevelSel : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// selector callbacks
	void GoToGameScene(Ref* pSender, int x);		//Start Game Button


	//void LoadNewLevel(Ref* pSender, int x);
	// implement the "static create()" method manually
	CREATE_FUNC(LevelSel);

};

#endif // __LEVEL_SEL_H__
