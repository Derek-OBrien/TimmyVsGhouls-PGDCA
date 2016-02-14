#ifndef _PAUSESCENE_
#define _PAUSESCENE_
#include "cocos2d.h"
#include "GameDefines.h"

USING_NS_CC;

class PauseScene : public Layer{
public:
	static Scene* createScene();

	virtual bool init();

	void restartLevel(Ref* pSender);
	void exitGame(Ref* pSender);
	void gotoStart(Ref* pSender);
	void returnToGame(Ref* pSender);

	CREATE_FUNC(PauseScene);

private:

};

#endif