#ifndef _StartScene_
#define _StartScene_

#include "cocos2d.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class StartScene:public Layer
{
public:
	static Scene* createScene();
private:
	Sprite* background;
	Sprite* logo;
	void menuClose(Ref* pSender);
	void menuStart(Ref* pSender);
	virtual bool init();
	CREATE_FUNC(StartScene);
};

#endif