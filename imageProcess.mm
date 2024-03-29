//
//  imageProcess.cpp
//  CoolWarm
//
//  Created by hahmdong gyun on 2017. 2. 17..
//
//

#include "imageProcess.h"
#import "UIImage2OpenCV.h"
#include <vector>



void imageProcess::image2WhatIwant(cv::Mat result, Sprite* colorImage)
{
    //1차 전처리
    
    cv::CascadeClassifier face_classifier;
    cv::CascadeClassifier eye_classifier;
    
    NSString *cascadePathforFaces = [[NSBundle mainBundle] pathForResource: @"haarcascade_frontalface_default" ofType:@"xml"];
    NSString *cascadePathforEyes = [[NSBundle mainBundle] pathForResource: @"haarcascade_eye" ofType:@"xml"];
    
    if(!face_classifier.load([cascadePathforFaces UTF8String])||!eye_classifier.load([cascadePathforEyes UTF8String])){
        log("haarcascade xml loading failed");
    }
    
    
    
    //Convert frame to gray scale and equalize
    cv::Mat grayFrame;
    cv::cvtColor(result, grayFrame, CV_BGR2GRAY);
    cv::equalizeHist(grayFrame, grayFrame);
    std::vector<cv::Point> lipPos;
    //face detection routine
    cv::Mat drawing;
    
    //a vector array to store the face found
    std::vector<cv::Rect> faces;
    face_classifier.detectMultiScale(grayFrame, faces,
                                     1.1, //increase search scale by 10% each pass
                                     3,  // merge groups of three detections
                                     CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE,
                                     cv::Size(30, 30));
    //------------------------------------------------------------------
    //------------------------------------------------------------------
    //------------------------------------------------------------------
    //------------------------------------------------------------------
    for(int i = 0; i <faces.size() ; i++){
        cv::Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
        cv::Point tr(faces[i].x, faces[i].y);
        
        //cv::rectangle(result, lb, tr, cv::Scalar(0, 255, 0), 3, 4, 0);
    
        std::vector<cv::Rect> eyes;
        
        cv::Mat faceROI = grayFrame(faces[i]);
        
        //In each face, find eyes
        eye_classifier.detectMultiScale(faceROI,
                                        eyes,
                                        1.1,
                                        3,
                                        0|CV_HAAR_SCALE_IMAGE,
                                        cv::Size(30, 30));
        for(int j = 0; j<(int)eyes.size();j++){
            cv::Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
            int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
            //cv::circle(result, center, radius, cv::Scalar(0, 255, 0), 4, 8, 0);
        }
    
        cv::Mat lipROI = result(cv::Rect(faces[i].x+faces[i].width*0.2, faces[i].y + faces[i].height*0.6, faces[i].width*0.6, faces[i].height*0.4));
        cv::Point lbLip(faces[i].x + faces[i].width*0.8, faces[i].y + faces[i].height);
        cv::Point trLip(faces[i].x+faces[i].width*0.2, faces[i].y + faces[i].height*0.6);
        //cv::rectangle(result, lbLip, trLip, cv::Scalar(0, 255, 0), 3, 4, 0);
        
        
        //cv::Mat src_filtered;
        //cv::bilateralFilter(result, src_filtered, 9, 15, 15);
        
        //2차 전처리
        
        cv::Mat img_ycbcr;
        cv::Mat img_gray;
        cv::Mat img_thres;
        
        cv::cvtColor(lipROI, img_gray, CV_BGR2GRAY);
        cv::blur(img_gray, img_gray, cv::Size(3, 3));
        cv::GaussianBlur(img_gray, img_gray, cv::Size(3,3), 2);
        
        
        cv::cvtColor(lipROI, img_ycbcr, CV_BGR2YCrCb);
        std::vector<cv::Mat> channels;
        cv::split(img_ycbcr, channels);
        
        cv::threshold(channels[2], img_thres, 161, 255, CV_THRESH_BINARY);
        //cvCvtColor(img, ycbcr, CV_BGR2YCrCb);
        
        int erosion_elem = 0;
        int erosion_size = 0;
        int dilation_elem = 0;
        int dilation_size = 0;
        int const max_elem = 2;
        int const max_kernel_size = 21;
        
        cv::Mat elementErode = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2*erosion_size + 1, 2*erosion_size +1), cv::Point(erosion_size, erosion_size));
        
        cv::erode(img_thres, img_thres, elementErode);
        
        cv::Mat elementDilate = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(2*dilation_size + 1, 2*dilation_size +1), cv::Point(dilation_size, dilation_size));
        
        cv::dilate(img_thres, img_thres, elementDilate);
        
        for(int x = 0;x<img_thres.rows;x++){
            for(int y = 0;y<img_thres.cols;y++){
                cv::Vec4b &pixel = lipROI.at<cv::Vec4b>(x, y);
                if(img_thres.at<uchar>(x, y) == 255){
                    //pixel[1] = 255;
                    //lipROI.at<uchar>(x, y) = 240;  //왜 이놈으로 하면 좌표값이 어긋나지????
                    //cv::Point temp = cv::Point(x, y);
                    //lipPos.push_back(temp);
                }
                else{
                    //pixel[3] = 0;
                }
                
            }
        }
        
        log("%d, %d, %d, %d", img_thres.cols, img_thres.rows, lipROI.cols, lipROI.rows);
        //img_thres.copyTo(result(cv::Rect(faces[i].x+faces[i].width*0.2, faces[i].y + faces[i].height*0.5, img_thres.cols, img_thres.rows)));
        
        cv::Canny(img_gray, img_gray, 15, 45, 3);
        /// Find contours
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::RNG rng(12345);
        cv::findContours(img_gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
        /// Draw contours
        drawing = cv::Mat::zeros(img_gray.size(), CV_8UC3);
        for (int h = 0; h< contours.size(); h++)
        {
            
            cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
            cv::drawContours(result, contours, h, color, 2, 8, hierarchy, 0, cv::Point(faces[i].x+faces[i].width*0.2, faces[i].y + faces[i].height*0.6));
        }
        
       
        //------------------------------------------------------------------
        //------------------------------------------------------------------
        //------------------------------------------------------------------
    }
    
    //cvSplit(ycbcr, NULL, cr, NULL, NULL);
    //cvThreshold(cr, cr, 161, 255, CV_THRESH_BINARY);
    
    
    /*
    cv::Mat greyMat;
    cv::cvtColor(result, greyMat, CV_BGR2YCrCb);
    cv::inRange(greyMat, cv::Scalar(0, 133, 77), cv::Scalar(255, 173, 127), greyMat);
    */
    
    UIImage *imageProcess = [UIImage alloc];
    Image* processedImage = [imageProcess UIImageFromCVMat:result];
    
    Texture2D* texture = new Texture2D();
    texture->initWithImage(processedImage);
    texture->autorelease();
    processedImage->release();
    colorImage->initWithTexture(texture);
    
}





// ccSrite2cvMat変換
cv::Mat imageProcess::ccImage2cvMat(cocos2d::Image* ccImage)
{
    // Expansion of information from CCImage
    //総ピクセル数(unsigned int)
    int imageSize = (int)ccImage->getDataLen();
    log("-----imageSize:%d", imageSize);
    
    //横ピクセル数(unsigned int)
    int imageXW = ccImage->getWidth();
    //縦ピクセル数(unsigned int)
    int imageYW = ccImage->getHeight();
    //ピクセルデータ(配列)
    unsigned char * srcData = ccImage->getData();
    // (補足)
    // unsigned char : Since it is 8 bits (1 byte), in order to extract 1 pixel information, it must be taken out in units of 4 pieces.
    // Color information is fixed in one byte unit, and it is red, green, blue, transparency.
    log("getNumberOfMipmaps:%d", ccImage->getNumberOfMipmaps());
    log("imageXW=%d, imageYW=%d", imageXW, imageYW);
    
    return this->createCvMatFromRaw(srcData, imageXW, imageYW);
}


// Raw2cvMat変換
cv::Mat imageProcess::createCvMatFromRaw(unsigned char *rawData, int rawXW, int rawYW)
{
    // Preparation of deployed Mat
    cv::Mat cvMat( rawYW, rawXW, CV_8UC4); // 8 bits per component, 4 channels
    
    for (int py=0; py<rawYW; py++) {
        for (int px=0; px<rawXW; px++) {
            // Set pixel information of this coordinates
            //Extract 1 pixel information
            int nBasePos = ((rawXW * py)+px) * 4;
            cvMat.at<cv::Vec4b>(py, px) = cv::Vec4b(rawData[nBasePos + 0],  // 赤
                                                    rawData[nBasePos + 1],  // 緑
                                                    rawData[nBasePos + 2],  // 青
                                                    0xFF);   // Alafa
            
        }
    }
    
    return cvMat;
}


// cvMat2ccImage変換
cocos2d::Image* imageProcess::cvMat2ccImage(cv::Mat cvMat)
{
    // cvMatを用意するときは常にCV_8UC4(='8 bits per component, 4 channels')の前提とするので考慮の必要なし
    int elemSize = (int)cvMat.elemSize();
    unsigned char *srcData;
    
    
    int width  = cvMat.cols;
    int height = cvMat.rows;
    
    log("revers elemSize:%d", elemSize);
    //log("revers size:%d", size);
    log("revers width=%d, height=%d", width, height);
    
    
    unsigned char * pTempData = NULL;
    if(1==elemSize){
        log("gray-mode");
        // glayscale
        int bytesPerComponent = 4;
        long size = bytesPerComponent * width * height;
        pTempData = static_cast<unsigned char*>(malloc(size * sizeof(unsigned char)));
        
        
        if(pTempData){
            int imageYW=height;
            int imageXW=width;
            
            unsigned char * matData = (unsigned char *)cvMat.data;
            
            for (int py=0; py<imageYW; py++) {
                for (int px=0; px<imageXW; px++) {
                    // この座標の画素情報をセット
                    //1ピクセルの情報を取り出す
                    int matPixPos = (imageXW * py * 1) + (px * 1);
                    int pixPos = (imageXW * py * bytesPerComponent) + (px * bytesPerComponent);
                    pTempData[pixPos+0]=matData[matPixPos];    // Red
                    pTempData[pixPos+1]=matData[matPixPos];    // Green
                    pTempData[pixPos+2]=matData[matPixPos];    // Blue
                    pTempData[pixPos+3]=0xFF;    // Alfa
                }
            }
        }
        
        srcData = pTempData;
    } else {
        log("color-mode");
        // color
        srcData = (unsigned char *)cvMat.data;
    }
    long size = 4  * width * height;
    
    // イメージデータ生成
    Image* ccImage = new Image();
    if (ccImage && ccImage->initWithRawData( srcData,
                                            size,
                                            width,
                                            height,
                                            elemSize * 8
                                            )
        ) {
        return ccImage;
    }
    if(pTempData){
        free(pTempData);
    }
    return NULL;
    
}




