#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "cocos2d.h"
#include "zlib.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocos2d::ui;
class LoginScene : public cocos2d::Layer,public EditBoxDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    
    void menuCallBack(Ref *pSender, Widget::TouchEventType eventType);
    
    static void readFrom(std::vector<char> read_str, int len);
    static std::vector<char> decompress_gzip2(const char* byte_arr, uLong length);
    
	
	// implement the "static create()" method manually
	CREATE_FUNC(LoginScene);
    
    
    void update(float) override;
    
public:
    
    std::string user_id_str;
    std::string password_str;

private:
    
    Sprite * sprite;
    virtual void editBoxEditingDidBegin(EditBox *editBox)  override;
    virtual void editBoxEditingDidEnd(EditBox *editBox)  override;
    virtual void editBoxTextChanged(EditBox *editBox, const std::string& text)  override;
    virtual void editBoxReturn(EditBox *editBox)  override;
};

#endif // __LOGIN_SCENE_H__
