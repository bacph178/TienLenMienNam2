//
//  MLabel.hpp
//  GameVina
//
//  Created by Black3rry on 3/25/16.
//
//

#ifndef MLabel_hpp
#define MLabel_hpp

#include "cocos2d.h"

class MLabel : public cocos2d::Label{
  
public:
    static MLabel* create(std::string text,float size);
    static MLabel* create(std::string text,float size,cocos2d::Color3B color);
    
    virtual bool init() override; // Initializing process
    
    CREATE_FUNC(MLabel);
    
public:
    
    float getWidth();
    float getHeight();
    
};

#endif /* MLabel_hpp */
