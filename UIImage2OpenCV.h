//
//  
//  CoolWarm
//
//  Created by hahmdong gyun on 2017. 2. 24..
//
//
#include "cocos2d.h"
using namespace cocos2d;

@interface UIImage (OpenCV)

//-(cv::Mat) toMat;
-(cv::Mat)cvMatFromUIImage;
-(cv::Mat)cvMatGrayFromUIImage:(UIImage *)image;
-(Image *)UIImageFromCVMat:(cv::Mat)cvMat;

@end
