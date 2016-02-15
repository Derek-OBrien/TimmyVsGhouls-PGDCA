#ifndef _HUD_
#define _HUD_

#include "cocos2d.h"
#include "GameDefines.h"

USING_NS_CC;

class Hud : public Layer{
public:
	Hud();
	virtual bool init();
	void update();

	void goToPauseScene(Ref* pSender);

	CREATE_FUNC(Hud);

	Label* addPAmountLabel();
	Label* addEAmountLabel();
	Label* addTimerLabel();


	void setPAmount(int a){ m_Pamount = a; };
	int getPAmount(){ return m_Pamount; };

	void setEAmount(int a){ m_Eamount = a; };
	int getEAmount(){ return m_Eamount; };

	void setTimer(int a){ m_timer = a; };
	int getTimer(){ return m_timer; };

	void updatePAmount(int amt);
	void updateEAmount(int amt);
	void updateTimer();


private:
	int m_Pamount;
	int m_Eamount;
	int m_timer;

	Label* m_PamountLabel;
	Label* m_EamountLabel;
	Label* m_timerLabel;
	Size visibleSize;
	Vec2 origin;

};

#endif

