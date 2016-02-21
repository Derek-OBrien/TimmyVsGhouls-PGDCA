#include "WaveFactory.h"

#include "cocos2d.h"
USING_NS_CC;

WaveFactory::WaveFactory(){
	minLane = 0;
	maxLane = 5;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

//used to get data from game scene
void WaveFactory::getData(int amo, int min, int max, float sp){

	minLane = min;
	maxLane = max;
	amount = amo;
	speed = sp;
}

//create the wave with data from level files
void WaveFactory::createWave(Layer* layer){

	//generate random lane depending on level min / max lane
	std::random_device rd;    
	std::mt19937 rng(rd());   
	std::uniform_int_distribution<int> uni(minLane, maxLane);
	int randLane = uni(rng);

	//Create enemy on the lane
	enemy = new Enemy();
	enemy->create(100, speed, layer, getLane(randLane));

	if (enemy->getPositionX() < 0){
		CC_SAFE_DELETE(enemy);
	}
}

void WaveFactory::update(float dt){
		
}

//Lanes numbered 0 to 5 
//convert number to acutal position on screen
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
	default:
		break;
	}

	return l;
}