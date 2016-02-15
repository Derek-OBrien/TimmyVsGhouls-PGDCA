#include "Ladder.h"



Ladder::Ladder(){

	m_ladderSprite = NULL;
}

Ladder::~Ladder(){}



void Ladder::create(Vec2 pos, Layer* layer){
	m_ladderSprite = Sprite::create("box.png");
	m_ladderSprite->setAnchorPoint(Vec2(0, 0));
	m_ladderSprite->setPosition(pos);
	layer->addChild(m_ladderSprite);
}