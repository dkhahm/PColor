#include "HelloWorldScene.h"
#include <vector>

#define Cover_Choice 10
#define Cover_Result 11
#define Cover_Clipping 13
#define Content_Image 14
#define Current_Possition 16
#define tempLayerForProgress 18


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}


bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    //log("visible size : %f, %f", visibleSize.width, visibleSize.height);
    //log("origin coor : %f, %f", origin.width, origin.height);
    
    MakingChoice();
    
    
    return true;
}

void HelloWorld::MakingChoice()
{
    if (getChildByTag(Cover_Result))
    {
        this->removeChildByTag(Cover_Result);
    }
    
    auto Backlayer = LayerColor::create(Color4B(240, 240, 240, 255));
    Backlayer->setContentSize(Size(visibleSize.width, visibleSize.height));
    Backlayer->setTag(Cover_Choice);
    this->addChild(Backlayer);
    
    auto magentaCircle = Sprite::create("circle(magenta).png");
    magentaCircle->setAnchorPoint(Point(0.5, 0.5));
    magentaCircle->setOpacity(30);
    magentaCircle->setPosition(Point(visibleSize.width/2, visibleSize.height*0.6));
    Backlayer->addChild(magentaCircle);

    auto labelofCamera = Label::createWithSystemFont("Camera", "Thonburi", 30, Size(500, 150), TextHAlignment::CENTER, TextVAlignment::TOP);
    labelofCamera->setColor(Color3B(0, 0, 0));
    labelofCamera->setAnchorPoint(Point(0.5, 1));
    labelofCamera->setPosition(Point(visibleSize.width*0.9, visibleSize.height/2));
    
    Backlayer->addChild(labelofCamera);
    
    auto labelofAlbum = Label::createWithSystemFont("Album", "Thonburi", 30, Size(500, 150), TextHAlignment::CENTER, TextVAlignment::TOP);
    labelofAlbum->setColor(Color3B(0, 0, 0));
    labelofAlbum->setAnchorPoint(Point(0.5, 1));
    labelofAlbum->setPosition(Point(visibleSize.width*0.1, visibleSize.height/2));
    Backlayer->addChild(labelofAlbum);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [=](Touch *touch, Event* event)
    {
        log("touch began");
        return true;
    };
    
    listener->onTouchEnded = [=](Touch *touch, Event* event)
    {
        log("touch ended");
        auto touchPoint = touch->getLocation();
        
        if (touchPoint.x > visibleSize.width/2)
        {
            log("touchpoint : %f, visiblesize : %f", touchPoint.x, visibleSize.width/2);
            UserDefault::getInstance()->setStringForKey("ImageSource", "Camera");
        }
        else
        {
            UserDefault::getInstance()->setStringForKey("ImageSource", "Album");
        }
        
        ImagePicker::getInstance()->pickImage(this);
        //_eventDispatcher->removeAllEventListeners();
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, Backlayer);

}





void HelloWorld::didFinishPickingWithResult(cocos2d::Texture2D* result)
{
    if (result != nullptr)
    {
        if (getChildByTag(Cover_Choice))
        {
            this->removeChildByTag(Cover_Choice);
        }
        
        auto BacklayerResult = LayerColor::create(Color4B(240, 240, 240, 255));
        BacklayerResult->setContentSize(Size(visibleSize.width, visibleSize.height));
        BacklayerResult->setTag(Cover_Result);
        this->addChild(BacklayerResult);
        
        auto Greenlayer = LayerColor::create(Color4B(0, 150, 136, 255));
        Greenlayer->setContentSize(Size(visibleSize.width, visibleSize.height*0.38));
        Greenlayer->setPosition(Point(0, visibleSize.height*0.63));
        BacklayerResult->addChild(Greenlayer);
        
        auto GreenBandlayer = LayerColor::create(Color4B(0, 121, 107, 255));
        GreenBandlayer->setContentSize(Size(visibleSize.width, visibleSize.height*0.07));
        GreenBandlayer->setPosition(Point(0, visibleSize.height*0.57));
        BacklayerResult->addChild(GreenBandlayer);
        
        
        
        //클리핑 이미지 배경 삽입(흰색)
        auto CoverCircleForClipping = Sprite::create("circle(white).png");
        CoverCircleForClipping->setPosition(Point(visibleSize.width/2, visibleSize.height*0.752));
        CoverCircleForClipping->setAnchorPoint(Point(0.5, 0.5));
        BacklayerResult->addChild(CoverCircleForClipping);
        
        
        labelofstatusBar = Label::createWithSystemFont("CIECAM02 value", "Thonburi", 30, Size(700, 350), TextHAlignment::LEFT, TextVAlignment::TOP);
        labelofstatusBar->setColor(Color3B(255, 255, 255));
        labelofstatusBar->setAnchorPoint(Point(0.5, 1));
        labelofstatusBar->setPosition(Point(visibleSize.width/2, visibleSize.height*0.98));
        
        BacklayerResult->addChild(labelofstatusBar);
        
        
        ////////////cliping
        auto drawCover = DrawNode::create();
        // 정점 좌표 설정
        
        std::vector<Vec2> vecs;
        
        // 정점 수
        int vertices = 100;
        
        for (int i = 0; i <vertices; i ++)
        {
            vecs.push_back(Vec2 (300 * cos (3.14 / 180 * (360 * i / vertices)), 300 * sin (3.14 / 180 * (360 * i / vertices))));
        }
        drawCover->setPosition(Point(visibleSize.width/2, visibleSize.height * 0.7));
        drawCover->drawPolygon(&vecs[0], vertices, Color4F::WHITE, 0, Color4F::WHITE);
        
        auto clipping = ClippingNode::create();
        clipping->setTag(Cover_Clipping);
        clipping->setStencil(drawCover);
        //clipping->setInverted(true);
        clipping->setAlphaThreshold(1.0);
        BacklayerResult->addChild(clipping);
        
        auto colorImage = Sprite::createWithTexture(result);
        colorImage->setTag(Content_Image);
        colorImage->setPosition(visibleSize.width/2, visibleSize.height * 0.7);
        //colorImage->setContentSize(Size(visibleSize.width/2, visibleSize.height/2));
        colorImage->setAnchorPoint(Point(0.5, 0.5));
        clipping->addChild(colorImage);
        
        _scrolling = false;
        
        
        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
        listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
        listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, BacklayerResult);
        
        //클리핑 이미지 커버
        
        auto circleForClipping = Sprite::create("iosCircleOutline(big).png");
        circleForClipping->setPosition(Point(visibleSize.width/2, visibleSize.height*0.7));
        circleForClipping->setAnchorPoint(Point(0.5, 0.5));
        circleForClipping->setOpacity(80);
        BacklayerResult->addChild(circleForClipping);
        
        
        
        
        
        
        //BacklayerResult->addChild(colorImage);
        log("eh?");
    
        //동그라미 진도의 아래 깔리는 배경, 흰색 원
        auto circleForNo1 = Sprite::create("iosCircleOutline(black).png");
        circleForNo1->setPosition(Point(visibleSize.width*0.2, visibleSize.height*0.31));
        circleForNo1->setAnchorPoint(Point(0.5, 0));
        circleForNo1->setOpacity(20);
        BacklayerResult->addChild(circleForNo1);
        
        labelofNo1_L = Label::createWithSystemFont("Green", "Thonburi", 25, Size(200, 50), TextHAlignment::RIGHT, TextVAlignment::TOP);
        labelofNo1_L->setColor(Color3B(0, 0, 0));
        labelofNo1_L->setAnchorPoint(Point(1, 1));
        labelofNo1_L->setPosition(Point(visibleSize.width*0.18, visibleSize.height*0.32));
        BacklayerResult->addChild(labelofNo1_L);
        
        auto labelofNo1 = Label::createWithSystemFont("-", "Thonburi", 25, Size(200, 50), TextHAlignment::CENTER, TextVAlignment::TOP);
        labelofNo1->setColor(Color3B(0, 0, 0));
        labelofNo1->setAnchorPoint(Point(0.5, 1));
        labelofNo1->setPosition(Point(visibleSize.width*0.2, visibleSize.height*0.32));
        BacklayerResult->addChild(labelofNo1);
        
        labelofNo1_R = Label::createWithSystemFont("Red", "Thonburi", 25, Size(200, 50), TextHAlignment::LEFT, TextVAlignment::TOP);
        labelofNo1_R->setColor(Color3B(0, 0, 0));
        labelofNo1_R->setAnchorPoint(Point(0, 1));
        labelofNo1_R->setPosition(Point(visibleSize.width*0.22, visibleSize.height*0.32));
        BacklayerResult->addChild(labelofNo1_R);
        
        
        auto circleForNo2 = Sprite::create("iosCircleOutline(black)_small.png");
        circleForNo2->setPosition(Point(visibleSize.width*0.5, visibleSize.height*0.31));
        circleForNo2->setAnchorPoint(Point(0.5, 0));
        circleForNo2->setOpacity(20);
        BacklayerResult->addChild(circleForNo2);
        
        auto labelofNo2 = Label::createWithSystemFont("Brightness", "Thonburi", 25, Size(200, 50), TextHAlignment::CENTER, TextVAlignment::TOP);
        labelofNo2->setColor(Color3B(0, 0, 0));
        labelofNo2->setAnchorPoint(Point(0.5, 1));
        labelofNo2->setPosition(Point(visibleSize.width/2, visibleSize.height*0.32));
        BacklayerResult->addChild(labelofNo2);
        
        auto circleForNo3 = Sprite::create("iosCircleOutline(black).png");
        circleForNo3->setPosition(Point(visibleSize.width*0.8, visibleSize.height*0.31));
        circleForNo3->setAnchorPoint(Point(0.5, 0));
        circleForNo3->setOpacity(20);
        BacklayerResult->addChild(circleForNo3);
    
        labelofNo3_L = Label::createWithSystemFont("Blue", "Thonburi", 25, Size(200, 50), TextHAlignment::RIGHT, TextVAlignment::TOP);
        labelofNo3_L->setColor(Color3B(0, 0, 0));
        labelofNo3_L->setAnchorPoint(Point(1, 1));
        labelofNo3_L->setPosition(Point(visibleSize.width*0.78, visibleSize.height*0.32));
        BacklayerResult->addChild(labelofNo3_L);
        
        auto labelofNo3 = Label::createWithSystemFont("-", "Thonburi", 25, Size(200, 50), TextHAlignment::CENTER, TextVAlignment::TOP);
        labelofNo3->setColor(Color3B(0, 0, 0));
        labelofNo3->setAnchorPoint(Point(0.5, 1));
        labelofNo3->setPosition(Point(visibleSize.width*0.8, visibleSize.height*0.32));
        BacklayerResult->addChild(labelofNo3);
        
        labelofNo3_R = Label::createWithSystemFont("Yellow", "Thonburi", 25, Size(200, 50), TextHAlignment::LEFT, TextVAlignment::TOP);
        labelofNo3_R->setColor(Color3B(0, 0, 0));
        labelofNo3_R->setAnchorPoint(Point(0, 1));
        labelofNo3_R->setPosition(Point(visibleSize.width*0.82, visibleSize.height*0.32));
        BacklayerResult->addChild(labelofNo3_R);
        
        /*
        //원형 구분용 드로우서클
        DrawNode *coverCircle = DrawNode::create();
        coverCircle->drawCircle(Vec2::ZERO, 300, 0, 360, false, 1, 1, Color4F(Color4B(200, 200, 200, 200)));
        coverCircle->setPosition(Point(visibleSize.width/2, visibleSize.height*0.7));
        BacklayerResult->addChild(coverCircle);
        */
        /*
        templayer = LayerColor::create(Color4B(100, 100, 100, 255), 200, 200);
        templayer->setPosition(Point(visibleSize.width/2, visibleSize.height*0));
        templayer->setIgnoreAnchorPointForPosition(false);
        templayer->setAnchorPoint(Point(0.5, 0));
        BacklayerResult->addChild(templayer);
        */
        
        
        auto BottomlayerStatus = LayerColor::create(Color4B(255, 255, 255, 255));
        BottomlayerStatus->setContentSize(Size(visibleSize.width, visibleSize.height*0.25));
        BacklayerResult->addChild(BottomlayerStatus);
        
        /*
        auto upperDraw = DrawNode::create();
        BacklayerResult->addChild(upperDraw);
        upperDraw->drawLine(Vec2(visibleSize.width*0.15, visibleSize.height*0.2), Vec2(visibleSize.width*0.85, visibleSize.height*0.2), Color4F(Color4B(230, 230, 230, 230)));
        */
        
        auto middleDraw = DrawNode::create();
        BacklayerResult->addChild(middleDraw);
        middleDraw->drawLine(Vec2(visibleSize.width*0.05, visibleSize.height*0.16), Vec2(visibleSize.width*0.95, visibleSize.height*0.16), Color4F(Color4B(230, 230, 230, 230)));
    
        auto bottomDraw = DrawNode::create();
        BacklayerResult->addChild(bottomDraw);
        bottomDraw->drawLine(Vec2(visibleSize.width*0.05, visibleSize.height*0.08), Vec2(visibleSize.width*0.95, visibleSize.height*0.08), Color4F(Color4B(230, 230, 230, 230)));
        
        
        auto gridlayer = LayerColor::create(Color4B(255, 255, 255, 255));
        gridlayer->setContentSize(Size(75, 40));
        gridlayer->setIgnoreAnchorPointForPosition(false);
        gridlayer->setAnchorPoint(Point(0.5, 0.5));
        gridlayer->setPosition(Point(visibleSize.width/2, visibleSize.height*0.25));
        BacklayerResult->addChild(gridlayer);
        
        auto gridIcon = Sprite::create("iosBarcode.png");
        gridIcon->setAnchorPoint(Point(0.5, 0.5));
        gridIcon->setPosition(Point(visibleSize.width/2, visibleSize.height*0.25));
        BacklayerResult->addChild(gridIcon);
        
        auto checkBoxRed = Sprite::create("CheckBox(red).png");
        checkBoxRed->setAnchorPoint(Point(0.5, 0.5));
        checkBoxRed->setPosition(Point(visibleSize.width*0.08, visibleSize.height*0.2));
        BacklayerResult->addChild(checkBoxRed);
        
        auto checkBoxCyam = Sprite::create("CheckBox(cyam).png");
        checkBoxCyam->setAnchorPoint(Point(0.5, 0.5));
        checkBoxCyam->setPosition(Point(visibleSize.width*0.08, visibleSize.height*0.12));
        BacklayerResult->addChild(checkBoxCyam);
        
        auto checkBoxOrange = Sprite::create("CheckBox(orange).png");
        checkBoxOrange->setAnchorPoint(Point(0.5, 0.5));
        checkBoxOrange->setPosition(Point(visibleSize.width*0.08, visibleSize.height*0.04));
        BacklayerResult->addChild(checkBoxOrange);
        
        
        auto labelofBottom1 = Label::createWithSystemFont("Skin Color : Pale White with beige tint", "Thonburi", 25, Size(700, 50), TextHAlignment::LEFT, TextVAlignment::CENTER);
        labelofBottom1->setColor(Color3B(0, 0, 0));
        labelofBottom1->setAnchorPoint(Point(0, 0.5));
        labelofBottom1->setPosition(Point(visibleSize.width*0.12, visibleSize.height*0.2));
        BacklayerResult->addChild(labelofBottom1);
        
        auto labelofBottom2 = Label::createWithSystemFont("Dominant Undertone : Light-Cool(T 4,133K)", "Thonburi", 25, Size(700, 50), TextHAlignment::LEFT, TextVAlignment::CENTER);
        labelofBottom2->setColor(Color3B(0, 0, 0));
        labelofBottom2->setAnchorPoint(Point(0, 0.5));
        labelofBottom2->setPosition(Point(visibleSize.width*0.12, visibleSize.height*0.12));
        BacklayerResult->addChild(labelofBottom2);
        
        auto labelofBottom3 = Label::createWithSystemFont("Recommended Color : Pink, Violet, Blue-based Red", "Thonburi", 25, Size(700, 50), TextHAlignment::LEFT, TextVAlignment::CENTER);
        labelofBottom3->setColor(Color3B(0, 0, 0));
        labelofBottom3->setAnchorPoint(Point(0, 0.5));
        labelofBottom3->setPosition(Point(visibleSize.width*0.12, visibleSize.height*0.04));
        BacklayerResult->addChild(labelofBottom3);
    
    }
    
    /*
    
    //sample->setPosition(visibleSize.width/2, visibleSize.height/2);
    
    Size szSprite = sample->getContentSize();
    RenderTexture* pRT = RenderTexture::create(500, 500);
    pRT->beginWithClear(1, 1, 1, 0);
    sample->retain();
    sample->visit();
    pRT->end();
    
    pRT->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(pRT, 100000);

    
    std::shared_ptr<Image> image(new Image);
    image->initWithImageFile("circle(cyam).png");
    
    
    
    Image* pImage = pRT->newImage();
    
    //7. 이미지 데이터 얻기
    unsigned char* pData = pImage->getData();
    
    //8. RGBA 값 얻기
    
    for(int i = 0; i < szSprite.width; ++i)
    {
        for(int j = 0; j < szSprite.height; ++j)
        {
            //좌표값이 다르기 때문 변동해도 됨
            unsigned char* pPixel = pData + (int)((i + (szSprite.height - j) * szSprite.width) * 4);
            unsigned char r = *pPixel;
            unsigned char g = *(pPixel + 1);
            unsigned char b = *(pPixel + 2);
            unsigned char a = *(pPixel + 3);
            log("x : %i, y : %i\r\nRGBA : %i, %i, %i, %i", i, j, r, g, b, a);
        }
    }

*/
}



void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
    log("touch began");
    Touch *touch = touches.front();
    auto clipper = this->getChildByTag(Cover_Result)->getChildByTag(Cover_Clipping);
    Vec2 point = clipper->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
   
    _lastPoint = point;
    _firstPoint = point;
    
    auto determinInOut = sqrtf(pow(std::abs(touch->getLocation().x - visibleSize.width/2), 2)+pow(std::abs(touch->getLocation().y - visibleSize.height * 0.7), 2));
    log("%f", determinInOut);
    
    if(determinInOut < 300) _scrolling = true;
    else _scrolling = false;
    
    //auto rect = Rect(visibleSize.width/2-300, visibleSize.height/2-300, 600, 600);
    //_scrolling = rect.containsPoint(point);

}

void HelloWorld::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    log("touch moved");
    if (!_scrolling) return;
    Touch *touch = touches[0];
    auto clipper = this->getChildByTag(Cover_Result)->getChildByTag(Cover_Clipping);
    auto point = clipper->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
    Vec2 diff = point - _lastPoint;
    auto content = clipper->getChildByTag(Content_Image);
    content->setPosition(content->getPosition() + diff);
    _lastPoint = point;
}

void HelloWorld::onTouchesEnded(const std::vector<Touch*>& touches, Event  *event)
{
    auto firstClick = touches.front();
    
    log("touch ended");
    
    if (!_scrolling)
    {
        if(firstClick->getLocation().y > visibleSize.height*0.95)
        {
            log("%f", firstClick->getLocation().y);
            MakingChoice();
        }
        return;
    }
    
    if(_firstPoint == _lastPoint)
    {
        TrigerGetPixelData(firstClick);
        
    }
    _scrolling = false;
}

void HelloWorld::TrigerGetPixelData(Touch *touch)
{
    int r = 0, g = 0, b = 0;
    float T = 0.0, h = 0.0, H = 0.0, ciea = 0.0, cieb = 0.0, J = 0.0, C = 0.0, Q = 0.0, ac = 0.0, bc =0.0, am = 0.0, bm = 0.0, as = 0.0, bs =0.0;
    int *rptr, *gptr, *bptr;
    float *Tptr, *hptr, *Hptr, *cieaptr, *ciebptr, *Jptr, *Cptr, *Qptr, *acptr, *bcptr, *amptr, *bmptr, *asptr, *bsptr;
    rptr = &r;
    gptr = &g;
    bptr = &b;
    Tptr = &T;
    hptr = &h;
    Hptr = &H;
    cieaptr = &ciea;
    ciebptr = &cieb;
    Jptr = &J;
    Cptr = &C;
    Qptr = &Q;
    acptr = &ac;
    bcptr = &bc;
    amptr = &am;
    bmptr =&bm;
    asptr = &as;
    bsptr = &bs;
    
    getPixelData(touch, rptr, gptr, bptr, Tptr, hptr, Hptr, cieaptr, ciebptr, Jptr, Cptr, Qptr, acptr, bcptr, amptr, bmptr, asptr, bsptr);

}



void HelloWorld::getPixelData(Touch *touch, int *rptr, int *gptr, int *bptr, float *Tptr, float *hptr, float *Hptr, float *cieaptr, float *ciebptr, float *Jptr, float *Cptr, float *Qptr, float *acptr, float *bcptr, float *amptr, float *bmptr, float *asptr, float *bsptr)
{
    if (this->getChildByTag(Cover_Result)->getChildByTag(Cover_Clipping)->getChildByTag(Content_Image)->getChildByTag(Current_Possition))
    {
        this->getChildByTag(Cover_Result)->getChildByTag(Cover_Clipping)->getChildByTag(Content_Image)->removeChildByTag(Current_Possition);
    }
    
    
    auto glView = Director::getInstance()->getOpenGLView();
    auto frameSize = glView->getFrameSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    frameSize = frameSize * glView->getFrameZoomFactor() * glView->getRetinaFactor();
#endif
    
    int width = static_cast<int>(frameSize.width);
    int height = static_cast<int>(frameSize.height);
    
    //bool succeed = false;
    
    do
    {
        std::shared_ptr<GLubyte> buffer(new GLubyte[width * height * 4], [](GLubyte* p){ CC_SAFE_DELETE_ARRAY(p); });
        if (!buffer)
        {
            break;
        }
        
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer.get());
        
        std::shared_ptr<GLubyte> flippedBuffer(new GLubyte[width * height * 4], [](GLubyte* p) { CC_SAFE_DELETE_ARRAY(p); });
        if (!flippedBuffer)
        {
            break;
        }
        
        for (int row = 0; row < height; ++row)
        {
            memcpy(flippedBuffer.get() + (height - row - 1) * width * 4, buffer.get() + row * width * 4, width * 4);
        }
        std::shared_ptr<Image> image(new Image);
        if (image)
        {
            if(!image->initWithRawData(flippedBuffer.get(), width * height * 4, width, height, 8))
                break;
            
            //image->initWithRawData(flippedBuffer.get(), width * height * 4, width, height, 8);
            ////7. 이미지 데이터 얻기
            unsigned char* pData = image->getData();
            
            //float x1 = (VIEW_WIDTH - PAGEVIEW_WIDTH) / 2;
            //float x2 = x1 + PAGEVIEW_WIDTH;
            
            int sum_r, sum_g, sum_b;
            sum_r = 0;
            sum_g = 0;
            sum_b = 0;
            int cnt = 0;
            //8. RGBA 값 얻기
            
            
            auto touchPoint = touch->getLocation();
            int touchX = touchPoint.x/visibleSize.width*frameSize.width;
            int touchY = touchPoint.y/visibleSize.height*frameSize.height;
            
            int rectSize = 30/2;
            
            
            for(int i = touchX - rectSize; i < touchX + rectSize; ++i)
            {
                //if( x1 < i && i < x2) {
                    for(int j = touchY - rectSize ; j < touchY +rectSize; ++j)
                    {
                        
                        unsigned char* pPixel = pData + (int)((i + (frameSize.height - j) * frameSize.width) * 4);
                        unsigned char r = *pPixel;
                        unsigned char g = *(pPixel + 1);
                        unsigned char b = *(pPixel + 2);
                        sum_r += (int) r;
                        sum_g += (int) g;
                        sum_b += (int) b;
                        cnt++;
                        //log("R : %d, G : %d, B : %d, Count : %d", r, g, b, cnt);
                        
                        /*
                        auto dot = DrawNode::create();
                        
                        dot->drawDot(Point(i, j), 1, Color4F::RED);
                        this->addChild(dot);
                        */
                    }
                //}
            }
            
            
            
            
            
            log("visible size : %f, %f", visibleSize.width, visibleSize.height);
            log("origin coor : %f, %f", origin.width, origin.height);
            log("framesize : %f, %f", frameSize.width, frameSize.height);
            log("%d, %d", touchX, touchY);
            log("%d, %d, %d", sum_r/cnt, sum_g/ cnt, sum_b/ cnt);
            
            
            //*color = Color3B(sum_r/cnt, sum_g/ cnt, sum_b/ cnt);
            *rptr = sum_r/cnt;
            *gptr = sum_g/cnt;
            *bptr = sum_b/cnt;
            //templayer->initWithColor(Color4B(sum_r/cnt, sum_g/cnt, sum_b/cnt, 255), 200, 200);
            
            log("%d, %d, %d", *rptr, *gptr, *bptr);
            
            
            /////////caculate h (CIECAM02)
            //RGB2JCH::RGB2JCH();
            RGB2JCH::getCIECAM02h(rptr, gptr, bptr, Tptr, hptr, Hptr, cieaptr, ciebptr, Jptr, Cptr, Qptr, acptr, bcptr, amptr, bmptr, asptr, bsptr);
            
            
            
            //labelofstatusBar->setString(StringUtils::format("J : %g, C : %g, h : %g, H : %g\na : %g, b = %g, T = %g\nQ = %g, ac = %g, bc = %g\nam = %g, bm = %g\nas = %g, bs = %g", Rounding(*Jptr, 2), Rounding(*Cptr, 2), Rounding(*hptr, 2) ,Rounding(*Hptr, 2), Rounding(*cieaptr, 3), Rounding(*ciebptr, 3), Rounding(*Tptr, 2), Rounding(*Qptr, 2), Rounding(*acptr, 2), Rounding(*bcptr, 2), Rounding(*amptr, 2), Rounding(*bmptr, 2), Rounding(*asptr, 2), Rounding(*bsptr, 2)));
            
            log("%f, %f", *Tptr, *hptr);
            
            displayStatus(Jptr, amptr, bmptr);
            displayBottomBar(Jptr, amptr, bmptr);
            
            /*
             Touch *touch = touches[0];
             auto clipper = this->getChildByTag(11)->getChildByTag(13);
             auto point = clipper->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
             Vec2 diff = point - _lastPoint;
             auto content = clipper->getChildByTag(14);
             content->setPosition(content->getPosition() + diff);
             _lastPoint = point;
            */
            
            auto tempImage = this->getChildByTag(Cover_Result)->getChildByTag(Cover_Clipping)->getChildByTag(Content_Image);
            auto tempPoint = tempImage->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
            
            
            
            auto rectNode = DrawNode::create();
            Vec2 rectangle[4];
            rectangle[0] = Vec2(tempPoint.x-rectSize, tempPoint.y-rectSize);
            rectangle[1] = Vec2(tempPoint.x+rectSize, tempPoint.y-rectSize);
            rectangle[2] = Vec2(tempPoint.x+rectSize, tempPoint.y+rectSize);
            rectangle[3] = Vec2(tempPoint.x-rectSize, tempPoint.y+rectSize);
            
            Color4F white(1, 1, 1, 1);
            rectNode->drawLine(rectangle[0], rectangle[1], white);
            rectNode->drawLine(rectangle[1], rectangle[2], white);
            rectNode->drawLine(rectangle[2], rectangle[3], white);
            rectNode->drawLine(rectangle[3], rectangle[0], white);
            this->getChildByTag(Cover_Result)->getChildByTag(Cover_Clipping)->getChildByTag(Content_Image)->addChild(rectNode);
            //this->addChild(rectNode);
            rectNode->setTag(Current_Possition);
            
        
        }
    }while(0);
    
    
}

void HelloWorld::displayStatus(float *Jptr, float *amptr, float *bmptr)
{
    if (getChildByTag(Cover_Result)->getChildByTag(tempLayerForProgress))
    {
        this->getChildByTag(Cover_Result)->removeChildByTag(tempLayerForProgress);
    }
    
    labelofNo1_L->setColor(Color3B(0, 0, 0));
    labelofNo1_R->setColor(Color3B(0, 0, 0));
    labelofNo3_L->setColor(Color3B(0, 0, 0));
    labelofNo3_R->setColor(Color3B(0, 0, 0));
    
    
    int valueOfJ = (int)*Jptr;
    int valueOfr = (int)*amptr;
    int valueOfy = (int)*bmptr;
    log("a:%d, j:%d, b:%d", valueOfr, valueOfJ, valueOfy);
    
    auto layer_For_Progress = LayerColor::create(Color4B(255, 255, 255, 0));
    layer_For_Progress->setContentSize(Size(visibleSize.width, visibleSize.height/2));
    layer_For_Progress->setTag(tempLayerForProgress);
    this->getChildByTag(Cover_Result)->addChild(layer_For_Progress);
    
    
    //Red-green
    auto circleForNoRed = Sprite::create("iosCircleOutline(red).png");
    ProgressTimer *ppTforRed;
    ppTforRed = ProgressTimer::create(circleForNoRed);
    ppTforRed->setType(ProgressTimer::Type::RADIAL);
    ppTforRed->setPosition(Point(visibleSize.width*0.2, visibleSize.height*0.31));
    ppTforRed->setAnchorPoint(Point(0.5, 0));
    layer_For_Progress->addChild(ppTforRed);
    
    auto circleForNoGreen = Sprite::create("iosCircleOutline(green).png");
    ProgressTimer *ppTforGreen;
    ppTforGreen = ProgressTimer::create(circleForNoGreen);
    ppTforGreen->setType(ProgressTimer::Type::RADIAL);
    ppTforGreen->setReverseProgress(true);
    ppTforGreen->setPosition(Point(visibleSize.width*0.2, visibleSize.height*0.31));
    ppTforGreen->setAnchorPoint(Point(0.5, 0));
    layer_For_Progress->addChild(ppTforGreen);
    
    
    //Brightness
    auto circleForNoBright = Sprite::create("iosCircleOutline(cyam).png");
    ProgressTimer *ppTforBright;
    ppTforBright = ProgressTimer::create(circleForNoBright);
    ppTforBright->setType(ProgressTimer::Type::RADIAL);
    ppTforBright->setPosition(Point(visibleSize.width*0.5, visibleSize.height*0.31));
    ppTforBright->setAnchorPoint(Point(0.5, 0));
    layer_For_Progress->addChild(ppTforBright);
    
    //Yellow-Bule
    auto circleForNoYellow = Sprite::create("iosCircleOutline(yellow).png");
    ProgressTimer *ppTforYellow;
    ppTforYellow = ProgressTimer::create(circleForNoYellow);
    ppTforYellow->setType(ProgressTimer::Type::RADIAL);
    ppTforYellow->setPosition(Point(visibleSize.width*0.8, visibleSize.height*0.31));
    ppTforYellow->setAnchorPoint(Point(0.5, 0));
    layer_For_Progress->addChild(ppTforYellow);
    
    auto circleForNoBlue = Sprite::create("iosCircleOutline(blue).png");
    ProgressTimer *ppTforBlue;
    ppTforBlue = ProgressTimer::create(circleForNoBlue);
    ppTforBlue->setType(ProgressTimer::Type::RADIAL);
    ppTforBlue->setReverseProgress(true);
    ppTforBlue->setPosition(Point(visibleSize.width*0.8, visibleSize.height*0.31));
    ppTforBlue->setAnchorPoint(Point(0.5, 0));
    layer_For_Progress->addChild(ppTforBlue);
    
    //동그라미 진도를 오파시티 0에서 255까지 적용 2초에 걸쳐서
    auto fadeforRadial = Sequence::create(FadeTo::create(2.0f, 255),
                                          NULL);
    auto toRadial1 = ProgressTo::create(2.0f, std::abs(*amptr));
    auto toRadial2 = ProgressTo::create(2.0f, *Jptr);
    auto toRadial3 = ProgressTo::create(2.0f, std::abs(*bmptr));
    
    ppTforGreen->setOpacity(0);
    ppTforRed->setOpacity(0);
    if(valueOfr > 0)
    {
        ppTforRed->runAction(toRadial1->clone());//클론 기능은 나중에 공부좀 하자
        ppTforRed->runAction(fadeforRadial->clone());
    }
    else
    {
        ppTforGreen->runAction(toRadial1->clone());//클론 기능은 나중에 공부좀 하자
        ppTforGreen->runAction(fadeforRadial->clone());
    }
    
    ppTforBright->setOpacity(0);
    ppTforBright->runAction(toRadial2->clone());//클론 기능은 나중에 공부좀 하자
    ppTforBright->runAction(fadeforRadial->clone());
    
    ppTforYellow->setOpacity(0);
    ppTforBlue->setOpacity(0);
    if(valueOfy > 0)
    {
        ppTforYellow->runAction(toRadial3->clone());//클론 기능은 나중에 공부좀 하자
        ppTforYellow->runAction(fadeforRadial->clone());
    }
    else
    {
        ppTforBlue->runAction(toRadial3->clone());//클론 기능은 나중에 공부좀 하자
        ppTforBlue->runAction(fadeforRadial->clone());
    }
    
    auto labelofRed = Label::createWithSystemFont(std::string("0"), "Thonburi", 30, Size(visibleSize.width*0.2, visibleSize.height*0.2), TextHAlignment::CENTER, TextVAlignment::CENTER);
    labelofRed->setColor(Color3B(0, 0, 0));
    labelofRed->setPosition(Point(visibleSize.width*0.2, visibleSize.height*0.405));
    labelofRed->setAnchorPoint(Point(0.5, 0.5));
    labelofRed->setTag(21);
    layer_For_Progress->addChild(labelofRed);
    if(valueOfr != 0)
    {
        float Intervalr = 2.0f/(float)(abs(valueOfr));
        count(labelofRed, 0, valueOfr, Intervalr);
    }
    if(valueOfr < 0) labelofNo1_L->setColor(Color3B(29, 219, 22));
    if(valueOfr > 0) labelofNo1_R->setColor(Color3B(255, 0, 0));
    
    auto labelofBright = Label::createWithSystemFont(std::string("0"), "Thonburi", 30, Size(visibleSize.width*0.2, visibleSize.height*0.2), TextHAlignment::CENTER, TextVAlignment::CENTER);
    labelofBright->setColor(Color3B(0, 0, 0));
    labelofBright->setPosition(Point(visibleSize.width*0.5, visibleSize.height*0.385));
    labelofBright->setAnchorPoint(Point(0.5, 0.5));
    labelofBright->setTag(22);
    layer_For_Progress->addChild(labelofBright);
    if(valueOfJ != 0)
    {
        float IntervalJ = 2.0f/(float)(abs(valueOfJ));
        count(labelofBright, 0, valueOfJ, IntervalJ);
    }
    
    auto labelofYellow = Label::createWithSystemFont(std::string("0"), "Thonburi", 30, Size(visibleSize.width*0.2, visibleSize.height*0.2), TextHAlignment::CENTER, TextVAlignment::CENTER);
    labelofYellow->setColor(Color3B(0, 0, 0));
    labelofYellow->setPosition(Point(visibleSize.width*0.8, visibleSize.height*0.405));
    labelofYellow->setAnchorPoint(Point(0.5, 0.5));
    labelofYellow->setTag(23);
    layer_For_Progress->addChild(labelofYellow);
    if(valueOfy != 0)
    {
        float Intervaly = 2.0f/(float)(abs(valueOfy));
        count(labelofYellow, 0, valueOfy, Intervaly);
    }
    if(valueOfy < 0) labelofNo3_L->setColor(Color3B(0, 84, 255));
    if(valueOfy > 0) labelofNo3_R->setColor(Color3B(255, 200, 0));
    
    
}

void HelloWorld::count(Label *lbl, int from, int to, float interval)
{
    
    int times = abs(to);
    mCurrentCountR = from;
    mCurrentCountJ = from;
    mCurrentCountY = from;
    
    log("re!");
    lbl->setString(std::to_string(from));
    lbl->runAction(Repeat::create(Sequence::create(DelayTime::create(interval),
                                                   CallFunc::create(CC_CALLBACK_0(HelloWorld::increaseCountRight, this, lbl)),
                                                   NULL), times));
    log("%d", times);
}

void HelloWorld::increaseCountRight(Label *lbl)
{
    if(lbl->getTag() == 21) lbl->setString(std::to_string(++mCurrentCountR));
    if(lbl->getTag() == 22) lbl->setString(std::to_string(++mCurrentCountJ));
    if(lbl->getTag() == 23) lbl->setString(std::to_string(++mCurrentCountY));
    
    //log("%d, %d, %d", mCurrentCountR, mCurrentCountJ, mCurrentCountY);
}


void HelloWorld::displayBottomBar(float *Jptr, float *amptr, float *bmptr)
{
    
}



double HelloWorld::Rounding( double x, int digit )
{
    return ( floor( (x) * pow( float(10), digit ) + 0.5f ) / pow( float(10), digit ) );
}