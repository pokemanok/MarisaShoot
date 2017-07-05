
#include "Player.h"

Player::Player() 
{
    
    m_iHP = 1000;
}

Player::~Player() 
{
}

bool Player::init() 
{

    return true;
}

void Player::jump() {
    if (getSprite() == NULL) {
        return;
    }
  
   
    auto jump = JumpBy::create(1.0f, Point(0, 0), 160, 1);
    auto callFunc = CallFunc::create([&](){
       
    });
    auto jumpActions = Sequence::create(jump, callFunc, NULL);
    this->runAction(jumpActions);
}

int Player::getiHP() {
    return this->m_iHP;
}

void Player::resetData() {
    
    setPosition(Point(200, 70));
    setScale(1.0f);
    setRotation(0);
}