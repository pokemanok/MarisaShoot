#ifndef __FireDemo__Bullet__
#define __FireDemo__Bullet__
 
#include "cocos2d.h"
USING_NS_CC;
 
class Bullet : public Layer {
public:
    Bullet();
    ~Bullet();
    CREATE_FUNC(Bullet);
    virtual bool init();
     
    void addNewBullet(float x,float y);//����һ�����ӵ�

    Size winSize;
    __Array* m_allBulletArray;//���������Ѵ��ڵ��ӵ�����
     
    SpriteBatchNode* m_bulletSprite;//ʹ��BatchNode�������е��ӵ�������gl�滭����
     
    void initData();
    void moveBullet(float dt);//�ƶ��ӵ�

	Sprite* BulletPos();

	void RemoveBullet(Sprite* bullet);//ɾ���ӵ�
private:
	Sprite* newBullet;
};
 
 
#endif 