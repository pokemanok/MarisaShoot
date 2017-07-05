#include "GameScene.h"
#include "Bullet.h"
 
#define MOVE_SPEED     9  //子弹的速度
#define REMOVE_POSY     -1280 //子弹消失的位置，根据自己项目定
 
Bullet::Bullet(){
     
}
 
Bullet::~Bullet(){
    m_allBulletArray->release();
}
 
bool Bullet::init(){
    if (!Layer::init()) {
        return false;
    }
    initData();
    return true;
}
 
void Bullet::initData(){
    auto visiblesize = Director::getInstance()->getVisibleSize();
     
    //创建对象数组，保存已存在的子弹
    m_allBulletArray = Array::create();
    m_allBulletArray->retain();
     
    //子弹贴图
    m_bulletSprite = SpriteBatchNode::create("bulletAa000_03.png");
	m_bulletSprite->setPosition(Point::ZERO);
    addChild(m_bulletSprite,4);
     
    //更新子弹速度
    schedule(schedule_selector(Bullet::moveBullet));
}
 
//增加一个新子弹
void Bullet::addNewBullet(float x,float y){
    //构建一个子弹，添加到BatchNode中。
    newBullet = Sprite::createWithTexture(m_bulletSprite->getTexture());

	

    newBullet->setPosition(x+130,y+25);

    m_bulletSprite->addChild(newBullet);
    //添加子弹到已存在子弹数组
    m_allBulletArray->addObject(newBullet);
}

Sprite*  Bullet::BulletPos()
{
	auto Bullet = newBullet;
	return Bullet;
}
 
//移动子弹
void Bullet::moveBullet(float dt){
    //遍历更新每个子弹的位置
    for (int i = 0; i < m_allBulletArray->count(); ++i) {
        //获取一个子弹对象
        auto bullet = (Sprite*)m_allBulletArray->objectAtIndex(i);
		
        //更新位置
		bullet->setPositionX(bullet->getPositionX()+MOVE_SPEED);

        //如果已到达消失位置，就移除该子弹
        if (bullet->getPositionX() <= REMOVE_POSY) {
            m_allBulletArray->removeObjectAtIndex(i);
            m_bulletSprite->removeChild(bullet, true);
        }
    }
}

void  Bullet::RemoveBullet(Sprite* bullet)
{
	if (bullet != nullptr)
	{
//		this->bulletBatchNode->removeChild(bullet, true);
        this->removeChild(bullet, true);
		this->m_allBulletArray->removeObject(bullet);
	}
}