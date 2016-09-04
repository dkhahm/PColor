#ifndef CHECKCOLOR_H_
#define CHECKCOLOR_H_

#include "cocos2d.h"
#include "IntroScene.h"


class CheckColor : public cocos2d::Layer{
public:
	CREATE_FUNC(CheckColor);
private:
	void startGameButtonCallback(Ref* pSender);
	virtual bool init() override;
};

#endif /* CHECKCOLOR_H_ */