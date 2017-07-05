#include "GameScene.h"
#include "Bullet.h"
 
#define MOVE_SPEED     9  //�ӵ����ٶ�
#define REMOVE_POSY     -1280 //�ӵ���ʧ��λ�ã������Լ���Ŀ��
 
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
     
    //�����������飬�����Ѵ��ڵ��ӵ�
    m_allBulletArray = Array::create();
    m_allBulletArray->retain();
     
    //�ӵ���ͼ
    m_bulletSprite = SpriteBatchNode::create("bulletAa000_03.png");
	m_bulletSprite->setPosition(Point::ZERO);
    addChild(m_bulletSprite,4);
     
    //�����ӵ��ٶ�
    schedule(schedule_selector(Bullet::moveBullet));
}
 
//����һ�����ӵ�
void Bullet::addNewBullet(float x,float y){
    //����һ���ӵ�����ӵ�BatchNode�С�
    newBullet = Sprite::createWithTexture(m_bulletSprite->getTexture());

	

    newBullet->setPosition(x+130,y+25);

    m_bulletSprite->addChild(newBullet);
    //����ӵ����Ѵ����ӵ�����
    m_allBulletArray->addObject(newBullet);
}

Sprite*  Bullet::BulletPos()
{
	auto Bullet = newBullet;
	return Bullet;
}
 
//�ƶ��ӵ�
void Bullet::moveBullet(float dt){
    //��������ÿ���ӵ���λ��
    for (int i = 0; i < m_allBulletArray->count(); ++i) {
        //��ȡһ���ӵ�����
        auto bullet = (Sprite*)m_allBulletArray->objectAtIndex(i);
		
        //����λ��
		bullet->setPositionX(bullet->getPositionX()+MOVE_SPEED);

        //����ѵ�����ʧλ�ã����Ƴ����ӵ�
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