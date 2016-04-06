
#ifndef __SHOWGAME_SCENE_H__
#define __SHOWGAME_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "PopupSetting.hpp"

USING_NS_CC;

using namespace cocos2d::ui;
class ShowGame : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void gotoMenuDialog();
    
    void menuCallBack(Ref *sender,Widget::TouchEventType type);
    
    void gameItemCallBack(Ref *sender,Widget::TouchEventType type);
	
	// implement the "static create()" method manually
	CREATE_FUNC(ShowGame);
    
private:
    PopupSetting  *m_popupSetting;
    
};

#endif // __SHOWGAME_SCENE_H__
