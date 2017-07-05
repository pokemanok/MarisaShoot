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
     
    void addNewBullet(float x,float y);//增加一个新子弹

    Size winSize;
    __Array* m_allBulletArray;//保存所有已存在的子弹对象
     
    SpriteBatchNode* m_bulletSprite;//使用BatchNode构建所有的子弹，减少gl绘画次数
     
    void initData();
    void moveBullet(float dt);//移动子弹

	Sprite* BulletPos();

	void RemoveBullet(Sprite* bullet);//删除子弹
private:
	Sprite* newBullet;
};
 
 
#endif 