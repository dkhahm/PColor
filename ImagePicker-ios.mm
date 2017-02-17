// Image Picker for cocos2d-x
// @Author: Kanglai Qian
// @url: https://github.com/qiankanglai/ImagePicker

#import <QuartzCore/QuartzCore.h>

#import "ImagePicker.h"
#import "ImagePicker-ios.h"


#include "cocos2d.h"

using namespace cocos2d;

@implementation ImagePickerIOS

// **ATTENTION**: if you encounter any crash here, please check the device orientation
// https://github.com/qiankanglai/ImagePicker/issues/2
-(void) takePicture
{
    
    UIImagePickerController *imagePicker = [[UIImagePickerController alloc] init];
    if (UserDefault::getInstance()->getStringForKey("ImageSource") == "Camera")
    {
        [imagePicker setSourceType:UIImagePickerControllerSourceTypeCamera];
    }
    else
    {
        [imagePicker setSourceType:UIImagePickerControllerSourceTypePhotoLibrary];
    }
    
    [imagePicker setDelegate:self];
    imagePicker.wantsFullScreenLayout = YES;
    
    // CCEAGLView is a subclass of UIView
    UIView *view = (UIView *)Director::getInstance()->getOpenGLView()->getEAGLView();
    [view addSubview:imagePicker.view];
}





-(void) imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //auto origin = Director::getInstance()->getVisibleOrigin();
    
    Image *image = new Image();
    
    @autoreleasepool
    {
        UIImage *img = [info objectForKey:UIImagePickerControllerOriginalImage];
        //
        
        img = [self scaleImage:img toSize:CGSizeMake(visibleSize.width,visibleSize.height)]; // or some other size
        //
        NSData *imgData = UIImagePNGRepresentation(img);
        NSUInteger len = [imgData length];
        
        Byte *byteData = (Byte*)malloc(len);
        memcpy(byteData, [imgData bytes], len);
    
        image->initWithImageData(byteData, len);
        
        free(byteData);
    }
    
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([image]{
        /*
        Texture2D* texture = new Texture2D();
        texture->initWithImage(image);
        texture->autorelease();
        image->release();
        */
        ImagePicker::getInstance()->finishImage(image);
    });
    
    [picker.view removeFromSuperview];
    [picker release];
}



-(UIImage *)scaleImage:(UIImage *)image toSize:(CGSize)targetSize {
    
    
    UIImage *sourceImage = image;
    UIImage *newImage = nil;
    
    CGSize imageSize = sourceImage.size;
    CGFloat width = imageSize.width;
    CGFloat height = imageSize.height;
    
    CGFloat targetWidth = targetSize.width;
    CGFloat targetHeight = targetSize.height;
    
    CGFloat scaleFactor = 0.0;
    CGFloat scaledWidth = targetWidth;
    CGFloat scaledHeight = targetHeight;
    
    CGPoint thumbnailPoint = CGPointMake(0.0,0.0);
    
    if (CGSizeEqualToSize(imageSize, targetSize) == NO) {
        
        CGFloat widthFactor = targetWidth / width;
        CGFloat heightFactor = targetHeight / height;
        
        if (widthFactor < heightFactor)
            scaleFactor = widthFactor;
        else
            scaleFactor = heightFactor;
        
        scaledWidth  = width * scaleFactor;
        scaledHeight = height * scaleFactor;
        
        // center the image
        
        
        if (widthFactor < heightFactor) {
            thumbnailPoint.y = (targetHeight - scaledHeight) * 0.5;
        } else if (widthFactor > heightFactor) {
            thumbnailPoint.x = (targetWidth - scaledWidth) * 0.5;
        }
    }
    
    
    // this is actually the interesting part:
    
    UIGraphicsBeginImageContext(targetSize);
    
    CGRect thumbnailRect = CGRectZero;
    thumbnailRect.origin = thumbnailPoint;
    thumbnailRect.size.width  = scaledWidth;
    thumbnailRect.size.height = scaledHeight;
    
    [sourceImage drawInRect:thumbnailRect];
    
    newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    if(newImage == nil) NSLog(@"could not scale image");
    
    
    return newImage ;
    
}



- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker{
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([]{
        ImagePicker::getInstance()->finishImage(nullptr);
    });
    [picker.view removeFromSuperview];
    [picker release];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

@end
