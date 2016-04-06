
#ifndef __REGISTER_SCENE_H__
#define __REGISTER_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <MenuScene/LoginScene.h>

USING_NS_CC;
using namespace cocos2d::ui;

class RegisterScene : public cocos2d::Layer,public EditBoxDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    
    virtual void editBoxEditingDidBegin(EditBox* editBox) override;
    virtual void editBoxEditingDidEnd(EditBox* editBox) override;
    virtual void editBoxTextChanged(EditBox* editBox, std::string &text);
    virtual void editBoxReturn(EditBox * editBox) override;
	
	// implement the "static create()" method manually
	CREATE_FUNC(RegisterScene);
    
public:
    void initMenu(Size size,Vec2 origin);
    
public:
    
    std::string nhap_matkhau_str;
    std::string nhap_sdt_str;
    std::string nhaplai_matkhau_str;

private:
    void menuCallBack(Ref *sende,Widget::TouchEventType type);
};

#endif // __REGISTER_SCENE_H__
