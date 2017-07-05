#ifndef example15_1_GameMark_h
#define example15_1_GameMark_h

#include "cocos2d.h"
using namespace cocos2d;

USING_NS_CC;

// 游戏计分类，主要用于使用自定义数字图片来显示游戏成绩
class GameMark : public Node
{
public:
    GameMark(void);
    virtual ~GameMark(void);
    
    virtual void onEnter();
    virtual void onExit();
    
    cocos2d::Vector<Sprite*> bits;
    int mark;
    void addnumber(int var);
    Texture2D* ui;
};

#endif
