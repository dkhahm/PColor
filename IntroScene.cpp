#include "IntroScene.h"

USING_NS_CC;
using namespace std;

Scene* Intro::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
   
    // 'layer' is an autorelease object
    auto layer = Intro::create();
    
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

Intro::~Intro()
{
    this->removeAllChildrenWithCleanup(true);
    Director::getInstance()->purgeCachedData();
}

// on "init" you need to initialize your instance
bool Intro::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    createIntroLayer();
    
    
    return true;
}


void Intro::createIntroLayer(){
    
    
    auto Backlayer = LayerColor::create(Color4B(240, 240, 240, 255));
    Backlayer->setContentSize(Size(visibleSize.width, visibleSize.height));
    this->addChild(Backlayer);
    
    
    auto labelofCamera = Label::createWithSystemFont("Something Else?", "Thonburi", 40, Size(500, 150), TextHAlignment::CENTER, TextVAlignment::TOP);
    labelofCamera->setColor(Color3B(0, 0, 0));
    labelofCamera->setAnchorPoint(Point(0.5, 1));
    labelofCamera->setPosition(Point(visibleSize.width/2, visibleSize.height*0.6));
    Backlayer->addChild(labelofCamera);
    
    
    
    /*
    auto greenCircle = Sprite::create("circle(green).png");
    greenCircle->setAnchorPoint(Point(0.5, 0.5));
    greenCircle->setOpacity(60);
    greenCircle->setPosition(Point(visibleSize.width/2, visibleSize.height*0.6+150));
    Backlayer->addChild(greenCircle);
    
    auto yellowCircle = Sprite::create("circle(yellow).png");
    yellowCircle->setAnchorPoint(Point(0.5, 0.5));
    yellowCircle->setOpacity(60);
    yellowCircle->setPosition(Point(visibleSize.width/2-150, visibleSize.height*0.6-150));
    Backlayer->addChild(yellowCircle);
    
    auto magentaCircle = Sprite::create("circle(magenta).png");
    magentaCircle->setAnchorPoint(Point(0.5, 0.5));
    magentaCircle->setOpacity(60);
    magentaCircle->setPosition(Point(visibleSize.width/2+150, visibleSize.height*0.6-150));
    Backlayer->addChild(magentaCircle);
    
    auto actionToCenter = MoveTo::create(3.0f, Point(visibleSize.width/2, visibleSize.height*0.6));
    auto ease_inout = EaseInOut::create(actionToCenter, 6.0f);
    
    FiniteTimeAction *actionToCenterwithPause = Sequence::create(DelayTime::create(1.0f), ease_inout, NULL);
    
    
    magentaCircle->runAction(actionToCenterwithPause->clone());
    yellowCircle->runAction(actionToCenterwithPause->clone());
    greenCircle->runAction(actionToCenterwithPause->clone());
    
    */
    /*
    //곰
    auto labelofIntro1 = Label::createWithSystemFont("G", "Thonburi", visibleSize.width*0.04, Size(visibleSize.width*0.2, visibleSize.height*0.2), TextHAlignment::CENTER, TextVAlignment::CENTER);
    labelofIntro1->setColor(Color3B(0, 188, 212));
    labelofIntro1->setPosition(Point(visibleSize.width*0.37, visibleSize.height*0.26));
    this->addChild(labelofIntro1, 2);
    
    auto action1 = MoveTo::create(0.4f, Point(visibleSize.width*0.37, visibleSize.height*0.33));
    labelofIntro1->runAction(action1);
    
    labelofIntro1->setOpacity(0);
    auto action11 = FadeTo::create(1.0f, 255);
    labelofIntro1->runAction(action11);
                                   
                                   
    
    //매
    auto labelofIntro2 = Label::createWithSystemFont("O", "Thonburi", visibleSize.width*0.04, Size(visibleSize.width*0.2, visibleSize.height*0.2), TextHAlignment::CENTER, TextVAlignment::CENTER);
    labelofIntro2->setColor(Color3B(0, 188, 212));
    labelofIntro2->setPosition(Point(visibleSize.width*0.4, visibleSize.height*0.26));
    labelofIntro2->setOpacity(0);
    this->addChild(labelofIntro2, 2);
    
    FiniteTimeAction * actionF2 = Sequence::create(DelayTime::create(0.1f), MoveTo::create(0.4f, Point(visibleSize.width*0.4, visibleSize.height*0.33)), NULL);
    labelofIntro2->runAction(actionF2);
    FiniteTimeAction * actionF22 = Sequence::create(DelayTime::create(0.1f),FadeTo::create(1.0f, 255), NULL);
    labelofIntro2->runAction(actionF22);
    
    
    auto labelofIntro3 = Label::createWithSystemFont("M", "Thonburi", visibleSize.width*0.04, Size(visibleSize.width*0.2, visibleSize.height*0.2), TextHAlignment::CENTER, TextVAlignment::CENTER);
    labelofIntro3->setColor(Color3B(0, 188, 212));
    labelofIntro3->setPosition(Point(visibleSize.width*0.43, visibleSize.height*0.26));
    labelofIntro3->setOpacity(0);
    this->addChild(labelofIntro3, 2);
    
    FiniteTimeAction * actionF3 = Sequence::create(DelayTime::create(0.2f), MoveTo::create(0.4f, Point(visibleSize.width*0.43, visibleSize.height*0.33)), NULL);
    labelofIntro3->runAction(actionF3);
    FiniteTimeAction * actionF33 = Sequence::create(DelayTime::create(0.2f), FadeTo::create(1.0f, 255), NULL);
    labelofIntro3->runAction(actionF33);
    
    
    
    auto labelofIntro4 = Label::createWithSystemFont("M", "Thonburi", visibleSize.width*0.04, Size(visibleSize.width*0.2, visibleSize.height*0.2), TextHAlignment::CENTER, TextVAlignment::CENTER);
    labelofIntro4->setColor(Color3B(0, 188, 212));
    labelofIntro4->setPosition(Point(visibleSize.width*0.46, visibleSize.height*0.26));
    labelofIntro4->setOpacity(0);
    this->addChild(labelofIntro4, 2);
    
    FiniteTimeAction * actionF4 = Sequence::create(DelayTime::create(0.3f), MoveTo::create(0.4f, Point(visibleSize.width*0.46, visibleSize.height*0.33)), NULL);
    labelofIntro4->runAction(actionF4);
    FiniteTimeAction * actionF44 = Sequence::create(DelayTime::create(0.3f),FadeTo::create(1.0f, 255), NULL);
    labelofIntro4->runAction(actionF44);
    
    
    auto labelofIntro5 = Label::createWithSystemFont("I", "Thonburi", visibleSize.width*0.04, Size(visibleSize.width*0.2, visibleSize.height*0.2), TextHAlignment::CENTER, TextVAlignment::CENTER);
    labelofIntro5->setColor(Color3B(0, 188, 212));
    labelofIntro5->setPosition(Point(visibleSize.width*0.48, visibleSize.height*0.26));
    labelofIntro5->setOpacity(0);
    this->addChild(labelofIntro5, 2);
    
    FiniteTimeAction * actionF5 = Sequence::create(DelayTime::create(0.4f), MoveTo::create(0.4f, Point(visibleSize.width*0.48, visibleSize.height*0.33)), NULL);
    labelofIntro5->runAction(actionF5);
    FiniteTimeAction * actionF55 = Sequence::create(DelayTime::create(0.4f), FadeTo::create(1.0f, 255), NULL);
    labelofIntro5->runAction(actionF55);
    
    
    
    auto labelofIntro6 = Label::createWithSystemFont("'", "Thonburi", visibleSize.width*0.04, Size(visibleSize.width*0.2, visibleSize.height*0.2), TextHAlignment::CENTER, TextVAlignment::CENTER);
    labelofIntro6->setColor(Color3B(0, 188, 212));
    labelofIntro6->setPosition(Point(visibleSize.width*0.49, visibleSize.height*0.26));
    labelofIntro6->setOpacity(0);
    this->addChild(labelofIntro6, 2);
    
    FiniteTimeAction * actionF6 = Sequence::create(DelayTime::create(0.5f), MoveTo::create(0.4f, Point(visibleSize.width*0.49, visibleSize.height*0.33)), NULL);
    labelofIntro6->runAction(actionF6);
    FiniteTimeAction * actionF66 = Sequence::create(DelayTime::create(0.5f), FadeTo::create(1.0f, 255), NULL);
    labelofIntro6->runAction(actionF66);
    
    
    
    auto labelofIntro7 = Label::createWithSystemFont("s", "Thonburi", visibleSize.width*0.04, Size(visibleSize.width*0.2, visibleSize.height*0.2), TextHAlignment::CENTER, TextVAlignment::CENTER);
    labelofIntro7->setColor(Color3B(0, 188, 212));
    labelofIntro7->setPosition(Point(visibleSize.width*0.505, visibleSize.height*0.26));
    labelofIntro7->setOpacity(0);
    this->addChild(labelofIntro7, 2);
    
    FiniteTimeAction * actionF7 = Sequence::create(DelayTime::create(0.6f), MoveTo::create(0.4f, Point(visibleSize.width*0.505, visibleSize.height*0.33)), NULL);
    labelofIntro7->runAction(actionF7);
    FiniteTimeAction * actionF77 = Sequence::create(DelayTime::create(0.6f), FadeTo::create(1.0f, 255), NULL);
    labelofIntro7->runAction(actionF77);
    
    
    
    auto labelofIntro8 = Label::createWithSystemFont("B", "Thonburi", visibleSize.width*0.04, Size(visibleSize.width*0.2, visibleSize.height*0.2), TextHAlignment::CENTER, TextVAlignment::CENTER);
    labelofIntro8->setColor(Color3B(0, 188, 212));
    labelofIntro8->setPosition(Point(visibleSize.width*0.55, visibleSize.height*0.26));
    labelofIntro8->setOpacity(0);
    this->addChild(labelofIntro8, 2);
    
    FiniteTimeAction * actionF8 = Sequence::create(DelayTime::create(0.7f), MoveTo::create(0.4f, Point(visibleSize.width*0.55, visibleSize.height*0.33)), NULL);
    labelofIntro8->runAction(actionF8);
    FiniteTimeAction * actionF88 = Sequence::create(DelayTime::create(0.7f),FadeTo::create(1.0f, 255), NULL);
    labelofIntro8->runAction(actionF88);
    
    
    
    auto labelofIntro9 = Label::createWithSystemFont("R", "Thonburi", visibleSize.width*0.04, Size(visibleSize.width*0.2, visibleSize.height*0.2), TextHAlignment::CENTER, TextVAlignment::CENTER);
    labelofIntro9->setColor(Color3B(0, 188, 212));
    labelofIntro9->setPosition(Point(visibleSize.width*0.575, visibleSize.height*0.26));
    labelofIntro9->setOpacity(0);
    this->addChild(labelofIntro9, 2);
    
    FiniteTimeAction * actionF9 = Sequence::create(DelayTime::create(0.8f), MoveTo::create(0.4f, Point(visibleSize.width*0.575, visibleSize.height*0.33)), NULL);
    labelofIntro9->runAction(actionF9);
    FiniteTimeAction * actionF99 = Sequence::create(DelayTime::create(0.8f), FadeTo::create(1.0f, 255), NULL);
    labelofIntro9->runAction(actionF99);
  
    
    auto labelofIntro10 = Label::createWithSystemFont("e", "Thonburi", visibleSize.width*0.04, Size(visibleSize.width*0.2, visibleSize.height*0.2), TextHAlignment::CENTER, TextVAlignment::CENTER);
    labelofIntro10->setColor(Color3B(0, 188, 212));
    labelofIntro10->setPosition(Point(visibleSize.width*0.60, visibleSize.height*0.26));
    labelofIntro10->setOpacity(0);
    this->addChild(labelofIntro10, 2);
    
    FiniteTimeAction * actionF10 = Sequence::create(DelayTime::create(0.9f), MoveTo::create(0.4f, Point(visibleSize.width*0.60, visibleSize.height*0.33)), NULL);
    labelofIntro10->runAction(actionF10);
    FiniteTimeAction * actionF101 = Sequence::create(DelayTime::create(0.9f), FadeTo::create(1.0f, 255), NULL);
    labelofIntro10->runAction(actionF101);
    
    auto labelofIntro11 = Label::createWithSystemFont("a", "Thonburi", visibleSize.width*0.04, Size(visibleSize.width*0.2, visibleSize.height*0.2), TextHAlignment::CENTER, TextVAlignment::CENTER);
    labelofIntro11->setColor(Color3B(0, 188, 212));
    labelofIntro11->setPosition(Point(visibleSize.width*0.62, visibleSize.height*0.26));
    labelofIntro11->setOpacity(0);
    this->addChild(labelofIntro11, 2);
    
    FiniteTimeAction * actionF11 = Sequence::create(DelayTime::create(1.0f), MoveTo::create(0.4f, Point(visibleSize.width*0.62, visibleSize.height*0.33)), NULL);
    labelofIntro11->runAction(actionF11);
    FiniteTimeAction * actionF111 = Sequence::create(DelayTime::create(1.0f),FadeTo::create(1.0f, 255), NULL);
    labelofIntro11->runAction(actionF111);
    
    auto labelofIntro12 = Label::createWithSystemFont("D", "Thonburi", visibleSize.width*0.04, Size(visibleSize.width*0.2, visibleSize.height*0.2), TextHAlignment::CENTER, TextVAlignment::CENTER);
    labelofIntro12->setColor(Color3B(0, 188, 212));
    labelofIntro12->setPosition(Point(visibleSize.width*0.645, visibleSize.height*0.26));
    labelofIntro12->setOpacity(0);
    this->addChild(labelofIntro12, 2);
    
    FiniteTimeAction * actionF12 = Sequence::create(DelayTime::create(1.1f), MoveTo::create(0.4f, Point(visibleSize.width*0.645, visibleSize.height*0.33)), NULL);
    labelofIntro12->runAction(actionF12);
    FiniteTimeAction * actionF121 = Sequence::create(DelayTime::create(1.1f), FadeTo::create(1.0f, 255), NULL);
    labelofIntro12->runAction(actionF121);
    */
    
    
    
    
    
    FiniteTimeAction * action = Sequence::create(DelayTime::create(2.0f),
                                                 CallFunc::create([=]{Intro::changeSceneToOpfromIntro();}),
                                                 NULL);
    this->runAction(action);
    
    
}

void Intro::lineDraw(void)
{
    auto underlineDraw = DrawNode::create();
    addChild(underlineDraw, 2);
    
    underlineDraw->drawLine(Vec2(visibleSize.width*0.355, visibleSize.height*0.285), Vec2(visibleSize.width*0.65, visibleSize.height*0.285), Color4F(0.0, 0.737, 0.831, 1.0));
    
}


void Intro::changeSceneToOpfromIntro() {
    //  Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
    
    auto hScene = HelloWorld::createScene();
    auto pScene =
    //TransitionScene::create(0, hScene);
    TransitionFade::create(0, hScene, Color3B(240, 240, 240));
    //TransitionCrossFade::create(1.0f, hScene);
    
    //          TransitionCrossFade::create(1.0f, HelloWorld::createScene());
    //          TransitionRotoZoom::create(0.5f, hScene);
    //          TransitionFade::create(0.5f,hScene,Color3B::GREEN);
    //          TransitionFadeBL::create(0.5f,hScene);
    //          TransitionFadeDown::create(0.5f,hScene);
    //          TransitionFadeTR::create(0.5f,hScene);
    //          TransitionFadeUp::create(0.5f, hScene);
    //          TransitionFlipAngular::create(0.5f, hScene, TransitionScene::Orientation::LEFT_OVER);
    //          TransitionFlipX::create(0.5f, hScene, TransitionScene::Orientation::DOWN_OVER);
    //          TransitionFlipY::create(0.5f, hScene, TransitionScene::Orientation::UP_OVER);
    //          TransitionJumpZoom::create(3.0f, hScene); //시간이 충분히 커야 효과를 제대로 볼 수 있음.
    //          TransitionMoveInB::create(0.5f, hScene);
    //          TransitionMoveInL::create(0.5f, hScene);
    //          TransitionMoveInR::create(0.5f, hScene);
    //          TransitionMoveInT::create(0.5f, hScene);
    //          TransitionPageTurn::create(0.5f, hScene, false);
    //          TransitionProgress::create(0.5f, hScene); //앱이 죽어버립니다.
    //          TransitionProgressHorizontal::create(0.5f, hScene);
    //          TransitionProgressInOut::create(0.5f, hScene);
    //          TransitionProgressOutIn::create(0.5f, hScene);
    //          TransitionProgressRadialCCW::create(0.5f, hScene);
    //          TransitionProgressRadialCW::create(0.5f, hScene;
    //          TransitionProgressVertical::create(0.5f, hScene);
    //          TransitionRotoZoom::create(2.0f, hScene); //시간이 너무 짧으면 제대로 안보임
    //          TransitionScene::create(0.5f, hScene); //전환된 씬에서 터치가 동작하지 않음.
    //          TransitionSceneOriented::create(0.5f, hScene, TransitionScene::Orientation::RIGHT_OVER); //전환된 씬에서 터치 동작x
    //          TransitionShrinkGrow::create(0.5f, hScene);
    //          TransitionSlideInB::create(0.5f, hScene);
    //          TransitionSlideInL::create(0.5f, hScene);
    //          TransitionSlideInR::create(0.5f, hScene);
    //          TransitionSlideInT::create(0.5f, hScene);
    //          TransitionSplitCols::create(1.5f, hScene);
    //          TransitionSplitRows::create(1.5f, hScene);
    //          TransitionTurnOffTiles::create(0.5f, hScene);
    //          TransitionZoomFlipAngular::create(0.5f, hScene, TransitionScene::Orientation::DOWN_OVER);
    //          TransitionZoomFlipX::create(0.5f, hScene, TransitionScene::Orientation::LEFT_OVER);
    //          TransitionZoomFlipY::create(0.5f, hScene, TransitionScene::Orientation::RIGHT_OVER);
    
    Director::getInstance()->replaceScene(pScene);
}








