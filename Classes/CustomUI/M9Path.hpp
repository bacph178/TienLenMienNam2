//
//  M9Path.hpp
//  GameVina
//
//  Created by Black3rry on 3/24/16.
//
//

#ifndef M9Path_hpp
#define M9Path_hpp

#include "ui/UIScale9Sprite.h"
#include "cocos2d.h"

class M9Path : public cocos2d::ui::Scale9Sprite{
    
public:
    
    static M9Path* create(std::string textureName,cocos2d::Size size);
    //static M9Path* create(std::string textureName);
    
    virtual bool init() override; // Initializing process
    
    CREATE_FUNC(M9Path);
    
public:
    
    float getWidth();
    float getHeight();
    
};

#endif /* M9Path_hpp */
