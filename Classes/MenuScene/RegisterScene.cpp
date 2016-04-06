#include "RegisterScene.h"
#include <CustomUI/MSprite.hpp>
#include <CustomUI/MLabel.hpp>
#include <CustomUI/MButton.hpp>
#include <CustomUI/MEditBox.hpp>

#include <Config/GameConfig.h>

#define TAG_BTN_REGISTER 1
#define TAG_BTN_BACK 2

#define TAG_EDITBOX_NHAP_MATKHAU 3
#define TAG_EDITBOX_NHAPLAI_MATKHAU 4
#define TAG_EDITBOX_NHAP_SDT 5

using namespace cocos2d::ui;

Scene* RegisterScene::createScene() {
    
    auto scene = Scene::create();
    
    auto layer = RegisterScene::create();

    scene->addChild(layer);

    return scene;
}

bool RegisterScene::init() {
    
    if ( !Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    auto bkg = MSprite::create("bgr_register.jpg",visibleSize);
    bkg->setPosition(Vec2(origin.x,origin.y));
    this->addChild(bkg);
    
    this->initMenu(visibleSize, origin);

    return true;
}

void RegisterScene::initMenu(Size visibleSize, Vec2 origin){
    
    auto bigken = MSprite::create("bigken_logo.png");
    bigken->setPosition(Point(origin.x+20,origin.y+visibleSize.height-bigken->getHeight()-20));
    this->addChild(bigken);
    
    auto girl = MSprite::create("girl2.png");
    girl->setPosition(Point(origin.x+visibleSize.width/6,origin.y));
    this->addChild(girl);
    
    
    //==================================== Buttons
    
    //register Button
    auto btn_register = MButton::create("ic_button_register.png",TAG_BTN_REGISTER);
    btn_register->setPosition(Point(origin.x + visibleSize.width-50-btn_register->getWidth(),
                                   origin.y + visibleSize.height / 3));
    btn_register->setZoomScale(0.01f);
    btn_register->addTouchEventListener(CC_CALLBACK_2(RegisterScene::menuCallBack, this));
    this->addChild(btn_register);
    
    // item nhap lai mat khau
    auto item_nhaplai_matkhau = MSprite::create("ic_button_password.png");
    item_nhaplai_matkhau->setPosition(Vec2(btn_register->getPosition().x,
                                        btn_register->getPosition().y+btn_register->getHeight()+20));
    this->addChild(item_nhaplai_matkhau);
    
    // item nhap mat khau
    auto item_nhap_matkhau = MSprite::create("ic_button_password.png");
    item_nhap_matkhau->setPosition(Vec2(btn_register->getPosition().x,
                                        item_nhaplai_matkhau->getPosition().y+item_nhaplai_matkhau->getHeight()+20));
    this->addChild(item_nhap_matkhau);
    
    // item nhap sdt
    auto item_nhap_sdt = MSprite::create("ic_button_isdn.png");
    item_nhap_sdt->setPosition(Vec2(btn_register->getPosition().x,
                                    item_nhap_matkhau->getPosition().y+item_nhap_matkhau->getHeight()+20));
    this->addChild(item_nhap_sdt);
    
    auto background_nhap_register = MSprite::create("ic_editbox_register.png");
    
    
    // btn back
    auto btn_back = MButton::create(BTN_BACK,TAG_BTN_BACK);
    btn_back->setPosition(Vec2(origin.x + visibleSize.width-10 - btn_back->getWidth(),
                               origin.y + 10));
    btn_back->addTouchEventListener(CC_CALLBACK_2(RegisterScene::menuCallBack, this));
    this->addChild(btn_back);
    
    
    //==================================== Text Field
    
    
    
    auto nhaplai_matkhau = MEditBox::create(background_nhap_register->getContentSize(),"ic_editbox_register.png");
    nhaplai_matkhau->setPosition(Vec2(item_nhaplai_matkhau->getPosition().x+item_nhaplai_matkhau->getWidth(),
                                      item_nhaplai_matkhau->getPosition().y));
    nhaplai_matkhau->setPlaceHolder("Nhập lại mật khẩu");
    nhaplai_matkhau->setMaxLength(12);
    nhaplai_matkhau->setTag(TAG_EDITBOX_NHAPLAI_MATKHAU);
    nhaplai_matkhau->setInputFlag(EditBox::InputFlag::PASSWORD);
    nhaplai_matkhau->setDelegate(this);
    this->addChild(nhaplai_matkhau);
    
    // editbox nhap mat khau

    auto nhap_matkhau = MEditBox::create(background_nhap_register->getContentSize(),"ic_editbox_register.png");
    nhap_matkhau->setPosition(Vec2(item_nhap_matkhau->getPosition().x + item_nhap_matkhau->getWidth(),
                                   item_nhap_matkhau->getPosition().y));
    nhap_matkhau->setPlaceHolder("Nhập mật khẩu");
    nhap_matkhau->setMaxLength(12);
    nhap_matkhau->setTag(TAG_EDITBOX_NHAP_MATKHAU);
    nhap_matkhau->setInputFlag(EditBox::InputFlag::PASSWORD);
    nhap_matkhau->setDelegate(this);
    this->addChild(nhap_matkhau);
    
    
    // editbox nhap sdt
    
    auto nhap_sdt = MEditBox::create(background_nhap_register->getContentSize(),"ic_editbox_register.png");
    nhap_sdt->setPosition(Vec2(item_nhap_sdt->getPosition().x+item_nhap_sdt->getWidth(),
                               item_nhap_sdt->getPosition().y));
    nhap_sdt->setPlaceHolder("Nhập số điện thoại");
    nhap_sdt->setMaxLength(12);
    nhap_sdt->setTag(TAG_EDITBOX_NHAP_SDT);
    nhap_sdt->setInputMode(EditBox::InputMode::NUMERIC);
    nhap_sdt->setDelegate(this);
    this->addChild(nhap_sdt);
    
}

void RegisterScene::menuCallBack(Ref *sender,Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED){
        MButton * button = (MButton*) sender;
        int tag = button->getTag();
        switch (tag) {
            case TAG_BTN_REGISTER:
                {
                    //auto registerscene = ShowGame::createScene();
                    //Director::getInstance()->replaceScene(TransitionCrossFade::create(0.25f, registerscene));
                }
                break;
            case TAG_BTN_BACK:
                {
                    auto registerscene = LoginScene::createScene();
                    Director::getInstance()->replaceScene(TransitionMoveInL::create(0.25f, registerscene));
                    //Director::getInstance()->popScene();
                }
                break;
            default:
                break;
        }
        
    }
}

void RegisterScene::editBoxEditingDidBegin(EditBox *editBox) {
    CCLOG("%s","edit begin!");
}

void RegisterScene::editBoxEditingDidEnd(EditBox *editBox) {
    CCLOG("%s","edit end!");
}

void RegisterScene::editBoxTextChanged(EditBox *editBox, std::string &text) {
    CCLOG("%s","edit changed!");
}

void RegisterScene::editBoxReturn(EditBox *editBox) {
    switch (editBox->getTag()) {
        case TAG_EDITBOX_NHAP_MATKHAU:
            this->nhap_matkhau_str = editBox->getText();
            CCLOG("%s",this->nhap_matkhau_str.c_str());
            break;
        case TAG_EDITBOX_NHAPLAI_MATKHAU:
            this->nhaplai_matkhau_str = editBox->getText();
            CCLOG("%s",this->nhaplai_matkhau_str.c_str());
            break;
        case TAG_EDITBOX_NHAP_SDT:
            this->nhap_sdt_str = editBox->getText();
            CCLOG("%s",this->nhap_sdt_str.c_str());
            break;
        default:
            break;
    }
}
