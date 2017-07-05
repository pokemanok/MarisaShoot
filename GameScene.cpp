#include "GameScene.h"
#include "HRocker.h"
#include "Bullet.h"
#include "Player.h"

GameScene::GameScene(void)
{
	enemyLayer = nullptr;
	score = 0;
}
Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	

	scene->addChild(layer);

	return scene;
}



bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//播放BGM
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgMusic.mp3",true);

	
	//背景精灵
	BG_sprite1 = Sprite::create("background.jpg");
	BG_sprite1->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(BG_sprite1,0);

	//结束界面
	gameOver = Sprite::create("gameover.png");
	gameOver->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(gameOver,5);
	gameOver->setVisible(false);


	//加入云层
	m_bgSprite1 = Sprite::create("cloud.png");
    m_bgSprite1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(m_bgSprite1,1);

	m_bgSprite2 = Sprite::create("cloud.png");
    m_bgSprite2->setPosition(Point(visibleSize.width /2+visibleSize.width /2+ visibleSize.width / 2, visibleSize.height / 2));
    m_bgSprite2->setFlippedX(true);
    this->addChild(m_bgSprite2,1);

	//摇杆添加到layer中
	spRocker = Sprite::create("rocker.png");
	spRockerBg = Sprite::create("foundation.png");
    rocker = HRocker::HRockerWithCenter(ccp(210.0f, 130.0f), 50.0f, spRocker, spRockerBg, false);
	this->addChild(rocker,3);

	//主角精灵
	m_player = Player::create();
	m_player->bindSprite(Sprite::create("spellEc1.png"));
    m_player->setPosition(Point(visibleSize.width / 2-200, visibleSize.height / 2));
    this->addChild(m_player,2);

	//给主角加入动画
	Size size = m_player->getContentSize();
	auto sprite = Sprite::create();
	sprite->runAction(createAnimate());
	sprite->setPosition(size.width*0.5f,size.height*0.5f);
	m_player->addChild(sprite);

	//加载子弹
	m_bullet = Bullet::create();
    m_bullet->setPosition(Point::ZERO);
    addChild(m_bullet,4);

	//加入分数
	gamemark = new GameMark;
	this->addChild(gamemark,4);

	//发射按钮
	auto shootItem = MenuItemImage::create(
                                           "menuShootNormal.png",
                                           "menuShootSelected.png",
                                           CC_CALLBACK_1(GameScene::menuShoot, this));

	shootItem->setPosition(Point(visibleSize.width / 2+350, visibleSize.height / 2-250));

	menu = Menu::create(shootItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 4);

	//回退按钮
	auto backItem = MenuItemImage::create(
                                           "menuBackNormal.png",
                                           "menuBackSelected.png",
                                           CC_CALLBACK_1(GameScene::menuBack, this));

	backItem->setPosition(Point(visibleSize.width / 2-visibleSize.width / 4-100, visibleSize.height / 2+visibleSize.height / 4+100));

	menu1 = Menu::create(backItem, NULL);
    menu1->setPosition(Point::ZERO);
    this->addChild(menu1, 4);

	//结束界面回退按钮
	auto overBackItem = MenuItemImage::create(
                                           "backNormal.png",
                                           "backSelected.png",
                                           CC_CALLBACK_1(GameScene::menuOverBack, this));
	overBackItem->setPosition(visibleSize.width / 2+118, visibleSize.height / 2+175);
    menu2 = Menu::create(overBackItem, NULL);
    menu2->setPosition(Point::ZERO);
	this->addChild(menu2,6);
	menu2->setVisible(false);

	//加入敌人
	this->enemyLayer = EnemyLayer::create();
	this->addChild(enemyLayer,2);

	 //开启循环
	schedule(schedule_selector(GameScene::update));

	return true;
}
//循环函数
void GameScene::update(float dt) {
	Point poi = rocker->getDirection();

	//摇杆距离检测
	Size size = Director::getInstance()->getVisibleSize();
	if ((poi.x  >  0) && (poi.x - poi.y) >0 && (poi.x + poi.y) > 0) 
	{
		//主角移动函数
		m_player->setPosition(m_player->getPosition().x + 5, m_player->getPosition().y );
		if((m_player->getPosition().x) > size.width-130)
		{    //边界检测
			m_player->setPosition(m_player->getPosition().x - 5, m_player->getPosition().y );
		}
	}
	else 
		if ((poi.x < 0) && (poi.x + poi.y) < 0 && (poi.x - poi.y) < 0) {
		m_player->setPosition(m_player->getPosition().x - 5, m_player->getPosition().y);
		if((m_player->getPosition().x) < 0)
		{
			m_player->setPosition(m_player->getPosition().x + 5, m_player->getPosition().y);
		}
	}
	else 
		if ((poi.y > 0) && (poi.y - poi.x) > 0 && (poi.y + poi.x) >0) {
		m_player->setPosition(m_player->getPosition().x , m_player->getPosition().y+5);
		if((m_player->getPosition().y) > size.height-70)
		{
			m_player->setPosition(m_player->getPosition().x , m_player->getPosition().y-5);
		}
	}
	else 
		if ((poi.y < 0) && (poi.y - poi.x) < 0 && (poi.y + poi.x) < 0) 
	{
		m_player->setPosition(m_player->getPosition().x, m_player->getPosition().y-5);
		if((m_player->getPosition().y) < 0)
		{
			m_player->setPosition(m_player->getPosition().x, m_player->getPosition().y+5);
		}

     }

    //云层运动
    int posX1 = m_bgSprite1->getPositionX();	
    int posX2 = m_bgSprite2->getPositionX();	
    int iSpeed = 1;
    posX1 -= iSpeed;
    posX2 -= iSpeed;
    Size mapSize = m_bgSprite1->getContentSize();
     if (posX1 <= -mapSize.width / 2) 
	 {
        posX1 = mapSize.width / 2+mapSize.width / 2+mapSize.width / 2;
      }
    if (posX2 <= -mapSize.width / 2)
	{
        posX2 = mapSize.width / 2+mapSize.width / 2+mapSize.width / 2;
    }
    m_bgSprite1->setPositionX(posX1);
    m_bgSprite2->setPositionX(posX2);

//检测子弹&敌人碰撞
Ref*bt,*et;
auto bulletsToDelete = __Array::create();
bulletsToDelete->retain();
CCARRAY_FOREACH(this->m_bullet->m_allBulletArray,bt)
{
	bullet =(Sprite*)bt;
	Size size = bullet->getContentSize();
	auto enemy1sToDelete = CCArray::create();
		enemy1sToDelete->retain();
		if(size.width>1920)
		{
			bulletsToDelete->addObject(bullet);
		}
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1, et)
		{
			auto enemy1 = (Enemy*)et;
			if (bullet->boundingBox().intersectsRect(enemy1->getBoundingBox()))
			{
				//if (enemy1->getLife() == 1)
				//{
					enemy1->loseLife();
					enemy1sToDelete->addObject(enemy1);
					score += ENEMY1_SCORE;
					enemy1->setVisible(0);
					gamemark->addnumber(20);
				//}
			}
		}
		CCARRAY_FOREACH(enemy1sToDelete, et)
		{
			auto enemy1 = (Enemy*)et;
			this->enemyLayer->enemy1Blowup(enemy1);
		}
		enemy1sToDelete->release();
	}

CCARRAY_FOREACH(bulletsToDelete, bt)
	{
		auto bullet = (Sprite*)bt;
		this->m_bullet->RemoveBullet(bullet);
	}
	bulletsToDelete->removeAllObjects();

//检测主角&敌人碰撞
CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1, et)
	{
		auto enemy1 = (Enemy*)et;
		auto pos = enemy1->boundingBox();;
		if(pos.intersectsRect(m_player->boundingBox()))
		{ //显示回退界面，隐藏界面元素
			gameOver->setVisible(true);
			menu2->setVisible(true);
	        m_bgSprite1->setVisible(false);
	        m_bgSprite2->setVisible(false);
	        m_player->setVisible(false);
	        spRocker->setVisible(false);
	        spRockerBg->setVisible(false);
	        menu->setVisible(false);
	        menu1->setVisible(false);
	        gamemark->setVisible(false);
	        enemyLayer->setVisible(false);  
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("wuwu.wav");
		}
	}

}

//射击按钮回调函数
void GameScene::menuShoot(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    m_bullet->addNewBullet(m_player->getPositionX(),m_player->getPositionY());
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("se_pldead00.wav");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//回退按钮回调函数
void GameScene::menuBack(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("touch.mp3");
    Director::getInstance()->replaceScene(TransitionFadeUp::create(0.5f,StartScene::createScene()));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//结束界面回退按钮回调函数
void GameScene::menuOverBack(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("touch.mp3");
    Director::getInstance()->replaceScene(TransitionFadeUp::create(0.5f,StartScene::createScene()));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//精灵动画
cocos2d::Animate* GameScene::createAnimate()
{
		int iFrameNum = 6;
		SpriteFrame* frame = NULL;
		Vector<SpriteFrame*> frameVec;
		for (int i=1;i <= iFrameNum;i++)
        {
	      frame = SpriteFrame::create(StringUtils::format("spellEc%d.png",i),Rect(0,0,121,64));
	      frameVec.pushBack(frame);
        }
		Animation* animation = Animation::createWithSpriteFrames(frameVec);
		animation->setLoops(-1);
		animation->setDelayPerUnit(0.1f);
		Animate* action = Animate::create(animation);
		return action;
}
