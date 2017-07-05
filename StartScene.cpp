#include "StartScene.h"

Scene* StartScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

bool StartScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	Size size = Director::getInstance()->getVisibleSize();

	//����BGM
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgMusic0.mp3",true);

	//���ñ���
	background = Sprite::create("startbackground.jpg");
	background->setPosition(size.width/2,size.height/2);
	this->addChild(background);

	//����logo
	logo = Sprite::create("logo.png");
	logo->setPosition(size.width/2,size.height/2);
	this->addChild(logo,1);

	//�����Ĵ���
	auto label =Label::create("Joystick pictures: Xaivier,Program and Art Designer: POKEMAN ","Arial",20);
	label->setColor(Color3B(161,159,159));
	label->setPosition(size.width/2,40);
	this->addChild(label);

	//��ʼ��ť
	auto startItem = MenuItemImage::create(
                                           "menuStartNormal.png",
                                           "menuStartSelected.png",
                                           CC_CALLBACK_1(StartScene::menuStart, this));

	startItem->setPosition(Point(size.width / 2-250, size.height / 2-250));

    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 4);

	//�رհ�ť
	auto closeItem = MenuItemImage::create(
                                           "menuCloseNormal.png",
                                           "menuCloseSelected.png",
                                           CC_CALLBACK_1(StartScene::menuClose, this));

	closeItem->setPosition(Point(size.width / 2+250, size.height / 2-250));

    auto menu1 = Menu::create(closeItem, NULL);
    menu1->setPosition(Point::ZERO);
    this->addChild(menu1, 4);
}

//��ʼ��ť�ص�����
void StartScene::menuStart(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
   return;
#endif

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("touch.mp3");
    Director::getInstance()->replaceScene(TransitionFadeUp::create(0.5f,GameScene::createScene()));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//�رհ�ť�ص�����
void StartScene::menuClose(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
   return;
#endif

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("touch.mp3");
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}