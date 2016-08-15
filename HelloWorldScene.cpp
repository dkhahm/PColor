#include "HelloWorldScene.h"
#include <vector>


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
    log("visible size : %f, %f", visibleSize.width, visibleSize.height);
    log("origin coor : %f, %f", origin.width, origin.height);
    
    MakingChoice();
    
    
    return true;
}

void HelloWorld::MakingChoice()
{
    if (getChildByTag(11))
    {
        this->removeChildByTag(11);
    }
    
    
    
    auto Backlayer = LayerColor::create(Color4B(255, 255, 255, 255));
    Backlayer->setContentSize(Size(visibleSize.width, visibleSize.height));
    Backlayer->setTag(10);
    this->addChild(Backlayer);
    
    auto labelofCamera = Label::createWithSystemFont("Camera", "Thonburi", 30, Size(500, 150), TextHAlignment::CENTER, TextVAlignment::TOP);
    labelofCamera->setColor(Color3B(0, 0, 0));
    labelofCamera->setAnchorPoint(Point(0.5, 1));
    labelofCamera->setPosition(Point(visibleSize.width*0.8, visibleSize.height/2));
    
    Backlayer->addChild(labelofCamera);
    
    auto labelofAlbum = Label::createWithSystemFont("Album", "Thonburi", 30, Size(500, 150), TextHAlignment::CENTER, TextVAlignment::TOP);
    labelofAlbum->setColor(Color3B(0, 0, 0));
    labelofAlbum->setAnchorPoint(Point(0.5, 1));
    labelofAlbum->setPosition(Point(visibleSize.width*0.2, visibleSize.height/2));
    
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
        
        if (getChildByTag(10))
        {
            this->removeChildByTag(10);
        }
        
        auto BacklayerResult = LayerColor::create(Color4B(255, 255, 255, 255));
        BacklayerResult->setContentSize(Size(visibleSize.width, visibleSize.height));
        BacklayerResult->setTag(11);
        this->addChild(BacklayerResult);
        
        labelofstatusBar = Label::createWithSystemFont("CIECAM02 value", "Thonburi", 30, Size(700, 150), TextHAlignment::CENTER, TextVAlignment::TOP);
        labelofstatusBar->setColor(Color3B(0, 0, 0));
        labelofstatusBar->setAnchorPoint(Point(0.5, 1));
        labelofstatusBar->setPosition(Point(visibleSize.width/2, visibleSize.height*0.98));
        
        BacklayerResult->addChild(labelofstatusBar);
        
        
        ////////////cliping
        auto drawCover = DrawNode :: create ();
        // 정점 좌표 설정
        
        std::vector<Vec2> vecs;
        
        // 정점 수
        int vertices = 100;
        
        for (int i = 0; i <vertices; i ++)
        {
            vecs.push_back(Vec2 (300 * cos (3.14 / 180 * (360 * i / vertices)), 300 * sin (3.14 / 180 * (360 * i / vertices))));
        }
        drawCover-> setPosition (Point (visibleSize.width / 2, visibleSize.height / 2));
        drawCover->drawPolygon (& vecs [0], vertices, Color4F::WHITE, 0, Color4F::WHITE);
        
        
        
        auto clipping = ClippingNode::create();
        clipping->setTag(13);
        clipping->setStencil(drawCover);
        //clipping->setInverted(true);
        clipping->setAlphaThreshold(1.0);
        BacklayerResult->addChild(clipping);
        
        
        auto colorImage = Sprite::createWithTexture(result);
        colorImage->setTag(14);
        colorImage->setPosition(visibleSize.width/2, visibleSize.height/2);
        //colorImage->setContentSize(Size(visibleSize.width/2, visibleSize.height/2));
        colorImage->setAnchorPoint(Point(0.5, 0.5));
        clipping->addChild(colorImage);
        
        //_scrolling = false;
        
        /*
        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
        listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
        listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, BacklayerResult);
        */
        
        //BacklayerResult->addChild(colorImage);
        log("eh?");
    
        int r = 0, g = 0, b = 0;
        float T = 0.0, h = 0.0, H = 0.0, ciea = 0.0, cieb = 0.0, J = 0.0, C = 0.0;
        int *rptr, *gptr, *bptr;
        float *Tptr, *hptr, *Hptr, *cieaptr, *ciebptr, *Jptr, *Cptr;
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
    
    
    
        log("%d, %d, %d", *rptr, *gptr, *bptr);
    
        
        //
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
            
            if (touchPoint.y < visibleSize.height*0.8)
            {
                log("get pixel data");
                getPixelData(touch, rptr, gptr, bptr, Tptr, hptr, Hptr, cieaptr, ciebptr, Jptr, Cptr);
            }
            
            else
            {
                log("return");
                MakingChoice();
            }
        };
    
    
    
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, BacklayerResult);
        
    
    
        templayer = LayerColor::create(Color4B(100, 100, 100, 255), 200, 200);
        templayer->setPosition(Point(visibleSize.width/2, visibleSize.height*0));
        templayer->setIgnoreAnchorPointForPosition(false);
        templayer->setAnchorPoint(Point(0.5, 0));
        BacklayerResult->addChild(templayer);
    
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

/*
void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
    log("touch began");
    Touch *touch = touches[0];
    auto clipper = this->getChildByTag(11)->getChildByTag(13);
    Vec2 point = clipper->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
    auto rect = Rect(0, 0, clipper->getContentSize().width, clipper->getContentSize().height);
    _scrolling = rect.containsPoint(point);
    _lastPoint = point;
}

void HelloWorld::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    log("touch moved");
    if (!_scrolling) return;
    Touch *touch = touches[0];
    auto clipper = this->getChildByTag(11)->getChildByTag(13);
    auto point = clipper->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
    Vec2 diff = point - _lastPoint;
    auto content = clipper->getChildByTag(14);
    content->setPosition(content->getPosition() + diff);
    _lastPoint = point;
}

void HelloWorld::onTouchesEnded(const std::vector<Touch*>& touches, Event  *event)
{
    log("touch ended");
    if (!_scrolling) return;
    _scrolling = false;
}
 */




void HelloWorld::getPixelData(Touch *touch, int *rptr, int *gptr, int *bptr, float *Tptr, float *hptr, float *Hptr, float *cieaptr, float *ciebptr, float *Jptr, float *Cptr)
{
    if (getChildByTag(10))
    {
        this->removeChildByTag(10);
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
            templayer->initWithColor(Color4B(sum_r/cnt, sum_g/cnt, sum_b/cnt, 255), 200, 200);
            
            log("%d, %d, %d", *rptr, *gptr, *bptr);
            
            
            /////////caculate h (CIECAM02)
            //RGB2JCH::RGB2JCH();
            RGB2JCH::getCIECAM02h(rptr, gptr, bptr, Tptr, hptr, Hptr, cieaptr, ciebptr, Jptr, Cptr);
            
            
            
            labelofstatusBar->setString(StringUtils::format("J : %g, C : %g, h : %g, H : %g\na : %g, b = %g, T = %g", Rounding(*Jptr, 2), Rounding(*Cptr, 2), Rounding(*hptr, 2) ,Rounding(*Hptr, 2), Rounding(*cieaptr, 3), Rounding(*ciebptr, 3), Rounding(*Tptr, 2)));
            
            
            
            log("%f, %f", *Tptr, *hptr);
            
            auto rectNode = DrawNode::create();
            Vec2 rectangle[4];
            rectangle[0] = Vec2(touchPoint.x-rectSize, touchPoint.y-rectSize);
            rectangle[1] = Vec2(touchPoint.x+rectSize, touchPoint.y-rectSize);
            rectangle[2] = Vec2(touchPoint.x+rectSize, touchPoint.y+rectSize);
            rectangle[3] = Vec2(touchPoint.x-rectSize, touchPoint.y+rectSize);
            
            Color4F white(1, 1, 1, 1);
            rectNode->drawLine(rectangle[0], rectangle[1], white);
            rectNode->drawLine(rectangle[1], rectangle[2], white);
            rectNode->drawLine(rectangle[2], rectangle[3], white);
            rectNode->drawLine(rectangle[3], rectangle[0], white);
            this->addChild(rectNode);
            rectNode->setTag(10);
            
        
        }
    }while(0);
    
    
}

double HelloWorld::Rounding( double x, int digit )
{
    return ( floor( (x) * pow( float(10), digit ) + 0.5f ) / pow( float(10), digit ) );
}