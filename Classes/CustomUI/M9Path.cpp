//
//  M9Path.cpp
//  GameVina
//
//  Created by Black3rry on 3/24/16.
//
//

#include "M9Path.hpp"


M9Path* M9Path::create(std::string textureName,cocos2d::Size size) {
    M9Path* sprite = (M9Path*)cocos2d::ui::Scale9Sprite::create(textureName);
    sprite->setAnchorPoint(cocos2d::Vec2(0,0));
    sprite->setContentSize(size);
    
    return sprite;
}

float M9Path::getWidth(){
    return this->getContentSize().width;
}

float M9Path::getHeight(){
    return this->getContentSize().height;
}

bool M9Path::init() {
    if (!cocos2d::ui::Scale9Sprite::init()) {
        return false;
    }
    return true;
}