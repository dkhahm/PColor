#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class Intro : public cocos2d::Layer
{
private:
    cocos2d::Size visibleSize;
    cocos2d::Size origin;
    
    ~Intro();
    
public:
    
    
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    void changeSceneToOpfromIntro();
    void createIntroLayer();
    void lineDraw();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Intro);
};

#endif // __INTRO_SCENE_H__
