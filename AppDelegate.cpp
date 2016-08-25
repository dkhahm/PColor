#include "AppDelegate.h"
#include "IntroScene.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(750, 1334);

static cocos2d::Size iphone4ResolutionSize = cocos2d::Size(640, 960);  //3.5inch  under iphone 4s
static cocos2d::Size iphone5ResolutionSize = cocos2d::Size(640, 1136);  //4inch  iphone 5
static cocos2d::Size iphone6ResolutionSize = cocos2d::Size(750, 1334);  //4.7inch  iphone 6
static cocos2d::Size iphone6plusResolutionSize = cocos2d::Size(1242, 2208);  //5.5inch  iphone 6+
static cocos2d::Size ipadResolutionSize = cocos2d::Size(1536, 2048);  //ipad

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("CoolWarm", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("CoolWarm");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    log("Framsize w : %f, H : %f", frameSize.width, frameSize.height);
    // ipad
    if (frameSize.width > iphone6plusResolutionSize.width)
    {        
        director->setContentScaleFactor(MIN(ipadResolutionSize.height/designResolutionSize.height, ipadResolutionSize.width/designResolutionSize.width));
        log("iPad Resolution");
    }
    // iphone 6+
    else if (frameSize.height > ipadResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(iphone6plusResolutionSize.height/designResolutionSize.height, iphone6plusResolutionSize.width/designResolutionSize.width));
        log("iPhone 6+ Resolution");
    }
    // iphone 6
    else if (frameSize.height > iphone5ResolutionSize.height && frameSize.height < iphone6plusResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(iphone6ResolutionSize.height/designResolutionSize.height,
                                            iphone6ResolutionSize.width/designResolutionSize.width));
        log("iPhone 6 Resolution");
    }
    // iphone 5
    else if (frameSize.height > iphone4ResolutionSize.height && frameSize.height < iphone6ResolutionSize.height)
    {
        director->setContentScaleFactor(MIN(iphone5ResolutionSize.height/designResolutionSize.height,
                                            iphone5ResolutionSize.width/designResolutionSize.width));
        log("iPhone 5 Resolution");
    }
    // iphone 4s or under
    else
    {
        director->setContentScaleFactor(MIN(iphone4ResolutionSize.height/designResolutionSize.height,
                                            iphone4ResolutionSize.width/designResolutionSize.width));
        log("iPhone 4 Resolution");
    }
    

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = Intro::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
