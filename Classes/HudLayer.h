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

	Label* addAmountLabel();

	void setAmount(int a){ m_amount = a; };
	int getAmount(){ return m_amount; };

	void updateAmount(int amt);

private:
	int m_amount;
	Label* m_amountLabel;
	Size visibleSize;
	Vec2 origin;

};

#endif

