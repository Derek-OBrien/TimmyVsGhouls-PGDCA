#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"

class SpalshScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void goToMenu(float dt);
    
    // implement the "static create()" method manually
	CREATE_FUNC(SpalshScene);
};

#endif // __HELLOWORLD_SCENE_H__
