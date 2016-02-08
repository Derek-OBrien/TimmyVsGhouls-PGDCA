#include "WaveFactory.h"

#include "cocos2d.h"
USING_NS_CC;

WaveFactory::WaveFactory(){
	minLane = 0;
	maxLane = 7;
}

void WaveFactory::createWave(int amount, int mil, int mxl, int speed, Layer* layer){

	//minLane = CCRANDOM_0_1() * 8;
	//maxLane = CCRANDOM_0_1() * 8;

	//int rndValue = minLane + std::rand() % (maxLane - minLane);

	std::random_device rd;     // only used once to initialise (seed) engine

	//enemy = new Enemy();

	for (size_t i = 0; i < amount; i++){
		enemy = new Enemy();
		std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
		std::uniform_int_distribution<int> uni(mil, mxl); // guaranteed unbiased

		auto random_integer = uni(rng);

		enemy->spawnEnemy(100, speed, layer, random_integer);
	}
}