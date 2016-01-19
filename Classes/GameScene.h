//
// Created by Derek on 18/01/2016.
//

#ifndef PGDCA_GAMESCENE_H
#define PGDCA_GAMESCENE_H

#include "cocos2d.h"



class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};



#endif //PGDCA_GAMESCENE_H
