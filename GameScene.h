#ifndef _GameScene_
#define _GameScene_

#include "cocos2d.h"
#include "HRocker.h"
#include "Player.h"
#include "Bullet.h"
#include "EnemyLayer.h"
#include "GameMark.h"
#include "SimpleAudioEngine.h"
#include "StartScene.h"

using namespace cocos2d;
const int ENEMY1_SCORE = 1000;
class Bullet; 
class GameScene:public Layer
{
public:
	HRocker *rocker;
	Sprite* sprite;

	GameScene(void);
	static Scene* createScene();
	virtual bool init();
	virtual void update(float);
	void menuShoot(cocos2d::Ref* pSender);
	void menuBack(cocos2d::Ref* pSender);
	void menuOverBack(cocos2d::Ref* pSender);
private:
	int score;
	Sprite* BG_sprite1;
	Sprite* m_bgSprite1;
	Sprite* m_bgSprite2;
	Sprite* bullet;
	Bullet* m_bullet;
	Player* m_player;
	Sprite* spRocker;
	Sprite* spRockerBg;
	Sprite* gameOver;
	Sprite* gameOverMenu;
	Menu* menu;
	Menu* menu1;
	Menu* menu2;
	GameMark *gamemark;
	EnemyLayer* enemyLayer;
	Animate* createAnimate();
	CREATE_FUNC(GameScene);
private:

};

#endif