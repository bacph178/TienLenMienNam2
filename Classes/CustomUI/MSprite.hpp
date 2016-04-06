//
//  MSprite.hpp
//  GameVina
//
//  Created by Black3rry on 3/23/16.
//
//

#ifndef MSprite_hpp
#define MSprite_hpp

#include "cocos2d.h"

class MSprite : public cocos2d::Sprite {
    
public:
    
    static MSprite* create(std::string text,cocos2d::Size size);
    static MSprite* create(std::string text);
    
    static MSprite* createExtends(std::string fileName,std::string text,cocos2d::Size size);
    static MSprite* createExtendsUp(std::string fileName,cocos2d::Size size);
    static MSprite* createExtendsDown(std::string fileName,cocos2d::Size size);
    
    virtual bool init() override; // Initializing process
    
    CREATE_FUNC(MSprite);
    
public:
    
    float getWidth();
    float getHeight();
    
};

#endif /* MSprite_hpp */
