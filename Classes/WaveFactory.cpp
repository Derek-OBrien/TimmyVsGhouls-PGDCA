#include "WaveFactory.h"

#include "cocos2d.h"
USING_NS_CC;

WaveFactory::WaveFactory(){

}

void WaveFactory::createWave(Layer* layer){

	int lane = CCRANDOM_0_1() * 8;

	enemy = new Enemy();

	enemy->spawnEnemy(100, 2, layer, lane);
}