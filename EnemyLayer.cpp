#include "EnemyLayer.h"
#include "GameScene.h"

EnemyLayer::EnemyLayer(void)
{
	enemy1SpriteFrame = nullptr;
	//建立敌人队列
	m_pAllEnemy1 = __Array::create();
	m_pAllEnemy1->retain();
}

EnemyLayer::~EnemyLayer(void)
{   //释放敌人
	m_pAllEnemy1->release();
	m_pAllEnemy1 = nullptr;
}

bool EnemyLayer::init()
{
	    bool bRet = false;
		//加载敌人纹理
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("qwe.plist");
		enemy1SpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Reimu.png");
		this->schedule(schedule_selector(EnemyLayer::addEnemy1),0.5f);
		bRet = true;
	return bRet;
}


void EnemyLayer::addEnemy1(float dt)
{
	auto enemy1 = Enemy::create();
	enemy1->bindSprite(Sprite::createWithSpriteFrame(enemy1SpriteFrame), ENEMY1_MAXLIFE);

	//敌人移动函数
	auto enemy1Size = enemy1->getSprite()->getContentSize();
	auto winSize = Director::getInstance()->getWinSize();
	int minY = enemy1Size.height/2;
	int maxY = winSize.height-enemy1Size.height/2;
	int rangeY = maxY-minY;
	int actualY = (rand()%rangeY)+minY;

	enemy1->setPosition(Point(winSize.width+enemy1Size.width/2,actualY));
	this->addChild(enemy1);
	this->m_pAllEnemy1->addObject(enemy1);

	float minDuration= 2.0f, maxDuration=4.0f;
	
	int rangeDuration = maxDuration-minDuration;
	int actualDuration = (rand()%rangeDuration)+minDuration;

	auto actionMove = MoveTo::create(actualDuration, Point(0-enemy1->getSprite()->getContentSize().width/2,actualY));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemy1MoveFinished, this));

	auto sequence = Sequence::create(actionMove, actionDone, nullptr);
	enemy1->runAction(sequence);

}

void EnemyLayer::enemy1MoveFinished(Node* pSender)
{
	auto enmey1 = (Enemy*)pSender;
	this->removeChild(enmey1, true);
	this->m_pAllEnemy1->removeObject(enmey1);
}



void EnemyLayer::removeEnemy1(Node* pTarget)
{
	auto enemy1 = (Enemy*)pTarget;
	if (enemy1 != nullptr)
	{
		m_pAllEnemy1->removeObject(enemy1);
		this->removeChild(enemy1, true);
	}
}

void EnemyLayer::enemy1Blowup(Enemy* enemy1)
{
     auto act = MoveBy::create(0.1,Point(0,0));
	auto removeEnemy1 = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeEnemy1, this, enemy1));
	auto sequence = Sequence::create(act, removeEnemy1, nullptr);
	enemy1->getSprite()->runAction(sequence);
}

void EnemyLayer::removeAllEnemy1()
{
	Ref* obj;
	CCARRAY_FOREACH(m_pAllEnemy1, obj)
	{
		auto enemy1 = (Enemy*)obj;
	}
}

void EnemyLayer::removeAllEnemy()
{
	removeAllEnemy1();
}
