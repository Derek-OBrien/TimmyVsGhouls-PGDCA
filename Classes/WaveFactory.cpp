#include "WaveFactory.h"

#include "cocos2d.h"
USING_NS_CC;

WaveFactory::WaveFactory(){
	minLane = 0;
	maxLane = 6;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void WaveFactory::getData(int amo, int min, int max, float sp){

	minLane = min;
	maxLane = max;
	amount = amo;
	speed = sp;
}

void WaveFactory::createWave(Layer* layer){

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(minLane, maxLane); // guaranteed unbiased

	int randLane = uni(rng);

	enemy = new Enemy();
	enemy->create(100, speed, layer, getLane(randLane));

	if (enemy->getPositionX() < 0){
		CC_SAFE_DELETE(enemy);
	}
}

void WaveFactory::update(float dt){
		
}


int WaveFactory::getLane(int x){
	int l = 0;

	switch (x)
	{
	case 0:
		l = origin.y;
		break;
	case 1:
		l = origin.y + visibleSize.height / 8;
		break;
	case 2:
		l = origin.y + visibleSize.height / 4;
		break;
	case 3:
		l = (origin.y + visibleSize.height / 2) - visibleSize.height / 8;
		break;
	case 4:
		l = (origin.y + visibleSize.height / 2);
		break;
	case 5:
		l = (origin.y + visibleSize.height / 2) + visibleSize.height / 8;
		break;
	case 6:
		l = (origin.y + visibleSize.height / 2) + visibleSize.height / 4;
		break;
	default:
		break;
	}

	return l;
}