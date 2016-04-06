//
//  MButton.cpp
//  GameVina
//
//  Created by Black3rry on 3/22/16.
//
//

#include "MButton.hpp"

USING_NS_CC;

MButton* MButton::create(std::string textureName,int tag){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureName);
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0,0));
    btn->setTag(tag);
    
    return btn;
}


MButton* MButton::create(std::string textureName,std::string text,float size,int tag){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureName);
    
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0,0));
    btn->setTitleText(text);
    btn->setTitleFontSize(size);
    btn->setTitleFontName("fonts/gamevina.otf");
    btn->setTag(tag);
    
    return btn;
    
}

MButton* MButton::create(std::string textureNormal,std::string texturePressed,std::string text,float size,int tag){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureNormal);
    btn->loadTexturePressed(texturePressed);
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0,0));
    btn->setTitleText(text);
    btn->setTitleFontSize(size);
    btn->setTitleFontName("fonts/gamevina.otf");
    btn->setTag(tag);
    
    return btn;
    
}


MButton* MButton::createExtends(std::string textureName,std::string text,float size,int tag){
    
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureName);
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0,0));
    btn->setTag(tag);
    btn->setTitleText(text);
    btn->setTitleFontSize(size);
    btn->setTitleFontName("fonts/gamevina.otf");
    btn->getTitleRenderer()->setAnchorPoint(Vec2(0,0));
    btn->getTitleRenderer()->setPosition(btn->getContentSize().width+5,0);
    
    return btn;
    
}

MButton* MButton::create(std::string textureName,std::string text,float size,cocos2d::Color3B color,int tag){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureName);
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0,0));
    btn->setTitleText(text);
    btn->setTitleFontSize(size);
    btn->setTitleColor(color);
    btn->setTitleFontName("fonts/gamevina.otf");
    btn->setTag(tag);
    
    return btn;
    
}

MButton* MButton::create(std::string text,float size,int tag) {
    MButton *btn = MButton::create();
    btn->setZoomScale(0.02f);
    btn->setAnchorPoint(cocos2d::Vec2(0,0));
    btn->setTitleText(text);
    btn->setTitleFontSize(size);
    btn->setTitleFontName("fonts/gamevina.otf");
    btn->setTag(tag);
    
    return btn;
    
}

MButton* MButton::createItem(std::string textureName,int tag){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureName);
    btn->setTag(tag);
    
    return btn;
}

MButton* MButton::createWidthSize(std::string textureNormal,cocos2d::Size size,std::string text,int tag){
    MButton *btn = MButton::create();
    btn->loadTextureNormal(textureNormal);
    btn->setScale9Enabled(true);
    btn->setContentSize(size);
    btn->setTitleText(text);
    btn->setTitleFontSize(30);
    btn->setTag(tag);
    
    return btn;
}

float MButton::getWidth(){
    return this->getContentSize().width;
}

float MButton::getHeight(){
    return this->getContentSize().height;
}


bool MButton::init()
{
    if (!Button::init()) {
        return false;
    }
    return true;
}


