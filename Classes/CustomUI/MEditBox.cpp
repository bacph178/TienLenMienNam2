//
//  MEditBox.cpp
//  GameVina
//
//  Created by Black3rry on 3/24/16.
//
//

#include "MEditBox.hpp"


MEditBox* MEditBox::create(cocos2d::Size size,std::string fileName){
    
    MEditBox* editbox = (MEditBox*)cocos2d::ui::EditBox::create(size,fileName);
    editbox->setAnchorPoint(cocos2d::Vec2(0,0));
    editbox->setFontName("fonts/gamevina.otf");
    editbox->setFontSize(30);
    editbox->setFontColor(cocos2d::Color3B::WHITE);
    editbox->setPlaceholderFont("fonts/gamevina.otf",30);
    editbox->setPlaceholderFontColor(cocos2d::Color3B(213,187,187));
    editbox->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
    editbox->setInputMode(EditBox::InputMode::SINGLE_LINE);
    
    return editbox;
}

MEditBox* MEditBox::createExtends(cocos2d::Size size,std::string fileName){
    
    MEditBox* editbox = (MEditBox*)cocos2d::ui::EditBox::create(size,fileName);
    editbox->setAnchorPoint(cocos2d::Vec2(0,0));
    editbox->setFontName("fonts/gamevina.otf");
    editbox->setFontSize(30);
    editbox->setFontColor(cocos2d::Color3B::WHITE);
    editbox->setPlaceholderFont("fonts/gamevina.otf",30);
    editbox->setPlaceholderFontColor(cocos2d::Color3B(213,187,187));
    editbox->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
    editbox->setInputMode(EditBox::InputMode::SINGLE_LINE);
    
    return editbox;
}

float MEditBox::getWidth(){
    return this->getContentSize().width;
}

float MEditBox::getHeight(){
    return this->getContentSize().height;
}

bool MEditBox::init()
{
    if (!cocos2d::ui::EditBox::init()) {
        return false;
    }
    return true;
}