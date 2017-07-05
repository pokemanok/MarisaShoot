#ifndef HRocker_H 
#define HRocker_H 
#include "cocos2d.h" 
USING_NS_CC;
class HRocker :public Layer {
public:
	//��ʼ�� aPoint��ҡ������ aRadius��ҡ�˰뾶 aJsSprite��ҡ�˿��Ƶ� aJsBg��ҡ�˱��� 
	static HRocker* HRockerWithCenter(Point aPoint, float aRadius, Sprite* ajsSprite, Sprite* aJsBg, bool isFollowRole);

	//����ҡ��
	void Active();

	//���ҡ��
	void Inactive();

	HRocker* initWithCenter(Point aPoint, float aRadius, Sprite* ajsSprite, Sprite* aJsBg, bool _isFollowRole);
	Point centerPoint;//ҡ������
	Point currentPoint;//ҡ�˵�ǰλ��
	bool isActive;//�Ƿ񼤻�ҡ��
	float radius;//ҡ�˰뾶
	Sprite  *jsSprite;//ҡ�˿��Ƶ�
	bool isFollowRole;//�Ƿ�����û����
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
