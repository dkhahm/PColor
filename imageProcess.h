//
//  imageProcess.h
//  CoolWarm
//
//  Created by hahmdong gyun on 2017. 2. 17..
//
//

#ifndef imageProcess_h
#define imageProcess_h

#include "cocos2d.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <HelloWorldScene.h>


using namespace cocos2d;

class imageProcess : public cocos2d::Layer
{
    
private:
    
public:
    
    
    void image2WhatIwant(cv::Mat result, Sprite* colorImage);
    cv::Mat ccImage2cvMat(cocos2d::Image* ccImage);
    cv::Mat createCvMatFromRaw(unsigned char *rawData, int rawXW, int rawYW);
    cocos2d::Image* cvMat2ccImage(cv::Mat cvMat);
    
    CREATE_FUNC(imageProcess);
    
    
};

#endif /* imageProcess_h */
