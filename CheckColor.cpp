#include "CheckColor.h"

USING_NS_CC;

bool CheckColor::init() {
    auto labelofCamera = Label::createWithSystemFont("Something Else?", "Thonburi", 30, Size(500, 150), TextHAlignment::CENTER, TextVAlignment::TOP);
    labelofCamera->setColor(Color3B(255, 255, 255));
    labelofCamera->setAnchorPoint(Point(0.5, 1));
    labelofCamera->setPosition(Point(750/2, 1334*0.218));
    this->addChild(labelofCamera);
    
    return true;
}

void CheckColor::startGameButtonCallback(Ref* pSender) {
    Scene* resultSceneWithAnimation = TransitionFade::create(2.0f, Intro::createScene());
    Director::getInstance()->replaceScene(resultSceneWithAnimation);
}