//
//  MSprite.cpp
//  GameVina
//
//  Created by Black3rry on 3/23/16.
//
//

#include "MSprite.hpp"

MSprite* MSprite::create(std::string textureName){
    MSprite* sprite = MSprite::create();
    sprite->setAnchorPoint(cocos2d::Vec2(0,0));
    sprite->setTexture(textureName);
    
    return sprite;
}

MSprite* MSprite::create(std::string textureName,cocos2d::Size size){
    MSprite* sprite = MSprite::create();
    sprite->setAnchorPoint(cocos2d::Vec2(0,0));
    sprite->setTexture(textureName);
    sprite->setScale(size.width/sprite->getContentSize().width,
                     size.height/sprite->getContentSize().height);
    
    return sprite;
}

MSprite* MSprite::createExtends(std::string textureName,std::string text,cocos2d::Size size){
    MSprite* sprite = MSprite::create();
    sprite->setAnchorPoint(cocos2d::Vec2(0,0));
    sprite->setTexture(textureName);
    sprite->setScale(size.width/sprite->getContentSize().width,
                     size.height/sprite->getContentSize().height);
    auto sp = Sprite::create("arrow_list_table.png");
    sp->setPosition(cocos2d::Vec2(sprite->getContentSize().width/2,
                                  sprite->getContentSize().height+sp->getContentSize().height/2));
    
    auto label = cocos2d::Label::createWithTTF(text,"fonts/gamevina.otf",30);
    label->setPosition(cocos2d::Vec2(sprite->getContentSize().width/2,sprite->getContentSize().height/2));
    
    sprite->addChild(sp);
    sprite->addChild(label);
    
    return sprite;
}

MSprite* MSprite::createExtendsUp(std::string textureName,cocos2d::Size size){
    MSprite* sprite = MSprite::create();
    sprite->setAnchorPoint(cocos2d::Vec2(0,0));
    sprite->setTexture(textureName);
    sprite->setScale(size.width/sprite->getContentSize().width,
                     size.height/sprite->getContentSize().height);
    auto sp = Sprite::create("arrow_list_table.png");
    sp->setPosition(cocos2d::Vec2(sprite->getContentSize().width/2,
                                  sprite->getContentSize().height+sp->getContentSize().height/2));
    
    sprite->addChild(sp);
    
    return sprite;
}

MSprite* MSprite::createExtendsDown(std::string textureName,cocos2d::Size size){
    MSprite* sprite = MSprite::create();
    sprite->setAnchorPoint(cocos2d::Vec2(0,0));
    sprite->setTexture(textureName);
    sprite->setScale(size.width/sprite->getContentSize().width,
                     size.height/sprite->getContentSize().height);
    auto sp = Sprite::create("arrow_list_table.png");
    sp->setFlippedY(true);
    sp->setPosition(cocos2d::Vec2(sprite->getContentSize().width/2,
                                  -sp->getContentSize().height/2));
    
    sprite->addChild(sp);
    
    return sprite;
}

float MSprite::getWidth(){
    return this->getContentSize().width;
}

float MSprite::getHeight(){
    return this->getContentSize().height;
}

bool MSprite::init()
{
    if (!Sprite::init()) {
        return false;
    }
    return true;
}