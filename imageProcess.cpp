//
//  imageProcess.cpp
//  CoolWarm
//
//  Created by hahmdong gyun on 2017. 2. 17..
//
//

#include "imageProcess.h"

void imageProcess::image2WhatIwant(Sprite *pSpriteIView, Image *rawImage)
{
    
    /*
    Image* srcImage = new Image();
    if(srcImage->initWithImageFile("faceTest.png")){
        log("srcImageLoad[OK]");
        cv::Mat srcMat = this->ccImage2cvMat(srcImage);
        cv::Mat greyMat;
        cv::cvtColor(srcMat, greyMat, CV_BGR2GRAY);
        Image* grayImage = this->cvMat2ccImage(greyMat);
      */
    Texture2D* texture = new Texture2D();
    texture->initWithImage(rawImage);
    //texture->autorelease();
    //rawImage->release();
    
    auto colorImage = Sprite::createWithTexture(texture);
    
    RenderTexture* r = RenderTexture::create(texture->getPixelsWide(), texture->getPixelsHigh());
    r->beginWithClear(1, 1, 1, 0);
    colorImage->visit();
    r->end();
    Image* srcImage = r->newImage();
    
    
    if(srcImage){
        log("srcImageLoad[OK]");
        cv::Mat srcMat = this->ccImage2cvMat(srcImage);
        cv::Mat greyMat;
        cv::cvtColor(srcMat, greyMat, CV_BGR2GRAY);
        Image* grayImage = this->cvMat2ccImage(greyMat);
        
        
        // 表示切り替え
        Texture2D* texture = new Texture2D();
        
        if (texture && texture->initWithImage(grayImage)) {
            //texture->autorelease();
            //Sprite *pSpriteIView = (Sprite *)this->getChildByTag(1);
            //pSpriteIView->setTexture(texture);
        }
        //CC_SAFE_DELETE(texture);
        
    } else {
        log("srcImageLoad[NG]");
        
    }
    
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
    
    //log("elemSize:%d", elemSize);
    //log("size:%d", size);
    //log("width=%d, height=%d", width, height);
    
    
    unsigned char * pTempData = NULL;
    if(1==elemSize){
        log("gray-mode");
        // グレースケール
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
        // カラー
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




