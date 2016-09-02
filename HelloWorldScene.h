#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ImagePicker.h"
#include "RGB2JCH.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer, public cocos2d::ImagePickerDelegate
{
private:
    bool _scrolling;
    cocos2d::Vec2 _lastPoint;
    cocos2d::Vec2 _firstPoint;
    //int mCurrentCount;
    Label *labelofNo1_L;
    Label *labelofNo1_R;
    Label *labelofNo3_L;
    Label *labelofNo3_R;
    
public:
    static cocos2d::Scene* createScene();
    double Rounding(double x, int digit);
    
    
    void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
    
    
    cocos2d::Size visibleSize;
    cocos2d::Size origin;
    LayerColor *templayer;
    
    Label* labelofstatusBar;
    
    virtual bool init();
    
    void MakingChoice();
    void displayStatus(float *Jptr, float *amptr, float *bmptr);
    void count(Label *lbl, int from, int to, float interval);
    void increaseCountRight(Label *lbl, int *mCurrentCount);
    void count1(Label *lbl, int from, int to, float interval);
    void increaseCountRight1(Label *lbl, int *mCurrentCount);
    void count2(Label *lbl, int from, int to, float interval);
    void increaseCountRight2(Label *lbl, int *mCurrentCount);
    //void increaseCountLeft(Label *lbl, int *mCurrentCount);
    void displayBottomBar(float *Jptr, float *amptr, float *bmptr);
    
    void didFinishPickingWithResult(cocos2d::Texture2D* result);
    void TrigerGetPixelData(Touch *touch);
    void getPixelData(Touch *touch, int *rptr, int *gptr, int *bptr, float *Tptr, float *hptr, float *Hptr, float *cieaptr, float *ciebptr, float *Jptr, float *Cptr, float *Qptr, float *acptr, float *bcptr, float *amptr, float *bmptr, float *asptr, float *bsptr);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
