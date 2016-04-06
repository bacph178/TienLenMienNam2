//
//  MText.hpp
//  GameVina
//
//  Created by Black3rry on 3/23/16.
//
//

#ifndef MText_hpp
#define MText_hpp

#include "ui/UIText.h"
#include "cocos2d.h"

class MText : public cocos2d::ui::Text {
    
public:

    static MText* create(std::string text,float size);
    
    virtual bool init() override; // Initializing process
    
    CREATE_FUNC(MText);
    
public:
    
    float getWidth();
    float getHeight();
    
};
#endif /* MText_hpp */
