#include "HelloWorldScene.h"

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
    

    auto Backlayer = LayerColor::create(Color4B(255, 255, 255, 255));
    Backlayer->setContentSize(Size(visibleSize.width, visibleSize.height));
    
    this->addChild(Backlayer);
    
    
    
    
    
    labelofstatusBar = Label::createWithSystemFont("RGB value", "Thonburi", 30, Size(500, 70), TextHAlignment::CENTER, TextVAlignment::TOP);
    labelofstatusBar->setColor(Color3B(0, 0, 0));
    labelofstatusBar->setAnchorPoint(Point(0.5, 1));
    labelofstatusBar->setPosition(Point(visibleSize.width/2, visibleSize.height*0.98));
    
    this->addChild(labelofstatusBar);

    ImagePicker::getInstance()->pickImage(this);
    
    
    return true;
}


void HelloWorld::didFinishPickingWithResult(cocos2d::Texture2D* result)
{
    
    
    
    
    //auto rectSize = Rect(100, 100, 300, 300);
    
    auto colorImage = Sprite::createWithTexture(result);
    colorImage->setPosition(visibleSize.width/2, 500);
    //colorImage->setContentSize(Size(visibleSize.width/2, visibleSize.height/2));
    colorImage->setAnchorPoint(Point(0.5, 0.5));
    this->addChild(colorImage);
    log("eh?");
    
    
    
    
    //터치되면 사라지게
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [=](Touch *touch, Event* event)
    {
        log("touch began");
        
        
        
        Color3B* temp1;
        
        getPixelData(temp1, touch);
        
        return true;
    };
    
    listener->onTouchEnded = [=](Touch *touch, Event* event)
    {
        log("touch ended");
        
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    
    templayer = LayerColor::create(Color4B(100, 100, 100, 255), 200, 200);
    templayer->setPosition(Point(visibleSize.width/2-100, visibleSize.height*0.75));
    this->addChild(templayer);
    
    
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



void HelloWorld::getPixelData(Color3B* color, Touch *touch)
{
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
            
            int rectSize = 40/2;
            
            
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
                        log("R : %d, G : %d, B : %d, Count : %d", r, g, b, cnt);
                        
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
            
            labelofstatusBar->setString(StringUtils::format("R : %d, G : %d, B : %d", sum_r/cnt, sum_g/ cnt, sum_b/ cnt));
            
            //*color = Color3B(sum_r/cnt, sum_g/ cnt, sum_b/ cnt);
            templayer->initWithColor(Color4B(sum_r/cnt, sum_g/cnt, sum_b/cnt, 255), 200, 200);
            
            if (getChildByTag(10))
            {
                this->removeChildByTag(10);
            }
            
            auto rectNode = DrawNode::create();
            Vec2 rectangle[4];
            rectangle[0] = Vec2(touchPoint.x, touchPoint.y);
            rectangle[1] = Vec2(touchPoint.x+rectSize, touchPoint.y);
            rectangle[2] = Vec2(touchPoint.x+rectSize, touchPoint.y+rectSize);
            rectangle[3] = Vec2(touchPoint.x, touchPoint.y+rectSize);
            
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