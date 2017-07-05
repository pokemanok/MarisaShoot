#ifndef HRocker_H 
#define HRocker_H 
#include "cocos2d.h" 
USING_NS_CC;
class HRocker :public Layer {
public:
	//初始化 aPoint是摇杆中心 aRadius是摇杆半径 aJsSprite是摇杆控制点 aJsBg是摇杆背景 
	static HRocker* HRockerWithCenter(Point aPoint, float aRadius, Sprite* ajsSprite, Sprite* aJsBg, bool isFollowRole);

	//启动摇杆
	void Active();

	//解除摇杆
	void Inactive();

	HRocker* initWithCenter(Point aPoint, float aRadius, Sprite* ajsSprite, Sprite* aJsBg, bool _isFollowRole);
	Point centerPoint;//摇杆中心
	Point currentPoint;//摇杆当前位置
	bool isActive;//是否激活摇杆
	float radius;//摇杆半径
	Sprite  *jsSprite;//摇杆控制点
	bool isFollowRole;//是否跟随用户点击
	Point getDirection();
	float getVelocity();
	void updatePos(float dt);
	EventListenerTouchOneByOne *listener;

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	CREATE_FUNC(HRocker);
	
};



#endif 
