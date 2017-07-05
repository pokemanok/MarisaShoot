#pragma once
#include "cocos2d.h"
#include "Enemy.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

const int ENEMY1_MAXLIFE=1;



class EnemyLayer : public Layer
{
public:
	EnemyLayer(void);
	~EnemyLayer(void);

	CREATE_FUNC(EnemyLayer);
	virtual bool init();

	void addEnemy1(float dt);
	void enemy1MoveFinished(Node* pSender);
	void removeEnemy1(Node* pTarget);
	void enemy1Blowup(Enemy* enemy1);
	void removeAllEnemy1();
	void removeAllEnemy();

	__Array* m_pAllEnemy1;
	
private:
	SpriteFrame* enemy1SpriteFrame;
	
};