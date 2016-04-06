//
//  MLabel.cpp
//  GameVina
//
//  Created by Black3rry on 3/25/16.
//
//

#include "MLabel.hpp"

MLabel* MLabel::create(std::string text, float size){
    
    MLabel *label = (MLabel*)Label::createWithTTF(text,"fonts/gamevina.otf", size);
    label->setString(text);
    label->setAnchorPoint(cocos2d::Vec2(0,0));
    return label;
}

MLabel* MLabel::create(std::string text,float size, cocos2d::Color3B color){
    MLabel *label = (MLabel*)Label::createWithTTF(text, "fonts/gamevina.otf", size);
    label->setAnchorPoint(cocos2d::Vec2(0,0));
    label->setString(text);
    label->setColor(color);
    
    return label;
}

float MLabel::getWidth(){
    return this->getContentSize().width;
}

float MLabel::getHeight(){
    return this->getContentSize().height;
}


bool MLabel::init()
{
    if (!MLabel::init()) {
        return false;
    }
    return true;
}