#include "HRocker.h"
USING_NS_CC;

HRocker* HRocker::initWithCenter(Point aPoint, float aRadius, Sprite* ajsSprite, Sprite* aJsBg, bool _isFollowRole) {
	isFollowRole = _isFollowRole;//�Ƿ�����û����
	isActive = false;
	radius = aRadius;
	if (!_isFollowRole) {
		centerPoint = aPoint;
	}
	else {
		centerPoint = Point::ZERO;
	}

	currentPoint = centerPoint;
	jsSprite = ajsSprite;
	jsSprite->setPosition(centerPoint);
	aJsBg->setPosition(centerPoint);
	aJsBg->setTag(88);
	this->addChild(ajsSprite,1);
	this->addChild(aJsBg);
	if (isFollowRole) {
		this->setVisible(false);
	}
   listener = EventListenerTouchOneByOne::create();
   listener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
   listener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
   listener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);
   _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->Active();
	return this;
}




void HRocker::updatePos(float dt) {
	jsSprite->setPosition(jsSprite->getPosition() + ((currentPoint - jsSprite->getPosition())*0.5));
}

//����ҡ��
void HRocker::Active() {
	if (!isActive) {
		isActive = true;
		schedule(schedule_selector(HRocker::updatePos));//���ˢ�º���
	}
	else{

	}
}

//���ҡ��
void HRocker::Inactive() {
	if (isActive) {
		isActive = false;
		this->unschedule(schedule_selector(HRocker::updatePos));//ɾ��ˢ��
	}
	else{}
}

//ҡ�˷�λ
Point HRocker::getDirection() {
	return ccpNormalize(currentPoint - centerPoint);//��׼������ ��λ����
}

// ҡ������
float HRocker::getVelocity() {
	return ccpDistance(centerPoint , currentPoint); //������С
}

HRocker* HRocker::HRockerWithCenter(Point aPoint, float aRadius, Sprite* ajsSprite, Sprite* aJsBg, bool _isFollowRole) {

	HRocker *jstick = HRocker::create();
	jstick->initWithCenter(aPoint, aRadius, ajsSprite, aJsBg, _isFollowRole);
	return jstick;
}

bool HRocker::onTouchBegan(Touch *touch, Event *unused_event) {
	if (!isActive) {
		return false;		
	}
	this->setVisible(true);
	auto touchLocation = touch->getLocation();
	touchLocation = this->convertToNodeSpace(touchLocation);
	if (!isFollowRole) {
		if (ccpDistance(touchLocation, centerPoint) > radius) {
			return false;
		}
	}
	currentPoint = touchLocation;
	if (isFollowRole) {
		centerPoint = currentPoint;
		jsSprite->setPosition(currentPoint);
		this->getChildByTag(88)->setPosition(currentPoint);
	}

	return true;
}

 
void HRocker::onTouchMoved(Touch *touch, Event *unused_event) {
	auto touchLocation = touch->getLocation();
	touchLocation = this->convertToNodeSpace(touchLocation);
	if (ccpDistance(touchLocation, centerPoint) > radius) {
		currentPoint = centerPoint + ccpMult(ccpNormalize(ccpSub(touchLocation, centerPoint)), radius);
	}
	else {
		currentPoint = touchLocation;
	}
}

void HRocker::onTouchEnded(Touch *touch, Event *unused_event) {
	currentPoint = centerPoint;
	if (isFollowRole) {
		this->setVisible(false);
	}
}