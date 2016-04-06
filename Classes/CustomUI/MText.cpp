//
//  MText.cpp
//  GameVina
//
//  Created by Black3rry on 3/23/16.
//
//

#include "MText.hpp"

MText* MText::create(std::string text, float size){
    MText* mText = MText::create();
    mText->setAnchorPoint(cocos2d::Vec2(0,0));
    mText->setFontName("fonts/gamevina.otf");
    mText->setFontSize(size);
    mText->setString(text);
    
    return mText;
}

float MText::getWidth(){
    return this->getContentSize().width;
}

float MText::getHeight(){
    return this->getContentSize().height;
}

bool MText::init()
{
    if (!Text::init()) {
        return false;
    }
    return true;
}
