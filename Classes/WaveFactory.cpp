#include "WaveFactory.h"

#include "cocos2d.h"
USING_NS_CC;

WaveFactory::WaveFactory(){
	lane = 1;
}

void WaveFactory::createWave(Layer* layer){

	lane = CCRANDOM_0_1() * 8;

	enemy = new Enemy();

	enemy->spawnEnemy(100, 5, layer, lane);
}