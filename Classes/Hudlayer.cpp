

#include "HudLayer.h"

Hud::Hud(){
	Hud::init();
}

bool Hud::init(){

	if (!Layer::init()){
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	//pause button
	auto pauseBtn = MenuItemImage::create(
		"menu_images/PlayNormal.png",
		"menu_images/PlaySelected.png",
		CC_CALLBACK_1(Hud::goToPauseScene, this));

	pauseBtn->setPosition(Vec2(
		origin.x + visibleSize.width - pauseBtn->getContentSize().width,			//X Position
		origin.y + visibleSize.height - pauseBtn->getContentSize().height));		//Y Position

	auto menu = Menu::create(pauseBtn, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	m_amountLabel = addAmountLabel();

	this->addChild(m_amountLabel, 2);
	return true;
}

Label* Hud::addAmountLabel(){
	m_amount = 0;
	auto temp = __String::createWithFormat("[ %i ]", getAmount());
	m_amountLabel = Label::createWithTTF(temp->getCString(), FONT, FONTSIZE);
	m_amountLabel->setPosition(Point(
		origin.x + m_amountLabel->getContentSize().width / 2, 
		origin.y + visibleSize.height - m_amountLabel->getContentSize().height));

	m_amountLabel->setColor(FONTCOLOR);
	return m_amountLabel;
}



void Hud::updateAmount(int amt){
	m_amount += amt;
	auto temp = __String::createWithFormat("[ %i ]", getAmount());
	m_amountLabel->setString(temp->getCString());
	m_amountLabel->setPosition(Point(
		origin.x + m_amountLabel->getContentSize().width / 2,
		origin.y + visibleSize.height - m_amountLabel->getContentSize().height));

}

//Go to Pause Scene
void Hud::goToPauseScene(Ref* pSender){
	//auto scene = PauseScene::createScene();
	//Director::getInstance()->pushScene(TransitionFade::create(TRANSITION_TIME, scene));
}